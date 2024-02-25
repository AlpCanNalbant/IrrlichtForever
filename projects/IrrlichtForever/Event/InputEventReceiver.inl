// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

namespace Irr
{
    template <std::size_t TypeSize, std::size_t CodeSize>
    template <typename C, typename T>
        requires std::is_scoped_enum_v<C> && std::is_scoped_enum_v<T>
    bool InputEventReceiver<TypeSize, CodeSize>::GetState(const C code, const T type) const noexcept
    {
        return inputState_[static_cast<std::underlying_type_t<C>>(code)][static_cast<std::underlying_type_t<T>>(type)];
    }

    template <std::size_t TypeSize, std::size_t CodeSize>
    template <typename C, typename T>
        requires std::is_scoped_enum_v<C> && std::is_scoped_enum_v<T>
    void InputEventReceiver<TypeSize, CodeSize>::SetState(const C code, const T type, const bool val) noexcept
    {
        inputState_[static_cast<std::underlying_type_t<C>>(code)][static_cast<std::underlying_type_t<T>>(type)] = val;
    }

    template <std::size_t TypeSize, std::size_t CodeSize>
    template <typename T>
        requires std::is_scoped_enum_v<T>
    void InputEventReceiver<TypeSize, CodeSize>::StoreLastCode(const T code) noexcept
    {
        lastCode_ = static_cast<std::underlying_type_t<T>>(code);
    }

    template <std::size_t TypeSize, std::size_t CodeSize>
    template <typename T>
        requires std::is_scoped_enum_v<T>
    void InputEventReceiver<TypeSize, CodeSize>::ResetLastState(const T type) noexcept
    {
        inputState_[lastCode_][static_cast<std::underlying_type_t<T>>(type)] = false;
    }

    template <std::size_t TypeSize, std::size_t CodeSize>
    template <typename T>
        requires std::is_scoped_enum_v<T>
    void InputEventReceiver<TypeSize, CodeSize>::ResetLastState(std::initializer_list<T> types) noexcept
    {
        for (auto it = types.begin(); it != types.end(); ++it)
        {
            inputState_[lastCode_][static_cast<std::underlying_type_t<T>>(*it)] = false;
        }
    }
}
