/* js/experiments/exp08-sim.js — DC Motor speed control simulator */
const mc = document.getElementById('motorCanvas');
const {ctx:mctx,W:mcW,H:mcH} = hiDPI(mc);
let motorAngle = 0, motorSpeed = 0, motorDir = 1, braked = false;
let animFrame;

function drawMotor(){
  const W=mcW,H=mcH,cx=W/2,cy=H/2;
  mctx.clearRect(0,0,W,H);
  mctx.fillStyle='#0c111d';mctx.fillRect(0,0,W,H);
  // Outer casing
  mctx.strokeStyle='rgba(249,115,22,0.3)';mctx.lineWidth=8;
  mctx.beginPath();mctx.arc(cx,cy,70,0,Math.PI*2);mctx.stroke();
  // Rotor
  mctx.save();mctx.translate(cx,cy);mctx.rotate(motorAngle*Math.PI/180);
  for(let i=0;i<6;i++){
    const a=i*60*Math.PI/180;
    mctx.strokeStyle=`rgba(249,115,22,${0.4+0.1*i})`;mctx.lineWidth=3;
    mctx.beginPath();mctx.moveTo(0,0);mctx.lineTo(Math.cos(a)*55,Math.sin(a)*55);mctx.stroke();
    mctx.fillStyle='rgba(249,115,22,0.6)';
    mctx.beginPath();mctx.arc(Math.cos(a)*55,Math.sin(a)*55,5,0,Math.PI*2);mctx.fill();
  }
  mctx.restore();
  // Center
  mctx.fillStyle='#f97316';mctx.beginPath();mctx.arc(cx,cy,10,0,Math.PI*2);mctx.fill();
  // Speed arc
  const pct=motorSpeed/255;
  mctx.strokeStyle=braked?'#ef4444':pct>0?'#f97316':'rgba(255,255,255,0.1)';
  mctx.lineWidth=4;mctx.beginPath();
  mctx.arc(cx,cy,78,-Math.PI/2,-Math.PI/2+pct*Math.PI*2);mctx.stroke();
  // Direction arrow
  if(motorSpeed>5){
    mctx.fillStyle='rgba(249,115,22,0.7)';mctx.font='14px Inter,sans-serif';mctx.textAlign='center';
    mctx.fillText(motorDir>0?'↻':'↺',cx,cy+46);
  }
}

function animate(){
  if(!braked && motorSpeed>0){
    motorAngle=(motorAngle+motorSpeed*motorDir*0.08)%360;
  }
  drawMotor();
  animFrame=requestAnimationFrame(animate);
}

function updateMotor(){
  braked=false;
  const val=+document.getElementById('speedSlider').value;
  motorSpeed=val<25?0:val;
  const pct=Math.round((motorSpeed/255)*100);
  document.getElementById('pwmDisplay').textContent=motorSpeed;
  document.getElementById('pctDisplay').textContent=pct+'%';
  document.getElementById('rpmDisplay').textContent='~'+Math.round(pct*1.5);
  document.getElementById('in1').textContent=motorDir>0?'HIGH':'LOW';
  document.getElementById('in2').textContent=motorDir>0?'LOW':'HIGH';
  document.getElementById('ena').textContent=motorSpeed;
}

function toggleDir(){
  motorDir*=-1;
  motorSpeed=0;
  document.getElementById('dirLabel').textContent=motorDir>0?'↻ FORWARD':'↺ REVERSE';
  document.getElementById('dirLabel').style.color=motorDir>0?'var(--green)':'var(--amber)';
  updateMotor();
}

function brakeMotor(){
  braked=true; motorSpeed=0;
  document.getElementById('speedSlider').value=0;
  updateMotor();
}

animate();
updateMotor();

// ── Simple Sim Logic ──
(function(){
  const cv = document.getElementById('sim8Motor');
  if(!cv) return;
  const ctx = hiDPI(cv).ctx;
  const W=160, H=160;

  const states = [
    {n:'FORWARD (128)', d:3000, spd:4, dir:1, c:'var(--green)'},
    {n:'STOP (0)', d:500, spd:0, dir:0, c:'var(--text2)'},
    {n:'REVERSE (255)', d:3000, spd:8, dir:-1, c:'var(--red)'},
    {n:'STOP (0)', d:500, spd:0, dir:0, c:'var(--text2)'}
  ];
  let sIdx = 0;
  let angle = 0;
  let sTime = performance.now();

  function drawSim8(){
    const now = performance.now();
    const st = states[sIdx];
    let elapsed = now - sTime;
    if(elapsed >= st.d){
      elapsed = 0; sTime = now;
      sIdx = (sIdx+1)%states.length;
      document.getElementById('sim8State').textContent = states[sIdx].n;
      document.getElementById('sim8State').style.color = states[sIdx].c;
      document.getElementById('sim8Bar').style.background = states[sIdx].c;
    }
    document.getElementById('sim8Bar').style.width = Math.max(0,100*(1 - elapsed/states[sIdx].d)) + '%';

    angle += st.spd * st.dir;
    ctx.fillStyle='#0c111d'; ctx.fillRect(0,0,W,H);
    const cx=W/2, cy=H/2;
    ctx.fillStyle='#2C2C2A'; ctx.beginPath(); ctx.arc(cx,cy,40,0,Math.PI*2); ctx.fill();
    ctx.strokeStyle='#4f8ef7'; ctx.lineWidth=3; ctx.beginPath(); ctx.arc(cx,cy,40,0,Math.PI*2); ctx.stroke();

    ctx.save(); ctx.translate(cx,cy); ctx.rotate(angle*Math.PI/180);
    ctx.fillStyle='#d4d4d4'; ctx.fillRect(-5,-20,10,40);
    ctx.fillStyle='#ef4444'; ctx.beginPath(); ctx.arc(0,-15,4,0,Math.PI*2); ctx.fill();
    ctx.restore();

    requestAnimationFrame(drawSim8);
  }
  requestAnimationFrame(drawSim8);
})();
