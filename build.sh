#!/bin/sh
set -eu

# Toolchain
CC=clang

# Files
SRC=main.c
OUT=main

# Include paths
INCLUDES="-I."

# Compiler flags
CFLAGS="
-g
-O0
"

# Linker flags
LDFLAGS="
-lX11
-I.
-lm
"

echo "==> Building $OUT"
$CC $CFLAGS $INCLUDES "$SRC" -o "$OUT" $LDFLAGS

echo "==> Running $OUT"
./"$OUT"
