#!/bin/bash

executable_name="order-book-pric"

perf record -F 99 -g ./compare.sh
perf script | stackcollapse-perf > out.folded
grep $executable_name out.folded | flamegraph > order-book-pricer.svg
