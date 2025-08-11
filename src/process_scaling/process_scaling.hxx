#pragma once
#include <array>
#include "../svg_texture/svg_texture.hxx"

auto isCtrlDown() -> const bool;
auto isShiftDown() -> const bool;
auto scaleUpModifier() -> const bool;
auto scaleDownModifier() -> const bool;

template<std::size_t N>
auto processScaling(const std::array<SVGTexture, N> &svgs_) -> void;

#include "process_scaling.txx"