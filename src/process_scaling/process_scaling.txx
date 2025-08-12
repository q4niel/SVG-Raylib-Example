#include "process_scaling.hxx"

template<std::size_t N>
auto processScaling(const std::array<svgr::SVGSprite, N> &svgs_) -> void {
    if (!_detail_::isCtrlDown()) return;

    if (const bool up_ = _detail_::scaleUpModifier(); up_ || _detail_::scaleDownModifier())
        for (const svgr::SVGSprite &svg_ : svgs_) {
            if (up_) svg_.incrementScale_();
            else svg_.decrementScale_();
            svg_.rasterize_();
        }
}