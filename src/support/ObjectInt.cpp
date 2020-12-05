#include "Object.hpp"

/* ---------- construtors ---------- */
ObjectInt::ObjectInt() = default;
ObjectInt::ObjectInt(iinf &&val): value(std::move(val)) {}

ObjectInt::ObjectInt(const iinf &val): value(val) {}
ObjectInt::ObjectInt(const str &s): value(s) {}
ObjectInt::ObjectInt(const char *&&s): value(s) {}
ObjectInt::ObjectInt(bool val): value(val ? 1 : 0) {}
ObjectInt::ObjectInt(f64 val): value(i64(val)) {}

/* ---------- destructor ---------- */
ObjectInt::~ObjectInt() = default;


ObjectInt ObjectInt::asInt() const { return *this; }
ObjectStr ObjectInt::asStr() const { return ObjectStr(value); }
ObjectBool ObjectInt::asBool() const { return ObjectBool(value); }
ObjectFloat ObjectInt::asFloat() const { return ObjectFloat(value); }


/* ---------- comparison operators ---------- */
template <> i32 ObjectInt::cmp<ObjectInt>(const ObjectInt &rhs) const {
	return value.cmp(rhs.value);
}
template <> i32 ObjectInt::cmp<ObjectBool>(const ObjectBool &rhs) const {
	return cmp(rhs.asInt());
}
template <> i32 ObjectInt::cmp<ObjectFloat>(const ObjectFloat &rhs) const {
	return cmp(rhs.asInt());
}
template <typename T> i32 ObjectInt::cmp(const T &rhs) const {
	throw std::invalid_argument(str("TypeError: comparison not supported between instances of 'int' and ") + typeid(T).name());
}
