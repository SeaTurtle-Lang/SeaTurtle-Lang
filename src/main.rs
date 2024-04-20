use crate::tokenizer::token_maker::tokenize;
pub mod tokenizer;

#[allow(unused_variables)]
fn main() {
    const FP: &str = "examples/main.st";
    for item in tokenize(FP) {
        println!("Found {:?}", item);
    }
}
