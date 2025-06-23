use std::{fs::File, io::{BufRead, BufReader}};

use chumsky::prelude::todo;

use crate::lexer::token::SpannedToken;

pub mod token;

pub enum LexError {
    Io(std::io::Error),
    Utf8Error(std::str::Utf8Error)
}

impl From<std::io::Error> for LexError {
    fn from(e: std::io::Error) -> Self {
        LexError::Io(e)
    }
}

impl From<std::str::Utf8Error> for LexError {
    fn from(e: std::str::Utf8Error) -> Self {
        LexError::Utf8Error(e)
    }
}

pub fn tokenize<'input>(file: &str) -> Result<Vec<SpannedToken<'input>>, LexError> {
    /*let f = File::open(file)?;
    let tokens: Vec<SpannedToken<'input>> = Vec::new();
    let mut reader = BufReader::new(f);
    
    loop {
        let buf = reader.fill_buf()?;
        if buf.is_empty() {
            break
        }
        let buf_str = std::str::from_utf8(&buf)?;

        for (i, ch) in &mut buf_str.chars().enumerate() {
            let token = match ch {
                '0' .. '9' => {
                    let (bytes_to_read, token) = tokenize_number::<'input>();
                    reader.consume(bytes_to_read);
                },
                _ => {}
            }
        }
    }

    Ok(tokens)*/
    todo!()
}

fn tokenize_number<'input>() -> (usize, SpannedToken<'input>) {
    todo!()
}

