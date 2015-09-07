#include "log.h"

using namespace Engine;

void Logger::log(std::string message, LogLevel level, SystemName system, const char* file, int line) {
	if (!initialized_)
		return;

	if (level >= reportLevel_) {
		std::string systemName;
		std::string levelName;

		switch (system) {

		case SystemName::SYSTEM_DISPLAY:
			systemName = "Display System ";
			break;

		case SystemName::SYSTEM_FILE:
			systemName = "File System ";
			break;

		default:
		case SystemName::SYSTEM_GENERAL:
			systemName = "";
			break;

		}

		
		switch (level) {

		case LogLevel::LOG_DEBUG:
			levelName = "Debug ";
			break;
			
		case LogLevel::LOG_WARNING:
			levelName = "Warning ";
			break;

		default:
			levelName == "";
			break;
		}

		
		std::time_t current = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm tstruct;
		localtime_s(&tstruct, &current);
		(*output_) << std::put_time(&tstruct, "%c") << " --- " << systemName << levelName << ": \"" << message << "\" in " << file << " @ ln" << line << "\n";
	}
}

void Logger::setOutput(std::ostream& output) {
	initialized_ = true;
	output_ = &output;
}

void Logger::setReportLevel(LogLevel level) {
	reportLevel_ = level;
}

bool Logger::initialized_ = false;
std::ostream* Logger::output_ = nullptr;

#ifdef DEBUG
LogLevel Logger::reportLevel_ = LogLevel::LOG_DEBUG;
#else
LogLevel Logger::reportLevel_ = LogLevel::LOG_WARNING;
#endif
