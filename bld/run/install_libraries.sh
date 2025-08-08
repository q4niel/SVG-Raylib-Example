#!/bin/bash
cd "$(dirname $(dirname $(dirname $(realpath "$0"))))"

if [ -d "3rd" ]; then
    rm -r "3rd"
fi
mkdir "3rd"

getLib() {
    wget $1 -P "3rd/"
    tar -xzf "3rd/$2.tar.gz" -C "3rd/"
    rm "3rd/$2.tar.gz"
    mv "3rd/$2" "3rd/$3"
}

getLib "https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_linux_amd64.tar.gz" "raylib-5.5_linux_amd64" "raylib"