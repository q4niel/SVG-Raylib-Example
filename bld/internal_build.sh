#!/bin/bash
shopt -s extglob

mkdir builder
mkdir builder/res

buildAnimation() {
    python3 "$1/main.py"
    name=$(basename "$1")
    cp -r "$1/${name}_anim" "./builder/res/${name}_anim"
}

# Libraries
cp "3rd/raylib/lib/libraylib.so.550" ./builder/
cp "3rd/resvg/target/release/libresvg.so" ./builder/

# Resources
cp res/square.html ./builder/res/square.svg
cp res/triangle.html ./builder/res/triangle.svg
buildAnimation res/circle

# Source files
clang++ -std=c++23 -c src/main.cxx -o main.o
clang++ -std=c++23 -c src/svg_renderable/svg_base.cxx -o svg_base.o
clang++ -std=c++23 -c src/svg_renderable/svg_sprite.cxx -o svg_sprite.o
clang++ -std=c++23 -c src/process_scaling/process_scaling.cxx -o process_scaling.o

cd ./builder
clang++ libraylib.so.550 libresvg.so ../main.o ../svg_base.o ../svg_sprite.o ../process_scaling.o -o ./app -Wl,-rpath,'$ORIGIN'
cd ..

rm -r !(builder)
mv builder/* .
rm -r builder