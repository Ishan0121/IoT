import React from 'react';
import { CATEGORIES } from '../data/hotspots';

const categoryColor = (cat) => CATEGORIES[cat]?.color || '#e2e8f0';

export default function HotspotOverlay({ hotspots, activeId, hoveredId, searchMatches, activeFilter, onHover, onLeave, onClick }) {
  return (
    <>
      {hotspots.map((hs) => {
        const isActive = activeId === hs.id;
        const isHovered = hoveredId === hs.id;
        const isSearchMatch = searchMatches.has(hs.id);
        const isFiltered = activeFilter !== 'all' && hs.category !== activeFilter;
        const color = categoryColor(hs.category);

        const opacity = isFiltered && !isActive ? 0.15 : (searchMatches.size > 0 && !isSearchMatch ? 0.2 : 1);
        const highlighted = isActive || isHovered || isSearchMatch;

        return (
          <div
            key={hs.id}
            id={`hotspot-${hs.id}`}
            className="absolute cursor-pointer rounded transition-all duration-200 group"
            style={{
              left: `${hs.x}%`,
              top: `${hs.y}%`,
              width: `${hs.w}%`,
              height: `${hs.h}%`,
              opacity,
              backgroundColor: highlighted ? `${color}20` : `${color}08`,
              border: `1px solid ${highlighted ? color : `${color}40`}`,
              boxShadow: highlighted ? `0 0 8px ${color}60, inset 0 0 6px ${color}20` : 'none',
              zIndex: highlighted ? 20 : 10,
              transition: 'all 0.15s ease',
            }}
            onMouseEnter={() => onHover(hs.id)}
            onMouseLeave={onLeave}
            onClick={() => onClick(hs.id)}
          >
            {/* Pulse ring on active */}
            {isActive && (
              <span
                className="absolute inset-0 rounded animate-ping"
                style={{ backgroundColor: `${color}30`, animationDuration: '1.5s' }}
              />
            )}
            {/* Tooltip label on hover */}
            {isHovered && !isActive && (
              <div
                className="absolute z-50 px-2 py-0.5 rounded text-xs font-medium whitespace-nowrap pointer-events-none"
                style={{
                  bottom: '110%',
                  left: '50%',
                  transform: 'translateX(-50%)',
                  backgroundColor: '#0a0d14',
                  border: `1px solid ${color}`,
                  color,
                  boxShadow: `0 0 8px ${color}50`,
                }}
              >
                {hs.name}
              </div>
            )}
          </div>
        );
      })}
    </>
  );
}
