// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include "PathNavigator.hpp"

namespace Irr
{
	const PathNavigator &PathNavigator::ToNextFolder(irr::path &currentPath, const irr::stringw &folderName) const noexcept
	{
		if (auto separator = FindSeparator(currentPath); separator != '\0')
		{
			currentPath += separator;
			currentPath += folderName;
		}
		return *this;
	}

	const PathNavigator &PathNavigator::ToNextFolder(irr::path &currentPath, std::initializer_list<irr::stringw> folderNames) const noexcept
	{
		for (auto &folderName : folderNames)
		{
			ToNextFolder(currentPath, folderName);
		}
		return *this;
	}

	const PathNavigator &PathNavigator::ToBackFolder(irr::path &currentPath) const noexcept
	{
		if (auto separator = FindSeparator(currentPath); separator != '\0')
		{
			currentPath.remove(currentPath.subString(currentPath.findLast(separator), currentPath.size()));
		}
		return *this;
	}

	const PathNavigator &PathNavigator::ToBackFolder(irr::path &currentPath, const unsigned int backCount) const noexcept
	{
		for (unsigned int i = 0; i < backCount; ++i)
		{
			ToBackFolder(currentPath);
		}
		return *this;
	}

	char PathNavigator::FindSeparator(const irr::path &path, std::initializer_list<char> separatorsToFind) const noexcept
	{
		for (unsigned int i = 0; i < path.size(); ++i)
		{
			for (auto &separator : separatorsToFind)
			{
				if (path[i] == separator)
				{
					return separator;
				}
			}
		}
		return '\0';
	}
}
