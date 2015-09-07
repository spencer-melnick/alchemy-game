#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <time.h>

#include "systemsList.h"

#define Log(msg, level, system) Logger::log(msg, level, system, __FILE__, __LINE__)

namespace Engine
{

	enum LogLevel {
		LOG_DEBUG = 1,
		LOG_WARNING = 2
	};

	class Logger {
	public:
		static void log(std::string message, LogLevel level, SystemName system, const char* file, int line);
		static void setOutput(std::ostream& output);
		static void setReportLevel(LogLevel level);

	private:
		static bool initialized_;
		static std::ostream* output_;
		static LogLevel reportLevel_;
	};

}
