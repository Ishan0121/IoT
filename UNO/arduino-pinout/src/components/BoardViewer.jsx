import React, { useRef, useState, useCallback, useEffect } from 'react';
import HotspotOverlay from './HotspotOverlay';

const MIN_SCALE = 0.7;
const MAX_SCALE = 4;

export default function BoardViewer({ hotspots, activeId, hoveredId, searchMatches, activeFilter, onHover, onLeave, onClick }) {
  const containerRef = useRef(null);
  const imgRef = useRef(null);
  const [scale, setScale] = useState(1);
  const [offset, setOffset] = useState({ x: 0, y: 0 });
  const dragging = useRef(false);
  const lastPos = useRef({ x: 0, y: 0 });
  const [debugMode, setDebugMode] = useState(false);
  const [mouseCoords, setMouseCoords] = useState({ x: 0, y: 0 });

  useEffect(() => {
    const handler = (e) => { if (e.key === 'd' || e.key === 'D') setDebugMode(p => !p); };
    window.addEventListener('keydown', handler);
    return () => window.removeEventListener('keydown', handler);
  }, []);

  const onWheel = useCallback((e) => {
    e.preventDefault();
    setScale(s => Math.min(MAX_SCALE, Math.max(MIN_SCALE, s + (e.deltaY > 0 ? -0.12 : 0.12))));
  }, []);

  useEffect(() => {
    const el = containerRef.current;
    if (!el) return;
    el.addEventListener('wheel', onWheel, { passive: false });
    return () => el.removeEventListener('wheel', onWheel);
  }, [onWheel]);

  const onMouseDown = (e) => { if (e.button !== 0) return; dragging.current = true; lastPos.current = { x: e.clientX, y: e.clientY }; };
  const onMouseMove = (e) => {
    if (!dragging.current) return;
    const dx = e.clientX - lastPos.current.x; const dy = e.clientY - lastPos.current.y;
    lastPos.current = { x: e.clientX, y: e.clientY };
    setOffset(o => ({ x: o.x + dx, y: o.y + dy }));
  };
  const onMouseUp = () => { dragging.current = false; };
  const onDoubleClick = () => { setScale(1); setOffset({ x: 0, y: 0 }); };

  const onOverlayMouseMove = (e) => {
    if (!imgRef.current) return;
    const rect = imgRef.current.getBoundingClientRect();
    setMouseCoords({
      x: ((e.clientX - rect.left) / rect.width * 100).toFixed(1),
      y: ((e.clientY - rect.top)  / rect.height * 100).toFixed(1),
    });
  };

  const touches = useRef([]); const lastDist = useRef(null);
  const onTouchStart = (e) => { touches.current = Array.from(e.touches); lastDist.current = null; };
  const onTouchMove = (e) => {
    if (e.touches.length === 2) {
      const dx = e.touches[0].clientX - e.touches[1].clientX;
      const dy = e.touches[0].clientY - e.touches[1].clientY;
      const dist = Math.sqrt(dx*dx + dy*dy);
      if (lastDist.current) setScale(s => Math.min(MAX_SCALE, Math.max(MIN_SCALE, s + (dist - lastDist.current) * 0.01)));
      lastDist.current = dist;
    } else if (e.touches.length === 1 && touches.current.length === 1) {
      const dx = e.touches[0].clientX - touches.current[0].clientX;
      const dy = e.touches[0].clientY - touches.current[0].clientY;
      touches.current = Array.from(e.touches);
      setOffset(o => ({ x: o.x + dx, y: o.y + dy }));
    }
  };

  return (
    <div
      ref={containerRef}
      className="relative w-full h-full overflow-hidden cursor-grab active:cursor-grabbing select-none"
      onMouseDown={onMouseDown} onMouseMove={onMouseMove}
      onMouseUp={onMouseUp} onMouseLeave={onMouseUp}
      onDoubleClick={onDoubleClick}
      onTouchStart={onTouchStart} onTouchMove={onTouchMove}
    >
      <div
        className="absolute inset-0 flex items-center justify-center"
        style={{ transform: `translate(${offset.x}px,${offset.y}px) scale(${scale})`, transformOrigin: 'center center' }}
      >
        {/* Wrapper must be inline-block so 100% = image size */}
        <div style={{ position: 'relative', display: 'inline-block', lineHeight: 0 }}>
          <img
            ref={imgRef}
            src="/arduino-r3.png"
            alt="Arduino UNO R3 board"
            draggable={false}
            style={{
              display: 'block',
              borderRadius: '12px',
              maxHeight: 'calc(100vh - 240px)',
              maxWidth: '88vw',
              width: 'auto', height: 'auto',
              filter: 'drop-shadow(0 0 24px rgba(34,211,238,0.1)) drop-shadow(0 16px 32px rgba(0,0,0,0.7))',
              userSelect: 'none', pointerEvents: 'none',
            }}
          />

          {/* Hotspot + debug overlay — covers 100% of image exactly */}
          <div
            style={{ position: 'absolute', inset: 0, pointerEvents: 'all' }}
            onMouseMove={debugMode ? onOverlayMouseMove : undefined}
          >
            <HotspotOverlay
              hotspots={hotspots} activeId={activeId} hoveredId={hoveredId}
              searchMatches={searchMatches} activeFilter={activeFilter}
              onHover={onHover} onLeave={onLeave} onClick={onClick}
            />

            {/* Debug 10% grid */}
            {debugMode && (
              <div style={{
                position:'absolute', inset:0, pointerEvents:'none',
                backgroundImage: 'linear-gradient(rgba(34,211,238,0.2) 1px,transparent 1px),linear-gradient(90deg,rgba(34,211,238,0.2) 1px,transparent 1px)',
                backgroundSize: '10% 10%',
              }}>
                {[0,10,20,30,40,50,60,70,80,90].map(n => (
                  <React.Fragment key={n}>
                    <span style={{position:'absolute',left:`${n}%`,top:1,fontSize:8,color:'#22d3ee',fontFamily:'monospace',opacity:0.8}}>{n}</span>
                    <span style={{position:'absolute',top:`${n}%`,left:1,fontSize:8,color:'#22d3ee',fontFamily:'monospace',opacity:0.8}}>{n}</span>
                  </React.Fragment>
                ))}
              </div>
            )}
          </div>
        </div>
      </div>

      {debugMode && (
        <div style={{
          position:'absolute', top:8, left:'50%', transform:'translateX(-50%)',
          background:'rgba(0,0,0,0.9)', border:'1px solid #22d3ee60',
          borderRadius:8, padding:'6px 14px', pointerEvents:'none', zIndex:99,
          fontFamily:'monospace', fontSize:13, color:'#67e8f9',
        }}>
          x: <b style={{color:'#fff'}}>{mouseCoords.x}</b>% &nbsp;
          y: <b style={{color:'#fff'}}>{mouseCoords.y}</b>%
          &nbsp;·&nbsp;<span style={{color:'#fbbf24',fontSize:11}}>DEBUG — press D to hide</span>
        </div>
      )}

      <div style={{position:'absolute',bottom:10,right:12,fontSize:11,color:'#475569',pointerEvents:'none'}}>
        Scroll zoom · Drag pan · Dbl-click reset · <b>D</b> debug coords
      </div>
      {scale !== 1 && (
        <div style={{position:'absolute',bottom:10,left:12,fontSize:11,color:'#64748b',fontFamily:'monospace',background:'rgba(15,20,32,0.8)',padding:'2px 8px',borderRadius:4,border:'1px solid #1e2640'}}>
          {Math.round(scale * 100)}%
        </div>
      )}
    </div>
  );
}
