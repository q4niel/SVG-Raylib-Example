#include "svg_texture.hxx"
#include <cstdlib>
#include <cstring>
#include <print>
#include <vector>
#include "../3rd/resvg/crates/c-api/resvg.h"

SVGTexture::SVGTexture (
    const std::string_view svgPath,
    const int width,
    const int height
) :
    _svgPath(svgPath),
    _width(width),
    _height(height)
{
    // Initialize rendering options (DPI, fonts, etc.)
    const resvg_options *options = resvg_options_create();
    if (!options) {
        std::println("Error: Failed to create resvg options.");
        exit(EXIT_FAILURE);
    }

    // Parse SVG file into a render tree structure
    resvg_render_tree *tree = nullptr;
    if (resvg_parse_tree_from_file(_svgPath.c_str(), options, &tree) != RESVG_OK) {
        std::println("Error: Failed to parse SVG: '{}'.", svgPath);
        exit(EXIT_FAILURE);
    }

    // Allocate pixel buffer: width * height * 4 (RGBA bytes)
    std::vector<uint8_t> pixels(_width * _height * 4, 0);

    // Define viewport for rendering: origin (0,0), size width x height
    resvg_rect viewport = {0, 0, (float)_width, (float)_height};

    // Rasterize SVG render tree into pixel buffer
    resvg_render (
        tree,
        resvg_transform_identity(),
        viewport.width,
        viewport.height,
        (char*)pixels.data()
    );

    // Free the render tree (no longer needed)
    resvg_tree_destroy(tree);

    // Prepare Raylib Image, which requires malloc’d pixel data buffer
    Image img {
        malloc(pixels.size()),          // Allocate memory Raylib will own
        _width,
        _height,
        1,                             // Number of mipmaps (1 for no mipmaps)
        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8  // Pixel format: 8 bits per RGBA channel
    };

    // Copy pixels from vector to Raylib Image buffer
    memcpy(img.data, pixels.data(), pixels.size());

    // Upload Image to GPU and get a Texture2D handle
    _raylibTexture = LoadTextureFromImage(img);

    // Free the CPU-side pixel data (Raylib now owns the texture on GPU)
    UnloadImage(img);
}

auto SVGTexture::getRaylibTexture() -> RAYLIB_TEXTURE_CALLBACK {
    return (0 == _raylibTexture.id)
        ? std::unexpected(std::format("Raylib texture of '{}' is invalid.", _svgPath))
        : RAYLIB_TEXTURE_CALLBACK{_raylibTexture}
    ;
}

auto SVGTexture::getWidth() -> const int {
    return _width;
}
auto SVGTexture::setWidth(const int value) -> const int {
    _width = value;
    return _width;
}

auto SVGTexture::getHeight() -> const int {
    return _height;
}
auto SVGTexture::setHeight(const int value) -> const int {
    _height = value;
    return _height;
}