#![allow(dead_code)]
#![allow(unused_variables)]

extern crate clang;

use clang::source::Location;
use clang::token::*;
use clang::*;
use std::collections::HashMap;
use std::collections::HashSet;
use std::hash::Hash;
use std::iter::FromIterator;
use std::vec::Vec;

fn dump(e: &Entity, indent: usize, sel: &HashSet<Entity>) {
    if (sel.contains(&e)) {
        let mut path: Vec<Entity> = Vec::new();
        let mut e2 = *e;
        while let Some(p) = e2.get_lexical_parent() {
            if (p.get_kind() == EntityKind::TranslationUnit) {
                break;
            }
            path.push(p);
            e2 = p;
        }
        path.reverse();
        let path = path
            .into_iter()
            .filter_map(|e| e.get_name())
            .collect::<Vec<_>>();
        let path = path.join("::");
        let text = e
            .get_range()
            .map(|r| r.tokenize())
            .into_iter()
            .flatten()
            .filter(|t| t.get_kind() != TokenKind::Comment)
            .inspect(|t| {
                let start = t.get_range().get_start().get_file_location().column;
                let end = t.get_range().get_end().get_file_location().column;
                println!(
                    "TOK .{}.  {}-{}  {:?}",
                    t.get_spelling(),
                    start,
                    end,
                    t.get_range()
                        .get_start()
                        .get_entity()
                        .map(|e| e.get_kind())
                        .unwrap()
                );
            })
            .scan(None, |prev, t| {
                let start = t.get_range().get_start().get_file_location();
                let end = t.get_range().get_end().get_file_location();
                let space = prev.filter(|&p| p != start).map(|_| " ").unwrap_or("");
                *prev = Some(end);
                Some(format!("{}{}", space, t.get_spelling()))
            })
            .collect::<Vec<_>>()
            .join("");
        println!(
            "{} {:?} {}{:?} {}   {}",
            " ".repeat(indent * 2),
            e.get_kind(),
            if e.is_static_method() { "static " } else { "" },
            path,
            e.get_display_name()
                .unwrap_or_else(|| e.get_name().unwrap_or_else(|| String::from("??"))),
            text
        );

        //for t in e.get_type().into_iter() {
        //    println!("{} {:?} {:?}", " ".repeat((indent + 1) * 2), t, "");
        //    for f in t.get_fields().into_iter().flatten() {
        //        println!("{} {:?} {:?}", " ".repeat((indent + 2) * 2), f, "");
        //    }
        //}
        for t in e.get_template().into_iter() {
            println!("t={} {:?} {:?}", " ".repeat((indent + 1) * 2), t, "");
        }
        for t in e.get_result_type().into_iter() {
            println!("r={} {:?} {:?}", " ".repeat((indent + 1) * 2), t, "");
        }
        //for t in e.get_children().into_iter() {
        //    println!("c={} {:?} {:?}", " ".repeat((indent + 1) * 2), t, "");
        //}
        for t in e.get_storage_class().into_iter() {
            println!("s={} {:?} {:?}", " ".repeat((indent + 1) * 2), t, "");
        }
    }
    for child in e.get_children().into_iter() {
        dump(&child, indent + 1, sel)
    }
}

/*
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
}*/

fn dedup_vec<T: Eq + Hash + Copy>(vec: &mut Vec<T>) {
    let mut set: HashSet<T> = HashSet::new();
    let old = vec.drain(0..).collect::<Vec<_>>();
    for i in old.into_iter() {
        if set.insert(i) {
            vec.push(i);
        }
    }
}

trait ClassX<'a> {
    fn get_base_specifiers(&self) -> Option<Vec<Entity<'a>>>;

    //fn get_references(&self) -> Option<Vec<Entity<'a>>>;

    fn get_all_base_specifiers(&self) -> Vec<(Entity<'a>, Entity<'a>)>;

    fn get_all_templates(&self) -> Vec<Entity<'a>>;

    fn get_all_public(&self, kind: Option<EntityKind>) -> Vec<Entity<'a>>;

    fn get_ancestors(&self) -> Option<Vec<Entity<'a>>> {
        self.get_base_specifiers().and_then(|bases| {
            let mut vec: Vec<Entity<'a>> = Vec::new();
            for base in bases {
                if let Some(anc) = base.get_ancestors() {
                    vec.extend(anc);
                    vec.push(base);
                } else {
                    return None;
                }
            }
            Some(vec)
        })
    }
}

