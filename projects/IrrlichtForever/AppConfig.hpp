// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once

namespace Irr
{
	struct AppConfig
	{
		AppConfig(const std::wstring &windowTitle, const irr::dimension2du &windowSize, const bool fullScreen, const bool vsync,
				  const unsigned int antiAliasing, const unsigned int colorBits, const unsigned int depthBits) noexcept;
		AppConfig(const std::wstring &windowTitle, const irr::SIrrlichtCreationParameters &deviceParams) noexcept;

		std::wstring WindowTitle;
		irr::SIrrlichtCreationParameters DeviceParams;
	};
}
