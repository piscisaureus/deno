#![allow(dead_code)]
#![allow(unused_variables)]

extern crate clang;

use clang::*;
use std::collections::HashMap;
use std::collections::HashSet;
use std::vec::Vec;

fn dump(e: &Entity, indent: usize) {
    if e.get_kind() == EntityKind::Namespace && e.get_name().unwrap() == "internal" {
        return;
    }
    println!(
        "{} {:?} {}",
        " ".repeat(indent * 2),
        e.get_kind(),
        e.get_display_name().unwrap_or_else(|| String::from("??"))
    );
    if e.get_kind() == EntityKind::Namespace {
        dbg!(e);
    }
    for child in e.get_children().into_iter() {
        dump(&child, indent + 1)
    }
}

#[derive(Debug)]
struct ClassInfo<'tu> {
    pub decl: Entity<'tu>,
    pub base: Option<Entity<'tu>>,
    pub deriv: HashSet<Entity<'tu>>,
}

type ClassIndex<'tu> = HashMap<Entity<'tu>, ClassInfo<'tu>>;

impl<'tu> ClassInfo<'tu> {
    pub fn new(decl: Entity<'tu>) -> Self {
        Self {
            decl,
            base: None,
            deriv: HashSet::new(),
        }
    }
}

fn get_heap_object_classes<'tu>(class_index: &ClassIndex<'tu>) -> Vec<Entity<'tu>> {
    let v8_value_class = class_index
        .keys()
        .cloned()
        .filter(|decl| {
            decl.get_name().unwrap() == "Value"
                && decl.get_lexical_parent().unwrap().get_name().unwrap() == "v8"
        })
        .next()
        .unwrap();
    println!("v8_value_class {:?}", class_index.get(&v8_value_class));

    let mut v8_root_class = v8_value_class;
    while let Some(ancestor) = class_index.get(&v8_root_class).unwrap().base {
        v8_root_class = ancestor;
    }
    let mut classes = Vec::new();
    classes.push(v8_root_class);
    let mut i = 0;
    while i < classes.len() {
        println!("{}", i);
        let decl = classes[i];
        i += 1;
        println!("{:?} {:?}", decl, class_index.get(&decl).unwrap().deriv);
        classes.extend(class_index.get(&decl).unwrap().deriv.iter());
    }
    println!("classes {:?}", classes);
    classes
}

fn class_data_fields<'tu>(decl: Entity<'tu>, class_index: &ClassIndex<'tu>) -> Vec<Entity<'tu>> {
    let info = class_index.get(&decl).unwrap();
    let mut fields = info
        .base
        .map(|decl| class_data_fields(decl, class_index))
        .unwrap_or_else(Vec::new);
    fields.extend(
        decl.get_children()
            .into_iter()
            .filter(|child| child.get_kind() == EntityKind::FieldDecl),
        //.filter(|child| child.get_storage_class()
    );
    fields
}

fn get_class_decl<'tu>(mut e: Entity<'tu>) -> Entity<'tu> {
    let k = e.get_kind();
    if k != EntityKind::StructDecl && k != EntityKind::ClassDecl {
        e = e.get_definition().unwrap();
    }
    e = e.get_canonical_entity();
    e
}

fn add_class<'tu>(e: Entity<'tu>, class_index: &mut ClassIndex<'tu>) {
    let class_decl = get_class_decl(e);
    let mut base_specifiers: Vec<Entity<'tu>> = Vec::new();

    for child in class_decl.get_children() {
        match child.get_kind() {
            EntityKind::BaseSpecifier => {
                base_specifiers.push(child);
            }
            _ => {
                //println!("{:?}", child);
            }
        }
    }

    assert!(
        base_specifiers.len() <= 1,
        "More than 1 base class not supported"
    );
    let maybe_base = base_specifiers.into_iter().next().map(get_class_decl);
    if let Some(base) = maybe_base {
        class_index
            .entry(base)
            .or_insert_with(|| ClassInfo::new(base))
            .deriv
            .insert(class_decl);
    }

    let info = class_index
        .entry(class_decl)
        .or_insert_with(|| ClassInfo::new(class_decl));
    if maybe_base.is_some() {
        info.base = maybe_base;
    }
}

fn main() {
    // Acquire an instance of `Clang`
    let clang = Clang::new().unwrap();

    // Create a new `Index`
    let index = Index::new(&clang, false, false);

    // Parse a source file into a translation unit
    let tu = index
        .parser("d:/v8gen/m.cpp")
        .arguments(&["-x", "c++"])
        .skip_function_bodies(true)
        .parse()
        .unwrap();

    let ents_v8 = tu
        .get_entity()
        .get_children()
        .into_iter()
        .filter(|e| e.get_kind() == EntityKind::Namespace)
        .filter(|e| e.get_name().unwrap() == "v8")
        .collect::<Vec<_>>();

    for e in &ents_v8 {
        dump(&e, 0);
    }

    // Get the structs in this translation unit
    let classes = ents_v8
        .into_iter()
        .flat_map(|e| e.get_children().into_iter())
        .filter(|e| {
            let k = e.get_kind();
            k == EntityKind::StructDecl || k == EntityKind::ClassDecl
        })
        .collect::<Vec<_>>();

    let mut class_index = ClassIndex::new();
    for c in classes {
        add_class(c, &mut class_index);
    }

    //get_heap_object_classes(&class_index);

    let mut classes = class_index.keys().cloned().collect::<Vec<_>>();
    classes.sort_unstable_by(|a, b| {
        let a = a.get_location().unwrap().get_file_location().offset;
        let b = b.get_location().unwrap().get_file_location().offset;
        a.cmp(&b)
    });

    for e in classes.iter() {
        println!("{}", e.get_name().unwrap());
        println!(
            "  base: {:?}",
            class_index[e]
                .base
                .iter()
                .map(|e| e.get_name().unwrap())
                .collect::<Vec<_>>()
        );
        println!(
            "  deriv: {:?}",
            class_index[e]
                .deriv
                .iter()
                .map(|e| e.get_name().unwrap())
                .collect::<Vec<_>>()
        );

        println!(
            "  fields: {:?}",
            class_data_fields(*e, &class_index)
                .into_iter()
                .map(|e| e.get_name().unwrap())
                .collect::<Vec<_>>()
        );
    }
}
