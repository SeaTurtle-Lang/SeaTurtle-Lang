#!/bin/bash

EXIT_STATUS_FILE=exit_status.txt


# C related variables
source_path=seaturtle_lang/src/c/main.c
build_path=build/main.o
remove_status_files=true

# SeaTurtle related variables
seaturtle_source=seaturtle_lang/examples/main.st

# Rust related variables
manifest_path=seaturtle_lang/Cargo.toml
crate_build_path=seaturtle_lang/target/debug
crate_path=seaturtle_lang

while getopts "rm:s:b:c:d:p:" opt; do
    case $opt in
        r)
            remove_status_files=false
            ;;
        m)
            manifest_path=$OPTARG
            ;;
        s)
            source_path=$OPTARG
            ;;
        b)
            build_path=$OPTARG
            ;;
        c)
            seaturtle_source=$OPTARG
            ;;
        d)
            crate_build_path=$OPTARG
            ;;
        d)
            crate_path=$OPTARG
            ;;
    esac
done

> $EXIT_STATUS_FILE

echo "========== Rust ==========" >> $EXIT_STATUS_FILE
cargo build --manifest-path $manifest_path >> $EXIT_STATUS_FILE 2>&1
if [ $? -ne 0 ]; then
    echo "Error in building rust crate"
    cat $EXIT_STATUS_FILE
else
    echo "Built Rust Crate Successfully"
    echo "========== C ==========" >> $EXIT_STATUS_FILE
    gcc $source_path -o $build_path -l $crate_path -L $crate_build_path >> $EXIT_STATUS_FILE
    if [ $? -ne 0 ]; then
        echo "Error in compiling C"
        cat $EXIT_STATUS_FILE
    else
        echo "C compiled successfully"
        echo "=============================="
        LD_LIBRARY_PATH=$crate_build_path $build_path $seaturtle_source
    fi
fi

if [ "$remove_status_files" = true ]; then
    rm $EXIT_STATUS_FILE
fi