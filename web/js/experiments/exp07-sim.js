/* js/experiments/exp07-sim.js — Smart Home dashboard simulator */
const logEl = document.getElementById('systemLog');
let relayOn=false, pirTimeout=null;

function log(msg){
  const t=new Date().toLocaleTimeString('en',{hour12:false,hour:'2-digit',minute:'2-digit',second:'2-digit'});
  logEl.innerHTML=`<span style="color:var(--text3)">[${t}]</span> ${msg}\n`+logEl.innerHTML;
}

function triggerPIR(){
  document.getElementById('pirVal').textContent='Motion!';
  document.getElementById('pirVal').style.color='var(--green)';
  document.getElementById('pirWidget').style.background='rgba(34,197,94,0.08)';
  if(!relayOn){relayOn=true;setRelay(true);log('<span style="color:var(--green)">[PIR] Motion detected → Relay ON</span>');}
  clearTimeout(pirTimeout);
  pirTimeout=setTimeout(()=>{
    document.getElementById('pirVal').textContent='No Motion';
    document.getElementById('pirVal').style.color='var(--text2)';
    document.getElementById('pirWidget').style.background='';
    relayOn=false;setRelay(false);
    log('<span style="color:var(--text2)">[PIR] No motion 10s → Relay OFF</span>');
  },5000);
}

function setRelay(on){
  const lamp=document.getElementById('relayLamp');
  document.getElementById('relayVal').textContent=on?'ON':'OFF';
  document.getElementById('relayVal').style.color=on?'var(--amber)':'var(--text2)';
  lamp.style.background=on?'rgba(245,158,11,0.8)':'rgba(255,255,255,0.05)';
  lamp.style.boxShadow=on?'0 0 20px 6px rgba(245,158,11,0.5)':'none';
}

function updateTemp(v){document.getElementById('tempVal').textContent=v+'°C';if(v>35)log('<span style="color:var(--red)">[DHT] ⚠ TEMP HIGH: '+v+'°C</span>');else log('[DHT] Temp: '+v+'°C');}
function updateHum(v){document.getElementById('humVal').textContent=v+'%';if(v>80)log('<span style="color:var(--amber)">[DHT] ⚠ HUMID HIGH: '+v+'%</span>');}
function updateLDR(v){document.getElementById('ldrVal').textContent=v;const dark=v>600;log('[LDR] '+v+(dark?' → DARK (LED ON)':' → BRIGHT'));}
function updateGas(v){
  const danger=v>400;
  document.getElementById('gasVal').textContent=v+(danger?' — ⚠ DANGER':' — Safe');
  document.getElementById('gasVal').style.color=danger?'var(--red)':'var(--green)';
  document.getElementById('gasWidget').style.background=danger?'rgba(239,68,68,0.08)':'';
  if(danger) log('<span style="color:var(--red)">[GAS] ⚠ DANGER! Level: '+v+' — ALARM ON</span>');
}
log('<span style="color:var(--green)">System initialized. Monitoring started.</span>');

// ── Simple Sim Logic ──
function sim7Trigger(active) {
  const led = document.getElementById('sim7Led');
  const serial = document.getElementById('sim7Serial');
  if(!led || !serial) return;

  if(active) {
    led.style.background = '#22c55e';
    led.style.boxShadow = '0 0 20px 6px rgba(34,197,94,0.6)';
    serial.textContent += "Motion detected!\n";
    serial.scrollTop = serial.scrollHeight;
    if (serial.textContent.length > 500) serial.textContent = serial.textContent.substring(serial.textContent.length - 400);
  } else {
    led.style.background = 'rgba(34,197,94,0.1)';
    led.style.boxShadow = 'none';
  }
}
sim7Trigger(false);

// DHT11 Simple Logic
setInterval(()=>{
  const s = document.getElementById('sim7DhtSerial');
  const t = document.getElementById('sim7DhtTemp');
  const h = document.getElementById('sim7DhtHum');
  if(!s||!t||!h) return;
  s.textContent += `Temp: ${t.value}.00°C  |  Humidity: ${h.value}.00%\n`;
  s.scrollTop = s.scrollHeight;
  if(s.textContent.length > 500) s.textContent = s.textContent.substring(s.textContent.length - 400);
}, 2000);

// LDR Simple Logic
function sim7UpdateLdr(v) {
  const lbl = document.getElementById('s7LdrV');
  const lamp = document.getElementById('sim7Lamp');
  const txt = document.getElementById('sim7LampLbl');
  if(!lbl||!lamp) return;
  lbl.textContent = v;
  if(v > 600) {
    lamp.style.background = '#f59e0b';
    lamp.style.boxShadow = '0 0 20px 4px rgba(245,158,11,0.5)';
    txt.textContent = 'LAMP ON (DARK)';
    txt.style.color = '#f59e0b';
  } else {
    lamp.style.background = 'rgba(255,255,255,0.05)';
    lamp.style.boxShadow = 'none';
    txt.textContent = 'LAMP OFF (BRIGHT)';
    txt.style.color = 'var(--text2)';
  }
}
sim7UpdateLdr(300);
