#include "draw.hxx"

auto clampf(float value, float min, float max) -> float {
    return (value < min) ? min : (value > max) ? max : value;
}