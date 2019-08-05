const { readFileSync, writeFileSync } = require("fs");
const { execFileSync } = require("child_process");

const enable = l => l.replace(/^\/\/\s*/g, "");
const disable = l => `// ${enable(l)}`;
const isDisabled = l => /^\/\//.test(l);
const isEnabled = l => !isDisabled(l);

function tryOut() {
  try {
    execFileSync(
      "clang-cl",
      [
        "/std:c++17",
        "/D_ITERATOR_DEBUG_LEVEL=0",
        "v8.cpp",
        "D:/deno2/target/debug/obj/core/libdeno/libdeno.lib",
        "-fuse-ld=lld-link",
        "/MTd",
        "/link",
        "winmm.lib"
      ],
      { stdio: ["ignore", "pipe", "pipe"], encoding: "utf-8" }
    );
    return [true, null];
  } catch (err) {
    return [false, err];
  }
}

/* Simple impl. */
function simple() {
  let lines = readFileSync("o2.h", "utf8").split(/\r?\n/);

  for (i = 0; i < lines.length; i++) {
    let l = lines[i];
    let enabled_l = enable(l);
    if (enabled_l === l) continue;
    console.log(i, enabled_l);
    lines[i] = enabled_l;
    writeFileSync("o2.h", lines.join("\n"));
    writeFileSync("o3.h", enabled_l);
    let [passed, err] = tryOut();
    if (passed) {
      console.log(i, "ok!");
    } else {
      console.log(err.stderr);
      console.log(i, "no!");
      lines[i] = disable(lines[i]);
    }
  }
}

/* Simple impl. */
function advanced() {
  let lines = readFileSync("o2.h", "utf8").split(/\r?\n/);

  let unevaluated_line_entries = Object.entries(lines)
    .filter(([num, l]) => isDisabled(l))
    .map(([num, l]) => [num, enable(l)]);
  let batch_size = 1;

  while (unevaluated_line_entries.length > 0) {
    const batch_line_entries = unevaluated_line_entries.slice(0, batch_size);
    const batch_lines = batch_line_entries.map(([num, l]) => l);

    writeFileSync("o3.h", batch_lines.join("\n"));

    const [passed, err] = tryOut();

    if (!passed && batch_size > 1) {
      batch_size = 1;
      continue;
    }

    unevaluated_line_entries.splice(0, batch_line_entries.length);

    if (passed) {
      batch_size *= 2;
      for (const [num, line] of batch_line_entries) {
        console.log(`pass! ${num}: ${line}`);
        lines[num] = line;
      }
      writeFileSync("o2.h", lines.join("\n"));
    } else {
      console.log(err.stderr);
      for (const [num, line] of batch_line_entries) {
        console.log(`fail! ${num}: ${line}`);
      }
    }
  }
}

advanced();
