#include "svg_base.hxx"
#include <cstdlib>
#include <cstring>
#include <print>
#include <vector>
#include <algorithm>
#include <limits>
#include "../../3rd/resvg/crates/c-api/resvg.h"

svgr::SVGBase::SVGBase (
    const float scale_,
    const float posX_,
    const float posY_
) :
    _scale(scale_),
    _posX(posX_),
    _posY(posY_),
    _width(1 * _scale),
    _height(1 * _scale)
{}

auto svgr::SVGBase::incrementScale_() const -> void {
    _scale = std::clamp (
        _scale+1,
        .1f,
        std::numeric_limits<float>::max()
    );
}

auto svgr::SVGBase::decrementScale_() const -> void {
    _scale = std::clamp (
        _scale-1,
        .1f,
        std::numeric_limits<float>::max()
    );
}

auto svgr::SVGBase::getPosX_() const -> const float {
    return _posX;
}

auto svgr::SVGBase::setPosX_(const float value_) const -> const float {
    _posX = value_;
    return _posX;
}

auto svgr::SVGBase::getPosY_() const -> const float {
    return _posY;
}

auto svgr::SVGBase::setPosY_(const float value_) const -> const float {
    _posY = value_;
    return _posY;
}

auto svgr::SVGBase::getWidth_() const -> const float {
    return _width * _scale;
}

auto svgr::SVGBase::setWidth_(const float value_) const -> void {
    _width = value_ * _scale;
}

auto svgr::SVGBase::getHeight_() const -> const float {
    return _height * _scale;
}

auto svgr::SVGBase::setHeight_(const float value_) const -> void {
    _height = value_ * _scale;
}

auto svgr::SVGBase::_getAspectRatio() -> const float {
    return getWidth_() / getHeight_();
}

auto svgr::SVGBase::_rasterizeTexture_ (
    std::string svgPath,
    Texture2D &outTexture
) const -> void {
    // Initialize rendering options (DPI, fonts, etc.)
    const resvg_options *options_ = resvg_options_create();

    if (!options_) {
        std::println("Error: Failed to create resvg options for {}.", svgPath);
        exit(EXIT_FAILURE);
    }

    // Parse SVG file into a render tree structure
    resvg_render_tree *tree = nullptr;

    if (resvg_parse_tree_from_file(svgPath.c_str(), options_, &tree) != RESVG_OK) {
        std::println("Error: Failed to parse SVG: '{}'.", svgPath);
        exit(EXIT_FAILURE);
    }

    // Allocate pixel buffer: width * height * 4 (RGBA bytes)
    std::vector<uint8_t> pixels(getWidth_() * getHeight_() * 4, 0);

    resvg_transform transform = resvg_transform_identity();
    transform.a = getWidth_();
    transform.d = getHeight_();

    // Rasterize SVG render tree into pixel buffer
    resvg_render (
        tree,
        transform,
        static_cast<uint32_t>(getWidth_()),
        static_cast<uint32_t>(getHeight_()),
        (char*)pixels.data()
    );

    // Free the render tree (no longer needed after rasterization)
    resvg_tree_destroy(tree);

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
    outTexture = LoadTextureFromImage(img);

    // Free the CPU-side pixel data (Raylib now owns the texture on GPU)
    UnloadImage(img);
}