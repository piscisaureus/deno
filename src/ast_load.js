const assert = require("assert");
const { readFileSync } = require("fs");
const { inspect } = require("util");
const astClass = require("./ast_class_gen.js");

Object.assign(inspect.defaultOptions, { maxArrayLength: null, depth: null });

const astJson = readFileSync("../ast.json", "utf8");
const astNodeMap = new Map();

const { isArray } = Array;

function isObject(value) {
  return typeof value === "object" && value !== null && !isArray(value);
}

function isNodeId(value) {
  return typeof value === "string" && /^0x[0-9a-f]+$/.test(value);
}

function merge(target, source, active = new Set()) {
  if (active.has(target)) return;
  active.add(target);

  for (const [key, sourceValue] of Object.entries(source)) {
    const targetValue = target[key];
    if (targetValue === undefined) {
      target[key] = sourceValue;
    } else if (isArray(sourceValue)) {
      assert(isArray(targetValue));
      merge(targetValue, sourceValue, active);
    } else if (isObject(sourceValue)) {
      assert(isObject(targetValue));
      merge(targetValue, sourceValue, active);
    } else {
      assert.strictEqual(sourceValue, targetValue);
    }
  }
}

function getOrCreateNode(idOrInfo) {
  const { id, kind, ...props } = isObject(idOrInfo)
    ? idOrInfo
    : isNodeId(idOrInfo)
    ? { id: idOrInfo }
    : assert.fail("Invalid argument", idOrInfo);

  if (id === "0x0") {
    assert.deepStrictEqual(props, {});
    return null;
  }

  let node = astNodeMap.get(id);
  if (!node) astNodeMap.set(id, (node = {}));

  if (kind) {
    const Class = astClass[kind];
    assert.strictEqual(typeof Class, "function");
    if (!(node instanceof Class)) Object.setPrototypeOf(node, Class.prototype);
  }

  merge(node, props);

  return node;
}

const keyMap = new Map();

function revive(key, value) {
  if (isObject(value) && value.kind === "CompoundStmt") return;

  if (isObject(value) && isNodeId(value.id)) return getOrCreateNode(value);

  if (key !== "id" && isNodeId(value)) {
    // Id reference info tracking.
    let ids = keyMap.get(key);
    if (!ids) keyMap.set(key, (ids = new Set()));
    ids.add(value);
    // End id info tracking.

    return getOrCreateNode(value);
  }

  if (key === "loc" || key === "range") return;

  if (isObject(value)) {
    for (const [k, v] of Object.entries(value)) {
      const m = /^(.*)Id/.test(k);
      if (!m) continue;
      const k2 = m[1];
      assert(!(k2 in value));
      delete value[k];
      value[k2] = v;
    }
  }

  return value;
}

function dumpIdReferenceInfo() {
  for (const [key, ids] of keyMap.entries()) {
    const kinds = Object.create(null);
    for (const id of ids.values()) {
      const kind = astNodeMap.get(id).kind || "Unknown " + id;
      if (kind in kinds) {
        kinds[kind]++;
      } else {
        kinds[kind] = 1;
      }
    }
    console.log(key);
    for (const [kind, count] of Object.entries(kinds)) {
      console.log("  %s: %d", kind, count);
    }
  }
}

const ast = JSON.parse(astJson, revive);
//dumpIdReferenceInfo()
console.log(ast);
