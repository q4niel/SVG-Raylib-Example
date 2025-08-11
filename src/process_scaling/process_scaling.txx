#include "process_scaling.hxx"

template<std::size_t N>
auto processScaling(const std::array<SVGTexture, N> &svgs_) -> void {
    if (!isCtrlDown()) return;

    if (const bool up_ = scaleUpModifier(); up_ || scaleDownModifier())
        for (const SVGTexture &svg_ : svgs_) {
            if (up_) svg_.incrementScale_();
            else svg_.decrementScale_();
            svg_.rasterize_();
        }
}