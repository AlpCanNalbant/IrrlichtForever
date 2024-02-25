// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include "EventManager.hpp"

namespace Irr
{
    bool EventManager::OnEvent(const irr::SEvent &event) noexcept
    {
        switch (event.EventType)
        {
        case irr::EET_MOUSE_INPUT_EVENT:
        {
            const auto &in = event.MouseInput;
            const auto &ev = in.Event;
            const auto &button = static_cast<Button>(in.ButtonStates);

            // Try bitwise equality on this.
            if (ev == irr::EMIE_LMOUSE_PRESSED_DOWN || ev == irr::EMIE_LMOUSE_LEFT_UP || ev == irr::EMIE_RMOUSE_PRESSED_DOWN || ev == irr::EMIE_RMOUSE_LEFT_UP || ev == irr::EMIE_MMOUSE_PRESSED_DOWN || ev == irr::EMIE_MMOUSE_LEFT_UP)
            {
                const auto &isDown = in.ButtonStates != 0;

                Mouse->SetState(button, ButtonState::Up, !isDown);
                Mouse->SetState(button, ButtonState::Hit, Mouse->GetState(button, ButtonState::Down));
                Mouse->SetState(button, ButtonState::Down, isDown);
                Mouse->StoreLastCode(button);
            }
            else if (ev == irr::EMIE_LMOUSE_DOUBLE_CLICK || ev == irr::EMIE_RMOUSE_DOUBLE_CLICK || ev == irr::EMIE_MMOUSE_DOUBLE_CLICK)
            {
                Mouse->SetState(button, ButtonState::DoubleHit, true);
            }
            else if (ev == irr::EMIE_LMOUSE_TRIPLE_CLICK || ev == irr::EMIE_RMOUSE_TRIPLE_CLICK || ev == irr::EMIE_MMOUSE_TRIPLE_CLICK)
            {
                Mouse->SetState(button, ButtonState::TripleHit, true);
            }
            else if (ev == irr::EMIE_MOUSE_MOVED)
            {
                Mouse->x_ = in.X;
                Mouse->y_ = in.Y;
            }
            else if (ev == irr::EMIE_MOUSE_WHEEL)
            {
                Mouse->wheel_ = in.Wheel;
            }
        }
            return false;
        case irr::EET_KEY_INPUT_EVENT:
        {
            const auto &in = event.KeyInput;
            const auto &key = static_cast<Key>(in.Key);

            Keyboard->SetState(key, KeyState::Up, !in.PressedDown);
            Keyboard->SetState(key, KeyState::Hit, Keyboard->GetKeyState(key, KeyState::Down) && in.PressedDown);
            Keyboard->SetState(key, KeyState::Down, in.PressedDown);
            Keyboard->StoreLastCode(key);
        }
            return false;
        default:
            return false;
        }
    }
}
