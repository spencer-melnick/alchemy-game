#pragma once

namespace Engine
{
	using Id = unsigned int;

	template <typename base, typename derived>
	class Type;

	template <typename base>
	class TypeCounter {
		template <typename T, typename U>
		friend class Type;

	protected:
		Id static requestId() {
			return lastId_++;
		}

	private:
		static Id lastId_;
	};

	template <typename base, typename derived>
	class Type {
	public:
		Id static getId() {
			if (!initialized_) {
				currentId_ = TypeCounter<base>::requestId();
				initialized_ = true;
			}

			return currentId_;
		}

	private:
		static bool initialized_;
		static Id currentId_;
	};

}
