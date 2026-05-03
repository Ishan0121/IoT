/* js/experiments/exp04-sim.js — 4-Way Traffic Light simulator */
const cv=document.getElementById('road');
const {ctx,W,H}=hiDPI(cv);
const CX=W/2,CY=H/2,RW=60;
const PHASES=[
  {name:'N/S Green',dur:5000,ns:[0,0,1],ew:[1,0,0],tag:'phase-ns',bar:'#22c55e'},
  {name:'N/S Yellow',dur:2000,ns:[0,1,0],ew:[1,0,0],tag:'phase-y',bar:'#f59e0b'},
  {name:'All Red',dur:500,ns:[1,0,0],ew:[1,0,0],tag:'phase-y',bar:'#5a6477'},
  {name:'E/W Green',dur:5000,ns:[1,0,0],ew:[0,0,1],tag:'phase-ew',bar:'#4f8ef7'},
  {name:'E/W Yellow',dur:2000,ns:[1,0,0],ew:[0,1,0],tag:'phase-y',bar:'#f59e0b'},
  {name:'All Red',dur:500,ns:[1,0,0],ew:[1,0,0],tag:'phase-y',bar:'#5a6477'},
];
let phase=0,elapsed=0,last=performance.now(),running=true;
let cntNS=0,cntEW=0,total=0;
let emergency=false;

