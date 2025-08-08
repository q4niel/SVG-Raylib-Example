#!/bin/bash
cd "$(dirname $(dirname $(dirname $(realpath "$0"))))"

sudo docker build -f "bld/Dockerfile.linux" -t "svg_raylib_test:latest" .
sudo docker rm "svg_raylib_test"
sudo docker run --name "svg_raylib_test" "svg_raylib_test:latest" "bld/internal_build_libraries.sh"
if [ -d "./bld/out" ]; then
    rm -r "./bld/out"
fi
sudo rm -r "3rd"
sudo docker cp "svg_raylib_test:/proj/3rd" "./3rd"
sudo chown -R $(whoami):$(whoami) "3rd"