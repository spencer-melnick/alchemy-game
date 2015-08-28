#pragma once

#include <functional>
#include <string>
#include <map>
#include <memory>

namespace Engine
{

	using Hash = size_t;

	enum class ResourceType
	{
		RESOURCE_TEXTURE
	};

	class Resource {
	public:
		std::hash<std::string> hashFunction;

		Resource(std::string filename);
		virtual ~Resource() = default;

		Hash getId();
		std::string getFilename();
		virtual ResourceType getType() = 0;

	private:
		Hash id_;
		std::string filename_;
	};

	using ResourceMap = std::map<Hash, std::unique_ptr<Resource> >;

}
