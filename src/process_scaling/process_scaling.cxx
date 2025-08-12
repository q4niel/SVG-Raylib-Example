#include "process_scaling.hxx"

auto _detail_::isCtrlDown() -> const bool {
    return
        IsKeyDown(KEY_LEFT_CONTROL)
    ||  IsKeyDown(KEY_RIGHT_CONTROL)
    ;
}

auto _detail_::isShiftDown() -> const bool {
    return
        IsKeyDown(KEY_LEFT_SHIFT)
    ||  IsKeyDown(KEY_RIGHT_SHIFT)
    ;
}

auto _detail_::scaleUpModifier() -> const bool {
    return
        IsKeyDown(KEY_EQUAL) && _detail_::isShiftDown()
    ||  IsKeyDown(KEY_KP_ADD)
    ||  GetMouseWheelMove() > 0
    ;
}

auto _detail_::scaleDownModifier() -> const bool {
    return
        IsKeyDown(KEY_MINUS)
    ||  IsKeyDown(KEY_KP_SUBTRACT)
    ||  GetMouseWheelMove() < 0
    ;
}