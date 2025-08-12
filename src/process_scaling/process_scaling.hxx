#pragma once
#include <array>
#include "../svg_renderable/svg_sprite.hxx"

namespace _detail_ {
    auto isCtrlDown() -> const bool;
    auto isShiftDown() -> const bool;
    auto scaleUpModifier() -> const bool;
    auto scaleDownModifier() -> const bool;
}

template<std::size_t N>
auto processScaling(const std::array<svgr::SVGSprite, N> &svgs_) -> void;

#include "process_scaling.txx"