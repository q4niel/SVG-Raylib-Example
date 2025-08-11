#pragma once
#include <string>
#include <string_view>
#include <expected>
#include <functional>
#include "../../3rd/raylib/include/raylib.h"
#include "../../3rd/resvg/crates/c-api/resvg.h"

class SVGTexture {
public:
    SVGTexture (
        const std::string_view svgPath_,
        const float scale_,
        const float posX_,
        const float posY_
    );
    ~SVGTexture();

    #define RAYLIB_TEXTURE_CALLBACK std::expected<std::reference_wrapper<const Texture2D>, std::string>
    auto getRaylibTexture_() const -> RAYLIB_TEXTURE_CALLBACK;

    auto destroyRaylibTexture_() const -> void;
    auto rasterize_() const -> void;
    auto getSVGPath_() const -> std::string_view;

    auto incrementScale_() const -> void;
    auto decrementScale_() const -> void;

    auto getPosX_() const -> const float;
    auto setPosX_(const float value_) const -> const float;

    auto getPosY_() const -> const float;
    auto setPosY_(const float value_) const -> const float;

    auto getWidth_() const -> const float;
    auto setWidth_(const float value_) const -> void;

    auto getHeight_() const -> const float;
    auto setHeight_(const float value_) const -> void;

private:
    // All members initialized in constructor initializer list

    mutable std::string _svgPath;
    mutable float _scale, _posX, _posY, _width, _height;
    mutable Texture2D _raylibTexture;

    const resvg_options *_options_;
    resvg_render_tree *_tree;

    auto _getAspectRatio() -> const float;
};