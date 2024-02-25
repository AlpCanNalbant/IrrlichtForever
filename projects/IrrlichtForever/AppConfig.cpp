// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include "AppConfig.hpp"

namespace Irr
{
	AppConfig::AppConfig(const std::wstring &windowTitle, const irr::dimension2du &windowSize, const bool fullScreen, const bool vsync,
						 const unsigned int antiAliasing, const unsigned int colorBits, const unsigned int depthBits) noexcept
		: WindowTitle(windowTitle)
	{
		DeviceParams.DeviceType = irr::EIDT_BEST;
		DeviceParams.DriverType = irr::EDT_OPENGL; // IrrDefault:Software
		// deviceParams.hppandleSRGB = true;
		DeviceParams.Stencilbuffer = true;
		// deviceParams.Stereobuffer = true;
		// deviceParams.WithAlphaChannel = true;
		DeviceParams.WindowSize = windowSize;  // IrrDefault:{800, 600}
		DeviceParams.Fullscreen = fullScreen;  // IrrDefault:false
		DeviceParams.Vsync = vsync;			   // IrrDefault:false
		DeviceParams.AntiAlias = antiAliasing; // IrrDefault:0  FullScreen only.
		DeviceParams.Bits = colorBits;		   // IrrDefault:16 FullScreen only.
		DeviceParams.ZBufferBits = depthBits;  // IrrDefault:16
	}

	AppConfig::AppConfig(const std::wstring &windowTitle, const irr::SIrrlichtCreationParameters &deviceParams) noexcept
		: WindowTitle(windowTitle), DeviceParams(deviceParams) {}
}
