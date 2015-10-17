#include "xmlLoader.h"

using namespace Engine;

Resource* XmlFactory::loadResource(std::string filename, Byte priority) {
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError loadSuccess = doc.LoadFile(filename.c_str());

	if (loadSuccess != tinyxml2::XML_NO_ERROR) {
		Log("Unable to open XML file " + filename, LogLevel::LOG_WARNING, SystemName::SYSTEM_FILE);
		return nullptr;
	}

	tinyxml2::XMLElement* mainElement = doc.FirstChildElement("alchemy");

	if (mainElement == nullptr) {
		Log(filename + " is not an alchemy-engine XML file", LogLevel::LOG_WARNING, SystemName::SYSTEM_FILE);
		return nullptr;
	}

	const char* typeRaw = mainElement->Attribute("filetype");
	
	if (typeRaw == nullptr) {
		Log(filename + " does not have a valid resource type", LogLevel::LOG_WARNING, SystemName::SYSTEM_FILE);
		return nullptr;
	}

	std::string type(typeRaw);

	for (auto i : processors_) {
		if (i.first == type)
			return i.second->processXmlFile(tinyxml2::XMLHandle(doc), filename, priority);
	}

	Log("Could not find the XML processor for type \"" + type + "\" in " + filename, LogLevel::LOG_WARNING, SystemName::SYSTEM_FILE);
	return nullptr;
}
