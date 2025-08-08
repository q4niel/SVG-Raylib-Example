#!/bin/bash
cd "$(dirname $(dirname $(dirname $(realpath "$0"))))"

sudo docker build -f "bld/Dockerfile.linux" -t "svg_raylib_test:latest" .
sudo docker rm "svg_raylib_test"
sudo docker run --name "svg_raylib_test" "svg_raylib_test:latest"
if [ -d "./bld/out" ]; then
    rm -r "./bld/out"
fi
sudo docker cp "svg_raylib_test:/proj" "./bld/out"
sudo chown -R $(whoami):$(whoami) "bld/out"