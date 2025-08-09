#pragma once
#include <string>
#include <string_view>
#include <expected>
#include <functional>
#include "../3rd/raylib/include/raylib.h"

class SVGTexture {
public:
    SVGTexture (
        const std::string_view svgPath,
        const int width,
        const int height
    );
    ~SVGTexture() = default;

    #define RAYLIB_TEXTURE_CALLBACK std::expected<std::reference_wrapper<const Texture2D>, std::string>

    auto getRaylibTexture() -> RAYLIB_TEXTURE_CALLBACK;

    auto createRaylibTexture (
        const std::string_view svgPath,
        const int width,
        const int height
    ) -> RAYLIB_TEXTURE_CALLBACK;

    auto destroyRaylibTexture() -> void;

    auto getWidth() -> const int;
    auto setWidth(const int value) -> const int;

    auto getHeight() -> const int;
    auto setHeight(const int value) -> const int;

private:
    Texture2D _raylibTexture;
    std::string _svgPath;
    int _width, _height;

    auto _clean() -> void;
};