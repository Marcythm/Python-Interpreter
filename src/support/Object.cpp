#include "Object.hpp"

const innerTypes::None Object::NONE;
innerTypes::None *const Object::noneptr(const_cast<innerTypes::None*>(&NONE));
