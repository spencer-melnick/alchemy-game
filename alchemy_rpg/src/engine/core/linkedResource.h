#pragma once

#include <list>

namespace Engine
{

	class LinkedResource {
	public:
		void destroy();
		void recreate();

		void linkResource(LinkedResource* resource);
		void unlinkResource(LinkedResource* resource);

	protected:
		LinkedResource() = default;

		virtual void onDestroy() {};
		virtual void onRecreate() {};

	private:
		std::list<LinkedResource*> resources_;

	};

}
