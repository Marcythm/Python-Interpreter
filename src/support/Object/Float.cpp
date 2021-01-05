#include "Object.hpp"

namespace innerTypes {

/* ---------- construtors ---------- */
Float::Float(): value(0) {}

Float::Float(const iinf &val): value(val.as<f64>()) {}
Float::Float(const str &s): value(std::stod(s)) {}
Float::Float(const char *&&s): value(std::stod(s)) {}
Float::Float(bool val): value(val ? 1 : 0) {}
Float::Float(f64 val): value(val) {}

/* ---------- destructor ---------- */
Float::~Float() = default;


template <> Int Float::as<Int>() const { return Int(value); }
template <> Str Float::as<Str>() const { return Str(value); }
template <> Bool Float::as<Bool>() const { return Bool(value); }
template <> Float Float::as<Float>() const { return *this; }


/* ---------- comparison operators ---------- */
template <> i8 Float::compare<Int>(const Int &rhs) const { return asInt().compare(rhs); }
template <> i8 Float::compare<Bool>(const Bool &rhs) const {
	return rhs.data() ? (value > 1 ? 1 : value < 1 ? -1 : 0) : (value > 0 ? 1 : value < 0 ? -1 : 0);
}
template <> i8 Float::compare<Float>(const Float &rhs) const {
	return value > rhs.value ? 1 : value < rhs.value ? -1 : 0;
}

template <typename T> i8 Float::compare(const T &rhs) const {
	throw std::invalid_argument(
		str("TypeError: comparison not supported between instances of 'float' and ") + typeid(T).name()
	);
}
}
