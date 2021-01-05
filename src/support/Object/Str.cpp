#include "Object.hpp"

namespace innerTypes {

/* ---------- construtors ---------- */
Str::Str() = default;
Str::Str(str &&s): value(std::move(s)) {}

Str::Str(const iinf &val): value(val.as<str>()) {}
Str::Str(const str &s): value(s) {}
Str::Str(const char *&&s): value(s) {}
Str::Str(bool val): value(val ? "True" : "False") {}
Str::Str(f64 val): value(std::to_string(val)) {}

/* ---------- destructor ---------- */
Str::~Str() = default;


template <> Int Str::as<Int>() const { return Int(value); }
template <> Str Str::as<Str>() const { return *this; }
template <> Bool Str::as<Bool>() const { return Bool(value); }
template <> Float Str::as<Float>() const { return Float(value); }


/* ---------- comparison operators ---------- */
template <> i8 Str::compare<Str>(const Str &rhs) const { return value.compare(rhs.value); }

template <typename T> i8 Str::compare(const T &rhs) const {
	throw std::invalid_argument(
		str("TypeError: comparison not supported between instances of 'str' and ") + typeid(T).name()
	);
}



}
