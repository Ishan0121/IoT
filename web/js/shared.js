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
 */
function hiDPI(canvas) {
  const dpr = window.devicePixelRatio || 1;
  const logW = parseInt(canvas.getAttribute('width'),  10) || canvas.offsetWidth  || 300;
  const logH = parseInt(canvas.getAttribute('height'), 10) || canvas.offsetHeight || 150;
  canvas.width  = Math.round(logW * dpr);
  canvas.height = Math.round(logH * dpr);
  const ctx = canvas.getContext('2d');
  ctx.scale(dpr, dpr);
  return { ctx, W: logW, H: logH, dpr };
}

// ─── Track experiment visit via localStorage ──────────────────────────────────
function trackVisit() {
  const page = location.pathname.split('/').pop();
  const m = page.match(/^exp(\d+)\.html$/);
  if (m) {
    try { localStorage.setItem('iot_visited_' + m[1], '1'); } catch(e) {}
  }
}

// ─── Reading progress bar (injected on experiment pages) ─────────────────────
function setupReadingProgress() {
  if (!document.querySelector('.exp-main')) return;
  const bar = document.createElement('div');
  bar.id = 'reading-progress';
  document.body.prepend(bar);
  function update() {
    const scrollY = window.scrollY;
    const docH    = document.documentElement.scrollHeight - window.innerHeight;
    bar.style.transform = `scaleX(${docH > 0 ? scrollY / docH : 0})`;
  }
  window.addEventListener('scroll', update, { passive: true });
}

// ─── Reveal sections on scroll (experiment pages) ────────────────────────────
function setupReveal() {
  const sections = document.querySelectorAll('.section.reveal');
  if (!sections.length) return;
  const io = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        entry.target.classList.add('revealed');
        io.unobserve(entry.target);
      }
    });
  }, { threshold: 0.08, rootMargin: '0px 0px -40px 0px' });
  sections.forEach((s, i) => {
    s.style.transitionDelay = (i * 0.05) + 's';
    io.observe(s);
  });
}

// ─── Back-to-top button (injected on experiment pages) ───────────────────────
function setupBackToTop() {
  if (!document.querySelector('.exp-main')) return;
  const btn = document.createElement('button');
  btn.id = 'back-to-top';
  btn.innerHTML = '↑';
  btn.title = 'Back to top';
  btn.setAttribute('aria-label', 'Back to top');
  document.body.appendChild(btn);
  window.addEventListener('scroll', () => {
    btn.classList.toggle('btt-visible', window.scrollY > 420);
  }, { passive: true });
  btn.addEventListener('click', () => window.scrollTo({ top: 0, behavior: 'smooth' }));
}

// ─── Index page: particle hero canvas ────────────────────────────────────────
function setupParticles(canvas) {
  if (!canvas) return;
  const W = canvas.offsetWidth  || 1200;
  const H = canvas.offsetHeight || 480;
  canvas.width  = W;
  canvas.height = H;
  const ctx = canvas.getContext('2d');
  const N = 55;
  const pts = Array.from({ length: N }, () => ({
    x: Math.random() * W,
    y: Math.random() * H,
    vx: (Math.random() - 0.5) * 0.35,
    vy: (Math.random() - 0.5) * 0.35,
    r: Math.random() * 1.5 + 0.6
  }));
  function draw() {
    ctx.clearRect(0, 0, W, H);
    // Draw connections
    for (let i = 0; i < N; i++) {
      for (let j = i + 1; j < N; j++) {
        const dx = pts[i].x - pts[j].x;
        const dy = pts[i].y - pts[j].y;
        const d  = Math.sqrt(dx * dx + dy * dy);
        if (d < 140) {
          ctx.beginPath();
          ctx.moveTo(pts[i].x, pts[i].y);
          ctx.lineTo(pts[j].x, pts[j].y);
          ctx.strokeStyle = `rgba(79,142,247,${0.22 * (1 - d / 140)})`;
          ctx.lineWidth = 0.8;
          ctx.stroke();
        }
      }
    }
    // Draw dots
    pts.forEach(p => {
      ctx.beginPath();
      ctx.arc(p.x, p.y, p.r, 0, Math.PI * 2);
      ctx.fillStyle = 'rgba(124,158,247,0.7)';
      ctx.fill();
    });
    // Move
    pts.forEach(p => {
      p.x += p.vx; p.y += p.vy;
      if (p.x < 0 || p.x > W) p.vx *= -1;
      if (p.y < 0 || p.y > H) p.vy *= -1;
    });
    requestAnimationFrame(draw);
  }
  draw();
}

