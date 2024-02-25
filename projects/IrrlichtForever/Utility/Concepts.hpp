// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once

namespace Irr
{
    template <typename T>
    concept ReferenceCountable = std::derived_from<T, irr::IReferenceCounted>;
}
