#include "Object.hpp"

/* ---------- construtors ---------- */
ObjectFloat::ObjectFloat(): value(0) {}

ObjectFloat::ObjectFloat(const iinf &val): value(val.to<f64>()) {}
ObjectFloat::ObjectFloat(const str &s): value(std::stod(s)) {}
ObjectFloat::ObjectFloat(const char *&&s): value(std::stod(s)) {}
ObjectFloat::ObjectFloat(bool val): value(val ? 1 : 0) {}
ObjectFloat::ObjectFloat(f64 val): value(val) {}

/* ---------- destructor ---------- */
ObjectFloat::~ObjectFloat() = default;


ObjectInt ObjectFloat::asInt() const { return ObjectInt(value); }
ObjectStr ObjectFloat::asStr() const { return ObjectStr(value); }
ObjectBool ObjectFloat::asBool() const { return ObjectBool(value); }
ObjectFloat ObjectFloat::asFloat() const { return *this; }


/* ---------- comparison operators ---------- */
template <> i32 ObjectFloat::cmp<ObjectInt>(const ObjectInt &rhs) const {
	return asInt().cmp(rhs);
}
template <> i32 ObjectFloat::cmp<ObjectBool>(const ObjectBool &rhs) const {
	return bool(rhs) ? (value > 1 ? 1 : value < 1 ? -1 : 0) : (value > 0 ? 1 : value < 0 ? -1 : 0);
}
template <> i32 ObjectFloat::cmp<ObjectFloat>(const ObjectFloat &rhs) const {
	return value > rhs.value ? 1 : value < rhs.value ? -1 : 0;
}
template <typename T> i32 ObjectFloat::cmp(const T &rhs) const {
	throw std::invalid_argument(str("TypeError: comparison not supported between instances of 'float' and ") + typeid(T).name());
}
