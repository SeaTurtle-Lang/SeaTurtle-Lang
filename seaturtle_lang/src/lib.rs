extern crate libc;
// use core::ffi;
use std::ffi::CString;
use std::ffi::CStr;

#[repr(C)]
pub struct TokenIdentifier {
    token: libc::c_int,
    offset: libc::c_int,
    // value: std::ffi::CStr,
}

#[repr(C)]
pub struct Token {
    token: libc::c_int,
    value: CString
}

#[no_mangle]
pub extern "C" fn parse(contents: *const libc::c_char, tokens: *const TokenIdentifier, len: libc::c_int) -> *mut Token {
    let data_slice = unsafe { std::slice::from_raw_parts(tokens, len as usize) };
    let c_str = unsafe { CStr::from_ptr(contents) };
    let actual_contents = c_str.to_str().expect("Invalid UTF-8");

    let mut curr_offset = 0;
    let mut tokens: Vec<Token> = vec![];

    for tk in data_slice {
        let mut curr_contents: String = actual_contents.chars().skip(curr_offset).take((tk.offset as usize) - curr_offset).collect();
        curr_contents = curr_contents.trim().to_string();
        let value = CString::new(curr_contents).expect("Error making CString from String");

        tokens.push(Token {token: tk.token, value: value});

        curr_offset = tk.offset as usize;
    }

    return tokens.as_mut_ptr();
}