// ─── Index page: search bar ───────────────────────────────────────────────────
function setupSearch() {
  const input = document.getElementById('idx-search');
  const noMsg = document.querySelector('.no-results-msg');
  if (!input) return;
  input.addEventListener('input', applyFilters);
}

// ─── Index page: difficulty filter pills ─────────────────────────────────────
function setupFilterPills() {
  const pills = document.querySelectorAll('.filter-pill');
  if (!pills.length) return;
  pills.forEach(pill => pill.addEventListener('click', () => {
    pills.forEach(p => p.classList.remove('active'));
    pill.classList.add('active');
    applyFilters();
  }));
}

// ─── Apply search + filter together ──────────────────────────────────────────
function applyFilters() {
  const query = (document.getElementById('idx-search')?.value || '').toLowerCase().trim();
  const activePill = document.querySelector('.filter-pill.active');
  const diff  = activePill?.dataset.diff || 'all';
  const cards = document.querySelectorAll('.exp-card');
  const noMsg = document.querySelector('.no-results-msg');
  let visible = 0;
  cards.forEach(card => {
    const text   = card.textContent.toLowerCase();
    const cardDiff = card.dataset.diff || '';
    const matchQ = !query || text.includes(query);
    const matchD = diff === 'all' || cardDiff === diff;
    if (matchQ && matchD) {
      card.classList.remove('card-hidden');
      visible++;
    } else {
      card.classList.add('card-hidden');
    }
  });
  if (noMsg) noMsg.classList.toggle('show', visible === 0);
}

// ─── Index page: stagger cards in on load ────────────────────────────────────
function animateCards() {
  const cards = document.querySelectorAll('.exp-card');
  cards.forEach((c, i) => {
    setTimeout(() => c.classList.add('card-in'), 60 + i * 60);
  });
}

// ─── Index page: visited badges ──────────────────────────────────────────────
function applyVisitedBadges() {
  const cards = document.querySelectorAll('.exp-card[data-exp]');
  let count = 0;
  cards.forEach(card => {
    const num = card.dataset.exp;
    try {
      if (localStorage.getItem('iot_visited_' + num)) {
        const badge = card.querySelector('.exp-card-visited');
        if (badge) { badge.classList.add('show'); count++; }
      }
    } catch(e) {}
  });
  const el = document.getElementById('visited-count');
  if (el) el.textContent = count;
}

// ─── Quick-Jump Experiment Flyout ─────────────────────────────────────────────
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
    const current = location.pathname.split('/').pop() || 'index.html';
    trigger.style.position = 'relative';
    trigger.style.cursor = 'pointer';
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
    trigger.addEventListener('click', function (e) {
      if (e.target.closest('.exp-flyout')) return;
      const isOpen = panel.classList.contains('open');
      panel.classList.toggle('open', !isOpen);
      trigger.setAttribute('aria-expanded', String(!isOpen));
    });
    document.addEventListener('click', function (e) {
      if (!trigger.contains(e.target)) {
        panel.classList.remove('open');
        trigger.setAttribute('aria-expanded', 'false');
      }
    });
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
    buildFlyout();
  }
})();

// ─── Auto-init on DOMContentLoaded ───────────────────────────────────────────
document.addEventListener('DOMContentLoaded', () => {
  trackVisit();          // Auto-track experiment visits (no-op on non-exp pages)
  setupReadingProgress();
  setupReveal();
  setupBackToTop();
  // Index-page specific
  if (document.getElementById('idx-search')) {
    setupSearch();
    setupFilterPills();
    animateCards();
    applyVisitedBadges();
    setupParticles(document.getElementById('hero-canvas'));
  }
});
