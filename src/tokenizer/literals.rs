#[derive(Debug)]
pub struct Literal<'a> {
    pub value: &'a str
}

impl Literal<'_> {
    pub fn as_integer(&self) -> i32 {
        return self.value.parse::<i32>().unwrap();
    }

    pub fn add_to_value(&mut self, character: char) {
        let string = (self.value.to_string() + character.to_string().as_str()).as_str();
        self.value = string;
    }
}