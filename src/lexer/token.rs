#[derive(Debug, Clone)]
pub enum Token<'input> {
    Fn,
    Ret,
    Const,
    Pub,
    Import,
    True,
    False,
    If,
    Else,
    Extern,
    Identifier(&'input str),
    Integer(i64),
    Float(f64),
    Boolean(bool),
    Str(&'input str),
    And,
    Or,
    Plus,
    Minus,
    Slash,
    Star,
    LeftBrace,
    RightBrace,
    LeftParen,
    RightParen,
    Semicolon,
    Assign,
    GreaterThen,
    LessThen,
    Equals,
    Comma,
    Colon,
    Undefined
}

#[derive(Debug, Clone)]
pub struct SpannedToken<'input> {
    pub token: Token<'input>,
    pub span: Span,
}

#[derive(Debug, Clone, Copy)]
pub struct Span {
    pub start: usize,
    pub end: usize,
}
