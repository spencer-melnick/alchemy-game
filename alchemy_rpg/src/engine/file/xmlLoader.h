#pragma once

#include <tinyxml2.h>

#include "resource.h"

namespace Engine
{
	class XmlProcessor {
	public:
		virtual Resource* processXmlFile(tinyxml2::XMLDocument doc);
	};

	class XmlFactory : public ResourceFactory {

	};

}
