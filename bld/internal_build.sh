#!/bin/bash
shopt -s extglob

mkdir builder
clang++ -std=c++23 -c src/main.cxx -o main.o

cp "3rd/raylib/lib/libraylib.so.550" ./builder/
cp "3rd/resvg/target/release/libresvg.so" ./builder/

cd ./builder
clang++ libraylib.so.550 libresvg.so ../main.o -o ./app -Wl,-rpath,'$ORIGIN'
cd ..

rm -r !(builder)
mv builder/* .
rm -r builder