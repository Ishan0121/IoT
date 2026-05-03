/* js/experiments/exp05-sim.js — Ultrasonic distance simulator */
const sonar = document.getElementById('sonarCanvas');
const {ctx:sctx,W:sW,H:sH} = hiDPI(sonar);
let dist = 55;

function updateDist(){
  dist = +document.getElementById('distSlider').value;
  document.getElementById('distVal').textContent = dist + ' cm';
  drawSonar();
  // Zone highlight
  document.getElementById('zoneGreen').style.opacity = dist >= 40 ? 1 : 0.4;
  document.getElementById('zoneYellow').style.opacity = (dist >= 20 && dist < 40) ? 1 : 0.4;
  document.getElementById('zoneRed').style.opacity = dist < 20 ? 1 : 0.4;
}

function drawSonar(){
  const W=sW, H=sH;
  sctx.clearRect(0,0,W,H);
  sctx.fillStyle='#0c111d'; sctx.fillRect(0,0,W,H);

  // Grid lines
  sctx.strokeStyle='rgba(255,255,255,0.05)'; sctx.lineWidth=1;
  for(let x=0;x<W;x+=40){ sctx.beginPath();sctx.moveTo(x,0);sctx.lineTo(x,H);sctx.stroke(); }

  // Zone backgrounds
  const maxCm = 100, px = (cm) => (cm/maxCm)*(W-60)+30;
  sctx.fillStyle='rgba(239,68,68,0.08)'; sctx.fillRect(px(0),0,px(20)-px(0),H);
  sctx.fillStyle='rgba(245,158,11,0.06)'; sctx.fillRect(px(20),0,px(40)-px(20),H);
  sctx.fillStyle='rgba(34,197,94,0.05)'; sctx.fillRect(px(40),0,W-px(40),H);

  // Zone labels
  sctx.font='10px Inter,sans-serif'; sctx.textAlign='center';
  sctx.fillStyle='rgba(239,68,68,0.7)'; sctx.fillText('DANGER',px(10),14);
  sctx.fillStyle='rgba(245,158,11,0.7)'; sctx.fillText('CAUTION',px(30),14);
  sctx.fillStyle='rgba(34,197,94,0.7)'; sctx.fillText('SAFE',px(65),14);

  // Sensor
  const sx = 30;
  sctx.fillStyle='#4f8ef7'; sctx.fillRect(sx-12,H/2-18,24,36);
  sctx.fillStyle='rgba(79,142,247,0.2)'; sctx.fillRect(sx-12,H/2-18,24,36);
  sctx.font='9px Inter,sans-serif'; sctx.textAlign='center';
  sctx.fillStyle='#4f8ef7'; sctx.fillText('HC-SR04',sx,H/2+32);

  // Pulse wave
  const objX = px(dist);
  const color = dist<20?'#ef4444':dist<40?'#f59e0b':'#22c55e';
  sctx.strokeStyle=color; sctx.lineWidth=2;
  sctx.setLineDash([6,4]);
  sctx.beginPath(); sctx.moveTo(sx+12,H/2); sctx.lineTo(objX,H/2); sctx.stroke();
  sctx.setLineDash([]);

  // Object
  sctx.fillStyle=color+'33'; sctx.fillRect(objX-6,H/2-30,12,60);
  sctx.strokeStyle=color; sctx.lineWidth=1.5; sctx.strokeRect(objX-6,H/2-30,12,60);
  sctx.font='bold 11px JetBrains Mono,monospace'; sctx.textAlign='center';
  sctx.fillStyle=color; sctx.fillText(dist+'cm',objX,H/2+48);

  // Ticks
  sctx.fillStyle='rgba(255,255,255,0.3)'; sctx.font='9px Inter';
  [0,20,40,60,80,100].forEach(cm=>{
    sctx.fillText(cm+'cm',px(cm),H-4);
  });
}
updateDist();

// ── Simple Sim Logic ──
(function(){
  const serial = document.getElementById('sim5Serial');
  const slider = document.getElementById('sim5Slider');
  if(!serial || !slider) return;

  setInterval(()=>{
    const val = slider.value;
    const msg = `Distance: ${val}.00 cm\n`;
    serial.textContent += msg;
    serial.scrollTop = serial.scrollHeight;

    // Keep log from getting too long
    if (serial.textContent.length > 1000) {
      serial.textContent = serial.textContent.substring(serial.textContent.length - 800);
    }
  }, 500);
})();
