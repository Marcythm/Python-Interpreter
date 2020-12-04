#include "Object.hpp"

Object::Object(): ptr(nullptr) {}

Object::~Object() { if (ptr != nullptr) delete ptr; }
