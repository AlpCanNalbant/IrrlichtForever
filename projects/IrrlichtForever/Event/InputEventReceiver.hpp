// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include <type_traits>
#include <array>
#include "EventReceiver.hpp"

namespace Irr
{
    template <std::size_t TypeSize, std::size_t CodeSize>
    class InputEventReceiver : public EventReceiver
    {
    public:
        InputEventReceiver() = default;
        InputEventReceiver(const InputEventReceiver &) = default;
        InputEventReceiver(InputEventReceiver &&) = default;
        InputEventReceiver &operator=(const InputEventReceiver &) = default;
        InputEventReceiver &operator=(InputEventReceiver &&) = default;

    protected:
        ~InputEventReceiver() = default;
        template <typename C, typename T>
            requires std::is_scoped_enum_v<C> && std::is_scoped_enum_v<T>
        bool GetState(const C code, const T type) const noexcept;
        template <typename C, typename T>
            requires std::is_scoped_enum_v<C> && std::is_scoped_enum_v<T>
        void SetState(const C code, const T type, const bool val) noexcept;
        template <typename T>
            requires std::is_scoped_enum_v<T>
        void StoreLastCode(const T code) noexcept;
        template <typename T>
            requires std::is_scoped_enum_v<T>
        void ResetLastState(const T type) noexcept;
        template <typename T>
            requires std::is_scoped_enum_v<T>
        void ResetLastState(std::initializer_list<T> types) noexcept;

    private:
        std::array<std::bitset<TypeSize>, CodeSize> inputState_{false};
        irr::u32 lastCode_{0u};
    };
}

#include "InputEventReceiver.inl"
