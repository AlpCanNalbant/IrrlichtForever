// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

namespace Irr
{
    inline bool Keyboard::IsKeyDown(const Key key) const noexcept
    {
        return GetState(key, KeyState::Down);
    }

    inline bool Keyboard::IsKeyHit(const Key key) const noexcept
    {
        return GetState(key, KeyState::Hit);
    }

    inline bool Keyboard::IsKeyUp(const Key key) const noexcept
    {
        return GetState(key, KeyState::Up);
    }

    inline bool Keyboard::GetKeyState(const Key key, const KeyState state) const noexcept
    {
        return GetState(key, state);
    }
}