#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H
#include <pgmspace.h>
const char panel_html[] PROGMEM = R"nova_panel(<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
<meta name="theme-color" content="#131314">
<title>Rover Nova</title>
<style>
@font-face { font-family: Head; font-weight: 700; src: url(data:font/woff2;base64,d09GMgABAAAAAB1kABEAAAAAbTgAAB0DAAEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGlIbg3ocbAZgAIQ+CFIJnAwRCAqBmwyBh0QLgzYAATYCJAOGaAQgBYQuB4RMDIEyG41gBdwYumHjAMx4ikxRlCzW+pEI+yxJLSj4/5ogTcaaHHyzTmHq6bZgQYJ0IauSAAjTdrt8ampp+1YUBZlKxeeir33GUdj3Nl3n9jnhKDKP/tZ/t4tlV8t70dYzwF2EM3T0n2hb78/OLiFiY9RajVFYGJdmXBReRRT+f6rf7n15ZmSbqIVc7VYV9TedSpk4vzQuCT4iljUE36+xff+OoVmzRKJUzSLSRC0zZCJVLNJIlYRngOfTZnJRXViBr/wAaQN0gDIl7HNICkrnPRe1izKzXfW0x/Cs7fFNUEGZu06Iv5SFVa9TWprKxKUQsAvBNd53XqZB4b9pZrMJKVoyvg87TfVDSGH3jlcPTUlXouom7tbuXn2M8CcMeGAagYFoMvF4KGk6azB+CPP2kSJZtZZVcS9kEEmFFW9g52E6JFMRjoRwd2bXTFug5wVQYX4qjB0LMs4HRSU+vm/H+fZ/qpbtn8GSC11IkdvJbiMcY9G6acD5HI4GAxCPBMWoxLBJ3ERdpi4ABMiFwgVJF6W1s9Y5paKK/bmoXLUpdS7b1BSV4f+fq+m7f5mZigo5pX3nZbNOIDl2Eu0xNmd7LkT2/WX27GTKXEmhjmILRwghhHEY5vhru3sfy5WxudZfZwkRIDbYIrbXZ0HYmaTlUMqBW57PSvyMgTBaAAAkYxSIiChoEK1UxCgfKdUVOes8wUWXCAgBlIjorHPOxz97AqjJDKihZk4JlDgAZjMBEDbSGdhPtQEoAMmw+9PEBJJIrBE1gGJxLEbRFRpihJM3eVN/GooDiBLF4IgCRQk02oSJGpKJZGpIDcmlQUfsd2lJSSwy+AD8DYbv0fMR9eK15ILXnlI4Lo2mlaYYwEgXH7m/HHtWx6VJ2A/IhZ3w03u+6X5oQSlGeAmKr6WTRKOPSNFH2Fv0O2CRIyLxtOgttPGih1c94tpXskuxEtdFKLMmEosT8ySrbMzeQIB3l7h1dCi2U9nb+TDYuCt7XwFP2EMopf
@font-face { font-family: Body; src: url(data:font/woff2;base64,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
:root {
  --bg: #131314; --surface: #333336; --press: #45454a;
  --text: #ece4d2; --muted: #a39a89; --edge: #4a4a50; --button-edge: #0a0a0b;
  --bevel: inset 2px 2px 0 rgb(255 255 255 / .16), inset -2px -2px 0 rgb(0 0 0 / .4);
  --bevel-in: inset 2px 2px 0 rgb(0 0 0 / .4), inset -2px -2px 0 rgb(255 255 255 / .08);
  --signal: #db8a2e;
  --head: Head, ui-monospace, monospace; --body: Body, ui-monospace, monospace;
  --s1: 4px; --s2: 8px; --s3: 16px; --s4: 24px;
  color-scheme: dark;
}
* { box-sizing: border-box; }
html { -webkit-text-size-adjust: 100%; scrollbar-gutter: stable; }
body { margin: 0; background: var(--bg); color: var(--text); font: 22px/1.2 var(--body); -webkit-font-smoothing: none; -webkit-tap-highlight-color: transparent; }
main { max-width: 430px; margin: 0 auto; padding: var(--s3) var(--s3) calc(64px + var(--s4) + env(safe-area-inset-bottom)); }
#logo { display: block; width: calc(100% + var(--s3)); margin: 0 calc(-1 * var(--s2)) var(--s3); touch-action: pan-y; cursor: pointer; }
h2, #byline, #link { font: 700 16px/1.2 var(--head); }
h2 { font-size: 24px; letter-spacing: -1px; white-space: nowrap; }
#link { margin: 0 0 var(--s3); color: var(--signal); }
#link[hidden] { display: none; }
#byline { color: var(--muted); text-align: right; margin: calc(-1 * var(--s3)) 0 var(--s3); }
summary, .row { text-transform: uppercase; }
h2 { margin: 0 0 var(--s3); }
button, select { font: inherit; color: var(--text); background: var(--surface); border: 2px solid var(--button-edge); border-radius: 0; min-height: 48px; }
button { box-shadow: var(--bevel); text-transform: uppercase; padding: var(--s2); cursor: pointer; touch-action: manipulation; transition: background-color 80ms, border-color 80ms; }
button:active { background: var(--press); box-shadow: var(--bevel-in); }
#classic { display: block; margin-top: var(--s4); padding: var(--s3); text-align: center; text-transform: uppercase; color: var(--text); text-decoration: none; background: var(--surface); border: 2px solid var(--button-edge); box-shadow: var(--bevel); }
#classic:active { background: var(--press); box-shadow: var(--bevel-in); }
:focus-visible { outline: 2px solid var(--text); outline-offset: 2px; }
svg { shape-rendering: crispEdges; fill: currentColor; flex: none; }
svg.i { width: 16px; height: 16px; }
.grid { display: grid; gap: var(--s2); }
#screen { display: block; width: 100%; aspect-ratio: 2 / 1; image-rendering: pixelated; background: #000; border: 4px solid var(--edge); }
#places { grid-template-columns: 1fr 1fr; margin-top: var(--s3); }
#places button { height: 64px; }
#places .on, nav [aria-selected=true] { background: var(--signal); border-color: var(--signal); color: var(--bg); }
.stop { background: var(--text); border-color: var(--text); color: var(--bg); }
.stop:active { background: var(--muted); border-color: var(--muted); }
#halt { display: flex; align-items: center; justify-content: center; gap: var(--s2); width: 100%; margin-top: var(--s3); }
#move { grid-template-columns: repeat(3, 1fr); max-width: 248px; margin: var(--s4) auto 48px; }
#move button { height: 64px; display: flex; align-items: center; justify-content: center; }
#poses { grid-template-columns: repeat(3, 1fr); }
details { margin-top: var(--s4); border-top: 2px solid var(--edge); }
summary { padding: var(--s3) 0; cursor: pointer; }
.row { display: flex; align-items: center; gap: var(--s2); min-height: 64px; border-top: 2px solid var(--edge); }
.row > span:first-child { flex: 1; }
.step { display: flex; align-items: center; gap: var(--s1); }
.step button { width: 48px; padding: 0; border-color: transparent; background: none; box-shadow: none; font-size: 36px; line-height: 1; }
.step button:active { background: var(--press); border-color: transparent; box-shadow: none; }
.step output { width: 4ch; text-align: center; }
select { text-transform: uppercase; height: 48px; padding: 0 var(--s2); flex: 1; min-width: 0; }
#fade { position: fixed; left: 0; right: 0; bottom: calc(74px + env(safe-area-inset-bottom)); height: 48px; z-index: 1; pointer-events: none; background: linear-gradient(transparent, var(--bg)); transition: opacity 200ms; }
#fade.clear { opacity: 0; }
nav { position: fixed; bottom: 0; left: 0; right: 0; z-index: 2; background: var(--bg); border-top: 2px solid var(--edge); padding: var(--s2) var(--s3) calc(var(--s2) + env(safe-area-inset-bottom)); }
nav div { max-width: 398px; margin: 0 auto; display: grid; grid-template-columns: 1fr 1fr; gap: var(--s2); }
nav button:not([aria-selected=true]) { box-shadow: none; }
nav button { display: flex; flex-direction: column; align-items: center; justify-content: center; gap: var(--s1); height: 56px; padding: var(--s1); border-color: transparent; background: none; color: var(--muted); }
nav button svg.i { width: 20px; height: 20px; }
</style>
</head>
<body>
<main>
<canvas id="logo" role="img" aria-label="Rover Nova"></canvas>
<p id="byline">by James Street</p>
<p id="link" role="status" hidden>Not connected. Join the Nova-Controller Wi-Fi.</p>
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
  <a id="classic" href="/classic">Wi-Fi setup</a>
</section>
</main>
<div id="fade" aria-hidden="true"></div>
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
const LOGO = (() => {
  const GLYPHS = {
    R: [[[0, 16], [0, 0], [8, 0], [12, 4], [12, 5], [9, 8], [0, 8]], [[6, 8], [12, 16]]],
    O: [[[4, 0], [8, 0], [12, 4], [12, 12], [8, 16], [4, 16], [0, 12], [0, 4], [4, 0]]],
    V: [[[0, 0], [0, 8], [6, 16], [12, 8], [12, 0]]],
    E: [[[12, 0], [0, 0], [0, 16], [12, 16]], [[0, 8], [9, 8]]],
    N: [[[0, 16], [0, 0], [12, 16], [12, 0]]],
    A: [[[0, 16], [0, 5], [5, 0], [7, 0], [12, 5], [12, 16]], [[0, 10], [12, 10]]]
  };
  const S = 2, R = 3.5, GAP = 4, SPACE = 14, SLANT = 0.3, PAD = 14, DEPTH = 5;
  const gw = 12 * S + 2 * R, gh = 16 * S + 2 * R;
  const mask = new Set(), key = (x, y) => x + ',' + y;
  let pen = PAD;
  for (const ch of 'ROVER NOVA') {
    if (ch === ' ') { pen += SPACE; continue; }
    for (const path of GLYPHS[ch]) for (let k = 0; k + 1 < path.length; k++) {
      const [ax, ay] = path[k], [bx, by] = path[k + 1];
      for (let t = 0; t <= 1; t += 0.005) {
        const cx = pen + R + (ax + (bx - ax) * t) * S, cy = PAD + R + (ay + (by - ay) * t) * S;
        for (let yy = Math.ceil(cy - R); yy <= cy + R; yy++) {
          const shift = Math.round((PAD + gh - yy) * SLANT);
          for (let xx = Math.ceil(cx - R); xx <= cx + R; xx++) mask.add(key(xx + shift, yy));
        }
      }
    }
    pen += gw + GAP;
  }
  const W = Math.ceil(pen - GAP + gh * SLANT + PAD + DEPTH + 4), H = Math.ceil(PAD * 2 + gh + DEPTH + 2);
  const P = [...mask].map(k => k.split(',').map(Number));
  const has = (x, y) => mask.has(key(x, y));
  const x0 = Math.min(...P.map(p => p[0])), x1 = Math.max(...P.map(p => p[0]));
  const back = new Map(), body = new Set(mask);
  const SIDE = ['#3a1340', '#2a0e30', '#1d0a22', '#130716', '#0c050e'];
  for (let d = DEPTH; d >= 1; d--) P.forEach(([x, y]) => { back.set(key(x + d, y + d), SIDE[d - 1]); body.add(key(x + d, y + d)); });
  const N8 = [[-1, 0], [1, 0], [0, -1], [0, 1], [-1, -1], [1, 1], [1, -1], [-1, 1]];
  const ring = (src, inside) => {
    const out = new Set();
    src.forEach(k => { const [x, y] = k.split(',').map(Number); N8.forEach(([dx, dy]) => { if (!inside(key(x + dx, y + dy))) out.add(key(x + dx, y + dy)); }); });
    return out;
  };
  const o1 = ring(body, k => body.has(k)), o2 = ring(o1, k => body.has(k) || o1.has(k));
  const all = new Set([...body, ...o1, ...o2]);
  ring(o2, k => all.has(k)).forEach(k => back.set(k, '#fff4dc'));
  [...o1, ...o2].forEach(k => back.set(k, '#07030a'));
  const face = P.map(([x, y]) => {
    let edge = 0;
    if (!has(x, y - 1) || !has(x - 1, y)) edge = 1;                     
    else if (!has(x, y + 1) || !has(x + 1, y)) edge = 2;                
    else if (y - PAD > gh * 0.55 && y - PAD < gh * 0.6) edge = 1;       
    return { x, y, f: (x - x0) / (x1 - x0) * 0.85 + (y - PAD) / gh * 0.15, edge };
  });
  return { W, H, back, face, x1, top: PAD, bottom: PAD + gh };
})();
(() => {
  const canvas = $('logo'), c = canvas.getContext('2d');
  const { W, H } = LOGO;
  canvas.width = W; canvas.height = H;
  const img = c.createImageData(W, H), buf = new Uint32Array(img.data.buffer);
  const pack = hex => { const n = parseInt(hex.slice(1), 16); return 0xff000000 | (n & 0xff) << 16 | (n & 0xff00) | n >> 16; };
  const rgb = hex => { const n = parseInt(hex.slice(1), 16); return [n >> 16, n >> 8 & 255, n & 255]; };
  const BACK = new Uint32Array(W * H);
  LOGO.back.forEach((col, k) => { const [x, y] = k.split(',').map(Number); if (x >= 0 && x < W && y >= 0 && y < H) BACK[y * W + x] = pack(col); });
  const RUN = ['#2a6fdb', '#3f9bf0', '#7cc8ff', '#c46bd6', '#e8445a', '#f5682f', '#ff9a2a', '#ffc43d', '#ffe27a', '#fff6d6'];
  const LOOP = [...RUN, ...RUN.slice(1, -1).reverse()].map(rgb);
  const WHITE = [255, 255, 255];
  const mix = (a, b, t) => a.map((v, i) => v + (b[i] - v) * t);
  const toPx = ([r, g, b]) => 0xff000000 | (b & 255) << 16 | (g & 255) << 8 | (r & 255);
  const colourAt = (f, x, y) => {
    let p = ((f % 1) + 1) % 1 * LOOP.length, i = Math.floor(p);
    if (p - i > 0.55 && (x + y) % 2 === 0) i++;          
    return LOOP[i % LOOP.length];
  };
  const still = matchMedia('(prefers-reduced-motion: reduce)').matches;
  let offset = 0, burst = 0, pointer = null, last = 0;
  function draw() {
    buf.set(BACK);
    for (const p of LOGO.face) {
      let col;
      if (p.edge === 1) col = WHITE;
      else col = colourAt(p.f * 0.5 + offset - (p.edge === 2 ? 0.12 : 0), p.x, p.y);
      if (pointer !== null) {
        const d = Math.abs(p.x - pointer - (LOGO.bottom - p.y) * 0.3);
        if (d < 10) col = mix(col, WHITE, (1 - d / 10) * 0.7);
      }
      if (burst > 0) col = mix(col, WHITE, burst * 0.35);
      buf[p.y * W + p.x] = toPx(col);
    }
    const spark = (cx, cy, n) => {
      for (let i = n; i >= 1; i--) for (const [dx, dy] of [[i, 0], [-i, 0], [0, i], [0, -i]]) {
        const x = cx + dx, y = cy + dy;
        if (x >= 0 && x < W && y >= 0 && y < H) buf[y * W + x] = pack(i > n - 2 ? '#ffc43d' : '#ffffff');
      }
    };
    const grow = Math.round(burst * 4);
    spark(LOGO.x1 - 1, LOGO.top - 3, 9 + grow);
    spark(LOGO.x1 - 20, LOGO.bottom + 4, 5 + grow);
    c.putImageData(img, 0, 0);
  }
  function frame(now) {
    const dt = Math.min(0.1, (now - last) / 1000 || 0);
    if (now - last >= 50) {                                
      last = now;
      if (!still) offset += dt * 0.05 + burst * dt * 1.6;
      burst = Math.max(0, burst - dt * 1.7);
      draw();
    }
    if (!document.hidden) requestAnimationFrame(frame);
  }
  document.addEventListener('visibilitychange', () => { if (!document.hidden) requestAnimationFrame(frame); });
  const toGrid = e => { const r = canvas.getBoundingClientRect(); return (e.clientX - r.left) / r.width * W; };
  canvas.addEventListener('pointermove', e => { pointer = toGrid(e); if (still) draw(); });
  ['pointerleave', 'pointerup', 'pointercancel'].forEach(t => canvas.addEventListener(t, () => { pointer = null; if (still) draw(); }));
  canvas.addEventListener('pointerdown', e => {
    pointer = toGrid(e);
    burst = 1;
    if (still) { offset += 0.25; burst = 0; draw(); }
  });
  draw();
  if (!still) requestAnimationFrame(frame);
})();
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
function request(path) {
  const ctl = new AbortController(), t = setTimeout(() => ctl.abort(), 4000);
  return fetch(ROBOT + path, { signal: ctl.signal })
    .then(r => { if (!r.ok) throw new Error('HTTP ' + r.status); setLink(true); return r; })
    .catch(e => { setLink(false); throw e; })
    .finally(() => clearTimeout(t));
}
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
  request(path).catch(() => {
    if (name === 'pose' || name === 'go') { state.command = ''; stopPlayback(); }
  });
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
const STEPS = {};
document.querySelectorAll('.step').forEach(el => {
  const key = el.dataset.key, min = +el.dataset.min, max = +el.dataset.max, inc = +(el.dataset.inc || 1);
  const out = el.querySelector('output');
  let v = parseInt(out.textContent, 10), wait = null;
  const [less, more] = el.querySelectorAll('button');
  const show = n => { v = Math.max(min, Math.min(max, n)); out.textContent = v; };
  const bump = dir => {
    show(v + dir * inc);
    if (key === 'motorAngle') { state.motorAngle = v; return; }
    clearTimeout(wait);
    wait = setTimeout(() => sendCommand('setting', { key, value: v }), 300);
  };
  less.onclick = () => bump(-1);
  more.onclick = () => bump(1);
  STEPS[key] = show;
});
request('/getSettings').then(r => r.json()).then(s => {
  Object.keys(s).forEach(k => { if (STEPS[k]) STEPS[k](s[k]); });
}).catch(() => {});
for (let m = 1; m <= 8; m++) $('motor-num').add(new Option('Motor ' + m, m));
$('motor-set').onclick = () => sendCommand('motor', { motor: +$('motor-num').value, angle: state.motorAngle });
function showTab(name) {
  document.querySelectorAll('nav button').forEach(b => b.setAttribute('aria-selected', b.dataset.tab === name));
  document.querySelectorAll('main section').forEach(s => { s.hidden = s.id !== 'tab-' + name; });
  try { localStorage.setItem('tab', name); } catch (e) {}
}
document.querySelectorAll('nav button').forEach(b => { b.onclick = () => { showTab(b.dataset.tab); scrollTo(0, 0); updateFade(); }; });
function updateFade() {
  const el = document.scrollingElement;
  $('fade').classList.toggle('clear', el.scrollTop + innerHeight >= el.scrollHeight - 2);
}
addEventListener('scroll', updateFade, { passive: true });
addEventListener('resize', updateFade);
document.querySelector('details').addEventListener('toggle', updateFade);
let first = location.hash.slice(1);
try { first = first || localStorage.getItem('tab'); } catch (e) {}
showTab(first === 'robot' ? 'robot' : 'space');
updateFade();
$('classic').href = ROBOT + '/classic';
</script>
</body>
</html>
)nova_panel";
#endif