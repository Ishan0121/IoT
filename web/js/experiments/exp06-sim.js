/* js/experiments/exp06-sim.js — Servo & Stepper motor simulators */

// Servo canvas
const sc = document.getElementById('servoCanvas');
const {ctx:sctx,W:scW,H:scH} = hiDPI(sc);
let servoAngle = 90;
let sweepInterval = null;

function drawServo(angle){
  const W=scW,H=scH,cx=W/2,cy=H*0.65;
  sctx.clearRect(0,0,W,H);
  sctx.fillStyle='#0c111d';sctx.fillRect(0,0,W,H);
  // Body
  sctx.fillStyle='#1e3a5f';roundRect(sctx,60,100,80,70,8);sctx.fill();
  sctx.strokeStyle='#4f8ef7';sctx.lineWidth=1.5;sctx.stroke();
  // Horn
  const rad=(angle-90)*Math.PI/180;
  const len=55;
  sctx.strokeStyle='#22c55e';sctx.lineWidth=5;sctx.lineCap='round';
  sctx.beginPath();sctx.moveTo(cx,cy);
  sctx.lineTo(cx+Math.cos(rad)*len,cy+Math.sin(rad)*len);
  sctx.stroke();
  // Center dot
  sctx.fillStyle='#4f8ef7';sctx.beginPath();sctx.arc(cx,cy,7,0,Math.PI*2);sctx.fill();
  // Label
  sctx.font='bold 16px Inter,sans-serif';sctx.textAlign='center';sctx.fillStyle='#e8ecf1';
  sctx.fillText(angle+'°',cx,H-10);
  // Arc guide
  sctx.strokeStyle='rgba(79,142,247,0.2)';sctx.lineWidth=1;
  sctx.beginPath();sctx.arc(cx,cy,55,-Math.PI/2,Math.PI/2);sctx.stroke();
}

function setServoAngle(a){
  servoAngle=a;
  document.getElementById('servoSlider').value=a;
  document.getElementById('angleDisplay').textContent=a+'°';
  const pw=Math.round(544+(a/180)*(2400-544));
  document.getElementById('pwmWidth').textContent=pw+' µs';
  drawServo(a);
}

function sweepServo(){
  if(sweepInterval){clearInterval(sweepInterval);sweepInterval=null;return;}
  let dir=1;
  sweepInterval=setInterval(()=>{
    servoAngle+=dir*2;
    if(servoAngle>=180){servoAngle=180;dir=-1;}
    if(servoAngle<=0){servoAngle=0;dir=1;}
    setServoAngle(servoAngle);
  },30);
}
drawServo(90);

// Stepper canvas
const stc = document.getElementById('stepperCanvas');
const {ctx:stx,W:stcW,H:stcH} = hiDPI(stc);
let stepperPos = 0;
let stepAnimation = null;

function drawStepper(angle){
  const W=stcW,H=stcH,cx=W/2,cy=H/2,r=60;
  stx.clearRect(0,0,W,H);
  stx.fillStyle='#0c111d';stx.fillRect(0,0,W,H);
  // Outer ring
  stx.strokeStyle='rgba(236,72,153,0.3)';stx.lineWidth=8;
  stx.beginPath();stx.arc(cx,cy,r,0,Math.PI*2);stx.stroke();
  // Teeth
  for(let i=0;i<12;i++){
    const a=angle*Math.PI/180+i*(Math.PI*2/12);
    stx.fillStyle='rgba(236,72,153,0.6)';
    stx.beginPath();
    stx.arc(cx+Math.cos(a)*(r+4),cy+Math.sin(a)*(r+4),4,0,Math.PI*2);
    stx.fill();
  }
  // Shaft
  stx.fillStyle='#2d1b4e';stx.beginPath();stx.arc(cx,cy,16,0,Math.PI*2);stx.fill();
  stx.strokeStyle='#ec4899';stx.lineWidth=2;stx.stroke();
  // Indicator
  const ir=angle*Math.PI/180;
  stx.strokeStyle='#ec4899';stx.lineWidth=3;stx.lineCap='round';
  stx.beginPath();stx.moveTo(cx,cy);
  stx.lineTo(cx+Math.cos(ir)*r*0.7,cy+Math.sin(ir)*r*0.7);stx.stroke();
  // Angle label
  stx.font='bold 14px Inter,sans-serif';stx.textAlign='center';stx.fillStyle='#e8ecf1';
  stx.fillText(Math.round(((angle%360)+360)%360)+'°',cx,H-8);
}

