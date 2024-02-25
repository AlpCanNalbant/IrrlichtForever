// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include "InputEventReceiver.hpp"
#include "Key.hpp"
#include "KeyState.hpp"

namespace Irr
{
    class EventManager;

    class Keyboard final : public InputEventReceiver<3uz, irr::KEY_KEY_CODES_COUNT>
    {
        friend EventManager;

    public:
        [[nodiscard]] bool IsKeyDown(const Key key) const noexcept;
        [[nodiscard]] bool IsKeyHit(const Key key) const noexcept;
        [[nodiscard]] bool IsKeyUp(const Key key) const noexcept;
        [[nodiscard]] bool GetKeyState(const Key key, const KeyState state) const noexcept;
    };
}

#include "Keyboard.inl"
