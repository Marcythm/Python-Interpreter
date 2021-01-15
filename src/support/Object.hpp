#pragma once

#ifndef PYTHON_INTERPRETER_SUPPORT_OBJECT
#define PYTHON_INTERPRETER_SUPPORT_OBJECT

#include "config.hpp"
#include "u99.hpp"
#include "i99.hpp"

namespace innerTypes {

	/* ---------- trait: in_typeset ---------- */
	template <typename T>
				struct in_typeset							: std::false_type {};
	template <> struct in_typeset<void>						: std::true_type {};
	template <> struct in_typeset<i99>						: std::true_type {};
	template <> struct in_typeset<str>						: std::true_type {};
	template <> struct in_typeset<bool>						: std::true_type {};
	template <> struct in_typeset<f64>						: std::true_type {};
	template <typename T> constexpr bool in_typeset_v = in_typeset<T>::value;

	/* ---------- trait: is_storage ---------- */
	template <typename T>
				struct is_storage							: std::false_type {};
	template <typename T>
				struct is_storage<Value<T>>					{	static constexpr bool value = in_typeset_v<T>;	};
	template <typename T> constexpr bool is_storage_v = is_storage<T>::value;

	/* ---------- trait: is_integral_type ---------- */
	template <typename T>
				struct is_integral_type						: std::false_type {};
	template <> struct is_integral_type<i99>				: std::true_type {};
	template <> struct is_integral_type<bool>				: std::true_type {};
	template <typename T> constexpr bool is_integral_type_v = is_integral_type<T>::value;

	/* ---------- trait: is_integral_storage ---------- */
	template <typename T>
				struct is_integral_storage					: std::false_type {};
	template <typename T>
				struct is_integral_storage<Value<T>>		{	static constexpr bool value = is_integral_type_v<T>;	};
	template <typename T> constexpr bool is_integral_storage_v = is_integral_storage<T>::value;

	/* ---------- trait: is_arithmetic_type ---------- */
	template <typename T>
				struct is_arithmetic_type					: std::false_type {};
	template <> struct is_arithmetic_type<i99>				: std::true_type {};
	template <> struct is_arithmetic_type<bool>				: std::true_type {};
	template <> struct is_arithmetic_type<f64>				: std::true_type {};
	template <typename T> constexpr bool is_arithmetic_type_v = is_arithmetic_type<T>::value;

	/* ---------- trait: is_arithmetic_storage ---------- */
	template <typename T>
				struct is_arithmetic_storage				: std::false_type {};
	template <typename T>
				struct is_arithmetic_storage<Value<T>>		{	static constexpr bool value = is_arithmetic_type_v<T>;	};
	template <typename T> constexpr bool is_arithmetic_storage_v = is_arithmetic_storage<T>::value;




	/* ---------- class: BaseType ---------- */
	struct BaseType {
		BaseType() = default;
		virtual ~BaseType() = default;
	};

	/* ---------- class: Value ---------- */
	template <typename ValueType>
	class Value: public BaseType {
	public:
		using value_type = ValueType;
		using reference = value_type&;
		using const_reference = const value_type&;

	private:
		value_type value;

	public:
		/* constructors */
		Value(): value() {}
		explicit Value(value_type &&rhs): value(std::move(rhs)) {}
		explicit Value(const value_type &rhs): value(rhs) {}
		Value(Value &&rhs): value(std::move(rhs.value)) {}
		Value(const Value &rhs): value(rhs.value) {}

		/* destructor */
		~Value() = default;

		reference ref() { return value; }
		const_reference data() const { return value; }

		template <typename T> T as() const;

		Value& operator = (Value &&rhs) { value = std::move(rhs.value); }
		Value& operator = (const Value &rhs) = default;

