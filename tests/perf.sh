#!/bin/bash

function generate_flamegraph {
    local mode=$1
    local executable_name="order-book-pric"

    make $mode

    perf record -F 99 -g ./compare.sh
    perf script | stackcollapse-perf > out.folded
    grep $executable_name out.folded | flamegraph > order-book-pricer-$mode.svg
}

generate_flamegraph "release"
generate_flamegraph "debug"