function draw(){
  const p=PHASES[phase];
  const ns=emergency ? [1,0,0] : p.ns;
  const ew=emergency ? [1,0,0] : p.ew;
  const dark=matchMedia('(prefers-color-scheme:dark)').matches;
  const road=dark?'#2C2C2A':'#D3D1C7';
  const lane=dark?'#F1EFE8':'#888780';
  const grass=dark?'#1a2218':'#c8e8b0';
  ctx.fillStyle=grass;ctx.fillRect(0,0,W,H);
  ctx.fillStyle=road;
  ctx.fillRect(CX-RW/2,0,RW,H);ctx.fillRect(0,CY-RW/2,W,RW);
  ctx.setLineDash([14,10]);ctx.strokeStyle=lane;ctx.lineWidth=1.5;
  ctx.beginPath();ctx.moveTo(CX,0);ctx.lineTo(CX,CY-RW/2-2);ctx.stroke();
  ctx.beginPath();ctx.moveTo(CX,CY+RW/2+2);ctx.lineTo(CX,H);ctx.stroke();
  ctx.beginPath();ctx.moveTo(0,CY);ctx.lineTo(CX-RW/2-2,CY);ctx.stroke();
  ctx.beginPath();ctx.moveTo(CX+RW/2+2,CY);ctx.lineTo(W,CY);ctx.stroke();
  ctx.setLineDash([]);
  ctx.fillStyle=road;ctx.fillRect(CX-RW/2,CY-RW/2,RW,RW);
  function drawLight(x,y,rot,lights){
    ctx.save();ctx.translate(x,y);ctx.rotate(rot);
    const lw=14,lh=38,lx=-7,ly=-19;
    ctx.fillStyle='#1a1a1a';roundRect(ctx,lx,ly,lw,lh,3);ctx.fill();
    [[0,lights[2],'#22c55e'],[1,lights[1],'#f59e0b'],[2,lights[0],'#ef4444']].forEach(([i,on,col])=>{
      ctx.beginPath();ctx.arc(0,ly+6+i*13,4.5,0,Math.PI*2);
      ctx.fillStyle=on?col:'#2C2C2A';ctx.fill();
      if(on){ctx.globalAlpha=.25;ctx.beginPath();ctx.arc(0,ly+6+i*13,8,0,Math.PI*2);ctx.fillStyle=col;ctx.fill();ctx.globalAlpha=1;}
    });
    ctx.restore();
  }
  drawLight(CX-RW/2-14,CY-RW/2-14,0,ns);
  drawLight(CX+RW/2+14,CY+RW/2+14,Math.PI,ns);
  drawLight(CX+RW/2+14,CY-RW/2-14,Math.PI/2,ew);
  drawLight(CX-RW/2-14,CY+RW/2+14,-Math.PI/2,ew);
  ctx.font='bold 10px Inter,sans-serif';ctx.textAlign='center';
  ctx.fillStyle=dark?'#B4B2A9':'#5F5E5A';
  ctx.fillText('N',CX,14);ctx.fillText('S',CX,H-6);
  ctx.fillText('W',10,CY+4);ctx.fillText('E',W-10,CY+4);
}
function updateUI(){
  const p=PHASES[phase];
  const pct=Math.max(0,1-(elapsed/p.dur));
  const tag=document.getElementById('phaseTag');
  if(emergency) {
    document.getElementById('timerBar').style.width='100%';
    document.getElementById('timerBar').style.background='#ef4444';
    tag.textContent='Phase: EMERGENCY (ALL RED)';
    tag.className='phase-tag';
    tag.style.color='var(--red)';
  } else {
    document.getElementById('timerBar').style.width=(pct*100)+'%';
    document.getElementById('timerBar').style.background=p.bar;
    tag.textContent='Phase: '+p.name;
    tag.className='phase-tag '+p.tag;
    tag.style.color='';
  }
  document.getElementById('cntNS').textContent=cntNS;
  document.getElementById('cntEW').textContent=cntEW;
  document.getElementById('cntTotal').textContent=total;
}
function tick(now){
  if(running && !emergency){
    const dt=Math.min(now-last,200);elapsed+=dt;
    if(elapsed>=PHASES[phase].dur){
      elapsed=0;const prev=phase;phase=(phase+1)%6;total++;
      if(prev===0)cntNS++;if(prev===3)cntEW++;
    }
  }
  last=now;draw();updateUI();requestAnimationFrame(tick);
}
function togglePlay(){running=!running;last=performance.now();document.getElementById('btnPlay').textContent=running?'⏸ Pause':'▶ Play';}
function toggleEmergency() {
  emergency = !emergency;
  const btn = document.getElementById('btnEmerg');
  if(emergency) {
    btn.style.background = 'rgba(239,68,68,0.15)';
    btn.style.borderColor = 'rgba(239,68,68,0.8)';
  } else {
    btn.style.background = '';
    btn.style.borderColor = 'rgba(239,68,68,0.5)';
    last=performance.now();
  }
}
function resetSim(){phase=0;elapsed=0;cntNS=0;cntEW=0;total=0;last=performance.now();emergency=false;document.getElementById('btnEmerg').style.background='';document.getElementById('btnEmerg').style.borderColor='rgba(239,68,68,0.5)';}
requestAnimationFrame(tick);

