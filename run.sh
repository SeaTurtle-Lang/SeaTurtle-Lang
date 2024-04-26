cargo build --manifest-path seaturtle_lang/Cargo.toml &> temp.txt
if [ $? == 1 ] || [ $? == 101 ]
then
    echo "Error in building rust crate"
    cat temp.txt
else
    echo "Built Rust Crate Successfully"
    gcc seaturtle_lang/src/c/main.c -o build/main.o -lseaturtle_lang -Lseaturtle_lang/target/debug &> temp.txt
    if [ $? -eq 1 ]
    then
        echo "Error in compiling C"
        cat temp.txt
    else
        echo "C compiled successfully"
        LD_LIBRARY_PATH=seaturtle_lang/target/debug build/main.o seaturtle_lang/src/examples/main.st
    fi
fi
rm temp.txt