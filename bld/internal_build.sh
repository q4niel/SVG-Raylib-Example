#!/bin/bash
shopt -s extglob

mkdir builder
mkdir builder/res

cp "3rd/raylib/lib/libraylib.so.550" ./builder/
cp "3rd/resvg/target/release/libresvg.so" ./builder/
cp src/resources/square.html ./builder/res/square.svg
cp src/resources/triangle.html ./builder/res/triangle.svg

clang++ -std=c++23 -c src/main.cxx -o main.o
clang++ -std=c++23 -c src/svg_texture/svg_texture.cxx -o svg_texture.o
clang++ -std=c++23 -c src/process_scaling/process_scaling.cxx -o process_scaling.o

cd ./builder
clang++ libraylib.so.550 libresvg.so ../main.o ../svg_texture.o ../process_scaling.o -o ./app -Wl,-rpath,'$ORIGIN'
cd ..

rm -r !(builder)
mv builder/* .
rm -r builder