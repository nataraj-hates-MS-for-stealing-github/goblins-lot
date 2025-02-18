/* Copyright 2010-2011 Ilkka Halila
             2020-2022 Nikolay Shaplov (aka dhyan.nataraj)
This file is part of Goblins' Lot (former Goblin Camp)

Goblin Camp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Goblin Camp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with Goblin Camp. If not, see <http://www.gnu.org/licenses/>.*/
#include "stdafx.hpp"

#include <sys/types.h>
#include <unistd.h>

#include <boost/filesystem.hpp>
#include <string>
#include <cstring>
#include <cstdlib>

namespace fs = boost::filesystem;

namespace PathsImpl {
	void FindPersonalDirectory(fs::path& dir) {
		// Get config dir according to XDG Base Directory Specification
		// https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html
		if (getenv("XDG_CONFIG_HOME"))
		{
			dir = fs::path(std::string(getenv("XDG_CONFIG_HOME")) + "/goblinw-lot");
		} else
		{
			dir = fs::path(std::string(getenv("HOME")) + "/.config/goblins-lot");
		} // FIXME: what will happen if HOME env var is not set?
	}
	
	void FindExecutableDirectory(fs::path& exec, fs::path& execDir, fs::path& dataDir) {
		char buffer[1024];
		ssize_t pos = readlink("/proc/self/exe", buffer, 1023);
		buffer[pos] = '\0';
		
		exec    = fs::path(std::string(buffer));
		execDir = exec.parent_path();
		dataDir = fs::path(execDir.parent_path()) / "share/games/goblins-lot/";
	}
}
