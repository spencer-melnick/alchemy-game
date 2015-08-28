#include "error.h"

Engine::Error::Error(SystemName System, bool Fatal, const std::string Error) :
	system(System), fatal(Fatal), error(Error), std::exception() {}
