pub enum HirExpression {
    LitInt(i64),
    LitBool(bool),
    LitChar(char),
    LitFloat(f64),
    LiteralUnit,

    Var,

    Binary,
    Call,
}

pub enum HirTopLevel {
    Function(),
    Extern()
}