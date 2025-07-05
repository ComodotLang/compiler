use std::{borrow::Cow, collections::HashMap, rc::Rc};

use crate::types::lang_types::LangType;

#[derive(Clone)]
pub struct Symbol<'a> {
    pub name: Cow<'a, str>,
    pub exported: bool,
    pub ty: LangType,
}

pub struct Scope<'a> {
    pub symbols: HashMap<Cow<'a, str>, Symbol<'a>>,
    pub parent: Option<Rc<Scope<'a>>>
}

impl<'a> Scope<'a> {
    pub fn new(parent: Option<Rc<Scope<'a>>>) -> Self {
        Scope {
            symbols: HashMap::new(),
            parent: parent
        }
    }

    pub fn find_symbol(&self, name: &str) -> Option<Symbol> {
        self.symbols.get(name).cloned()
            .or_else(|| self.parent.as_ref()?.find_symbol(name))
    }

    pub fn insert(&mut self, symbol: Symbol<'a>) {
        self.symbols.insert(symbol.name.clone(), symbol);
    }
}