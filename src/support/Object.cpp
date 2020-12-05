#include "Object.hpp"

const ObjectNone Object::None;

Object::Object(): ptr(const_cast<ObjectNone*>(&None)) {}

Object::~Object() { if (ptr != nullptr) delete ptr; }