		/* comparison operators */
		template <typename T, typename U> friend i8	compare(const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend bool operator == (const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend bool operator != (const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend bool operator <  (const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend bool operator >  (const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend bool operator <= (const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend bool operator >= (const Value<T> &, const Value<U> &);

		Object operator - () const;
		template <typename T, typename U> friend Object operator + (const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend Object operator - (const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend Object operator * (const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend Object operator / (const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend Object div        (const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend Object operator % (const Value<T> &, const Value<U> &);
	};

	template <> class Value<void>: public BaseType {
	public:
		Value() = default;
		~Value() = default;

		template <typename T> T as() const;

		/* comparison operators */
		template <typename T, typename U> friend bool operator == (const Value<T> &, const Value<U> &);
		template <typename T, typename U> friend bool operator != (const Value<T> &, const Value<U> &);
	};

	/*
	* methods need to be implemented in source file:
	* as, =, compare, -(pre), +, -, *, /, div, %
	*/

}

using innerTypes::BaseType;

class Object {
public:
static const innerTypes::NoneType None;
static BaseType *const noneptr;

private:
	BaseType *ptr;

public:
	Object();
	Object(Object &&);
	Object(const Object &);

	template <typename T> explicit Object(T &&);
	template <typename T> explicit Object(const T &);

	~Object();

	template <typename T>
	bool is_type() const { return as_type<T>() != nullptr; }

	template <typename T>
	T* as_type() const { return dynamic_cast<T*>(ptr); }

	template <typename T> T as() const;

	/* comparison operators */
	i8 compare(const Object &) const;
	bool operator == (const Object &rhs) const;
	bool operator != (const Object &rhs) const { return not operator==(rhs); };
	bool operator <  (const Object &rhs) const { return compare(rhs) <  0; };
	bool operator >  (const Object &rhs) const { return compare(rhs) >  0; };
	bool operator <= (const Object &rhs) const { return compare(rhs) <= 0; };
	bool operator >= (const Object &rhs) const { return compare(rhs) >= 0; };

	/* assignment operators */
	Object& operator = (const Object &);
	Object& operator = (Object &&);

	Object operator not () const;
	Object operator - () const;

	Object operator +	(const Object &) const;
	Object operator -	(const Object &) const;
	Object operator *	(const Object &) const;
	Object operator /	(const Object &) const;
	Object div			(const Object &) const;
	Object operator %	(const Object &) const;

	Object& operator +=	(const Object &rhs) { return *this = *this + rhs; };
	Object& operator -=	(const Object &rhs) { return *this = *this - rhs; };
	Object& operator *=	(const Object &rhs) { return *this = *this * rhs; };
	Object& operator /=	(const Object &rhs) { return *this = *this / rhs; };
	Object& diveq		(const Object &rhs) { return *this = this->div(rhs); };
	Object& operator %=	(const Object &rhs) { return *this = *this % rhs; };

};



/* ---------- implementations ---------- */

namespace innerTypes {


	/* ---------- method: as ---------- */
	template <typename T> T NoneType::as() const {
		if constexpr (std::is_same_v<str, T>)				return str("None");
		if constexpr (std::is_same_v<bool, T>)				return false;
		if constexpr (is_storage_v<T>)						return T(as<typename T::value_type>());
		throw std::invalid_argument(str("unsupported argument type(s) in method as(): ") + typeid(T).name());
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

			if constexpr (std::is_same_v<i99, U>) {
				if constexpr (std::is_same_v<Str, T>)		return U(data());
				if constexpr (std::is_same_v<Bool, T>)		return U(data() ? 1 : 0);
				if constexpr (std::is_same_v<Float, T>)		return U(i64(data()));
			}
			if constexpr (std::is_same_v<str, U>) {
				if constexpr (std::is_same_v<Bool, T>)		return U(data() ? "True" : "False");
				if constexpr (std::is_same_v<Float, T>)		return std::to_string(data());
			}
			if constexpr (std::is_same_v<bool, U>) {
				if constexpr (std::is_same_v<Str, T>)		return not data().empty();
				if constexpr (std::is_same_v<Float, T>)		return data() != 0;
			}
			if constexpr (std::is_same_v<f64, U>) {
				if constexpr (std::is_same_v<Str, T>)		return std::stod(data());
				if constexpr (std::is_same_v<Bool, T>)		return data() ? 1 : 0;
			}
		}
		if constexpr (std::is_integral_v<U>)				return as<i99>().template as<U>();
		throw std::invalid_argument(str("unsupported argument type(s) in method as(): ") + typeid(U).name());
	}

	/* ---------- method: compare ---------- */
	template <typename ValueTypeT, typename ValueTypeU>
	i8 compare(const Value<ValueTypeT> &lhs, const Value<ValueTypeU> &rhs) {
		using T = Value<ValueTypeT>; using U = Value<ValueTypeU>;
		if constexpr (std::is_same_v<Str, T> and std::is_same_v<Str, U>)
			return lhs.data().compare(rhs.data());
		if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
			if (std::is_same_v<Float, T> or std::is_same_v<Float, U>) {
				f64 lv = lhs.template as<f64>(), rv = rhs.template as<f64>();
				return lv < rv ? -1 : lv > rv ? 1 : 0;
			}
			return lhs.template as<i99>().compare(rhs.template as<i99>());
		}
		throw std::invalid_argument(str("unsupported argument type(s) in method compare(): ") + typeid(T).name() + " and " + typeid(U).name());
	}

	/* ---------- operator: == ---------- */
	template <typename ValueTypeT, typename ValueTypeU>
	bool operator == (const Value<ValueTypeT> &lhs, const Value<ValueTypeU> &rhs) {
		using T = Value<ValueTypeT>; using U = Value<ValueTypeU>;
		if constexpr (std::is_same_v<NoneType, T> or std::is_same_v<NoneType, U>)
			return std::is_same_v<NoneType, T> and std::is_same_v<NoneType, U>;
		if constexpr (std::is_same_v<Str, T> xor std::is_same_v<Str, U>)
			return false;
		return compare(lhs, rhs) == 0;
	}


	template <typename T, typename U> bool operator != (const Value<T> &lhs, const Value<U> &rhs) { return not (lhs == rhs); };
	template <typename T, typename U> bool operator <  (const Value<T> &lhs, const Value<U> &rhs) { return compare(lhs, rhs) <  0; };
	template <typename T, typename U> bool operator >  (const Value<T> &lhs, const Value<U> &rhs) { return compare(lhs, rhs) >  0; };
	template <typename T, typename U> bool operator <= (const Value<T> &lhs, const Value<U> &rhs) { return compare(lhs, rhs) <= 0; };
	template <typename T, typename U> bool operator >= (const Value<T> &lhs, const Value<U> &rhs) { return compare(lhs, rhs) >= 0; };

	/* ---------- operator: -(pre) ---------- */
	template <typename ValueType>
	Object Value<ValueType>::operator - () const {
		using T = Value<ValueType>;
		if constexpr (std::is_same_v<Bool, T>)
			return Object(data() ? -1 : 0);
		if constexpr (is_arithmetic_storage_v<T>)
			return Object(-data());
		throw std::invalid_argument(str("unsupported operand type(s) in operator -(pre): ") + typeid(T).name());
	}

	/* ---------- operator: + ---------- */
	template <typename ValueTypeT, typename ValueTypeU>
	Object operator + (const Value<ValueTypeT> &lhs, const Value<ValueTypeU> &rhs) {
		using T = Value<ValueTypeT>; using U = Value<ValueTypeU>;
		if constexpr (std::is_same_v<Str, T> and std::is_same_v<Str, U>)
			return Object(lhs.data() + rhs.data());
		if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
			if constexpr (std::is_same_v<Float, T> or std::is_same_v<Float, U>)
				return Object(lhs.template as<f64>() + rhs.template as<f64>());
			return Object(lhs.template as<i99>() + rhs.template as<i99>());
		}
		throw std::invalid_argument(str("unsupported operand type(s) in operator +: ") + typeid(T).name() + " and " + typeid(U).name());
	}

	/* ---------- operator: - ---------- */
	template <typename ValueTypeT, typename ValueTypeU>
	Object operator - (const Value<ValueTypeT> &lhs, const Value<ValueTypeU> &rhs) {
		using T = Value<ValueTypeT>; using U = Value<ValueTypeU>;
		if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
			if constexpr (std::is_same_v<Float, T> or std::is_same_v<Float, U>)
				return Object(lhs.template as<f64>() - rhs.template as<f64>());
			return Object(lhs.template as<i99>() - rhs.template as<i99>());
		}
		throw std::invalid_argument(str("unsupported operand type(s) in operator -: ") + typeid(T).name() + " and " + typeid(U).name());
	}

	/* ---------- operator: * ---------- */
	template <typename ValueTypeT, typename ValueTypeU>
	Object operator * (const Value<ValueTypeT> &lhs, const Value<ValueTypeU> &rhs) {
		using T = Value<ValueTypeT>; using U = Value<ValueTypeU>;
		if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
			if constexpr (std::is_same_v<Float, T> or std::is_same_v<Float, U>)
				return Object(lhs.template as<f64>() * rhs.template as<f64>());
			return Object(lhs.template as<i99>() * rhs.template as<i99>());
		}
		if constexpr (std::is_same_v<Str, T>) {
			if constexpr (std::is_same_v<Bool, U>)
				return Object(rhs.data() ? lhs.data() : str());
			if constexpr (std::is_same_v<Int, U>) {
				str res;
				for (i32 i = rhs.template as<i32>(); i; --i)
					res.insert(res.end(), lhs.data().begin(), lhs.data().end());
				return Object(res);
			}
		} else if constexpr (std::is_same_v<Str, U>)
			return rhs * lhs;
		throw std::invalid_argument(str("unsupported operand type(s) in operator *: ") + typeid(T).name() + " and " + typeid(U).name());
	}

	/* ---------- operator: / ---------- */
	template <typename ValueTypeT, typename ValueTypeU>
	Object operator / (const Value<ValueTypeT> &lhs, const Value<ValueTypeU> &rhs) {
		using T = Value<ValueTypeT>; using U = Value<ValueTypeU>;
		if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
			if constexpr (is_integral_storage_v<U>) {
				if (not rhs.template as<bool>())
					throw std::domain_error("ZeroDivisionError: float division by zero");
			}
			return Object(lhs.template as<f64>() / rhs.template as<f64>());
		}
		throw std::invalid_argument(str("unsupported operand type(s) in operator /: ") + typeid(T).name() + " and " + typeid(U).name());
	}

	/* ---------- method: div ---------- */
	template <typename ValueTypeT, typename ValueTypeU>
	Object div(const Value<ValueTypeT> &lhs, const Value<ValueTypeU> &rhs) {
		using T = Value<ValueTypeT>; using U = Value<ValueTypeU>;
		if constexpr (is_integral_storage_v<T> and is_integral_storage_v<U>) {
			if constexpr (std::is_same_v<Bool, U>) {
				if (rhs.data())	return Object(lhs.template as<i99>());
				throw std::domain_error("ZeroDivisionError: division by zero");
			}
			return Object(lhs.template as<i99>() / rhs.template as<i99>());
		}
		throw std::invalid_argument(str("unsupported operand type(s) in operator //: ") + typeid(T).name() + " and " + typeid(U).name());
	}

	/* ---------- operator: % ---------- */
	template <typename ValueTypeT, typename ValueTypeU>
	Object operator % (const Value<ValueTypeT> &lhs, const Value<ValueTypeU> &rhs) {
		using T = Value<ValueTypeT>; using U = Value<ValueTypeU>;
		if constexpr (is_integral_storage_v<T> and is_integral_storage_v<U>) {
			if constexpr (std::is_same_v<Bool, U>) {
				if (rhs.data())	return Object(0);
				throw std::domain_error("ZeroDivisionError: integer division or modulo by zero");
			}
			return Object(lhs.template as<i99>() % rhs.template as<i99>());
		}
		throw std::invalid_argument(str("unsupported operand type(s) in operator %: ") + typeid(T).name() + " and " + typeid(U).name());
	}


}



using innerTypes::BaseType;
using innerTypes::NoneType;
using innerTypes::Int;
using innerTypes::Str;
using innerTypes::Bool;
using innerTypes::Float;

/* ---------- construtors ---------- */
template <typename _Tp>
Object::Object(_Tp &&rhs) {
	using T = std::decay_t<_Tp>;
	if constexpr (innerTypes::in_typeset_v<T>)
		ptr = new innerTypes::Value<T>(std::move(rhs));
	else if constexpr (innerTypes::is_storage_v<T>)
		ptr = new T(std::move(rhs));
	else if constexpr (std::is_integral_v<T>)
		ptr = new innerTypes::Int(i99(rhs));
	else if constexpr (std::is_same_v<T, Object>)
		ptr = rhs.ptr, rhs.ptr = noneptr;
	else throw std::invalid_argument(str("unsupported argument type(s) in constructor Object(): ") + typeid(rhs).name());
}
template <typename _Tp>
Object::Object(const _Tp &rhs) {
	using T = std::decay_t<_Tp>;
	if constexpr (innerTypes::in_typeset_v<T>)
		ptr = new innerTypes::Value<T>(rhs);
	else if constexpr (innerTypes::is_storage_v<T>)
		ptr = new T(rhs);
	else if constexpr (std::is_integral_v<T>)
		ptr = new innerTypes::Int(i99(rhs));
	else if constexpr (std::is_same_v<T, Object>) {
		if (auto p = rhs.template as_type<Int>())				ptr = new Int(*p);
		else if (auto p = rhs.template as_type<Str>())			ptr = new Str(*p);
		else if (auto p = rhs.template as_type<Bool>())			ptr = new Bool(*p);
		else if (auto p = rhs.template as_type<Float>())		ptr = new Float(*p);
		else													ptr = noneptr;
	}
	else throw std::invalid_argument(str("unsupported argument type(s) in constructor Object(): ") + typeid(rhs).name());
}


/* ---------- method: as ---------- */
template <typename T> T Object::as() const {
	if (auto p = as_type<Int>())					return p->as<T>();
	if (auto p = as_type<Str>())					return p->as<T>();
	if (auto p = as_type<Bool>())					return p->as<T>();
	if (auto p = as_type<Float>())					return p->as<T>();
	if (auto p = as_type<NoneType>())				return p->as<T>();
	throw std::invalid_argument(str("conversion from unknown type to ") + typeid(T).name());
}

#endif
