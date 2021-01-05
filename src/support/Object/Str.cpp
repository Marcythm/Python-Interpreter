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


Int Str::asInt() const { return Int(value); }
Str Str::asStr() const { return *this; }
Bool Str::asBool() const { return Bool(value); }
Float Str::asFloat() const { return Float(value); }


/* ---------- comparison operators ---------- */
template <> i8 Str::compare<Str>(const Str &rhs) const { return value.compare(rhs.value); }

template <typename T> i8 Str::compare(const T &rhs) const {
	throw std::invalid_argument(
		str("TypeError: comparison not supported between instances of 'str' and ") + typeid(T).name()
	);
}

}
