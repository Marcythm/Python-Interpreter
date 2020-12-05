#include "Object.hpp"

/* ---------- construtors ---------- */
ObjectBool::ObjectBool(): value(false) {}

ObjectBool::ObjectBool(const iinf &val): value(val.to<bool>()) {}
ObjectBool::ObjectBool(const str &s): value(not s.empty()) {}
ObjectBool::ObjectBool(const char *&&s): value(*s != 0) {}
ObjectBool::ObjectBool(bool val): value(val) {}
ObjectBool::ObjectBool(f64 val): value(val != 0) {}

/* ---------- destructor ---------- */
ObjectBool::~ObjectBool() = default;


ObjectInt ObjectBool::asInt() const { return ObjectInt(value); }
ObjectStr ObjectBool::asStr() const { return ObjectStr(value); }
ObjectBool ObjectBool::asBool() const { return *this; }
ObjectFloat ObjectBool::asFloat() const { return ObjectFloat(value); }


/* ---------- comparison operators ---------- */
template <> i32 ObjectBool::cmp<ObjectInt>(const ObjectInt &rhs) const {
	return asInt().cmp(rhs);
}
template <> i32 ObjectBool::cmp<ObjectBool>(const ObjectBool &rhs) const {
	return (value == rhs.value) ? 0 : (value ? 1 : -1);
}
template <> i32 ObjectBool::cmp<ObjectFloat>(const ObjectFloat &rhs) const {
	const f64 val = f64(rhs);
	return value ? (1 > val ? 1 : 1 < val ? -1 : 0) : (0 > val ? 1 : 1 < val ? -1 : 0);
	// return i32(value) <=> f64(rhs);
}
template <typename T> i32 ObjectBool::cmp(const T &rhs) const {
	throw std::invalid_argument(str("TypeError: comparison not supported between instances of 'bool' and ") + typeid(T).name());
}
