use std::path::Path;
use std::fs::File;
use std::io::prelude::*;

pub fn get_file_contents(fp: &str) -> String {
    let path: &Path = Path::new(&fp);
    let display = path.display();

    let mut file: File = match File::open(&path) {
        Err(err) => panic!("Could not open {} due to {}", display, err),
        Ok(file) => file,
    };

    let mut s: String = String::new();
    match file.read_to_string(&mut s) {
        Err(err) => panic!("Could not read {} due to {}", display, err),
        Ok(_) => (),
    };

    return s;
}
