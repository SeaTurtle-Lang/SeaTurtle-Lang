use crate::tokenizer::reader::get_file_contents;
use crate::tokenizer::literals::Literal;

#[derive(Debug)]
pub enum Token<'a> {
    LITERAL(Literal<'a>),
}

const DIGITS: &str = "0123456789";

#[allow(unused_variables)]
pub fn tokenize(fp: &str) -> Vec<Token> {
    let contents: String = get_file_contents(&fp);
    let mut tokens: Vec<Token> = vec![];

    for (i, character) in contents.chars().enumerate() {
        match DIGITS.find(character) {
            //  Character is a digit
            Some(_) => match tokens.len() {
                // tokens vector is empty
                0 => tokens.push(Token::LITERAL(Literal {
                    value: character.to_string().as_str()
                })),
                _ => match tokens.last_mut() {
                    // Formality
                    Some(item) => match item {
                        // The item is of type Literal
                        &mut Token::LITERAL(literal) => println!("{:?}", item),
                        _ => ()
                    },
                    None => ()
                }
            }
            // Character is not a digit
            None => (),
        }
    }

    return tokens;
}
