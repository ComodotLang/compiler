use std::borrow::Cow;

#[derive(Clone)]
pub enum Primitive {
    Int,
    Float,
    Char, 
    Bool,
    Unit
}

#[derive(Clone)]
pub enum LangType {
    Primitives(Primitive)
}

impl LangType {
    pub fn is_primitive(&self) -> bool {
        match self {
            LangType::Primitives(_) => true,
            _ => false
        }
    }

    pub fn is_unit(&self) -> bool {
        match self {
            LangType::Primitives(Primitive::Unit) => true,
            _ => false
        }
    }

    pub fn short_text(&self) -> Cow<str> {
        let res = match self {
            LangType::Primitives(Primitive::Int) => "i",
            LangType::Primitives(Primitive::Float) => "f",
            LangType::Primitives(Primitive::Char) => "c",
            LangType::Primitives(Primitive::Bool) => "b",
            LangType::Primitives(Primitive::Unit) => "u"
        };

        Cow::from(res)
    }
}