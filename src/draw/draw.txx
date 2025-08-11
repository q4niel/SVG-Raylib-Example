#include "draw.hxx"

template<std::size_t N>
auto draw(const std::array<SVGTexture, N> &svgs_) -> void {
    BeginDrawing();
    ClearBackground(MAGENTA);

    for (const SVGTexture &svg_: svgs_) {
        if (RAYLIB_TEXTURE_CALLBACK cb = svg_.getRaylibTexture_(); cb) {
            DrawTextureV(*cb, {svg_.getPosX_(), svg_.getPosY_()}, WHITE);
        }
        else
            std::println("Error: {}", cb.error());
    }

    EndDrawing();
}