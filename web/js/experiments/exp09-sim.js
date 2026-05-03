/* js/experiments/exp09-sim.js — Ethernet web server dashboard simulator */

// Animate demo dashboard
let uptime=0, ledOn=false;
setInterval(()=>{
  uptime++;
  document.getElementById('demoUptime').textContent=uptime;
  document.getElementById('demoTemp').textContent=(22+Math.random()*4).toFixed(1);
  document.getElementById('demoHum').textContent=Math.round(55+Math.random()*15);
  document.getElementById('demoLDR').textContent=Math.round(300+Math.random()*400);
},2000);

function setLED(on){
  ledOn=on;
  document.getElementById('ledStateDemo').textContent=on?'ON':'OFF';
  document.getElementById('ledStateDemo').style.color=on?'#27ae60':'#c0392b';
}

// ── Simple Sim Logic ──
let sim9Start = performance.now();
function sim9Refresh(){
  const b = document.getElementById('sim9Browser');
  if(!b) return;
  b.innerHTML = '<span style="color:#888;font-size:12px">Connecting to 192.168.1.100...</span>';
  setTimeout(()=>{
    const uptime = Math.floor((performance.now() - sim9Start)/1000);
    b.innerHTML = `Hello from Arduino!<br>Uptime: ${uptime} seconds`;
  }, 400);
}
