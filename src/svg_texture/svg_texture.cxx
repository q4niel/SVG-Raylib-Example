#include "svg_texture.hxx"
#include <cstdlib>
#include <cstring>
#include <print>
#include <vector>
#include "../../3rd/resvg/crates/c-api/resvg.h"

SVGTexture::SVGTexture (
    const std::string_view svgPath_,
    const float scale_,
    const float posX_,
    const float posY_
) :
    _svgPath(svgPath_),
    _scale(scale_),
    _posX(posX_),
    _posY(posY_),
    _width(1 * _scale),
    _height(1 * _scale),
    _raylibTexture({}),
    _options_(resvg_options_create()),
    _tree(nullptr)
{
    // Initialize rendering options (DPI, fonts, etc.)
    if (!_options_) {
        std::println("Error: Failed to create resvg options for {}.", _svgPath);
        exit(EXIT_FAILURE);
    }

    // Parse SVG file into a render tree structure
    if (resvg_parse_tree_from_file(_svgPath.c_str(), _options_, &_tree) != RESVG_OK) {
        std::println("Error: Failed to parse SVG: '{}'.", _svgPath);
        exit(EXIT_FAILURE);
    }

    // Initalize texture as 'invalid' if rasterization fails
    _raylibTexture.id = 0;
    rasterize_();
}

SVGTexture::~SVGTexture() {
    destroyRaylibTexture_();
    resvg_tree_destroy(_tree);
}

auto SVGTexture::getRaylibTexture_() const -> RAYLIB_TEXTURE_CALLBACK {
    return (0 == _raylibTexture.id)
        ? std::unexpected(std::format("Raylib texture of '{}' is invalid.", _svgPath))
        : RAYLIB_TEXTURE_CALLBACK{_raylibTexture}
    ;
}

auto SVGTexture::destroyRaylibTexture_() const -> void {
    if (getRaylibTexture_()) return;
    UnloadTexture(_raylibTexture);
    _raylibTexture.id = 0;
}

auto SVGTexture::rasterize_() const -> void {
    destroyRaylibTexture_();

    // Allocate pixel buffer: width * height * 4 (RGBA bytes)
    std::vector<uint8_t> pixels(getWidth_() * getHeight_() * 4, 0);

    resvg_transform transform = resvg_transform_identity();
    transform.a = getWidth_();
    transform.d = getHeight_();

    // Rasterize SVG render tree into pixel buffer
    resvg_render (
        _tree,
        transform,
        static_cast<uint32_t>(getWidth_()),
        static_cast<uint32_t>(getHeight_()),
        (char*)pixels.data()
    );

    // Prepare Raylib Image, which requires malloc’d pixel data buffer
    Image img {
        malloc(pixels.size()),              // Allocate memory Raylib will own
        static_cast<int>(getWidth_()),
        static_cast<int>(getHeight_()),
        1,                                  // Number of mipmaps (1 for no mipmaps)
        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8   // Pixel format: 8 bits per RGBA channel
    };

    // Copy pixels from vector to Raylib Image buffer
    memcpy(img.data, pixels.data(), pixels.size());

    // Upload Image to GPU and get a Texture2D handle
    _raylibTexture = LoadTextureFromImage(img);

    // Free the CPU-side pixel data (Raylib now owns the texture on GPU)
    UnloadImage(img);
}

auto SVGTexture::getSVGPath_() const -> std::string_view {
    return _svgPath;
}

auto SVGTexture::incrementScale_() const -> void {
    _scale += 1;
}

auto SVGTexture::decrementScale_() const -> void {
    _scale -= 1;
}

auto SVGTexture::getPosX_() const -> const float {
    return _posX;
}

auto SVGTexture::setPosX_(const float value_) const -> const float {
    _posX = value_;
    return _posX;
}

auto SVGTexture::getPosY_() const -> const float {
    return _posY;
}

auto SVGTexture::setPosY_(const float value_) const -> const float {
    _posY = value_;
    return _posY;
}

auto SVGTexture::_getAspectRatio() -> const float {
    return getWidth_() / getHeight_();
}

auto SVGTexture::getWidth_() const -> const float {
    return _width * _scale;
}

auto SVGTexture::setWidth_(const float value_) const -> void {
    _width = value_ * _scale;
}

auto SVGTexture::getHeight_() const -> const float {
    return _height * _scale;
}

auto SVGTexture::setHeight_(const float value_) const -> void {
    _height = value_ * _scale;
}