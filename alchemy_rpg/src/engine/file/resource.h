#pragma once

#include <functional>
#include <string>
#include <map>
#include <memory>

namespace Engine
{

	using Hash = size_t;
	using Byte = unsigned char;

	enum class ResourceType
	{
		RESOURCE_TEXTURE
	};

	class Resource {
	public:
		std::hash<std::string> hashFunction;

		Resource(std::string filename, Byte priority);
		virtual ~Resource() = default;

		Hash getId();
		std::string getFilename();
		Byte getPriority();
		virtual ResourceType getType() = 0;

	private:
		Hash id_;
		std::string filename_;
		Byte priority_;
	};

	class ResourceFactory {
	public:
		virtual Resource* loadResource(std::string filename, Byte priority) = 0;
	};

	using ResourceMap = std::map<Hash, Resource*>;

}
