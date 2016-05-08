#!/bin/bash
function loop() { 
    for i in "$1"/*
    do
        if [ -e "$i" ]; then
            echo $i
            clang++ -std=c++14 SimpleSim.cpp  $VERILATOR_ROOT/include/verilated.cpp ./obj_dir/VSimpleUart.cpp ./obj_dir/VSimpleUart__Syms.cpp $VERILATOR_ROOT/include/verilated_cov.cpp -I$VERILATOR_ROOT/include -I$VERILATOR_ROOT/include/vltstd -O3 -o test
        else
            echo "$i"" - Folder Empty"
        fi
    done
}
loop "$PWD"
