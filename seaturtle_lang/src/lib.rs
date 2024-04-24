extern crate libc;
use std::ffi::CStr;

#[repr(C)]
pub struct token {
    token: libc::c_int,
    offset: libc::c_int,
}

#[no_mangle]
pub extern "C" fn parse(contents: *const libc::c_char, tokens: *const token, len: libc::c_int) {
    let data_slice = unsafe { std::slice::from_raw_parts(tokens, len as usize) };
    let c_str = unsafe { CStr::from_ptr(contents) };
    let actual_contents = c_str.to_str().expect("Invalid UTF-8");

    let mut curr_offset = 0;

    for tk in data_slice {
        let mutable_contents = actual_contents;

        let curr_contents: String = mutable_contents.chars().skip(curr_offset).take((tk.offset as usize) - curr_offset).collect();
        println!("'{}'", curr_contents);

        curr_offset = tk.offset as usize;
    }
}