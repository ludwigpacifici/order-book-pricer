#!/bin/bash

set -e

function diff_stream {
    local input=$1
    local output=$2
    local threshold=$3

    diff <( cat $input| ./src/order-book-pricer $threshold ) <( cat $output )
}

function uncompress_and_diff_stream {
    local input=$1
    local output=$2
    local threshold=$3

    diff <( zcat $input| ./src/order-book-pricer $threshold ) <( zcat $output )
}

root_directory=`git rev-parse --show-toplevel`
cd $root_directory

diff_stream ./data/basic.in.txt ./data/basic.out.txt 200

# uncompress_and_diff_stream ./data/pricer.in.gz ./data/pricer.out.10000.gz 100000
uncompress_and_diff_stream ./data/pricer.in.gz ./data/pricer.out.200.gz 200
uncompress_and_diff_stream ./data/pricer.in.gz ./data/pricer.out.1.gz 1
