import React from 'react';
import { Search, X } from 'lucide-react';

export default function SearchBar({ value, onChange }) {
  return (
    <div className="relative flex items-center">
      <Search size={14} className="absolute left-3 text-slate-500 pointer-events-none" />
      <input
        id="search-input"
        type="text"
        placeholder="Search pins, components…"
        value={value}
        onChange={e => onChange(e.target.value)}
        className="w-full pl-8 pr-8 py-1.5 rounded-lg text-sm bg-slate-900 border border-slate-700 text-slate-200 placeholder-slate-500 focus:outline-none focus:border-cyan-500 focus:ring-1 focus:ring-cyan-500/30 transition-all"
      />
      {value && (
        <button
          onClick={() => onChange('')}
          className="absolute right-2.5 text-slate-500 hover:text-white transition-colors"
        >
          <X size={13} />
        </button>
      )}
    </div>
  );
}
