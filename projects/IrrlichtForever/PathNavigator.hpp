// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once

namespace Irr
{
	struct PathNavigator final
	{
		const PathNavigator &ToNextFolder(irr::path &currentPath, const irr::stringw &folderName) const noexcept;
		const PathNavigator &ToNextFolder(irr::path &currentPath, std::initializer_list<irr::stringw> folderNames) const noexcept;
		const PathNavigator &ToBackFolder(irr::path &currentPath) const noexcept;
		const PathNavigator &ToBackFolder(irr::path &currentPath, const unsigned int backCount) const noexcept;
		[[nodiscard]] char FindSeparator(const irr::path &path, std::initializer_list<char> separatorsToFind = {{'\\'}, {'/'}}) const noexcept;
	};
}
