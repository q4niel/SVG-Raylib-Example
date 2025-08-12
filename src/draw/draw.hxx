#pragma once
#include <print>
#include <array>
#include "../svg_renderable/svg_sprite.hxx"
#include "../../3rd/raylib/include/raylib.h"

template<std::size_t N>
auto draw(const std::array<svgr::SVGSprite, N> &svgs_) -> void;

#include "draw.txx"