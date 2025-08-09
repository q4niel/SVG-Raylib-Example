#pragma once
#include <string>
#include <string_view>
#include "../3rd/raylib/include/raylib.h"

class SVGTexture {
public:
    SVGTexture (
        const std::string_view svgPath,
        const int width,
        const int height
    );
    ~SVGTexture() = default;

    auto getWidth() -> const int;
    auto setWidth(const int value) -> const int;

    auto getHeight() -> const int;
    auto setHeight(const int value) -> const int;

    auto getRaylibTexture() -> const Texture2D &;

private:
    const std::string _svgPath;
    int _width, _height;
    Texture2D _raylibTexture;

    auto _clean() -> void;
};