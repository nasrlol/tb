#!/bin/sh
set -eu

script_dir="$(dirname "$(readlink -f "$0")")"
cd "$script_dir"

build_dir="build"
mkdir -p "$build_dir"

compile()
{
 source="$1"
 out="$2"
 flags="${3:-}"

 common_flags="-I. -Wall -Wextra -Wno-unused-function -Wno-unused-variable"
 linker_flags="-lX11 -lm"

 flags="$common_flags $flags $linker_flags"

 gcc $flags "$(readlink -f "$source")" -o "$build_dir"/"$out"
}

# Build core shared lib
compile "source/core/core.h" "libcore.so" "-fPIC -shared -DCORE_UNITY"

# Build app
compile "source/core/core.c" "app" "-L$build_dir -lcore"

