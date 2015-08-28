#include "type.h"

template <typename base>
Engine::Id Engine::TypeCounter<base>::lastId_ = 0;

template <typename base, typename derived>
bool Engine::Type<base, derived>::initialized_ = false;
