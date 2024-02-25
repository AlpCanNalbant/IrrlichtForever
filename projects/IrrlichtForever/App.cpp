// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#ifdef IRR_FOREVER_WINDOWS
#include <windows.h>
#else
#include <filesystem>
#endif
#include "App.hpp"

namespace Irr
{
	App::App(const std::wstring &windowTitle, const irr::dimension2du &windowSize, const bool fullScreen, const bool vsync,
			 const unsigned int antiAliasing, const unsigned int colorBits, const unsigned int depthBits) noexcept
		: App(AppConfig{windowTitle, windowSize, fullScreen, vsync, antiAliasing, colorBits, depthBits}) {}

	App::App(const AppConfig &config) noexcept
		: eventMgr_{std::make_shared<EventManager>()}, Device{CreateDevice(config.DeviceParams)}, SceneMgr{GrabPtr(Device->getSceneManager())},
		  Driver{GrabPtr(Device->getVideoDriver())}, FileSys{GrabPtr(Device->getFileSystem())},
		  Mouse{eventMgr_->Mouse}, Keyboard{eventMgr_->Keyboard}, ResourceMgr{FileSys}
	{
		SetResourcePath(GetBasePath());
		Device->setEventReceiver(&*eventMgr_);
		Device->setWindowCaption(config.WindowTitle.c_str());
		Device->setResizable(true);
	}

	void App::Run() noexcept
	{
		if (!OnInit()) return;
		ResourceMgr.Initialize();
		if (!OnLoad()) return;

		while (Device->run())
		{
			Update();
			Draw();
			while (!Device->isWindowActive() && Device->run())
				Device->yield();
		}
		OnUnload();
	}

	void App::ShutDown() const noexcept
	{
		Device->closeDevice();
	}

	irr::path App::GetBasePath() const noexcept
	{
#ifdef IRR_FOREVER_WINDOWS // On WindowsOS don't use C++ 17.
		std::array<WCHAR, MAX_PATH> path{'\0'};
		irr::path result(path.data());
		GetModuleFileNameW(NULL, path.data(), MAX_PATH);
		PathNavigator{}.ToBackFolder(result);
		return result;
#else
		return {std::filesystem::current_path().c_str()};
#endif
	}

	ClearBufferBit App::GetClearBufferBits() noexcept
	{
		return magic_enum::enum_value<ClearBufferBit>(ClearBufferBits.to_ulong());
	}

	const irr::path &App::GetResourcePath() const noexcept
	{
		return FileSys->getWorkingDirectory();
	}

	void App::SetClearBufferBits(const ClearBufferBit bufferBits) noexcept
	{
		ClearBufferBits = {magic_enum::enum_integer(bufferBits)};
	}

	void App::SetResourcePath(const irr::path &resourcePath) noexcept
	{
		FileSys->changeWorkingDirectoryTo(resourcePath);
	}

	void App::Update() noexcept
	{
		OnUpdate();
		eventMgr_->ResetLastInputStates();
	}

	void App::Draw() noexcept
	{
		Clear();
		OnDraw();
		SceneMgr->drawAll();
		Swap();
	}
}
