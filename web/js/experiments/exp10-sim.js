/* js/experiments/exp10-sim.js — ThingSpeak cloud upload simulator */

// Live chart simulation
const cc = document.getElementById('chartCanvas');
const {ctx:cctx,W:ccW,H:ccH} = hiDPI(cc);
const history = [];
let countdown = 15, msgCount = 0;

function generatePoint(){
  return {
    temp: +(22+Math.random()*8).toFixed(1),
    hum: Math.round(50+Math.random()*30),
    light: Math.round(200+Math.random()*600),
    hi: +(24+Math.random()*6).toFixed(1)
  };
}

function drawChart(){
  const W=ccW, H=ccH;
  cctx.clearRect(0,0,W,H);
  cctx.fillStyle='#0c111d'; cctx.fillRect(0,0,W,H);
  if(history.length<2) return;
  const colors=['#4f8ef7','#14b8a6','#f59e0b'];
  const keys=['temp','hum'];
  keys.forEach((key,ki)=>{
    const vals=history.map(p=>p[key]);
    const mn=Math.min(...vals), mx=Math.max(...vals);
    const range=mx-mn||1;
    cctx.strokeStyle=colors[ki]; cctx.lineWidth=2;
    cctx.beginPath();
    history.forEach((p,i)=>{
      const x=(i/(history.length-1))*(W-20)+10;
      const y=H-((p[key]-mn)/range)*(H-20)-10;
      i===0?cctx.moveTo(x,y):cctx.lineTo(x,y);
    });
    cctx.stroke();
    // Last point dot
    const last=history[history.length-1];
    const lx=W-10, ly=H-((last[key]-mn)/range)*(H-20)-10;
    cctx.fillStyle=colors[ki];
    cctx.beginPath(); cctx.arc(lx,ly,4,0,Math.PI*2); cctx.fill();
  });
  // Legend
  cctx.font='10px Inter'; cctx.textAlign='left';
  [['#4f8ef7','Temp'],['#14b8a6','Humidity']].forEach(([c,l],i)=>{
    cctx.fillStyle=c; cctx.fillText('● '+l, 10+i*80, 14);
  });
}

function doUpload(){
  const pt = generatePoint();
  history.push(pt); if(history.length>30) history.shift();
  msgCount++;
  document.getElementById('f1').textContent=pt.temp;
  document.getElementById('f2').textContent=pt.hum;
  document.getElementById('f3').textContent=pt.light;
  document.getElementById('f4').textContent=pt.hi;
  document.getElementById('msgId').textContent=msgCount;
  document.getElementById('uploadStatus').textContent='✓ Upload OK';
  document.getElementById('uploadStatus').style.color='var(--green)';
  drawChart();
  setTimeout(()=>{document.getElementById('uploadStatus').textContent='Waiting...';document.getElementById('uploadStatus').style.color='var(--text2)';},2000);
}

// Initial data
for(let i=0;i<10;i++) history.push(generatePoint());
doUpload();

// Countdown
setInterval(()=>{
  countdown--;
  if(countdown<=0){countdown=15;doUpload();}
  document.getElementById('countdown').textContent=countdown+'s';
},1000);

// ── Simple Sim Logic ──
(function(){
  const s = document.getElementById('sim10Serial');
  if(!s) return;
  s.textContent = "Connecting to WiFi...\n";
  setTimeout(()=>{
    s.textContent += "Connected!\nIP Address: 192.168.1.105\n\n";
    setInterval(()=>{
      const t = (20 + Math.random()*5).toFixed(2);
      s.textContent += `Temp: ${t} C\nConnecting to api.thingspeak.com...\n`;
      s.scrollTop = s.scrollHeight;
      setTimeout(()=>{
        s.textContent += "GET /update?api_key=YOUR_API_KEY&field1=" + t + " HTTP/1.1\n";
        s.textContent += "HTTP/1.1 200 OK\nChannel update successful.\n\n";
        s.scrollTop = s.scrollHeight;
        if(s.textContent.length > 1000) s.textContent = s.textContent.substring(s.textContent.length - 800);
      }, 500);
    }, 5000); // 5s loop for active demo
  }, 1000);
})();
