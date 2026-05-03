document.addEventListener('DOMContentLoaded', () => {
  const svgLayer = document.getElementById('connection-svg');
  const detailsContainer = document.querySelector('.details');
  const unoContainer = document.querySelector('.uno');
  
  // Select all pins and hotspots that have data-tags
  const interactiveElements = document.querySelectorAll('.pin[data-tags], .hotspot[data-tags]');

  const colorMap = {
    blue: '#3b82f6',
    green: '#22c55e',
    white: '#cbd5e1',
    pink: '#ec4899',
    yellow: '#eab308',
    gray: '#94a3b8',
    black: '#64748b', /* slightly lighter than black for glow */
    red: '#ef4444'
  };

  let activePath = null;

  interactiveElements.forEach(el => {
    el.addEventListener('mouseenter', handleMouseEnter);
    el.addEventListener('mouseleave', handleMouseLeave);
  });

  function hexToRgba(hex, alpha) {
    if (!hex.startsWith('#') || hex.length !== 7) return `rgba(59, 130, 246, ${alpha})`;
    let r = parseInt(hex.slice(1, 3), 16);
    let g = parseInt(hex.slice(3, 5), 16);
    let b = parseInt(hex.slice(5, 7), 16);
    return `rgba(${r}, ${g}, ${b}, ${alpha})`;
  }

  function handleMouseEnter(e) {
    const target = e.currentTarget;

    // Parse the tags data
    const tagsData = JSON.parse(target.getAttribute('data-tags') || '[]');
    if (tagsData.length === 0) return;

    let activeColor = '#3b82f6'; // default blue

    // Determine color based on component/pin type
    if (target.classList.contains('digital')) activeColor = '#ec4899'; // pink
    else if (target.classList.contains('analog')) activeColor = '#22c55e'; // green
    else if (target.classList.contains('power')) activeColor = '#ef4444'; // red
    else if (target.classList.contains('icsp-top') || target.classList.contains('icsp-bottom')) activeColor = '#c084fc'; // purple
    else if (target.classList.contains('power-jack') || target.classList.contains('reset') || target.classList.contains('reset-right')) activeColor = '#ef4444'; // red
    else if (target.classList.contains('led-on')) activeColor = '#22c55e'; // green
    else if (target.classList.contains('led-l') || target.classList.contains('tx-led') || target.classList.contains('rx-led')) activeColor = '#eab308'; // yellow
    else if (target.classList.contains('atmega328p') || target.classList.contains('atmega16u2') || target.classList.contains('crystal')) activeColor = '#94a3b8'; // gray
    else if (target.classList.contains('usb-jack')) activeColor = '#3b82f6'; // blue
    else {
      // Fallback to the first tag's color
      const primaryColorStr = tagsData[0].color;
      activeColor = colorMap[primaryColorStr] || '#3b82f6';
    }
    
    // Set CSS variables for the target
    target.style.setProperty('--active-color', activeColor);
    target.style.setProperty('--active-bg', hexToRgba(activeColor, 0.4));

    target.classList.add('active');

    // Build the tags HTML and inject into the user's .details div
    detailsContainer.innerHTML = tagsData.map(tag => 
      `<div class="pin-tag tag-${tag.color}">${tag.label}</div>`
    ).join('');

    // Show details div
    detailsContainer.classList.add('visible');

    // Draw connection line
    updateConnection(target, activeColor);
  }

  function handleMouseLeave(e) {
    const target = e.currentTarget;
    target.classList.remove('active');
    
    target.style.removeProperty('--active-color');
    target.style.removeProperty('--active-bg');

    detailsContainer.classList.remove('visible');
    
    if (activePath) {
      activePath.remove();
      activePath = null;
    }
  }

  function updateConnection(target, activeColor) {
    const unoRect = unoContainer.getBoundingClientRect();
    const targetRect = target.getBoundingClientRect();
    const detailsRect = detailsContainer.getBoundingClientRect();
    const boardWrapper = document.querySelector('.board-wrapper');
    const boardRect = boardWrapper.getBoundingClientRect();
    
    // Pin center
    const pX = targetRect.left + (targetRect.width / 2) - unoRect.left;
    const pY = targetRect.top + (targetRect.height / 2) - unoRect.top;

    // Board boundaries
    const bL = boardRect.left - unoRect.left;
    const bR = boardRect.right - unoRect.left;
    const bT = boardRect.top - unoRect.top;
    const bB = boardRect.bottom - unoRect.top;

    // Track boundaries (padding around the board)
    const padding = 15;
    const tL = bL - padding;
    const tR = bR + padding;
    const tT = bT - padding;
    const tB = bB + padding;

    // 1. Find nearest board edge from the pin
    const dL = Math.abs(pX - bL);
    const dR = Math.abs(bR - pX);
    const dT = Math.abs(pY - bT);
    const dB = Math.abs(bB - pY);
    
    const minD = Math.min(dL, dR, dT, dB);
    let edge;
    if (minD === dR) edge = 'RIGHT';
    else if (minD === dL) edge = 'LEFT';
    else if (minD === dT) edge = 'TOP';
    else edge = 'BOTTOM';

    // The destination on the details div (Left middle point)
    const endX = detailsRect.left - unoRect.left;
    const endY = detailsRect.top + (detailsRect.height / 2) - unoRect.top;

    const pathPoints = [{x: pX, y: pY}];

    // Construct the path exactly as requested
    if (edge === 'TOP' || edge === 'BOTTOM') {
        const borderY = edge === 'TOP' ? tT : tB;
        pathPoints.push({x: pX, y: borderY}); // connect with nearest border
        pathPoints.push({x: tL, y: borderY}); // line goes to the left
        pathPoints.push({x: tL, y: endY});    // then down
        pathPoints.push({x: endX, y: endY});  // connect with details div in left middle
    } 
    else if (edge === 'LEFT') {
        pathPoints.push({x: tL, y: pY});      // connect with left border
        pathPoints.push({x: tL, y: endY});    // go downwards
        pathPoints.push({x: endX, y: endY});  // connect to details div
    } 
    else if (edge === 'RIGHT') {
        pathPoints.push({x: tR, y: pY});      // connect with right border
        pathPoints.push({x: tR, y: tB});      // go down
        pathPoints.push({x: tL, y: tB});      // then left (under the board)
        pathPoints.push({x: tL, y: endY});    // then down again
        pathPoints.push({x: endX, y: endY});  // connect with details div
    }

    // Energize the details container
    detailsContainer.style.borderColor = activeColor;
    detailsContainer.style.boxShadow = `0 0 15px ${hexToRgba(activeColor, 0.5)}`;

    drawSvgLine(pathPoints, activeColor);
  }

  function drawSvgLine(pathPoints, activeColor) {
    if (activePath) activePath.remove();

    let pathString = `M ${pathPoints[0].x} ${pathPoints[0].y}`;
    
    // Draw straight lines for the routed path
    for (let i = 1; i < pathPoints.length; i++) {
      pathString += ` L ${pathPoints[i].x} ${pathPoints[i].y}`;
    }

    const path = document.createElementNS('http://www.w3.org/2000/svg', 'path');
    path.setAttribute('d', pathString);
    path.setAttribute('class', 'glow-line');
    path.setAttribute('stroke-linejoin', 'miter'); // Keep it looking like hardware
    path.setAttribute('stroke', activeColor);
    path.style.filter = `drop-shadow(0 0 5px ${activeColor})`;
    
    const circle = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
    circle.setAttribute('cx', pathPoints[0].x);
    circle.setAttribute('cy', pathPoints[0].y);
    circle.setAttribute('r', 4);
    circle.setAttribute('fill', '#ffffff');
    circle.setAttribute('class', 'glow-line');
    circle.setAttribute('stroke', activeColor);
    circle.style.filter = `drop-shadow(0 0 5px ${activeColor})`;

    const g = document.createElementNS('http://www.w3.org/2000/svg', 'g');
    g.appendChild(path);
    g.appendChild(circle);

    svgLayer.appendChild(g);
    activePath = g;

    // Calculate exact length for the CSS animation so it never cuts off
    const pathLength = path.getTotalLength();
    path.style.setProperty('--path-length', pathLength);
  }
});
