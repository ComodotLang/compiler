use std::{borrow::Cow, rc::Rc};
use crate::types::{hir::HirTopLevel, scope::Scope};

pub struct File<'a> {
    pub name: Cow<'a, str>,
    pub path: Cow<'a, str>,
    pub tree: Vec<HirTopLevel>
}

pub struct Package<'a> {
    pub name: Cow<'a, str>,
    pub path: Cow<'a, str>,
    pub scope: Rc<Scope<'a>>,
    pub imports: Vec<Package<'a>>,
    pub files: Vec<File<'a>>,
    pub is_root: bool
}

impl<'a> Package<'a> {
    pub fn new(name: Cow<'a, str>, path: Cow<'a, str>, scope: Rc<Scope<'a>>, imports: Vec<Package<'a>>, files: Vec<File<'a>>, is_root: bool) -> Self {
        Package {
            name,
            path,
            scope,
            imports,
            files,
            is_root
        }
    }
}