#!/bin/sh
set -eu

build_dir=~/projects/tb/build

# Run
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH:-}:$build_dir"
"$build_dir/app"
