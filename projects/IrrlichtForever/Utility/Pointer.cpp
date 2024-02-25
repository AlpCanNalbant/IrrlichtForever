// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include "Pointer.hpp"

namespace Irr
{
    Pointer<irr::IrrlichtDevice> CreateDevice(const irr::E_DRIVER_TYPE deviceType, const irr::dimension2d<irr::u32> &windowSize, const irr::u32 bits,
                                              const bool fullscreen, const bool stencilbuffer, const bool vsync, irr::IEventReceiver *receiver) noexcept
    {
        return {irr::createDevice(deviceType, windowSize, bits, fullscreen, stencilbuffer, vsync, receiver), true};
    }

    Pointer<irr::IrrlichtDevice> CreateDevice(const irr::SIrrlichtCreationParameters &parameters) noexcept
    {
        return {irr::createDeviceEx(parameters), true};
    }
}