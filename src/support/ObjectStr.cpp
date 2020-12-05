#include "Object.hpp"

/* ---------- construtors ---------- */
ObjectStr::ObjectStr() = default;
ObjectStr::ObjectStr(str &&s): value(std::move(s)) {}

ObjectStr::ObjectStr(const iinf &val): value(std::move(val.to<str>())) {}
ObjectStr::ObjectStr(const str &s): value(s) {}
ObjectStr::ObjectStr(const char *&&s): value(s) {}
ObjectStr::ObjectStr(bool val): value(val ? "True" : "False") {}
ObjectStr::ObjectStr(f64 val): value(std::move(std::to_string(val))) {}

/* ---------- destructor ---------- */
ObjectStr::~ObjectStr() = default;


ObjectInt ObjectStr::asInt() const { return ObjectInt(value); }
ObjectStr ObjectStr::asStr() const { return *this; }
ObjectBool ObjectStr::asBool() const { return ObjectBool(value); }
ObjectFloat ObjectStr::asFloat() const { return ObjectFloat(value); }


/* ---------- comparison operators ---------- */
template <> i32 ObjectStr::cmp<ObjectStr>(const ObjectStr &rhs) const {
	return value.compare(rhs.value);
}
template <typename T> i32 ObjectStr::cmp(const T &rhs) const {
	throw std::invalid_argument(str("TypeError: comparison not supported between instances of 'str' and ") + typeid(T).name());
}
