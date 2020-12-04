#include "Object.hpp"

ObjectInt::ObjectInt() = default;
ObjectInt::ObjectInt(iinf &&val): value(std::move(val)) {}

ObjectInt::ObjectInt(const iinf &val): value(val) {}
ObjectInt::ObjectInt(const str &s): value(s) {}
ObjectInt::ObjectInt(const char *&&s): value(s) {}
ObjectInt::ObjectInt(bool val): value(val ? 1 : 0) {}
ObjectInt::ObjectInt(f64 val): value(i64(val)) {}

ObjectInt::~ObjectInt() = default;
