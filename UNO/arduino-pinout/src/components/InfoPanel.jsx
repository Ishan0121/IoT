import React, { useState } from 'react';
import { CATEGORIES } from '../data/hotspots';
import { ChevronDown, ChevronUp, Zap, AlertTriangle, Code2, Cpu } from 'lucide-react';

const categoryColor = (cat) => CATEGORIES[cat]?.color || '#e2e8f0';
const categoryLabel = (cat) => CATEGORIES[cat]?.label || cat;

export default function InfoPanel({ hotspot, panelRef }) {
  const [codeOpen, setCodeOpen] = useState(false);

  if (!hotspot) {
    return (
      <div
        ref={panelRef}
        className="h-full flex flex-col items-center justify-center gap-3 text-center px-6"
        style={{ borderTop: '1px solid #1e2640' }}
      >
        <Cpu size={36} className="opacity-20" />
        <p className="text-slate-500 text-sm">Hover or click a component on the board to explore its details</p>
        <p className="text-slate-600 text-xs">40+ interactive hotspots available</p>
      </div>
    );
  }

  const color = categoryColor(hotspot.category);

  return (
    <div
      ref={panelRef}
      className="h-full overflow-y-auto info-panel-enter"
      style={{ borderTop: `1px solid ${color}40` }}
    >
      <div className="flex flex-col md:flex-row h-full">

        {/* Left: Header */}
        <div className="flex-shrink-0 md:w-56 p-4 flex flex-col gap-2 border-b md:border-b-0 md:border-r" style={{ borderColor: `${color}25`, background: `${color}08` }}>
          <div className="flex items-center gap-2">
            <span className="w-2 h-2 rounded-full flex-shrink-0" style={{ backgroundColor: color, boxShadow: `0 0 6px ${color}` }} />
            <span className="text-xs font-medium uppercase tracking-widest" style={{ color }}>
              {categoryLabel(hotspot.category)}
            </span>
          </div>
          <h2 className="text-xl font-bold text-white font-mono leading-tight">{hotspot.name}</h2>
          <span className="text-xs text-slate-400 font-medium">{hotspot.type}</span>
          {hotspot.voltage && (
            <div className="mt-1 flex items-center gap-1.5">
              <Zap size={11} style={{ color }} />
              <span className="text-xs font-mono" style={{ color }}>{hotspot.voltage}</span>
            </div>
          )}
          {hotspot.pwm && (
            <span className="self-start text-xs px-2 py-0.5 rounded-full font-mono" style={{ background: `${color}20`, color, border: `1px solid ${color}50` }}>
              PWM ~
            </span>
          )}
        </div>

        {/* Middle: Description + Use Cases + Warnings */}
        <div className="flex-1 p-4 flex flex-col gap-3 overflow-y-auto min-w-0">
          <p className="text-sm text-slate-300 leading-relaxed">{hotspot.description}</p>

          {hotspot.useCases?.length > 0 && (
            <div>
              <p className="text-xs font-semibold uppercase tracking-wider text-slate-500 mb-1.5">Use Cases</p>
              <div className="flex flex-wrap gap-1.5">
                {hotspot.useCases.map((uc, i) => (
                  <span key={i} className="text-xs px-2 py-0.5 rounded-full bg-slate-800 text-slate-300 border border-slate-700">{uc}</span>
                ))}
              </div>
            </div>
          )}

          {hotspot.warnings?.length > 0 && (
            <div className="rounded-lg p-2.5" style={{ background: '#ff6b3510', border: '1px solid #ff6b3530' }}>
              <div className="flex items-center gap-1.5 mb-1">
                <AlertTriangle size={12} className="text-orange-400" />
                <span className="text-xs font-semibold text-orange-400">Warnings</span>
              </div>
              {hotspot.warnings.map((w, i) => (
                <p key={i} className="text-xs text-orange-200/70 leading-relaxed">• {w}</p>
              ))}
            </div>
          )}
        </div>

        {/* Right: Code snippet */}
        {hotspot.code && (
          <div className="flex-shrink-0 md:w-64 p-4 border-t md:border-t-0 md:border-l" style={{ borderColor: '#1e2640' }}>
            <button
              onClick={() => setCodeOpen(p => !p)}
              className="flex items-center justify-between w-full text-xs font-semibold uppercase tracking-wider text-slate-400 hover:text-white mb-2 transition-colors"
            >
              <span className="flex items-center gap-1.5"><Code2 size={12} /> Code Example</span>
              {codeOpen ? <ChevronUp size={12} /> : <ChevronDown size={12} />}
            </button>
            {codeOpen && (
              <pre className="code-block p-3 rounded-lg overflow-x-auto text-xs whitespace-pre leading-relaxed">
                {hotspot.code}
              </pre>
            )}
            {!codeOpen && (
              <div className="code-block p-3 rounded-lg cursor-pointer opacity-60 hover:opacity-100 transition-opacity" onClick={() => setCodeOpen(true)}>
                <span className="text-xs text-slate-500 font-mono">// click to expand...</span>
              </div>
            )}
          </div>
        )}

      </div>
    </div>
  );
}
