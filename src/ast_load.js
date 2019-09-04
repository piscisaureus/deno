const assert = require("assert");
const { inspect } = require("util");
const { readFileSync } = require("fs");

const astClass = require("./ast_class_gen.js");

exports.fromJsonString = fromJsonString;
exports.fromFile = fromFile;
exports.dump = dump;

const { isArray } = Array;

function isObject(value) {
  return typeof value === "object" && value !== null && !isArray(value);
}

function isString(value) {
  return typeof value === "string";
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

function fromJsonString(jsonString) {
  const astNodeMap = new Map();

  function getOrCreateNode(idOrInfo) {
    assert(isObject(idOrInfo) || isNodeId(idOrInfo));
    const { kind, ...props } = isObject(idOrInfo) ? idOrInfo : { id: idOrInfo };
    const { id } = props;

    let node;
    if (id === "0x0") {
      assert.deepStrictEqual(props, { id });
      return null;
    } else if (id !== undefined) {
      node = astNodeMap.get(id);
      if (node === undefined) {
        node = {};
        astNodeMap.set(id, node);
      }
    } else {
      node = {};
    }

    if (kind) {
      const Class = astClass[kind];
      if (!Class) console.log(kind);
      assert.strictEqual(typeof Class, "function");
      if (!(node instanceof Class))
        Object.setPrototypeOf(node, Class.prototype);
    }

    merge(node, props);

    return node;
  }

  function revive(_, node) {
    if (!isObject(node) || !isString(node.kind)) return node; // Not an AST node.

    // Replace IDs by the referenced AST node.
    // Strip Id suffix from key (e.g. parentDeclContextId), if applicable.
    for (let [k, v] of Object.entries(node)) {
      if (k === "id" || !isNodeId(v)) continue;

      delete node[k];
      k = k.replace(/Id$/, "");
      v = getOrCreateNode(v);
      node[k] = v;
    }

    // Drop uninteresting properties.
    delete node.loc;
    delete node.range;

    // Convert node from Object to AST object.
    node = getOrCreateNode(node);

    // Register this node as the parent node of its non-type children.
    // Notes:
    //   'array_filler' and 'inner' arrays contain child nodes.
    //   'lookups' contains nodes but they're not child nodes.
    //   'bases' contains 'CXXBaseSpecifier' nodes that we currently ignore.
    //   'args' and 'path' arrays contain non-node items.
    if (node instanceof astClass.Decl) {
      for (const k of ["array_filler", "inner"]) {
        if (!isArray(node[k])) continue;
        for (const v of node[k]) {
          if (v === null || v instanceof astClass.Type) {
            // Skip.
          } else if (
            node instanceof astClass.TemplateDecl &&
            (v instanceof astClass.ClassTemplateSpecializationDecl ||
              v instanceof astClass.VarTemplateSpecializationDecl)
          ) {
            // Skip.
          } else {
            assert(v.template === undefined);
            v.parent = node;
          }
        }
      }
    }

    return node;
  }

  return JSON.parse(jsonString, revive);
}

function fromFile(filename) {
  const jsonString = readFileSync(filename, "utf8");
  const ast = fromJsonString(jsonString);
  return ast;
}

function dump(ast) {
  const nodeProto = astClass.Node.prototype;
  const seen = new Set();
  nodeProto[inspect.custom] = function(depth, options) {
    if (seen.has(this)) return `[${this.kind}] ${this.id}`;
    seen.add(this);
    return this;
  };
  const inspectOptions = inspect.defaultOptions;
  const originalOptions = { ...inspectOptions };
  Object.assign(inspectOptions, { maxArrayLength: null, depth: null });
  console.log(ast);
  delete nodeProto[inspect.custom];
  Object.assign(inspectOptions, originalOptions);
}

const tu = fromFile("../ast.json");
//for (const node of tu.inner) {
//  if (node.kind === "NamespaceDecl" && node.
//}
dump(tu);