impl<'a> ClassX<'a> for Entity<'a> {
    fn get_base_specifiers(&self) -> Option<Vec<Entity<'a>>> {
        self.get_definition().map(|def| {
            def.get_children()
                .into_iter()
                .filter(|c| c.get_kind() == EntityKind::BaseSpecifier)
                .collect::<Vec<_>>()
        })
    }

    fn get_all_base_specifiers(&self) -> Vec<(Entity<'a>, Entity<'a>)> {
        let mut result = Vec::new();
        self.visit_children(|bspec, decl| {
            if bspec.get_kind() == EntityKind::BaseSpecifier {
                result.push((bspec, decl));
                EntityVisitResult::Continue
            } else {
                EntityVisitResult::Recurse
            }
        });
        result
    }

    fn get_all_templates(&self) -> Vec<Entity<'a>> {
        let mut result = Vec::new();
        self.visit_children(|e, p| {
            let kind = e.get_kind();
            if kind == EntityKind::Namespace && e.get_name().unwrap() == "internal" {
                return EntityVisitResult::Continue;
            } else if kind == EntityKind::AccessSpecifier || kind == EntityKind::FriendDecl {
                // Ignore templated friend declarations, e.g.
                // template <class U> friend Maybe<U> Nothing();
            } else if kind == EntityKind::ClassTemplate {
                // Ignore declared-but-not-defined templates.
                if let Some(defn) = e.get_definition() {
                    result.push(defn);
                }
            } else if kind == EntityKind::FunctionTemplate
                || kind == EntityKind::TemplateTemplateParameter
            {
                result.push(e);
            } else if kind == EntityKind::ClassTemplatePartialSpecialization
                || kind == EntityKind::TypeAliasTemplateDecl
            {
                // Not sure if we'll have to do anything with these.
            }
            EntityVisitResult::Recurse
        });
        dedup_vec(&mut result);
        result
    }

    fn get_all_public(&self, kind_filter: Option<EntityKind>) -> Vec<Entity<'a>> {
        let mut result = Vec::new();
        self.visit_children(|e, p| {
            let kind = e.get_kind();

            if kind == EntityKind::Namespace && e.get_name().unwrap() == "internal" {
                return EntityVisitResult::Continue;
            }

            if kind == EntityKind::FriendDecl || kind == EntityKind::AccessSpecifier {
                return EntityVisitResult::Continue;
            }

            if let Some(access) = e.get_accessibility() {
                if access != Accessibility::Public {
                    return EntityVisitResult::Continue;
                }
            }

            if kind_filter.is_none() || kind_filter == Some(kind) {
                //if let Some(def) = e.get_definition() {
                //    e = def;
                //}
                result.push(e);
            }
            EntityVisitResult::Recurse
        });
        dedup_vec(&mut result);
        result
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

    let v8_value = ents_v8
        .clone()
        .into_iter()
        .flat_map(|e| e.get_children().into_iter())
        .filter(|e| e.get_name().is_some())
        .filter(|e| e.get_name().unwrap() == "Value")
        .filter_map(|e| e.get_definition())
        .next()
        .unwrap();

    let v8_heap_root_class = ClassX::get_ancestors(&v8_value)
        .unwrap()
        .into_iter()
        .next()
        .unwrap()
        .get_definition()
        .unwrap();

    let v8_heap_classes = ents_v8
        .iter()
        .flat_map(|e| {
            ClassX::get_all_base_specifiers(e)
                .into_iter()
                .filter(|(_, decl)| {
                    ClassX::get_ancestors(decl)
                        .map(|vec| *vec.first().unwrap())
                        .map(|root_bspec| {
                            root_bspec.get_definition().unwrap() == v8_heap_root_class
                        })
                        .unwrap_or(false)
                })
                .map(|(_, decl)| decl.get_definition().unwrap())
        })
        .collect::<Vec<_>>();

    let mut public = ents_v8
        .iter()
        //.flat_map(|e| ClassX::get_all_public(e, Some(EntityKind::TemplateTypeParameter)))
        .flat_map(|e| ClassX::get_all_public(e, Some(EntityKind::TemplateRef)))
        //.flat_map(|e| ClassX::get_all_public(e, None))
        //.map(|e| e.get_canonical_entity())
        .chain(ents_v8.iter().flat_map(|e| ClassX::get_all_templates(e)))
        .filter(|e| e.get_kind() == EntityKind::FunctionTemplate)
        .collect::<Vec<_>>();
    dedup_vec(&mut public);

    let sel = HashSet::from_iter(public.iter().cloned());
    for e in ents_v8.iter() {
        dump(e, 0, &sel);
    }

    panic!("stop");

    /*
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
    }*/
}
