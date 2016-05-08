#!/bin/bash
VERILATOR_ROOT=/home/deepak/VTech/Spring16/TestingAndVerification/Project/verilator/
function loop() { 
    for i in "$1"/Generated_Mutants/*.cpp
    do
        if [ -e "$i" ]; then
            v=${i::-4}
            echo "$i --> $v"
            clang++ SimpleSim.cpp $VERILATOR_ROOT/include/verilated.cpp $i ./obj_dir/VSimpleUart__Syms.cpp $VERILATOR_ROOT/include/verilated_cov.cpp -I$VERILATOR_ROOT/include -I$VERILATOR_ROOT/include/vltstd -O3 -o binary
            ./binary > test.txt
            if cmp -s goldenOutput.txt test.txt
            then
                echo "The files match"
                echo $i
                echo $i >> Identical.txt
                printf '\n' >> Identical.txt
            else
                echo "The files are different"
                echo $i
            fi
        else
            echo "$i"" - Folder Empty"
        fi
    done
}
loop "$PWD"
