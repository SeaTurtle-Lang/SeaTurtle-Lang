cargo build --manifest-path seaturtle_lang/Cargo.toml &> temp.txt
if [ $? -eq  1 ]
then
    cat temp.txt
else
    gcc seaturtle_lang/src/c/main.c -o build/main.o -lseaturtle_lang -Lseaturtle_lang/target/debug
    LD_LIBRARY_PATH=seaturtle_lang/target/debug build/main.o seaturtle_lang/src/examples/main.st
fi
rm temp.txt