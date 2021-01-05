#include "Object.hpp"

namespace innerTypes {


template <> str None::as<str>() const { return str("None"); }
template <> bool None::as<bool>() const { return false; }

template <typename T> T None::as() const {
	if constexpr (std::is_base_of<None, T>::value)
		return T(as<typename T::value_type>());
	throw std::invalid_argument("Unsupported type in method as()");
}


/* ---------- method: as ---------- */
template <typename ValueType> template <typename U>
U Value<ValueType>::as() const {
	using T = Value<ValueType>;
	if constexpr (std::is_same_v<T, U>)					return *this;
	if constexpr (is_storage_v<U>)						return U(as<typename U::value_type>());
	if constexpr (in_typeset_v<U>) {
		if constexpr (std::is_same_v<ValueType, U>)		return data();
		if constexpr (std::is_same_v<Int, T>)			return data().template as<U>();

		if constexpr (std::is_same_v<iinf, U>) {
			if constexpr (std::is_same_v<Str, T>)		return U(data());
			if constexpr (std::is_same_v<Bool, T>)		return U(data() ? 1 : 0);
			if constexpr (std::is_same_v<Float, T>)		return U(i64(data()));
		}
		if constexpr (std::is_same_v<str, U>) {
			if constexpr (std::is_same_v<Bool, T>)		return U(data() ? "True" : "False");
			if constexpr (std::is_same_v<Float, T>)		return std::to_string(data());
		}
		if constexpr (std::is_same_v<Bool, U>) {
			if constexpr (std::is_same_v<Str, T>)		return not data().empty();
			if constexpr (std::is_same_v<Float, T>)		return data() != 0;
		}
		if constexpr (std::is_same_v<Float, U>) {
			if constexpr (std::is_same_v<Str, T>)		return std::stod(data());
			if constexpr (std::is_same_v<Bool, T>)		return data() ? 1 : 0;
		}
	}
	throw std::invalid_argument("Unsupported type in method as()");
}

/* ---------- method: compare ---------- */
template <typename ValueType> template <typename U>
i8 Value<ValueType>::compare(const U &rhs) const {
	using T = Value<ValueType>;
	if constexpr (std::is_same_v<Str, T> and std::is_same_v<Str, U>)
		return data().compare(rhs.data());
	if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
		if (std::is_same_v<Float, T> or std::is_same_v<Float, U>)
			return as<f64>() <=> rhs.template as<f64>();
		return as<iinf>().compare(rhs.template as<iinf>());
	}
	throw std::invalid_argument("Unsupported type in method compare()");
}

/* ---------- operator: -(pre) ---------- */
template <typename ValueType>
Object Value<ValueType>::operator - () const {
	using T = Value<ValueType>;
	if constexpr (std::is_same_v<Bool, T>)
		return Object(data() ? -1 : 0);
	if constexpr (is_arithmetic_storage_v<T>)
		return Object(-data());
	throw std::invalid_argument("Unsupported type in operator -(pre)");
}

/* ---------- operator: + ---------- */
template <typename ValueType> template <typename U>
Object Value<ValueType>::operator + (const U &rhs) const {
	using T = Value<ValueType>;
	if constexpr (std::is_same_v<Str, T> and std::is_same_v<Str, U>)
		return Object(data() + rhs.data());
	if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
		if constexpr (std::is_same_v<Float, T> or std::is_same_v<Float, U>)
			return Object(as<f64>() + rhs.template as<f64>());
		return Object(as<Int>() + rhs.template as<Int>());
	}
	throw std::invalid_argument("Unsupported type in operator +");
}

/* ---------- operator: - ---------- */
template <typename ValueType> template <typename U>
Object Value<ValueType>::operator - (const U &rhs) const {
	using T = Value<ValueType>;
	if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
		if constexpr (std::is_same_v<Float, T> or std::is_same_v<Float, U>)
			return Object(as<f64>() - rhs.template as<f64>());
		return Object(as<Int>() - rhs.template as<Int>());
	}
	throw std::invalid_argument("Unsupported type in operator -");
}

/* ---------- operator: * ---------- */
template <typename ValueType> template <typename U>
Object Value<ValueType>::operator * (const U &rhs) const {
	using T = Value<ValueType>;
	if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
		if constexpr (std::is_same_v<Float, T> or std::is_same_v<Float, U>)
			return Object(as<f64>() * rhs.template as<f64>());
		return Object(as<iinf>() * rhs.template as<iinf>());
	}
	if constexpr (std::is_same_v<Str, T>) {
		if constexpr (std::is_same_v<Bool, U>)
			return Object(rhs.data() ? data() : str());
		if constexpr (std::is_same_v<Int, U>) {
			str res;
			for (i32 i = rhs.template as<i32>(); i; --i)
				res.insert(res.end(), data().begin(), data().end());
			return Object(res);
		}
	}
	if constexpr (std::is_same_v<Str, U>) {
		if constexpr (std::is_same_v<Bool, T>)
			return Object(data() ? rhs.data() : str());
		if constexpr (std::is_same_v<Int, T>) {
			str res;
			for (i32 i = as<i32>(); i; --i)
				res.insert(res.end(), rhs.data().begin(), rhs.data().end());
			return Object(res);
		}
	}
	throw std::invalid_argument("Unsupported type in operator *");
}

/* ---------- operator: / ---------- */
template <typename ValueType> template <typename U>
Object Value<ValueType>::operator / (const U &rhs) const {
	using T = Value<ValueType>;
	if constexpr (is_integral_storage_v<T> and is_integral_storage_v<U>) {
		if constexpr (std::is_same_v<Bool, U>) {
			if (rhs.data())	return Object(as<iinf>());
			throw std::domain_error("ZeroDivisionError: division by zero");
		}
		return Object(as<iinf>() / rhs.template as<iinf>());
	}
	throw std::invalid_argument("Unsupported type in operator //");
}

/* ---------- method: div ---------- */
template <typename ValueType> template <typename U>
Object Value<ValueType>::div(const U &rhs) const {
	using T = Value<ValueType>;
	if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
		if constexpr (is_integral_storage_v<U>) {
			if (not rhs.template as<iinf>().template as<bool>())
				throw std::domain_error("ZeroDivisionError: float division by zero");
		}
		return Object(as<f64>() / rhs.template as<f64>());
	}
	throw std::invalid_argument("Unsupported type in operator /");
}

/* ---------- operator: % ---------- */
template <typename ValueType> template <typename U>
Object Value<ValueType>::operator % (const U &rhs) const {
	using T = Value<ValueType>;
	if constexpr (is_integral_storage_v<T> and is_integral_storage_v<U>) {
		if constexpr (std::is_same_v<Bool, U>) {
			if (rhs.data())	return Object(0);
			throw std::domain_error("ZeroDivisionError: integer division or modulo by zero");
		}
		return Object(as<iinf>() % rhs.template as<iinf>());
	}
	throw std::invalid_argument("Unsupported type in operator %");
}


}
