import React from 'react';
import { CATEGORIES } from '../data/hotspots';

const filters = [
  { id: 'all',       label: 'All',           color: '#e2e8f0' },
  { id: 'power',     label: 'Power',         color: CATEGORIES.power.color },
  { id: 'analog',    label: 'Analog',        color: CATEGORIES.analog.color },
  { id: 'digital',   label: 'Digital',       color: CATEGORIES.digital.color },
  { id: 'comm',      label: 'Comm',          color: CATEGORIES.comm.color },
  { id: 'component', label: 'Components',    color: CATEGORIES.component.color },
];

export default function FilterPanel({ active, onChange }) {
  return (
    <div className="flex flex-wrap gap-1.5">
      {filters.map(f => {
        const isActive = active === f.id;
        return (
          <button
            key={f.id}
            id={`filter-${f.id}`}
            onClick={() => onChange(f.id)}
            className="px-2.5 py-1 rounded-full text-xs font-medium border transition-all duration-150"
            style={{
              borderColor: isActive ? f.color : '#1e2640',
              color: isActive ? f.color : '#64748b',
              background: isActive ? `${f.color}18` : 'transparent',
              boxShadow: isActive ? `0 0 8px ${f.color}30` : 'none',
            }}
          >
            {f.label}
          </button>
        );
      })}
    </div>
  );
}
