#include "Object.hpp"

ObjectBool::ObjectBool(): value(false) {}

ObjectBool::ObjectBool(const iinf &val): value(not val.iszero()) {}
ObjectBool::ObjectBool(const str &s): value(not s.empty()) {}
ObjectBool::ObjectBool(const char *&&s): value(*s != 0) {}
ObjectBool::ObjectBool(bool val): value(val) {}
ObjectBool::ObjectBool(f64 val): value(val != 0) {}

ObjectBool::~ObjectBool() = default;
