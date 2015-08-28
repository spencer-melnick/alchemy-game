#pragma once

#include <exception>
#include <string>

#include "systemsList.h"

#define SdlStringError() std::string(SDL_GetError())

namespace Engine
{

	struct Error : std::exception
	{
		SystemName system;
		bool fatal;
		const std::string error;

		Error(SystemName System, bool Fatal, std::string Error = "");

		virtual const char* what() const throw() override {
			return error.c_str();
		}
	};

}
