#pragma once
#include <print>
#include <array>
#include "../svg_texture/svg_texture.hxx"
#include "../../3rd/raylib/include/raylib.h"

template<std::size_t N>
auto draw(const std::array<SVGTexture, N> &svgs_) -> void;

#include "draw.txx"