// ── Simple 6-pin simulation ─────────────────
const sc2=document.getElementById('simpleRoad');
const sc2x=sc2?(()=>{const {ctx:c}=hiDPI(sc2);return c;})():null;
const SIMPLE_PHASES=[
  {name:'N/S GREEN',dur:5000,ns:[0,0,1],ew:[1,0,0],bar:'#22c55e'},
  {name:'N/S YELLOW',dur:2000,ns:[0,1,0],ew:[1,0,0],bar:'#f59e0b'},
  {name:'ALL RED',dur:500,ns:[1,0,0],ew:[1,0,0],bar:'#5a6477'},
  {name:'E/W GREEN',dur:5000,ns:[1,0,0],ew:[0,0,1],bar:'#4f8ef7'},
  {name:'E/W YELLOW',dur:2000,ns:[1,0,0],ew:[0,1,0],bar:'#f59e0b'},
  {name:'ALL RED',dur:500,ns:[1,0,0],ew:[1,0,0],bar:'#5a6477'},
];
let sp=0,se=0,sl=performance.now(),sr=true;
function drawSimple(){
  if(!sc2x)return;
  const p=SIMPLE_PHASES[sp],ns=p.ns,ew=p.ew;
  const W=240,H=240,CX=120,CY=120,RW=50;
  sc2x.fillStyle='#0a180a';sc2x.fillRect(0,0,W,H);
  sc2x.fillStyle='#2a2a28';
  sc2x.fillRect(CX-RW/2,0,RW,H);sc2x.fillRect(0,CY-RW/2,W,RW);
  sc2x.setLineDash([10,8]);sc2x.strokeStyle='rgba(255,255,200,0.2)';sc2x.lineWidth=1.5;
  sc2x.beginPath();sc2x.moveTo(CX,0);sc2x.lineTo(CX,CY-RW/2);sc2x.stroke();
  sc2x.beginPath();sc2x.moveTo(CX,CY+RW/2);sc2x.lineTo(CX,H);sc2x.stroke();
  sc2x.beginPath();sc2x.moveTo(0,CY);sc2x.lineTo(CX-RW/2,CY);sc2x.stroke();
  sc2x.beginPath();sc2x.moveTo(CX+RW/2,CY);sc2x.lineTo(W,CY);sc2x.stroke();
  sc2x.setLineDash([]);
  sc2x.fillStyle='#2a2a28';sc2x.fillRect(CX-RW/2,CY-RW/2,RW,RW);
  function drawL(x,y,rot,lights){
    sc2x.save();sc2x.translate(x,y);sc2x.rotate(rot);
    sc2x.fillStyle='#111';roundRect(sc2x,-6,-17,12,34,3);sc2x.fill();
    [[0,lights[2],'#22c55e'],[1,lights[1],'#f59e0b'],[2,lights[0],'#ef4444']].forEach(([i,on,col])=>{
      sc2x.beginPath();sc2x.arc(0,-11+i*11,4,0,Math.PI*2);
      sc2x.fillStyle=on?col:'#222';sc2x.fill();
      if(on){sc2x.globalAlpha=.2;sc2x.beginPath();sc2x.arc(0,-11+i*11,7,0,Math.PI*2);sc2x.fillStyle=col;sc2x.fill();sc2x.globalAlpha=1;}
    });sc2x.restore();
  }
  drawL(CX-RW/2-12,CY-RW/2-12,0,ns);
  drawL(CX+RW/2+12,CY+RW/2+12,Math.PI,ns);
  drawL(CX+RW/2+12,CY-RW/2-12,Math.PI/2,ew);
  drawL(CX-RW/2-12,CY+RW/2+12,-Math.PI/2,ew);
  sc2x.font='bold 9px Inter';sc2x.textAlign='center';sc2x.fillStyle='rgba(255,255,255,0.4)';
  sc2x.fillText('N',CX,12);sc2x.fillText('S',CX,H-4);
  sc2x.fillText('W',8,CY+4);sc2x.fillText('E',W-8,CY+4);
}
function tickSimple(now){
  const dt=Math.min(now-sl,200);se+=dt;sl=now;
  if(se>=SIMPLE_PHASES[sp].dur){se=0;sp=(sp+1)%6;}
  drawSimple();
  const pct=Math.max(0,1-(se/SIMPLE_PHASES[sp].dur));
  const bar=document.getElementById('simpleBar');
  if(bar){bar.style.width=(pct*100)+'%';bar.style.background=SIMPLE_PHASES[sp].bar;}
  const lbl=document.getElementById('simplePhaseLabel');
  if(lbl){lbl.textContent=SIMPLE_PHASES[sp].name;
    lbl.style.color=SIMPLE_PHASES[sp].bar==='#22c55e'?'var(--green)':SIMPLE_PHASES[sp].bar==='#4f8ef7'?'var(--accent)':'var(--amber)';}
  requestAnimationFrame(tickSimple);
}
function simpleReset(){sp=0;se=0;sl=performance.now();}
requestAnimationFrame(tickSimple);
