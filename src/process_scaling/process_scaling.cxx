#include "process_scaling.hxx"

auto isCtrlDown() -> const bool {
    return
        IsKeyDown(KEY_LEFT_CONTROL)
    ||  IsKeyDown(KEY_RIGHT_CONTROL)
    ;
}

auto isShiftDown() -> const bool {
    return
        IsKeyDown(KEY_LEFT_SHIFT)
    ||  IsKeyDown(KEY_RIGHT_SHIFT)
    ;
}

auto scaleUpModifier() -> const bool {
    return
        IsKeyDown(KEY_EQUAL) && isShiftDown()
    ||  IsKeyDown(KEY_KP_ADD)
    ||  GetMouseWheelMove() > 0
    ;
}

auto scaleDownModifier() -> const bool {
    return
        IsKeyDown(KEY_MINUS)
    ||  IsKeyDown(KEY_KP_SUBTRACT)
    ||  GetMouseWheelMove() < 0
    ;
}