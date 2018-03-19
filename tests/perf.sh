#!/bin/bash

function generate_flamegraph {
    local mode=$1
    local executable_name="order-book-pric"

    make $mode

    perf record -o tests/perf.data -F 99 -g tests/compare.sh
    perf script -i tests/perf.data | stackcollapse-perf > tests/out.folded
    grep $executable_name tests/out.folded | flamegraph > tests/order-book-pricer-$mode.svg
}

root_directory=`git rev-parse --show-toplevel`
cd $root_directory

generate_flamegraph "release"
generate_flamegraph "debug"
