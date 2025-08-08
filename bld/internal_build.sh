#!/bin/bash
shopt -s extglob

mkdir builder

clang++ -std=c++23 -c src/main.cxx -o main.o

raylib=$"3rd/raylib/lib/libraylib.so.550"
cp $raylib ./builder/

clang++ $raylib main.o -o ./builder/app

rm -r !(builder)
mv builder/* .
rm -r builder