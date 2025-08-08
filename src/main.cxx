#include <print>
#include <thread>
#include <chrono>
#include "../3rd/raylib/include/raylib.h"

int main(int argc, char **argv) {
    SetTraceLogLevel(LOG_NONE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "My Window");

    int tick = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(MAGENTA);

        std::println("{}", tick++);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        EndDrawing();
    }

    CloseWindow();
    return 0;
}