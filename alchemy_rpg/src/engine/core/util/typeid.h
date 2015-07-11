#ifndef engine_core_util_typeid_h
#define engine_core_util_typeid_h

#include <typeinfo>

class BaseType {
public:
	size_t getType() {
		return type_;
	}

protected:
	BaseType() :
		type_(0)
	{};

	size_t type_;
};

template <typename T>
class Type: public virtual BaseType
{
public:
	Type() {
		type_ = typeid(T).hash_code();
	}
};

template <typename T>
class StaticType {
public:
	static const size_t getStaticType() {
		if (!initialized_)
		{
			initialized_ = true;
			statictype_ = typeid(T).hash_code();
		}

		return statictype_;
	}

private:
	static size_t statictype_;
	static bool initialized_;
};

template <typename T>
size_t StaticType<T>::statictype_ = 0;

template <typename T>
bool StaticType<T>::initialized_ = 0;

#endif
