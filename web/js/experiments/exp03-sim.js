/* js/experiments/exp03-sim.js — LED Blink simulator */
let mode = 'blink';
let ledOn = false;
let blinkCount = 0;
let lastToggle = Date.now();
let onTime = 700, offTime = 300;
let fadeDir = 1, fadeBr = 0;

function setMode(m) {
  mode = m;
  document.querySelectorAll('.sim-btn').forEach(b => b.classList.remove('active'));
  document.getElementById('btnMode1').classList.toggle('active', m==='blink');
  document.getElementById('btnMode2').classList.toggle('active', m==='fade');
  document.getElementById('btnMode3').classList.toggle('active', m==='off');
}

document.getElementById('onTime').addEventListener('input', function(){
  onTime = +this.value;
  document.getElementById('onTimeVal').textContent = onTime + ' ms';
});
document.getElementById('offTime').addEventListener('input', function(){
  offTime = +this.value;
  document.getElementById('offTimeVal').textContent = offTime + ' ms';
});

function setLed(brightness) {
  const bulb = document.getElementById('ledBulb');
  const alpha = brightness / 255;
  const glow = Math.round(alpha * 32);
  bulb.style.background = `rgba(34,197,94,${0.2 + alpha * 0.8})`;
  bulb.style.boxShadow = `0 0 ${glow}px ${Math.round(glow/2)}px rgba(34,197,94,${alpha * 0.8})`;
  document.getElementById('brightness').textContent = Math.round(brightness);
  document.getElementById('ledStateLabel').textContent = brightness > 0 ? 'ON' : 'OFF';
  document.getElementById('ledStateLabel').style.color = brightness > 0 ? 'var(--green)' : 'var(--text2)';
}

function tick() {
  const now = Date.now();
  if (mode === 'blink') {
    const interval = ledOn ? onTime : offTime;
    if (now - lastToggle >= interval) {
      lastToggle = now;
      ledOn = !ledOn;
      if (ledOn) {
        blinkCount++;
        document.getElementById('blinkCount').textContent = blinkCount;
      }
    }
    setLed(ledOn ? 255 : 0);
  } else if (mode === 'fade') {
    fadeBr += fadeDir * 4;
    if (fadeBr >= 255) { fadeBr = 255; fadeDir = -1; }
    if (fadeBr <= 0)   { fadeBr = 0;   fadeDir = 1; }
    setLed(fadeBr);
  } else {
    setLed(0);
  }
  requestAnimationFrame(tick);
}
tick();

// Simple LED blink sim (1s on/1s off)
;(function(){
  let on=false;
  setInterval(()=>{
    on=!on;
    const b=document.getElementById('simpleLed');
    const s=document.getElementById('simpleLedState');
    if(!b)return;
    b.style.background=on?'#22c55e':'rgba(34,197,94,0.1)';
    b.style.boxShadow=on?'0 0 22px 8px rgba(34,197,94,0.6)':'none';
    s.textContent=on?'ON':'OFF';
    s.style.color=on?'var(--green)':'var(--text2)';
  },1000);
})();
