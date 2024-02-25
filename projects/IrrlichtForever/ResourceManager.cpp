// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include <algorithm>
#include "Pazu/Resource.hpp"
#include "ResourceManager.hpp"

namespace Irr
{
	ResourceManager::ResourceManager(const Pointer<irr::IFileSystem> &fileSys, const std::array<std::wstring, 2> &basePaths) noexcept
		: fileSys_{fileSys}, basePaths_{basePaths[0], basePaths[1], L""} { }

	void ResourceManager::Initialize() noexcept
	{
		RegisterAssets();
	}

	const Pointer<irr::IReadFile> &ResourceManager::Load(const std::wstring &resourcePath) noexcept
	{
		Wcm::Log->Info("Resource is loading...");
		if (const auto pos = cache_.find(resourcePath); pos != cache_.cend())
        {
			return pos->second; // If the given resource path is an empty string then return nullptr (first added value).
        }
		Wcm::Log->Info("Resource cannot loaded from memory trying to load from in disk...");
		if (const auto res = Pazu::GetResource(Wcm::ToString(GetBasePath(true) + resourcePath)); res)
		{
			return CacheResource(resourcePath, GrabCreatedPtr(fileSys_->createMemoryReadFile(const_cast<unsigned char *>(res.value().data()), res.value().length(), resourcePath.c_str())));
		}
		if (const auto res = fileSys_->createAndOpenFile((GetBasePath() + resourcePath).c_str()); res)
		{
			return CacheResource(resourcePath, GrabCreatedPtr(res));
		}
		Wcm::Log->Error("Resource cannot loaded.").Sub("Resource", resourcePath);
		return cache_[L""];
	}

	const Pointer<irr::IReadFile> &ResourceManager::CacheResource(const std::wstring &resourcePath, const Pointer<irr::IReadFile> &resource) noexcept
	{
		return cache_[resourcePath] = resource;
	}

	const std::wstring &ResourceManager::GetBasePath(const bool isMemory) const noexcept
	{
		return basePaths_[isMemory];
	}

	bool ResourceManager::IsRelative() const noexcept
	{
		return isRelative;
	}

	void ResourceManager::SetBasePath(const std::wstring &path, const std::source_location &location) noexcept
	{
		SetBasePath({path, path}, location);
	}

	void ResourceManager::SetBasePath(const std::wstring &path, const bool isMemory, const std::source_location &location) noexcept
	{
		if (path.ends_with('/') || path.ends_with('\\'))
		{
			basePaths_[isMemory] = path;
		}
		else
		{
			basePaths_[isMemory] = path + Wcm::WSeparator;
		}
		if (isMemory)
		{
			basePaths_[2] = Wcm::ToBaseDirectory(location.file_name()) / Wcm::ToPathName(basePaths_[1]);
			for (auto i = 1uz; i < basePaths_.size(); ++i)
			{
				std::replace(basePaths_[i].begin(), basePaths_[i].end(), '\\', '/'); // Pazu Resource is does not supports back-slashes as a seperator.
			}
		}
		else if (!isMemory && isRelative)
		{
			basePaths_[0] = (Wcm::GetBaseDirectory() / basePaths_[0]).native();
		}
	}

	void ResourceManager::SetBasePath(const std::array<std::wstring, 2> &basePaths, const std::source_location &location) noexcept
	{
		for (auto i = 0uz; i < basePaths.size(); ++i)
		{
			SetBasePath(basePaths[i], i, location);
		}
	}

	void ResourceManager::SetRelativeMode(const bool enabled) noexcept
	{
		isRelative = enabled;
	}

    void ResourceManager::RegisterAssets() noexcept
    {
		Wcm::Execute(GetGeneratorPath(), Wcm::ToQuoted(L"--OutDir") + L' ' + Wcm::ToQuoted(basePaths_[0]) + L' ' + Wcm::ToQuoted(L"--BaseDirName") + L' ' +
					 Wcm::ToQuoted(Wcm::ToPathName(basePaths_[1])) + L' ' + Wcm::ToQuoted(L"--DirList") + L' ' + Wcm::ToQuoted(basePaths_[2]));
    }

	std::wstring ResourceManager::GetGeneratorPath() const noexcept
	{
		return Wcm::GetSourceDirectory() / "ResourceGenerator" / "ResourceGenerator.exe";
	}
}
