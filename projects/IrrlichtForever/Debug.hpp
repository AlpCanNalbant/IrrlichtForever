// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once

#include "Utility/Concepts.hpp"

namespace Irr
{
    template <ReferenceCountable T>
    class Pointer;

    template <std::derived_from<irr::IReferenceCounted> T>
    const irr::c8 *GetDebugName(const T *ptr) noexcept;
    template <std::derived_from<irr::IReferenceCounted> T>
    const irr::c8 *GetDebugName(const Pointer<T> &ptr) noexcept;
}

#include "Debug.inl"
