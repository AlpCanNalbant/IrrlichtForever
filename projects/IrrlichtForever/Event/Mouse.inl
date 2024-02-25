// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

namespace Irr
{
    inline bool Mouse::IsButtonDown(const Button button) const noexcept
    {
        return GetState(button, ButtonState::Down);
    }

    inline bool Mouse::IsButtonHit(const Button button) const noexcept
    {
        return GetState(button, ButtonState::Hit);
    }

    inline bool Mouse::IsButtonUp(const Button button) const noexcept
    {
        return GetState(button, ButtonState::Up);
    }

    inline bool Mouse::IsButtonDoubleHit(const Button button) const noexcept
    {
        return GetState(button, ButtonState::DoubleHit);
    }

    inline bool Mouse::IsButtonTripleHit(const Button button) const noexcept
    {
        return GetState(button, ButtonState::TripleHit);
    }

    inline bool Mouse::GetButtonState(const Button button, const ButtonState state) const noexcept
    {
        return GetState(button, state);
    }

    inline bool Mouse::IsShiftDown() const noexcept
    {
        return isShiftDown_;
    }

    inline bool Mouse::IsControlDown() const noexcept
    {
        return isCtrlDown_;
    }

    inline irr::position2di Mouse::GetPosition() const noexcept
    {
        return {x_, y_};
    }

    inline irr::s32 Mouse::GetX() const noexcept
    {
        return x_;
    }

    inline irr::s32 Mouse::GetY() const noexcept
    {
        return y_;
    }

    inline irr::f32 Mouse::GetWheelDelta() const noexcept
    {
        return wheel_;
    }
}