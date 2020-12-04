#include "Object.hpp"

ObjectStr::ObjectStr() = default;
ObjectStr::ObjectStr(str &&s): value(std::move(s)) {}

ObjectStr::ObjectStr(const iinf &val): value(std::move(val.tostr())) {}
ObjectStr::ObjectStr(const str &s): value(s) {}
ObjectStr::ObjectStr(const char *&&s): value(s) {}
ObjectStr::ObjectStr(bool val): value(val ? "True" : "False") {}
ObjectStr::ObjectStr(f64 val): value(std::move(std::to_string(val))) {}

ObjectStr::~ObjectStr() = default;
