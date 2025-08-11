#pragma once
#include <print>
#include <array>
#include "../svg_texture/svg_texture.hxx"
#include "../../3rd/raylib/include/raylib.h"

auto clampf(float value, float min, float max) -> float;

template<std::size_t N>
auto draw(const std::array<SVGTexture, N> &svgs_) -> void;

#include "draw.txx"