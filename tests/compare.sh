#!/bin/bash

set -e

function do_diff {
    local input=$1
    local output=$2
    local threshold=$3

    diff <( cat $input| ./src/order-book-pricer $threshold ) <( cat $output )
}

root_directory=`git rev-parse --show-toplevel`
cd $root_directory

do_diff ./data/basic.in.txt ./data/basic.out.txt 200
