import React, { useEffect, useRef, useState } from 'react';

export default function ConnectionLine({ hotspotEl, panelEl, color, active }) {
  const [path, setPath] = useState('');
  const rafRef = useRef(null);

  useEffect(() => {
    if (!active || !hotspotEl || !panelEl) { setPath(''); return; }

    const update = () => {
      const hRect = hotspotEl.getBoundingClientRect();
      const pRect = panelEl.getBoundingClientRect();
      const x1 = hRect.left + hRect.width / 2;
      const y1 = hRect.bottom;
      const x2 = pRect.left + pRect.width / 2;
      const y2 = pRect.top;
      const cy = (y1 + y2) / 2;
      setPath(`M ${x1} ${y1} C ${x1} ${cy}, ${x2} ${cy}, ${x2} ${y2}`);
    };

    update();
    rafRef.current = requestAnimationFrame(update);
    window.addEventListener('resize', update);
    return () => {
      cancelAnimationFrame(rafRef.current);
      window.removeEventListener('resize', update);
    };
  }, [hotspotEl, panelEl, active]);

  if (!path) return null;

  return (
    <svg
      className="fixed inset-0 pointer-events-none"
      style={{ zIndex: 30, width: '100vw', height: '100vh' }}
    >
      <defs>
        <filter id="glow">
          <feGaussianBlur stdDeviation="2" result="blur" />
          <feMerge><feMergeNode in="blur" /><feMergeNode in="SourceGraphic" /></feMerge>
        </filter>
        <linearGradient id="flowGrad" x1="0%" y1="0%" x2="0%" y2="100%">
          <stop offset="0%" stopColor={color} stopOpacity="0.9" />
          <stop offset="100%" stopColor={color} stopOpacity="0.2" />
        </linearGradient>
      </defs>

      {/* Base line */}
      <path d={path} fill="none" stroke={color} strokeWidth="1" strokeOpacity="0.25" />

      {/* Animated glow line */}
      <path
        d={path}
        fill="none"
        stroke={`url(#flowGrad)`}
        strokeWidth="2"
        strokeDasharray="12 8"
        strokeLinecap="round"
        filter="url(#glow)"
        style={{ animation: 'electricFlow 1.2s ease-in-out infinite' }}
      />

      {/* Particle dots */}
      <path
        d={path}
        fill="none"
        stroke={color}
        strokeWidth="3"
        strokeDasharray="3 30"
        strokeLinecap="round"
        style={{ animation: 'particleFlow 0.9s linear infinite' }}
      />
    </svg>
  );
}
