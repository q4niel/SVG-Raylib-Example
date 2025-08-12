#pragma once
#include <string>
#include <string_view>
#include <expected>
#include <functional>
#include "../../3rd/raylib/include/raylib.h"
#include "../../3rd/resvg/crates/c-api/resvg.h"

namespace svgr {
    class SVGBase {
    public:
        SVGBase (
            const float scale_,
            const float posX_,
            const float posY_
        );
        virtual ~SVGBase() = default;

        #define RAYLIB_TEXTURE_CALLBACK std::expected<std::reference_wrapper<const Texture2D>, std::string>
        virtual auto getRaylibTexture_() const -> RAYLIB_TEXTURE_CALLBACK = 0;
        virtual auto destroyRasterized_() const -> void = 0;
        virtual auto rasterize_() const -> void = 0;

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

    protected:
        // All members initialized in constructor initializer list
        mutable float _scale, _posX, _posY, _width, _height;

        auto _getAspectRatio() -> const float;
        auto _rasterizeTexture_ (
            std::string svgPath,
            Texture2D &outTexture
        ) const -> void;
    };
}