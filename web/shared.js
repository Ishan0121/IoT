/* shared.js — Arduino IoT Lab Shared Utilities */

// ─── Copy code block to clipboard ────────────────────────────────────────────
function copyCode(id) {
  const el = document.getElementById(id);
  if (!el) return;
  const text = el.innerText || el.textContent;
  navigator.clipboard.writeText(text).then(() => {
    const btn = el.closest('.code-container')?.querySelector('.copy-btn');
    if (btn) {
      const orig = btn.textContent;
      btn.textContent = 'Copied!';
      btn.classList.add('copied');
      setTimeout(() => { btn.textContent = orig; btn.classList.remove('copied'); }, 2000);
    }
  });
}

// ─── roundRect helper for canvas ─────────────────────────────────────────────
function roundRect(ctx, x, y, w, h, r) {
  ctx.beginPath();
  ctx.moveTo(x + r, y);
  ctx.lineTo(x + w - r, y);
  ctx.quadraticCurveTo(x + w, y, x + w, y + r);
  ctx.lineTo(x + w, y + h - r);
  ctx.quadraticCurveTo(x + w, y + h, x + w - r, y + h);
  ctx.lineTo(x + r, y + h);
  ctx.quadraticCurveTo(x, y + h, x, y + h - r);
  ctx.lineTo(x, y + r);
  ctx.quadraticCurveTo(x, y, x + r, y);
  ctx.closePath();
}

/**
 * hiDPI — make a canvas sharp on Retina / high-DPI screens.
 *
 * Strategy:
 *   • Uses the canvas HTML attribute dimensions (width="…" height="…") as
 *     the logical drawing coordinate space — these NEVER change.
 *   • Multiplies the internal pixel buffer by devicePixelRatio for sharpness.
 *   • Does NOT override CSS style.width / style.height so the element keeps
 *     whatever responsive layout the CSS provides (width:100%, max-width, etc.)
 *
 * Usage:
 *   const { ctx, W, H } = hiDPI(myCanvas);
 *   // draw using W and H as the coordinate space (the canvas attribute values)
 *
 * @param {HTMLCanvasElement} canvas
 * @returns {{ ctx: CanvasRenderingContext2D, W: number, H: number, dpr: number }}
 */
function hiDPI(canvas) {
  const dpr = window.devicePixelRatio || 1;

  // Logical (CSS-pixel) drawing dimensions come from the HTML attributes.
  // This keeps coordinates stable regardless of how CSS sizes the element.
  const logW = parseInt(canvas.getAttribute('width'),  10) || canvas.offsetWidth  || 300;
  const logH = parseInt(canvas.getAttribute('height'), 10) || canvas.offsetHeight || 150;

  // Scale the backing store up by dpr so every logical pixel maps to a
  // physical pixel — text and lines are crisp on every screen.
  canvas.width  = Math.round(logW * dpr);
  canvas.height = Math.round(logH * dpr);

  // Do NOT touch style.width / style.height — let CSS handle layout.
  // (CSS width:100%, max-width, flex, etc. all keep working.)

  const ctx = canvas.getContext('2d');
  ctx.scale(dpr, dpr);             // draw in logical-pixel space from here on
  return { ctx, W: logW, H: logH, dpr };
}

// ─── Quick-Jump Experiment Flyout ─────────────────────────────────────────────
// Injects a flyout panel onto the home FAB that lets users jump directly to
// any experiment without going back to the index page first.
;(function () {

  const EXPERIMENTS = [
    { href: 'exp01.html', num: '01', name: 'UNO Board'      },
    { href: 'exp02.html', num: '02', name: 'IDE Setup'       },
    { href: 'exp03.html', num: '03', name: 'LED Blink'       },
    { href: 'exp04.html', num: '04', name: 'Traffic Light'   },
    { href: 'exp05.html', num: '05', name: 'Ultrasonic'      },
    { href: 'exp06.html', num: '06', name: 'Servo & Stepper' },
    { href: 'exp07.html', num: '07', name: 'Smart Home'      },
    { href: 'exp08.html', num: '08', name: 'DC Motor'        },
    { href: 'exp09.html', num: '09', name: 'Shields'         },
    { href: 'exp10.html', num: '10', name: 'IoT Cloud'       },
  ];

  function buildFlyout() {
    const trigger = document.querySelector('.nav-exp-id');
    if (!trigger) return;

    // ── Detect current page ──────────────────────────────────
    const current = location.pathname.split('/').pop() || 'index.html';

    // Set relative positioning on the trigger so the absolute flyout drops down from it
    trigger.style.position = 'relative';
    trigger.style.cursor = 'pointer';

    // ── Build the flyout panel ───────────────────────────────
    const panel = document.createElement('div');
    panel.className = 'exp-flyout';
    panel.setAttribute('role', 'menu');
    panel.innerHTML = `
      <div class="flyout-header">Jump to Experiment</div>
      ${EXPERIMENTS.map(e => `
        <a href="${e.href}"
           class="flyout-item${e.href === current ? ' fi-active' : ''}"
           role="menuitem">
          <span class="fi-num">${e.num}</span>
          <span class="fi-name">${e.name}</span>
          ${e.href === current ? '<span class="fi-here">●</span>' : ''}
        </a>`).join('')}
      <div class="flyout-divider"></div>
      <a href="index.html" class="flyout-item flyout-index-link" role="menuitem">
        <span class="fi-num">⌂</span>
        <span class="fi-name">Index</span>
      </a>`;

    trigger.appendChild(panel);

    // Mobile: tap trigger → toggle flyout
    trigger.addEventListener('click', function (e) {
      if (e.target.closest('.exp-flyout')) return; // Let clicks inside panel work naturally
      const isOpen = panel.classList.contains('open');
      panel.classList.toggle('open', !isOpen);
      trigger.setAttribute('aria-expanded', String(!isOpen));
    });

    // Click outside → close
    document.addEventListener('click', function (e) {
      if (!trigger.contains(e.target)) {
        panel.classList.remove('open');
        trigger.setAttribute('aria-expanded', 'false');
      }
    });

    // Keyboard: Escape → close
    document.addEventListener('keydown', function (e) {
      if (e.key === 'Escape') {
        panel.classList.remove('open');
        trigger.setAttribute('aria-expanded', 'false');
      }
    });

    trigger.setAttribute('aria-haspopup', 'true');
    trigger.setAttribute('aria-expanded', 'false');
    trigger.setAttribute('aria-label', 'Navigation — Jump to an experiment');
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', buildFlyout);
  } else {
    buildFlyout();   // already loaded (e.g. script at end of body)
  }
})();
