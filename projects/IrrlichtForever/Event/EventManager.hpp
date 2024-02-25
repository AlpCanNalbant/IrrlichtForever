// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include "Mouse.hpp"
#include "Keyboard.hpp"

namespace Irr
{
    class EventManager final : public irr::IEventReceiver
    {
    public:
        bool OnEvent(const irr::SEvent &event) noexcept final;
        void ResetLastInputStates() const noexcept;

        std::shared_ptr<Mouse> Mouse{std::make_shared<Irr::Mouse>()};
        std::shared_ptr<Keyboard> Keyboard{std::make_shared<Irr::Keyboard>()};
    };
}

#include "EventManager.inl"
