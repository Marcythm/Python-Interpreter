#include "Object.hpp"

namespace innerTypes {

/* ---------- construtors ---------- */
Int::Int() = default;
Int::Int(iinf &&val): value(std::move(val)) {}

Int::Int(const iinf &val): value(val) {}
Int::Int(const str &s): value(s) {}
Int::Int(const char *&&s): value(s) {}
Int::Int(bool val): value(val ? 1 : 0) {}
Int::Int(f64 val): value(i64(val)) {}

/* ---------- destructor ---------- */
Int::~Int() = default;


Int Int::asInt() const { return *this; }
Str Int::asStr() const { return Str(value); }
Bool Int::asBool() const { return Bool(value); }
Float Int::asFloat() const { return Float(value); }


/* ---------- comparison operators ---------- */
template <> i8 Int::compare<Int>(const Int &rhs) const { return value.compare(rhs.value); }
template <> i8 Int::compare<Bool>(const Bool &rhs) const { return compare(rhs.asInt()); }
template <> i8 Int::compare<Float>(const Float &rhs) const { return compare(rhs.asInt()); }

template <typename T> i8 Int::compare(const T &rhs) const {
	throw std::invalid_argument(
		str("TypeError: comparison not supported between instances of 'int' and ") + typeid(T).name()
	);
}

}
