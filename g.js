const { readFileSync, writeFileSync } = require('fs');
const { execFileSync } = require('child_process');

const enable = l =>  l.replace(/^\/\/\s*/g, '');
const disable = l =>  `// ${l}`

let lines = readFileSync('o2.h', 'utf8').split(/\r?\n/);
//lines = lines.map(enable).map(disable);


for (i = 0; i < lines.length; i++) {
  let l = lines[i];
  let enabled_l = enable(l);
  if (enabled_l === l) continue;
  console.log(i, enabled_l);
  lines[i] = enabled_l;
  writeFileSync('o2.h', lines.join('\n'));
  writeFileSync('o3.h', enabled_l);
  try { 
    let r = execFileSync('clang-cl', ['/std:c++17', '/D_ITERATOR_DEBUG_LEVEL=0', 'v8.cpp', 'D:/deno2/target/debug/obj/core/libdeno/libdeno.lib', '-fuse-ld=lld-link', '/MTd', '/link', 'winmm.lib']);
    console.log(i, "ok!");
  } catch (e) {
    console.log(i, "no!");
    lines[i] = disable(lines[i]);
  }
}