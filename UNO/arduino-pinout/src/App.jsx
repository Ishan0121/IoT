import React, { useState, useRef, useMemo, useCallback } from 'react';
import hotspots, { CATEGORIES } from './data/hotspots';
import BoardViewer from './components/BoardViewer';
import ConnectionLine from './components/ConnectionLine';
import InfoPanel from './components/InfoPanel';
import SearchBar from './components/SearchBar';
import FilterPanel from './components/FilterPanel';
import { Cpu, Github, ChevronDown } from 'lucide-react';

export default function App() {
  const [activeId, setActiveId] = useState(null);
  const [hoveredId, setHoveredId] = useState(null);
  const [search, setSearch] = useState('');
  const [activeFilter, setActiveFilter] = useState('all');

  const panelRef = useRef(null);
  const hotspotElRefs = useRef({});

  // Derive active/hovered hotspot objects
  const activeHotspot = useMemo(() => hotspots.find(h => h.id === activeId), [activeId]);

  // Search matching
  const searchMatches = useMemo(() => {
    if (!search.trim()) return new Set();
    const q = search.toLowerCase();
    return new Set(
      hotspots
        .filter(h =>
          h.name.toLowerCase().includes(q) ||
          h.id.toLowerCase().includes(q) ||
          h.type.toLowerCase().includes(q) ||
          h.category.toLowerCase().includes(q) ||
          h.description.toLowerCase().includes(q) ||
          h.tags?.some(t => t.includes(q)) ||
          h.useCases?.some(u => u.toLowerCase().includes(q))
        )
        .map(h => h.id)
    );
  }, [search]);

  const handleHover = useCallback((id) => setHoveredId(id), []);
  const handleLeave = useCallback(() => setHoveredId(null), []);
  const handleClick = useCallback((id) => {
    setActiveId(prev => prev === id ? null : id);
  }, []);

  // Get DOM element of the active hotspot for connection line
  const activeHotspotEl = activeId
    ? document.getElementById(`hotspot-${activeId}`)
    : null;

  // Category color for connection line
  const activeColor = activeHotspot ? CATEGORIES[activeHotspot.category]?.color : '#22d3ee';

  const totalPins = hotspots.filter(h => ['digital', 'analog', 'power'].includes(h.category)).length;
  const totalComponents = hotspots.filter(h => h.category === 'component').length;

  return (
    <div className="flex flex-col h-screen bg-grid text-slate-200 overflow-hidden">

      {/* ── HEADER ── */}
      <header className="flex-shrink-0 flex items-center justify-between px-4 py-2.5 border-b border-slate-800/60 glass-card z-40">
        <div className="flex items-center gap-3">
          <div className="w-7 h-7 rounded-lg flex items-center justify-center" style={{ background: 'linear-gradient(135deg,#22d3ee20,#a855f720)', border: '1px solid #22d3ee30' }}>
            <Cpu size={15} className="text-cyan-400" />
          </div>
          <div>
            <h1 className="text-sm font-bold text-white leading-none">Arduino UNO Pinout Explorer</h1>
            <p className="text-xs text-slate-500 leading-none mt-0.5">{totalPins} pins · {totalComponents} components · ATmega328P</p>
          </div>
        </div>

        <div className="hidden md:flex items-center gap-4">
          <div className="w-48">
            <SearchBar value={search} onChange={setSearch} />
          </div>
          <FilterPanel active={activeFilter} onChange={setActiveFilter} />
        </div>

        <div className="flex items-center gap-2 text-xs text-slate-500">
          <span className="hidden sm:block">R3 · 16MHz · 5V</span>
          <span className="w-1.5 h-1.5 rounded-full bg-green-500 animate-pulse" />
        </div>
      </header>

      {/* Mobile search/filter */}
      <div className="md:hidden flex-shrink-0 px-3 py-2 border-b border-slate-800/50 flex flex-col gap-2">
        <SearchBar value={search} onChange={setSearch} />
        <FilterPanel active={activeFilter} onChange={setActiveFilter} />
      </div>

      {/* ── BOARD SECTION (top, flex-1) ── */}
      <div className="flex-1 relative min-h-0">
        <BoardViewer
          hotspots={hotspots}
          activeId={activeId}
          hoveredId={hoveredId}
          searchMatches={searchMatches}
          activeFilter={activeFilter}
          onHover={handleHover}
          onLeave={handleLeave}
          onClick={handleClick}
        />

        {/* Connection line from active hotspot to info panel */}
        <ConnectionLine
          hotspotEl={activeHotspotEl}
          panelEl={panelRef.current}
          color={activeColor}
          active={!!activeId}
        />

        {/* Divider hint */}
        {!activeId && !hoveredId && (
          <div className="absolute bottom-3 left-1/2 -translate-x-1/2 flex flex-col items-center gap-1 text-slate-600 pointer-events-none animate-bounce">
            <ChevronDown size={16} />
          </div>
        )}
      </div>

      {/* ── INFO PANEL (bottom) ── */}
      <div
        className="flex-shrink-0 glass-card z-40"
        style={{
          height: activeHotspot ? '220px' : '80px',
          transition: 'height 0.35s cubic-bezier(0.16,1,0.3,1)',
          borderTop: `1px solid ${activeColor}30`,
        }}
      >
        <InfoPanel hotspot={activeHotspot} panelRef={panelRef} />
      </div>

      {/* Legend strip */}
      <div className="flex-shrink-0 flex items-center gap-4 px-4 py-1.5 border-t border-slate-800/40 bg-slate-950/60">
        {Object.entries(CATEGORIES).map(([key, val]) => (
          <button
            key={key}
            onClick={() => setActiveFilter(prev => prev === key ? 'all' : key)}
            className="flex items-center gap-1.5 text-xs text-slate-500 hover:text-slate-300 transition-colors"
          >
            <span className="w-2 h-2 rounded-full" style={{ backgroundColor: val.color, boxShadow: `0 0 4px ${val.color}` }} />
            {val.label}
          </button>
        ))}
        {activeId && (
          <button
            onClick={() => setActiveId(null)}
            className="ml-auto text-xs text-slate-500 hover:text-slate-200 transition-colors border border-slate-700 hover:border-slate-500 px-2 py-0.5 rounded"
          >
            Clear selection
          </button>
        )}
      </div>
    </div>
  );
}
