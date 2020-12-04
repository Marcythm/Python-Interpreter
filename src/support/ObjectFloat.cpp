#include "Object.hpp"

ObjectFloat::ObjectFloat(): value(0) {}

ObjectFloat::ObjectFloat(const iinf &val): value(std::stod(val.tostr())) {}
ObjectFloat::ObjectFloat(const str &s): value(std::stod(s)) {}
ObjectFloat::ObjectFloat(const char *&&s): value(std::stod(s)) {}
ObjectFloat::ObjectFloat(bool val): value(val ? 1 : 0) {}
ObjectFloat::ObjectFloat(f64 val): value(val) {}

ObjectFloat::~ObjectFloat() = default;
