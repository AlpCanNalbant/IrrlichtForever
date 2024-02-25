// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include "Utility/Pointer.hpp"
#include "Event/EventManager.hpp"
#include "AppConfig.hpp"
#include "ResourceManager.hpp"
#include "PathNavigator.hpp"
#include "ClearBufferBit.hpp"

namespace Irr
{
	class App
	{
	public:
		App(const std::wstring &windowTitle, const irr::dimension2du &windowSize = {1280, 768}, const bool fullScreen = {false},
			const bool vsync = {false}, const unsigned int antiAliasing = {8}, const unsigned int colorBits = {32},
			const unsigned int depthBits = {24}) noexcept;
		App(const AppConfig &config) noexcept;
		App(const App &) = default;
		App(App &&) = default;
		virtual ~App() = default;
		void Run() noexcept;
		void ShutDown() const noexcept;
		void Clear() const noexcept;
		void Swap() const noexcept;
		irr::path GetBasePath() const noexcept;
		ClearBufferBit GetClearBufferBits() noexcept;
		[[nodiscard]] const irr::path &GetResourcePath() const noexcept;
		void SetClearBufferBits(const ClearBufferBit bufferBits) noexcept;
		void SetResourcePath(const irr::path &resourcePath) noexcept;
		App &operator=(const App &) = default;
		App &operator=(App &&) = default;

		irr::SColor ClearColor{255, 100, 149, 237};

	private:
		void Update() noexcept;
		void Draw() noexcept;

		const std::shared_ptr<EventManager> eventMgr_;

	protected:
		virtual bool OnInit() = 0;
		virtual bool OnLoad() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDraw() = 0;
		virtual void OnUnload() = 0;

		const Pointer<irr::IrrlichtDevice> Device;
		const Pointer<irr::ISceneManager> SceneMgr;
		const Pointer<irr::IVideoDriver> Driver;
		const Pointer<irr::IFileSystem> FileSys;
		const std::shared_ptr<Mouse> Mouse;
		const std::shared_ptr<Keyboard> Keyboard;
		ResourceManager ResourceMgr;

		std::bitset<2> ClearBufferBits{0b11};
	};
}

#include "App.inl"
