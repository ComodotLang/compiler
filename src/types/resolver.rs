use std::rc::Rc;

use crate::types::scope::Scope;

pub struct TypeResolver<'a> {
    top_scope: Rc<Scope<'a>>
}

impl <'a> TypeResolver<'a> {
    fn declare_topelevel_symbols(&self) {
        
    }

    fn open_scope(&mut self) {
        self.top_scope = Rc::new(Scope::new(Some(self.top_scope.clone())));
    }

    fn close_scope(&mut self) {
        self.top_scope = self.top_scope.parent.clone().unwrap();
    }
}