function stepperRotate(deg,dir){
  if(stepAnimation)return;
  const target=stepperPos+deg*dir;
  const step=dir*3;
  stepAnimation=setInterval(()=>{
    stepperPos+=step;
    const diff=target-stepperPos;
    if(Math.abs(diff)<Math.abs(step)){stepperPos=target;clearInterval(stepAnimation);stepAnimation=null;}
    document.getElementById('stepperAngle').textContent=Math.round(((stepperPos%360)+360)%360)+'°';
    const seqs=['1000','1100','0100','0110','0010','0011','0001','1001'];
    const si=Math.floor(Math.abs(stepperPos)/45)%8;
    document.getElementById('stepSeq').textContent=seqs[si];
    drawStepper(stepperPos);
  },20);
}
drawStepper(0);

// ── Simple Sim Logic ──
(function(){
  const cvServo = document.getElementById('sim6ServoCanvas');
  const cvStep = document.getElementById('sim6StepperCanvas');
  if(!cvServo || !cvStep) return;

  const ctxS = hiDPI(cvServo).ctx;
  const ctxT = hiDPI(cvStep).ctx;
  const WS=160, HS=160, WT=160, HT=160;

  let sAngle=0, sDir=1;
  let tAngle=0, tSpeed=2;

  function drawSim(){
    // Draw Servo
    sAngle += sDir*2;
    if(sAngle>=180){sAngle=180;sDir=-1;}
    if(sAngle<=0){sAngle=0;sDir=1;}

    ctxS.fillStyle='#0c111d'; ctxS.fillRect(0,0,WS,HS);
    const cx=WS/2, cy=HS/2+10;
    ctxS.fillStyle='#1e3a5f'; roundRect(ctxS,cx-30,cy-20,60,50,6); ctxS.fill();
    const rad=(sAngle-90)*Math.PI/180;
    ctxS.strokeStyle='#22c55e'; ctxS.lineWidth=4; ctxS.lineCap='round';
    ctxS.beginPath(); ctxS.moveTo(cx,cy); ctxS.lineTo(cx+Math.cos(rad)*40,cy+Math.sin(rad)*40); ctxS.stroke();
    ctxS.fillStyle='#4f8ef7'; ctxS.beginPath(); ctxS.arc(cx,cy,5,0,Math.PI*2); ctxS.fill();

    // Draw Stepper
    tAngle += tSpeed;
    if(tAngle>=360) tAngle=0;
    ctxT.fillStyle='#0c111d'; ctxT.fillRect(0,0,WT,HT);
    const tcx=WT/2, tcy=HT/2;
    ctxT.fillStyle='#2C2C2A'; ctxT.beginPath(); ctxT.arc(tcx,tcy,40,0,Math.PI*2); ctxT.fill();
    ctxT.fillStyle='#d4d4d4'; ctxT.beginPath(); ctxT.arc(tcx,tcy,15,0,Math.PI*2); ctxT.fill();
    const trad=tAngle*Math.PI/180;
    ctxT.fillStyle='#ef4444'; ctxT.beginPath(); ctxT.arc(tcx+Math.cos(trad)*30, tcy+Math.sin(trad)*30, 4, 0, Math.PI*2); ctxT.fill();

    requestAnimationFrame(drawSim);
  }
  requestAnimationFrame(drawSim);
})();
