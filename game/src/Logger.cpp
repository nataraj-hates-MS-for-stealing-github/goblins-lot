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

#include <fstream>
#include <cassert>

#include <boost/iostreams/tee.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#define BOOST_FILESYSTEM_VERSION 3
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

#include "Logger.hpp"

namespace Logger {
	std::ofstream log_file;
	TeeDevice tee_device(std::cout, log_file);
	TeeStream log(tee_device);
	
	TeeStream& Prefix(const char *file, int line, const char *function) {
		log <<
			"C++ (`" << fs::path(file).filename().string() << "` @ " <<
			line << "), `" << function << "`:\n\t"
		;
		log.flush();
		return log;
	}
	
	const char* Suffix() {
		return "\n================================\n";
	}
	
	void OpenLogFile(const std::string& logFile) {
		// no buffering
		log_file.rdbuf()->pubsetbuf(0, 0);
		log_file.open(logFile.c_str());
		log_file.rdbuf()->pubsetbuf(0, 0);

		
		LOG("Log opened " << boost::posix_time::second_clock::local_time());
		// Instead of explicit closing: to ensure it's always flushed at the end, even when we bail out with exit().
		atexit(CloseLogFile);
	}
	
	void CloseLogFile() {
		LOG("Log closed");
		log.close();
	}
}
