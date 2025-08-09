#include <cstdlib>
#include "../3rd/raylib/include/raylib.h"
#include "svg_texture.hxx"

auto main(int argc, char **argv) -> int {
    SetTraceLogLevel(LOG_NONE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "SVG-Raylib-Example");
    SetTargetFPS(60);

    SVGTexture tex{"res/circle.svg", 512, 512};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(MAGENTA);
        DrawTextureV(tex.getRaylibTexture(), {0, 0}, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}