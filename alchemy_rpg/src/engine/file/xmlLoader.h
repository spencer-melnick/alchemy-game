#pragma once

#include <map>

#include <tinyxml2.h>

#include "../core/log.h"
#include "resource.h"

namespace Engine
{
	class XmlProcessor {
	public:
		virtual Resource* processXmlFile(tinyxml2::XMLHandle doc, std::string filename, Byte priority) = 0;
	};

	class XmlFactory : public ResourceFactory {
	public:
		virtual Resource* loadResource(std::string filename, Byte priority) override;

	protected:
		std::map<std::string, XmlProcessor*> processors_;
	};

}
