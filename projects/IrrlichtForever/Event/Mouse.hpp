// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include "InputEventReceiver.hpp"
#include "Button.hpp"
#include "ButtonState.hpp"

namespace Irr
{
    class EventManager;

    class Mouse final : public InputEventReceiver<5uz, 6uz>
    {
        friend EventManager;

    public:
        [[nodiscard]] bool IsButtonDown(const Button button) const noexcept;
        [[nodiscard]] bool IsButtonHit(const Button button) const noexcept;
        [[nodiscard]] bool IsButtonUp(const Button button) const noexcept;
        [[nodiscard]] bool IsButtonDoubleHit(const Button button) const noexcept;
        [[nodiscard]] bool IsButtonTripleHit(const Button button) const noexcept;
        [[nodiscard]] bool GetButtonState(const Button button, const ButtonState state) const noexcept;
        // True if shift key was also pressed.
        [[nodiscard]] bool IsShiftDown() const noexcept;
        // True if ctrl key was also pressed.
        [[nodiscard]] bool IsControlDown() const noexcept;
        // X and Y coordinates of mouse cursor.
        [[nodiscard]] irr::position2di GetPosition() const noexcept;
        [[nodiscard]] irr::s32 GetX() const noexcept;
        [[nodiscard]] irr::s32 GetY() const noexcept;
        // Delta value of mouse wheel.
        [[nodiscard]] irr::f32 GetWheelDelta() const noexcept;

    private:
        irr::s32 x_{}, y_{};
        irr::f32 wheel_{};
        bool isShiftDown_{};
        bool isCtrlDown_{};
    };
}

#include "Mouse.inl"
