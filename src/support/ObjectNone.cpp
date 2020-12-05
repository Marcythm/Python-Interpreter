#include "Object.hpp"

ObjectNone::ObjectNone() = default;
ObjectNone::~ObjectNone() = default;


ObjectInt ObjectNone::asInt() const { return ObjectInt(); }
ObjectStr ObjectNone::asStr() const { return ObjectStr("None"); }
ObjectBool ObjectNone::asBool() const { return ObjectBool(); }
ObjectFloat ObjectNone::asFloat() const { return ObjectFloat(); }
