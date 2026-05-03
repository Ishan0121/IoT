/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        bg: {
          primary: '#0a0d14',
          secondary: '#0f1420',
          card: '#141928',
          border: '#1e2640',
        },
        neon: {
          power: '#ff6b35',
          analog: '#a855f7',
          digital: '#22d3ee',
          comm: '#4ade80',
          component: '#facc15',
          white: '#e2e8f0',
        }
      },
      fontFamily: {
        sans: ['Inter', 'system-ui', 'sans-serif'],
        mono: ['JetBrains Mono', 'Fira Code', 'monospace'],
      },
      animation: {
        'pulse-glow': 'pulseGlow 1.5s ease-in-out infinite',
        'flow': 'flow 1.5s linear infinite',
        'slide-up': 'slideUp 0.3s ease-out',
        'fade-in': 'fadeIn 0.3s ease-out',
        'ping-slow': 'ping 2s cubic-bezier(0, 0, 0.2, 1) infinite',
      },
      keyframes: {
        pulseGlow: {
          '0%, 100%': { opacity: '0.7', transform: 'scale(1)' },
          '50%': { opacity: '1', transform: 'scale(1.05)' },
        },
        flow: {
          '0%': { strokeDashoffset: '100' },
          '100%': { strokeDashoffset: '0' },
        },
        slideUp: {
          '0%': { transform: 'translateY(20px)', opacity: '0' },
          '100%': { transform: 'translateY(0)', opacity: '1' },
        },
        fadeIn: {
          '0%': { opacity: '0' },
          '100%': { opacity: '1' },
        },
      },
      boxShadow: {
        'neon-power': '0 0 10px #ff6b35, 0 0 20px #ff6b3580',
        'neon-analog': '0 0 10px #a855f7, 0 0 20px #a855f780',
        'neon-digital': '0 0 10px #22d3ee, 0 0 20px #22d3ee80',
        'neon-comm': '0 0 10px #4ade80, 0 0 20px #4ade8080',
        'neon-component': '0 0 10px #facc15, 0 0 20px #facc1580',
      }
    },
  },
  plugins: [],
}
