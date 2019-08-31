const assert = require("assert");
const { readFileSync } = require("fs");
const { inspect } = require("util");
const astClass = require("./ast_class_gen.js");

Object.assign(inspect.defaultOptions, { maxArrayLength: null, depth: null });

const astJson = readFileSync("../ast.json", "utf8");
const astNodeMap = new Map();

function isObject(value) {
  return typeof value === "object" && value !== null;
}

function merge(target, source, active = new Set()) {
  if (active.has(target)) return;
  active.add(target);

  for (const [key, sourceValue] of Object.entries(source)) {
    const targetValue = target[key];
    if (targetValue === undefined) {
      target[key] = sourceValue;
    } else if (isObject(sourceValue)) {
      assert(isObject(targetValue));
      merge(targetValue, sourceValue, active);
    } else {
      assert.strictEqual(sourceValue, targetValue);
    }
  }
}

function isNodeId(value) {
  return typeof value === "string" && /^0x[0-9a-f]+$/.test(value);
}

function getOrCreateNode(id, props) {
  if (id === "0x0") {
    if (props !== undefined) assert.deepStrictEqual(props, { id: "0x0" });
    return null;
  }

  let node = astNodeMap.get(id);
  if (!node) {
    assert(isObject(props));
    const Class = astClass[props.kind];
    assert.strictEqual(typeof Class, "function");
    node = Object.assign(new Class(), props);
    astNodeMap.set(id, node);
  } else if (props !== undefined) {
    assert(isObject(props));
    merge(node, props);
  }

  return node;
}

function revive(key, value) {
  if (isObject(value) && isNodeId(value.id))
    return getOrCreateNode(value.id, value);

  return value;
}

const ast = JSON.parse(astJson, revive);
console.log(ast);
