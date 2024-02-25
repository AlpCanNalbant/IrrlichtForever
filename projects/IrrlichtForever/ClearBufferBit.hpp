// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once

namespace Irr
{
    enum class ClearBufferBit : irr::u32
    {
        Color = 0b01,
        Depth = 0b10
    };
}