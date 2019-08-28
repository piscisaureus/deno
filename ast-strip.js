const { writeFileSync } = require("fs");

const { isArray } = Array;
const isObject = val =>
  typeof val === "object" && val !== null && !isArray(val);
const isString = val => typeof val === "string";

const nodeKindsWithIsUsedProperty = new Set([
  "VarDecl",
  "FunctionDecl",
  "ParmVarDecl",
  "CXXConstructorDecl",
  "VarTemplateSpecializationDecl",
  "CXXMethodDecl",
  "CXXDestructorDecl",
  "CXXConversionDecl"
]);
const nodeKindsWithIsReferencedProperty = new Set([
  "CXXRecordDecl",
  "TypedefDecl",
  "TemplateTypeParmDecl",
  "NonTypeTemplateParmDecl",
  "FieldDecl",
  "CXXDestructorDecl",
  "VarTemplateSpecializationDecl",
  "TypeAliasDecl",
  "VarDecl",
  "ParmVarDecl",
  "FunctionDecl",
  "EnumDecl",
  "EnumConstantDecl",
  "CXXMethodDecl",
  "CXXConstructorDecl",
  "UnresolvedUsingTypenameDecl"
]);

function visit(val) {
  if (isObject(val)) {
    delete val["loc"];
    delete val["range"];

    for (const ent of Object.values(val)) {
      visit(ent);
    }
  } else if (isArray(val)) {
    for (let i = val.length - 1; i >= 0; i--) {
      const el = val[i];
      if (!isObject(el)) continue;
      const { kind } = el;
      if (!isString(kind)) continue;

      if (
        kind === "CompoundStmt" ||
        (nodeKindsWithIsUsedProperty.has(kind) && !el.isUsed) ||
        (nodeKindsWithIsReferencedProperty.has(kind) && !el.isReferenced)
      ) {
        val.splice(i, 1);
      }
    }
    for (const el of val) {
      visit(el);
    }
  }
}

const ast = require("./ast.json");
visit(ast);
writeFileSync("ast2.json", JSON.stringify(ast, null, 2));
