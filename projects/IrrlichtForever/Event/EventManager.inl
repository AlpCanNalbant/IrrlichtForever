// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

namespace Irr
{
    inline void EventManager::ResetLastInputStates() const noexcept
    {
        Mouse->ResetLastState({ButtonState::Hit, ButtonState::Up, ButtonState::DoubleHit, ButtonState::TripleHit});
        Keyboard->ResetLastState({KeyState::Hit, KeyState::Up});
    }
}