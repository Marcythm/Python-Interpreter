#include "Object.hpp"

namespace innerTypes {

/* ---------- construtors ---------- */
Bool::Bool(): value(false) {}

Bool::Bool(const iinf &val): value(val.as<bool>()) {}
Bool::Bool(const str &s): value(not s.empty()) {}
Bool::Bool(const char *&&s): value(*s != 0) {}
Bool::Bool(bool val): value(val) {}
Bool::Bool(f64 val): value(val != 0) {}

/* ---------- destructor ---------- */
Bool::~Bool() = default;


template <> Int Bool::as<Int>() const { return Int(value); }
template <> Str Bool::as<Str>() const { return Str(value); }
template <> Bool Bool::as<Bool>() const { return *this; }
template <> Float Bool::as<Float>() const { return Float(value); }


/* ---------- comparison operators ---------- */
template <> i8 Bool::compare<Int>(const Int &rhs) const { return asInt().compare(rhs); }
template <> i8 Bool::compare<Bool>(const Bool &rhs) const {
	return (value == rhs.value) ? 0 : (value ? 1 : -1);
}
template <> i8 Bool::compare<Float>(const Float &rhs) const {
	const f64 val = rhs.data();
	return value ? (1 > val ? 1 : 1 < val ? -1 : 0) : (0 > val ? 1 : 1 < val ? -1 : 0);
	// return i32(value) <=> f64(rhs);
}

template <typename T> i8 Bool::compare(const T &rhs) const {
	throw std::invalid_argument(
		str("TypeError: comparison not supported between instances of 'bool' and ") + typeid(T).name()
	);
}

}
