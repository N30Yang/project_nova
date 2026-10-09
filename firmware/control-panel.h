#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H
#include <pgmspace.h>
const char panel_html[] PROGMEM = R"nova_panel(<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
<meta name="theme-color" content="#11151c">
<title>Rover Nova</title>
<style>
@font-face { font-family: Px; src: url(data:font/woff2;base64,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
:root { --bg: #11151c; --raise: #181e27; --line: #2b3340; --text: #e7e2d7; --dim: #9ba1aa; --acc: #d8a24a; --stop: #d47a62; color-scheme: dark; }
* { box-sizing: border-box; }
html { -webkit-text-size-adjust: 100%; }
body { margin: 0; background: var(--bg); color: var(--text); font: 16px/1.5 Px, ui-monospace, monospace; -webkit-font-smoothing: none; -webkit-tap-highlight-color: transparent; }
main { max-width: 430px; margin: 0 auto; padding: 0 16px; }
h2 { font-size: 16px; font-weight: normal; margin: 20px 0 12px; }
main { padding-bottom: 96px; }
button { font: inherit; color: var(--text); background: var(--raise); border: 2px solid var(--line); border-radius: 0; padding: 8px; min-height: 48px; cursor: pointer; touch-action: manipulation; transition: background-color 80ms, border-color 80ms; }
button:active { background: #232b37; border-color: #4b5667; }
:focus-visible { outline: 2px solid var(--acc); outline-offset: 2px; }
a { color: var(--acc); }
#link { margin: 12px 0 0; padding: 8px; color: var(--stop); border: 2px solid #5c3a33; }
svg { shape-rendering: crispEdges; fill: currentColor; flex: none; }
svg.i { width: 16px; height: 16px; }
.grid { display: grid; gap: 4px; }
#screen { display: block; width: 100%; aspect-ratio: 2 / 1; image-rendering: pixelated; background: #000; border: 2px solid var(--line); }
#places { grid-template-columns: 1fr 1fr; margin-top: 12px; }
#places button { height: 64px; }
#places .on { border-color: var(--acc); color: var(--acc); }
.stop { color: var(--stop); border-color: #5c3a33; }
#halt { display: flex; align-items: center; justify-content: center; gap: 8px; width: 100%; margin-top: 4px; }
#move { grid-template-columns: repeat(3, 1fr); max-width: 260px; margin: 24px auto; }
#move button { height: 64px; }
#poses { grid-template-columns: repeat(3, 1fr); }
details { margin-top: 24px; border-top: 2px solid var(--line); }
summary { padding: 14px 0; cursor: pointer; }
.row { display: flex; align-items: center; gap: 12px; min-height: 52px; border-top: 2px solid var(--line); }
.row > span:first-child { flex: 1; }
.step { display: flex; align-items: center; }
.step button { width: 44px; padding: 0; }
.step output { width: 4ch; text-align: center; }
select { font: inherit; color: var(--text); background: var(--raise); border: 2px solid var(--line); border-radius: 0; height: 48px; padding: 0 8px; flex: 1; min-width: 0; }
nav { position: fixed; bottom: 0; left: 0; right: 0; z-index: 2; background: var(--bg); border-top: 2px solid var(--line); padding-bottom: env(safe-area-inset-bottom); }
nav div { max-width: 430px; margin: 0 auto; display: grid; grid-template-columns: 1fr 1fr; }
nav button { border: 0; background: none; display: flex; flex-direction: column; align-items: center; gap: 4px; height: 64px; color: var(--dim); }
nav button svg.i { width: 24px; height: 24px; }
nav [aria-selected=true] { color: var(--acc); }
</style>
</head>
<body>
<main>
<p id="link" role="status" hidden>Robot not connected. Join the Nova-Controller Wi-Fi, then try again.</p>
<section id="tab-space">
  <h2>My place in space:</h2>
  <canvas id="screen" width="128" height="64" aria-label="Nova's screen"></canvas>
  <div class="grid" id="places"></div>
  <button class="stop" id="halt"><i data-icon="stop"></i>Stop</button>
</section>
<section id="tab-robot" hidden>
  <div class="grid" id="move">
    <span></span><button data-go="forward" aria-label="Forward"><i data-icon="up"></i></button><span></span>
    <button data-go="left" aria-label="Left"><i data-icon="left"></i></button><button class="stop" data-stop aria-label="Stop"><i data-icon="stop"></i></button><button data-go="right" aria-label="Right"><i data-icon="right"></i></button>
    <span></span><button data-go="backward" aria-label="Back"><i data-icon="down"></i></button><span></span>
  </div>
  <div class="grid" id="poses"></div>
  <details>
    <summary>Tuning</summary>
    <div class="row"><span>Frame delay</span><div class="step" data-key="frameDelay" data-min="10" data-max="1000" data-inc="10"><button aria-label="Less">-</button><output>100</output><button aria-label="More">+</button></div></div>
    <div class="row"><span>Walk cycles</span><div class="step" data-key="walkCycles" data-min="1" data-max="50"><button aria-label="Less">-</button><output>10</output><button aria-label="More">+</button></div></div>
    <div class="row"><span>Motor delay</span><div class="step" data-key="motorCurrentDelay" data-min="0" data-max="200" data-inc="5"><button aria-label="Less">-</button><output>20</output><button aria-label="More">+</button></div></div>
    <div class="row"><span>Face fps</span><div class="step" data-key="faceFps" data-min="1" data-max="30"><button aria-label="Less">-</button><output>8</output><button aria-label="More">+</button></div></div>
    <div class="row"><select id="motor-num" aria-label="Motor"></select>
      <div class="step" data-key="motorAngle" data-min="0" data-max="180" data-inc="10"><button aria-label="Less">-</button><output>90</output><button aria-label="More">+</button></div>
      <button id="motor-set">Set</button></div>
  </details>
  <p><a id="classic" href="/classic">Wi-Fi settings and classic controls</a></p>
</section>
</main>
<nav><div role="tablist">
  <button role="tab" data-tab="space"><i data-icon="planet"></i>Space</button>
  <button role="tab" data-tab="robot"><i data-icon="robot"></i>Robot</button>
</div></nav>
<script>
const TIMELINE = {"moon":[[0,"excited"],[3356,"excited"],[9686,"stand"],[9846,"end"]],"mars":[[0,"surprised"],[1680,"sad"],[8245,"stand"],[8405,"end"]],"earth":[[0,"happy"],[1020,"happy"],[8640,"stand"],[8800,"end"]],"jupiter":[[0,"angry"],[6644,"sleepy"],[11477,"stand"],[11885,"end"]]};
const FACES = {"excited":"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA+AAAAAAAAAAAAAAAAAPAAPAAAAAAAAAAAAAAAAAB4AHwAAAAAAAAAAAAAAAAAfAB4AAAAAAAAAAAAAAAAADwA+AAAAAAAAAAAAAAAAAA+APAAAAAAAAAAAAAAAAAAHgHwAAAAAAAAAAAAAAAAAB8B8AAAAAAAAAAAAAAAAAAfAeAAAAAAAAAAAAAAAAAADwHgAAAAAAAAAAAAAAAAAA8D4AAAP+AAAAAAAAAAAAAPA+AAAD/gAAAAAAAP+AAAD4PgAAA/4AAAAAAAD/gAAA+D4AAAP+AAAAAAAA/4AAAPg+AAAB/AAOA4HAAH8AAAD4PgAAAPgADgOBwAA+AAAA+D4AAAAAAA4DgcAAAAAAAPg+AAAAAAAOA4HAAAAAAAD4PgAAA4AADweBwADAAAAA8B4AAAP+AAcHwcAA/wAAAPAfAAAAAAAHj8PAAAAAAAHwHwAAAAAAA///gAAAAAAB8A8AAAAAAAH8fwAAAAAAAeAPgAAAAAAADnAAAAAAAAPgD4AAAAAAAA/wAAAAAAADwAfAAAAAAAAAAAAAAAAAB8ADwAAAAAAAAAAAAAAAAAeAA+AAAAAAAAAAAAAAAAAPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==","surprised":"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA+AAAAAAAAAAAAAAAAAPAAPAAAAAAAAAAAAAAAAAB4AHwAAAAAAAAAAAAAAAAAfAB4AAAAAAAAAAAAAAAAADwA+AAAAAAAAAAAAAAAAAA+APAAAAAAAAAAAAAAAAAAHgHwAAAAAAAAAAAAAAAAAB8B8AAAAAAAAAAAAAAAAAAfAeAAAAAAAAAAAAAAAAAADwHgAAAAAAAAAAAAAAAAAA8D4AAAP+AAAAAAAAAAAAAPA+AAAD/gAAAAAAAP+AAAD4PgAAA/4AAAAAAAD/gAAA+D4AAAP+AAAAAAAA/4AAAPg+AAAB/AAOA4HAAH8AAAD4PgAAAPgADgOBwAA+AAAA+D4AAAAAAA4DgcAAAAAAAPg+AAAAAAAOA4HAAAAAAAD4PgAAA4AADweBwADAAAAA8B4AAAP+AAcHwcAA/wAAAPAfAAAAAAAHj8PAAAAAAAHwHwAAAAAAA///gAAAAAAB8A8AAAAAAAH8fwAAAAAAAeAPgAAAAAAADnAAAAAAAAPgD4AAAAAAAA/wAAAAAAADwAfAAAAAAAAAAAAAAAAAB8ADwAAAAAAAAAAAAAAAAAeAA+AAAAAAAAAAAAAAAAAPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==","sad":"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA+AAAAAAAAAAAAAAAAAPAAPAAAAAAAAAAAAAAAAAB4AHwAAAAAAAAAAAAAAAAAfAB4AAAAAAAAAAAAAAAAADwA+AAAAAAAAAAAAAAAAAA+APAAAAAAAAAAAAAAAAAAHgHwAAAAAAAAAAAAAAAAAB8B8AAAAAAAAAAAAAAAAAAfAeAAAAAAAAAAAAAAAAAADwHgAAAAAAAAAAAAAAAAAA8D4AAAP+AAAAAAAAAAAAAPA+AAAD/gAAAAAAAP+AAAD4PgAAA/4AAAAAAAD/gAAA+D4AAAP+AAAAAAAA/4AAAPg+AAAB/AAOA4HAAH8AAAD4PgAAAPgADgOBwAA+AAAA+D4AAAAAAA4DgcAAAAAAAPg+AAAAAAAOA4HAAAAAAAD4PgAAA4AADweBwADAAAAA8B4AAAP+AAcHwcAA/wAAAPAfAAAAAAAHj8PAAAAAAAHwHwAAAAAAA///gAAAAAAB8A8AAAAAAAH8fwAAAAAAAeAPgAAAAAAADnAAAAAAAAPgD4AAAAAAAA/wAAAAAAADwAfAAAAAAAAAAAAAAAAAB8ADwAAAAAAAAAAAAAAAAAeAA+AAAAAAAAAAAAAAAAAPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==","happy":"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA+AAAAAAAAAAAAAAAAAPAAPAAAAAAAAAAAAAAAAAB4AHwAAAAAAAAAAAAAAAAAfAB4AAAAAAAAAAAAAAAAADwA+AAAAAAAAAAAAAAAAAA+APAAAAAAAAAAAAAAAAAAHgHwAAAAAAAAAAAAAAAAAB8B8AAAAAAAAAAAAAAAAAAfAeAAAAAAAAAAAAAAAAAADwHgAAAAAAAAAAAAAAAAAA8D4AAAP+AAAAAAAAAAAAAPA+AAAD/gAAAAAAAP+AAAD4PgAAA/4AAAAAAAD/gAAA+D4AAAP+AAAAAAAA/4AAAPg+AAAB/AAOA4HAAH8AAAD4PgAAAPgADgOBwAA+AAAA+D4AAAAAAA4DgcAAAAAAAPg+AAAAAAAOA4HAAAAAAAD4PgAAA4AADweBwADAAAAA8B4AAAP+AAcHwcAA/wAAAPAfAAAAAAAHj8PAAAAAAAHwHwAAAAAAA///gAAAAAAB8A8AAAAAAAH8fwAAAAAAAeAPgAAAAAAADnAAAAAAAAPgD4AAAAAAAA/wAAAAAAADwAfAAAAAAAAAAAAAAAAAB8ADwAAAAAAAAAAAAAAAAAeAA+AAAAAAAAAAAAAAAAAPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==","angry":"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA+AAAAAAAAAAAAAAAAAPAAPAAAAAAAAAAAAAAAAAB4AHwAAAAAAAAAAAAAAAAAfAB4AAAAAAAAAAAAAAAAADwA+AAAAAAAAAAAAAAAAAA+APAAAAAAAAAAAAAAAAAAHgHwAAAAAAAAAAAAAAAAAB8B8AAAAAAAAAAAAAAAAAAfAeAAAAAAAAAAAAAAAAAADwHgAAAAAAAAAAAAAAAAAA8D4AAAP+AAAAAAAAAAAAAPA+AAAD/gAAAAAAAP+AAAD4PgAAA/4AAAAAAAD/gAAA+D4AAAP+AAAAAAAA/4AAAPg+AAAB/AAOA4HAAH8AAAD4PgAAAPgADgOBwAA+AAAA+D4AAAAAAA4DgcAAAAAAAPg+AAAAAAAOA4HAAAAAAAD4PgAAA4AADweBwADAAAAA8B4AAAP+AAcHwcAA/wAAAPAfAAAAAAAHj8PAAAAAAAHwHwAAAAAAA///gAAAAAAB8A8AAAAAAAH8fwAAAAAAAeAPgAAAAAAADnAAAAAAAAPgD4AAAAAAAA/wAAAAAAADwAfAAAAAAAAAAAAAAAAAB8ADwAAAAAAAAAAAAAAAAAeAA+AAAAAAAAAAAAAAAAAPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==","sleepy":"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA+AAAAAAAAAAAAAAAAAPAAPAAAAAAAAAAAAAAAAAB4AHwAAAAAAAAAAAAAAAAAfAB4AAAAAAAAAAAAAAAAADwA+AAAAAAAAAAAAAAAAAA+APAAAAAAAAAAAAAAAAAAHgHwAAAAAAAAAAAAAAAAAB8B8AAAAAAAAAAAAAAAAAAfAeAAAAAAAAAAAAAAAAAADwHgAAAAAAAAAAAAAAAAAA8D4AAAP+AAAAAAAAAAAAAPA+AAAD/gAAAAAAAP+AAAD4PgAAA/4AAAAAAAD/gAAA+D4AAAP+AAAAAAAA/4AAAPg+AAAB/AAOA4HAAH8AAAD4PgAAAPgADgOBwAA+AAAA+D4AAAAAAA4DgcAAAAAAAPg+AAAAAAAOA4HAAAAAAAD4PgAAA4AADweBwADAAAAA8B4AAAP+AAcHwcAA/wAAAPAfAAAAAAAHj8PAAAAAAAHwHwAAAAAAA///gAAAAAAB8A8AAAAAAAH8fwAAAAAAAeAPgAAAAAAADnAAAAAAAAPgD4AAAAAAAA/wAAAAAAADwAfAAAAAAAAAAAAAAAAAB8ADwAAAAAAAAAAAAAAAAAeAA+AAAAAAAAAAAAAAAAAPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=="};
const PLACES = [['moon', 'Moon'], ['mars', 'Mars'], ['earth', 'Earth'], ['jupiter', 'Jupiter']];
const POSES = ['rest', 'stand', 'wave', 'dance', 'swim', 'point', 'pushup', 'bow',
  'cute', 'freaky', 'worm', 'shake', 'shrug', 'dead', 'crab'];
const ICONS = {
  up:    ['...##...', '..####..', '.######.', '########', '...##...', '...##...', '...##...', '...##...'],
  stop:  ['........', '.######.', '.######.', '.######.', '.######.', '.######.', '.######.', '........'],
  planet:['..####..', '.#....#.', '#..##..#', '#.####.#', '#.####.#', '#..##..#', '.#....#.', '..####..'],
  robot: ['....#...', '..####..', '.######.', '.#.##.#.', '.######.', '..#..#..', '.##..##.', '........']
};
ICONS.down = [...ICONS.up].reverse();
ICONS.left = ICONS.up.map((_, y) => ICONS.up.map(row => row[y]).join(''));
ICONS.right = ICONS.left.map(row => [...row].reverse().join(''));
const SVG = 'http://www.w3.org/2000/svg';
function pixelSvg(rows, cls) {
  const s = document.createElementNS(SVG, 'svg');
  s.setAttribute('viewBox', '0 0 ' + rows[0].length + ' ' + rows.length);
  s.setAttribute('aria-hidden', 'true');
  if (cls) s.setAttribute('class', cls);
  rows.forEach((row, y) => [...row].forEach((ch, x) => {
    if (ch === '.') return;
    const r = document.createElementNS(SVG, 'rect');
    r.setAttribute('x', x); r.setAttribute('y', y);
    r.setAttribute('width', 1); r.setAttribute('height', 1);
    s.appendChild(r);
  }));
  return s;
}
document.querySelectorAll('i[data-icon]').forEach(i => i.replaceWith(pixelSvg(ICONS[i.dataset.icon], 'i')));
const state = { command: '', settings: {}, motors: {}, motorAngle: 90 };
const $ = id => document.getElementById(id);
const ROBOT = location.protocol === 'file:' ? 'http://192.168.4.1' : '';
function robotPath(name, value) {
  switch (name) {
    case 'go':      return '/cmd?go=' + encodeURIComponent(value);
    case 'pose':    return '/cmd?pose=' + encodeURIComponent(value);
    case 'stop':    return '/cmd?stop=1';
    case 'setting': return '/setSettings?' + encodeURIComponent(value.key) + '=' + encodeURIComponent(value.value);
    case 'motor':   return '/cmd?motor=' + value.motor + '&value=' + value.angle;
  }
  return null;
}
function setLink(ok) { $('link').hidden = ok; }
function sendCommand(name, value) {
  switch (name) {
    case 'go': case 'pose': state.command = value; break;
    case 'stop': state.command = ''; break;
    case 'setting': state.settings[value.key] = value.value; break;
    case 'motor': state.motors[value.motor] = value.angle; break;
  }
  if (TIMELINE[state.command]) play(state.command);
  else if (name !== 'setting' && name !== 'motor') stopPlayback();
  const path = robotPath(name, value);
  if (!path) return;
  fetch(ROBOT + path)
    .then(r => { if (!r.ok) throw new Error('HTTP ' + r.status); setLink(true); })
    .catch(() => setLink(false));
}
const ctx = $('screen').getContext('2d');
const img = ctx.createImageData(128, 64);
function showFace(name) {
  const bits = atob(FACES[name]);
  for (let p = 0; p < 128 * 64; p++) {
    const on = bits.charCodeAt(p >> 3) & (0x80 >> (p & 7));
    img.data.set(on ? [235, 235, 235, 255] : [0, 0, 0, 255], p * 4);
  }
  ctx.putImageData(img, 0, 0);
}
ctx.fillRect(0, 0, 128, 64);
let timer = null, playing = '';
function play(cmd) {
  stopPlayback();
  playing = cmd;
  const start = performance.now(), events = TIMELINE[cmd];
  let shown = '';
  const tick = () => {
    const t = performance.now() - start;
    let face = shown;
    for (const [at, name] of events) if (at <= t && FACES[name]) face = name;
    if (face !== shown) showFace(shown = face);
    if (t >= events[events.length - 1][0]) {
      if (state.command === cmd) state.command = '';
      stopPlayback();
    }
  };
  timer = setInterval(tick, 50);
  tick();
  markPlace();
}
function stopPlayback() {
  clearInterval(timer);
  playing = '';
  markPlace();
}
function markPlace() {
  document.querySelectorAll('#places button').forEach(b => b.classList.toggle('on', b.dataset.cmd === playing));
}
PLACES.forEach(([cmd, name]) => {
  const b = document.createElement('button');
  b.dataset.cmd = cmd;
  b.textContent = name;
  b.onclick = () => sendCommand('pose', cmd);
  $('places').appendChild(b);
});
POSES.forEach(n => {
  const b = document.createElement('button');
  b.textContent = n;
  b.onclick = () => sendCommand('pose', n);
  $('poses').appendChild(b);
});
document.querySelectorAll('[data-go]').forEach(b =>
  b.onclick = () => sendCommand('go', b.dataset.go));
document.querySelectorAll('[data-stop], #halt').forEach(b => { b.onclick = () => sendCommand('stop'); });
document.querySelectorAll('.step').forEach(el => {
  const key = el.dataset.key, min = +el.dataset.min, max = +el.dataset.max, inc = +(el.dataset.inc || 1);
  const out = el.querySelector('output');
  let v = parseInt(out.textContent, 10);
  const [less, more] = el.querySelectorAll('button');
  const bump = dir => {
    v = Math.max(min, Math.min(max, v + dir * inc));
    out.textContent = v;
    if (key === 'motorAngle') state.motorAngle = v;
    else sendCommand('setting', { key, value: v });
  };
  less.onclick = () => bump(-1);
  more.onclick = () => bump(1);
});
for (let m = 1; m <= 8; m++) $('motor-num').add(new Option('Motor ' + m, m));
$('motor-set').onclick = () => sendCommand('motor', { motor: +$('motor-num').value, angle: state.motorAngle });
function showTab(name) {
  document.querySelectorAll('nav button').forEach(b => b.setAttribute('aria-selected', b.dataset.tab === name));
  document.querySelectorAll('main section').forEach(s => { s.hidden = s.id !== 'tab-' + name; });
  try { localStorage.setItem('tab', name); } catch (e) {}
}
document.querySelectorAll('nav button').forEach(b => { b.onclick = () => { showTab(b.dataset.tab); scrollTo(0, 0); }; });
let first = location.hash.slice(1);
try { first = first || localStorage.getItem('tab'); } catch (e) {}
showTab(first === 'robot' ? 'robot' : 'space');
$('classic').href = ROBOT + '/classic';
</script>
</body>
</html>
)nova_panel";
#endif