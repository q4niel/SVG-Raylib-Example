#include "svg_sprite.hxx"
#include <format>

svgr::SVGSprite::SVGSprite (
    const std::string_view svgPath_,
    const float scale_,
    const float posX_,
    const float posY_
) :
    svgr::SVGBase::SVGBase(scale_, posX_, posY_),
    _svgPath_(svgPath_),
    _raylibTexture({0})
{
    rasterize_();
}

svgr::SVGSprite::~SVGSprite() {
    destroyRasterized_();
}

auto svgr::SVGSprite::getRaylibTexture_() const -> RAYLIB_TEXTURE_CALLBACK {
    return (0 != _raylibTexture.id)
        ? RAYLIB_TEXTURE_CALLBACK{_raylibTexture}
        : std::unexpected(std::format("Raylib texture of '{}' is invalid.", _svgPath_))
    ;
}

auto svgr::SVGSprite::destroyRasterized_() const -> void {
    if (!getRaylibTexture_()) return;
    UnloadTexture(_raylibTexture);
}

auto svgr::SVGSprite::rasterize_() const -> void {
    destroyRasterized_();
    _rasterizeTexture_(_svgPath_, _raylibTexture);
}