#!/bin/bash

set -e

function run_timings {
    local mode=$1

    make $mode > /dev/null

    echo -ne "[$mode][identity]"
    time zcat ./data/pricer.in.gz | ./src/order-book-pricer --dry-run > /dev/null
    echo -ne "\n[$mode][1]"
    time zcat ./data/pricer.in.gz | ./src/order-book-pricer 1 > /dev/null
    echo -ne "\n[$mode][200]"
    time zcat ./data/pricer.in.gz | ./src/order-book-pricer 200 > /dev/null
    echo -ne "\n[$mode][10000]"
    time zcat ./data/pricer.in.gz | ./src/order-book-pricer 10000 > /dev/null
    echo
}

root_directory=`git rev-parse --show-toplevel`
cd $root_directory

run_timings "release"
