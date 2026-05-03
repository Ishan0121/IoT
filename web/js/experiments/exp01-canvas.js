/* js/experiments/exp01-canvas.js
 * Dead canvas board visualization (currently disabled in HTML via comment).
 * Extracted and kept here ready to re-enable if needed.
 * Depends on: shared.js (hiDPI, roundRect)
 */
// Interactive Board Canvas — 6 non-overlapping zones
const cv = document.getElementById('boardCanvas');
if (cv) {
  const { ctx, W, H } = hiDPI(cv);  // sharp on Retina/HiDPI screens

  // Every zone is its own column — nothing overlaps.
  // ATmega328P chip is drawn as a proper IC graphic inside its column.
  const zones = [
    { x:8,   y:4,  w:82,  h:332, color:'#1b2f52', label:'Power\nPins',
      detail:'5V, 3.3V, GND (×2), Vin, RESET, IOREF\nRegulated supply for your circuit.\nMax 200mA from 5V pin.' },
    { x:98,  y:4,  w:85,  h:332, color:'#2d1b4e', label:'Analog\nA0–A5',
      detail:'A0–A5: 10-bit ADC → reads 0 to 1023\nMaps: 0V→0, 5V→1023\nA4=SDA, A5=SCL for I2C bus' },
    { x:191, y:4,  w:160, h:332, color:'#162816', label:'ATmega328P',
      detail:'8-bit AVR microcontroller @ 16 MHz\n32 KB Flash | 2 KB SRAM | 1 KB EEPROM\nAll I/O, timers, PWM, ADC run here.' },
    { x:359, y:4,  w:110, h:332, color:'#131f13', label:'Digital\nD0–D7',
      detail:'D0(RX) D1(TX) — Serial (avoid for sensors)\nD2, D3(~), D4, D5(~), D6(~), D7\n~ pins support PWM via analogWrite()' },
    { x:477, y:4,  w:105, h:332, color:'#221313', label:'Digital\nD8–D13',
      detail:'D8, D9(~), D10(~), D11(~), D12, D13\nD13 = built-in LED\nSPI: D10=SS D11=MOSI D12=MISO D13=SCK' },
    { x:590, y:4,  w:102, h:96,  color:'#3a1e09', label:'USB-B\nPort',
      detail:'Upload sketches from Arduino IDE\nPowers board from PC (5V)\nSerial Monitor via ATmega16U2 bridge' },
    { x:590, y:108,w:102, h:90,  color:'#092038', label:'DC Power\nJack',
      detail:'7–12V barrel jack recommended\nOnboard linear regulator → 5V\nDo NOT exceed 12V input voltage!' },
    { x:590, y:206,w:102, h:130, color:'#162216', label:'Crystal\n+ Reset',
      detail:'16 MHz quartz crystal oscillator\nSets the CPU clock speed precisely\nRESET button: pull LOW to restart sketch' },
  ];

  let hovZone = null, selZone = null;

  function rr(x,y,w,h,r) {
    ctx.beginPath(); ctx.moveTo(x+r,y); ctx.lineTo(x+w-r,y);
    ctx.quadraticCurveTo(x+w,y,x+w,y+r); ctx.lineTo(x+w,y+h-r);
    ctx.quadraticCurveTo(x+w,y+h,x+w-r,y+h); ctx.lineTo(x+r,y+h);
    ctx.quadraticCurveTo(x,y+h,x,y+h-r); ctx.lineTo(x,y+r);
    ctx.quadraticCurveTo(x,y,x+r,y); ctx.closePath();
  }

  function drawChipInZone(z) {
    const pad=28, chipH=z.h-90;
    const bx=z.x+pad, by=z.y+45, bw=z.w-pad*2, bh=chipH;
    // Body
    ctx.fillStyle='#1e3a1e'; rr(bx,by,bw,bh,5); ctx.fill();
    ctx.strokeStyle='#3a6a3a'; ctx.lineWidth=1.5; ctx.stroke();
    // IC notch (top center)
    ctx.fillStyle='#162816';
    ctx.beginPath(); ctx.arc(bx+bw/2, by, 9, Math.PI, 0, false); ctx.fill();
    // Pins — 7 per side
    const pinCols=['#4f8ef7','#22c55e','#f59e0b','#ef4444','#a78bfa','#06b6d4','#fb923c'];
    const nPins=7, ps=bh/(nPins+1);
    for(let i=0;i<nPins;i++){
      const py2=by+ps*(i+1);
      // Left pins
      ctx.strokeStyle=pinCols[i]; ctx.lineWidth=2;
      ctx.beginPath(); ctx.moveTo(bx,py2); ctx.lineTo(bx-18,py2); ctx.stroke();
      ctx.fillStyle=pinCols[i];
      ctx.beginPath(); ctx.arc(bx-18,py2,3.5,0,Math.PI*2); ctx.fill();
      // Right pins (reversed colour)
      ctx.strokeStyle=pinCols[nPins-1-i]; ctx.lineWidth=2;
      ctx.beginPath(); ctx.moveTo(bx+bw,py2); ctx.lineTo(bx+bw+18,py2); ctx.stroke();
      ctx.fillStyle=pinCols[nPins-1-i];
      ctx.beginPath(); ctx.arc(bx+bw+18,py2,3.5,0,Math.PI*2); ctx.fill();
    }
    // Text inside chip
    ctx.textAlign='center';
    ctx.fillStyle='rgba(160,240,160,0.85)'; ctx.font='bold 12px "JetBrains Mono",monospace';
    ctx.fillText('ATmega', z.x+z.w/2, by+bh/2-10);
    ctx.fillText('328P',   z.x+z.w/2, by+bh/2+8);
    ctx.fillStyle='rgba(120,200,120,0.5)'; ctx.font='9px Inter,sans-serif';
    ctx.fillText('16 MHz · 8-bit AVR', z.x+z.w/2, by+bh/2+26);
  }

  function draw() {
    ctx.clearRect(0,0,W,H);
    // PCB board
    ctx.fillStyle='#091609'; rr(2,1,W-4,H-2,10); ctx.fill();
    ctx.strokeStyle='#1d501d'; ctx.lineWidth=2; ctx.stroke();

    zones.forEach(z => {
      const hov=z===hovZone, sel=z===selZone;
      ctx.fillStyle=z.color; rr(z.x,z.y,z.w,z.h,6); ctx.fill();
      ctx.strokeStyle=sel?'#4f8ef7':hov?'rgba(255,255,255,0.25)':'rgba(255,255,255,0.06)';
      ctx.lineWidth=sel?2.5:1; ctx.stroke();

      if(z.label==='ATmega328P'){
        drawChipInZone(z);
        // Zone column label
        ctx.fillStyle='rgba(160,240,160,0.35)'; ctx.font='9px Inter,sans-serif'; ctx.textAlign='center';
        ctx.fillText('ATmega328P', z.x+z.w/2, z.y+16);
      } else {
        ctx.fillStyle='rgba(255,255,255,0.68)'; ctx.font='bold 10px Inter,sans-serif'; ctx.textAlign='center';
        const cx=z.x+z.w/2, cy=z.y+z.h/2;
        z.label.split('\n').forEach((l,i,a)=>ctx.fillText(l,cx,cy-(a.length-1)*7+i*14));
      }
    });

    // ── Pin header dots ───
    // Analog A0–A5 in analog column
    ['#a78bfa','#a78bfa','#a78bfa','#a78bfa','#22c55e','#22c55e'].forEach((c,i)=>{
      ctx.fillStyle=c; ctx.beginPath(); ctx.arc(106+i*13,16,4.5,0,Math.PI*2); ctx.fill();
    });
    // D0–D7 in digital 0-7 column
    for(let i=0;i<8;i++){
      const pwm=[3,5,6].includes(i);
      ctx.fillStyle=pwm?'#f59e0b':'#4f8ef7';
      ctx.beginPath(); ctx.arc(366+i*12,16,4.5,0,Math.PI*2); ctx.fill();
      if(pwm){ctx.strokeStyle='rgba(245,158,11,0.3)';ctx.lineWidth=1.5;ctx.beginPath();ctx.arc(366+i*12,16,7.5,0,Math.PI*2);ctx.stroke();}
    }
    // D8–D13 in digital 8-13 column
    for(let i=0;i<6;i++){
      ctx.fillStyle=[1,2,3].includes(i)?'#f59e0b':'#4f8ef7';
      ctx.beginPath(); ctx.arc(484+i*12,16,4.5,0,Math.PI*2); ctx.fill();
    }

    // Crystal visual
    ctx.fillStyle='rgba(180,220,180,0.12)'; rr(603,240,46,30,3); ctx.fill();
    ctx.strokeStyle='rgba(140,200,140,0.3)'; ctx.lineWidth=1; ctx.stroke();
    ctx.fillStyle='rgba(160,210,160,0.6)'; ctx.font='7px Inter'; ctx.textAlign='center';
    ctx.fillText('16MHz', 626, 259);
  }

  draw();

  cv.style.cursor='pointer';
  cv.addEventListener('mousemove', function(e) {
    const r=cv.getBoundingClientRect(), sx=W/r.width, sy=H/r.height;
    const mx=(e.clientX-r.left)*sx, my=(e.clientY-r.top)*sy;
    const hit=zones.find(z=>mx>=z.x&&mx<=z.x+z.w&&my>=z.y&&my<=z.y+z.h)||null;
    if(hit!==hovZone){hovZone=hit; draw();}
  });

  cv.addEventListener('click', function(e) {
    const r=cv.getBoundingClientRect(), sx=W/r.width, sy=H/r.height;
    const mx=(e.clientX-r.left)*sx, my=(e.clientY-r.top)*sy;
    const hit=zones.find(z=>mx>=z.x&&mx<=z.x+z.w&&my>=z.y&&my<=z.y+z.h);
    if(!hit)return;
    selZone=hit; draw();
    document.getElementById('boardLegend').innerHTML=
      `<div class="legend-title" style="color:#4f8ef7">${hit.label.replace('\n',' ')}</div>`+
      `<div class="legend-detail">${hit.detail.replace(/\n/g,'<br>')}</div>`;
  });
}
