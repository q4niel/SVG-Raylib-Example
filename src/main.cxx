#include <cstdlib>
#include <array>
#include "../3rd/raylib/include/raylib.h"
#include "svg_texture/svg_texture.hxx"
#include "process_scaling/process_scaling.hxx"
#include "draw/draw.hxx"

auto main(int argc, char **argv) -> int {
    SetTraceLogLevel(LOG_NONE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1920, 1080, "SVG-Raylib-Example");
    SetTargetFPS(60);

    const std::array<SVGTexture, 2> svgs_ = {
        SVGTexture{"res/square.svg", 10, 1000, 1000},
        SVGTexture{"res/triangle.svg", 10, 0, 0}
    };

    while (!WindowShouldClose()) {
        processScaling(svgs_);
        draw(svgs_);
    }

    CloseWindow();
    return EXIT_SUCCESS;
}