// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include <unordered_map>
#include <array>
#include "Utility/Pointer.hpp"
#include "WinAPICommon.hpp"

namespace Irr
{
	class ResourceManager
	{
	public:
		ResourceManager(const Pointer<irr::IFileSystem> &fileSys, const std::array<std::wstring, 2> &basePaths = {}) noexcept;
		void Initialize() noexcept;
		[[nodiscard]] const Pointer<irr::IReadFile> &Load(const std::wstring &resourcePath) noexcept;
		const Pointer<irr::IReadFile> &CacheResource(const std::wstring &resourcePath, const Pointer<irr::IReadFile> &resource) noexcept;
		[[nodiscard]] const std::wstring &GetBasePath(const bool isMemory = false) const noexcept;
		[[nodiscard]] bool IsRelative() const noexcept;
		void SetBasePath(const std::wstring &path, const std::source_location &location = std::source_location::current()) noexcept;
		void SetBasePath(const std::wstring &path, const bool isMemory, const std::source_location &location = std::source_location::current()) noexcept;
		void SetBasePath(const std::array<std::wstring, 2> &basePaths, const std::source_location &location = std::source_location::current()) noexcept;
		void SetRelativeMode(const bool enabled) noexcept;

		bool isRelative{true};

	private:
		void RegisterAssets() noexcept;
		[[nodiscard]] std::wstring GetGeneratorPath() const noexcept;

		const Pointer<irr::IFileSystem> fileSys_;
		std::unordered_map<std::wstring, Pointer<irr::IReadFile>> cache_{{L"", nullptr}};
		std::array<std::wstring, 3> basePaths_;
	};
}
