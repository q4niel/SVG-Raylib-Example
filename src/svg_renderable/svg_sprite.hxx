#pragma once
#include "svg_base.hxx"

namespace svgr {
    class SVGSprite : public svgr::SVGBase {
    public:
        SVGSprite (
            const std::string_view svgPath_,
            const float scale_,
            const float posX_,
            const float posY_
        );

        ~SVGSprite();

        auto getRaylibTexture_() const -> RAYLIB_TEXTURE_CALLBACK override;
        auto destroyRasterized_() const -> void override;
        auto rasterize_() const -> void override;

    private:
        // All members initialized in constructor initializer list
        const std::string _svgPath_;
        mutable Texture2D _raylibTexture;
    };
}