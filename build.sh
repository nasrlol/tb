#!/bin/sh
set -eu
script_dir="$(dirname "$(readlink -f "$0")")"
cd "$script_dir"
build_dir="build"
mkdir -p "$build_dir"

gcc -I. \
    -Wall -Wextra -Wno-unused-function -Wno-unused-variable \
    -DCORE_UNITY \
    source/core/core.c \
    -lX11 -lm \
    -o "$build_dir"/app
