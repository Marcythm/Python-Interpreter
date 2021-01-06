#pragma once

#ifndef PYTHON_INTERPRETER_SUPPORT_OBJECT
#define PYTHON_INTERPRETER_SUPPORT_OBJECT

#include "iinf.hpp"

namespace innerTypes {

	/* ---------- trait: in_typeset ---------- */
	template <typename T>
				struct in_typeset 							{	static constexpr bool value = false;	};
	template <> struct in_typeset<iinf> 					{	static constexpr bool value = true; 	};
	template <> struct in_typeset<str>						{	static constexpr bool value = true; 	};
	template <> struct in_typeset<bool>						{	static constexpr bool value = true;		};
	template <> struct in_typeset<f64>						{	static constexpr bool value = true; 	};
	template <typename T> constexpr bool in_typeset_v = in_typeset<T>::value;

	/* ---------- trait: is_storage ---------- */
	template <typename T>
				struct is_storage 							{	static constexpr bool value = false;	};
	template <typename T>
				struct is_storage<Value<T>> 				{	static constexpr bool value = in_typeset_v<T>; 	};
	template <typename T> constexpr bool is_storage_v = is_storage<T>::value;

	/* ---------- trait: is_integral_type ---------- */
	template <typename T>
				struct is_integral_type						{	static constexpr bool value = false;	};
	template <> struct is_integral_type<iinf>				{	static constexpr bool value = true;		};
	template <> struct is_integral_type<bool>				{	static constexpr bool value = true;		};
	template <typename T> constexpr bool is_integral_type_v = is_integral_type<T>::value;

	/* ---------- trait: is_integral_storage ---------- */
	template <typename T>
				struct is_integral_storage					{	static constexpr bool value = false;	};
	template <typename T>
				struct is_integral_storage<Value<T>>		{	static constexpr bool value = is_integral_type_v<T>;	};
	template <typename T> constexpr bool is_integral_storage_v = is_integral_storage<T>::value;

	/* ---------- trait: is_arithmetic_type ---------- */
	template <typename T>
				struct is_arithmetic_type					{	static constexpr bool value = false;	};
	template <> struct is_arithmetic_type<iinf>				{	static constexpr bool value = true;		};
	template <> struct is_arithmetic_type<bool>				{	static constexpr bool value = true;		};
	template <> struct is_arithmetic_type<f64>				{	static constexpr bool value = true;		};
	template <typename T> constexpr bool is_arithmetic_type_v = is_arithmetic_type<T>::value;

	/* ---------- trait: is_arithmetic_storage ---------- */
	template <typename T>
				struct is_arithmetic_storage				{	static constexpr bool value = false;	};
	template <typename T>
				struct is_arithmetic_storage<Value<T>>		{	static constexpr bool value = is_arithmetic_type_v<T>;	};
	template <typename T> constexpr bool is_arithmetic_storage_v = is_arithmetic_storage<T>::value;




	/* ---------- class: None ---------- */

	struct None {
		None() = default;
		virtual ~None() = default;

		template <typename T> T as() const;
	};

	/* ---------- class: Value ---------- */
	template <typename ValueType>
	class Value: public None {
	public:
		using value_type = ValueType;
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

		value_type& ref() { return value; }
		const value_type& data() const { return value; }

		template <typename T> T as() const;

		Value& operator = (Value &&rhs) { value = std::move(rhs.value); }
		Value& operator = (const Value &rhs) = default;

		/* comparison operators */
		template <typename T> i8 compare(const T &) const;
		template <typename T> bool operator == (const T &rhs) const { return compare(rhs) == 0; };
		template <typename T> bool operator != (const T &rhs) const { return compare(rhs) != 0; };
		template <typename T> bool operator <  (const T &rhs) const { return compare(rhs) <  0; };
		template <typename T> bool operator >  (const T &rhs) const { return compare(rhs) >  0; };
		template <typename T> bool operator <= (const T &rhs) const { return compare(rhs) <= 0; };
		template <typename T> bool operator >= (const T &rhs) const { return compare(rhs) >= 0; };

		Object operator - () const;
		template <typename T> Object operator + (const T &) const;
		template <typename T> Object operator - (const T &) const;
		template <typename T> Object operator * (const T &) const;
		template <typename T> Object operator / (const T &) const;
		template <typename T> Object div		(const T &) const;
		template <typename T> Object operator % (const T &) const;
	};

	/*
	* methods need to be implemented in source file:
	* as, =, compare, -(pre), +, -, *, /, div, %
	*/

}

using innerTypes::None;

class Object {
public:
static const None NONE;
static None *const noneptr;

private:
	None *ptr;

public:
	Object();
	Object(Object &&);
	Object(const Object &);

	template <typename T> Object(T &&);
	template <typename T> Object(const T &);

	~Object();

	// template <typename T>
	// bool is_type() const { return as_type<T>() != nullptr; }

	template <typename T>
	T* as_type() const { return dynamic_cast<T*>(ptr); }

	template <typename T> T as() const;

	/* comparison operators */
	i8 compare(const Object &) const;
	bool operator == (const Object &rhs) const { return compare(rhs) == 0; };
	bool operator != (const Object &rhs) const { return compare(rhs) != 0; };
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

	 i32 type() const {
		if (auto p = as_type<innerTypes::Int>())				return 1;
		else if (auto p = as_type<innerTypes::Str>()) 			return 2;
		else if (auto p = as_type<innerTypes::Bool>()) 			return 3;
		else if (auto p = as_type<innerTypes::Float>()) 		return 4;
																return 0;
	}
};



/* ---------- implementations ---------- */

namespace innerTypes {


	template <typename T> T None::as() const {
		if constexpr (std::is_same_v<str, T>)				return str("None");
		if constexpr (std::is_same_v<bool, T>)				return false;
		if constexpr (is_storage_v<T>)						return T(as<typename T::value_type>());
		throw std::invalid_argument(str("Unsupported type in method as(): ") + typeid(T).name());
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
			if constexpr (std::is_same_v<bool, U>) {
				if constexpr (std::is_same_v<Str, T>)		return not data().empty();
				if constexpr (std::is_same_v<Float, T>)		return data() != 0;
			}
			if constexpr (std::is_same_v<f64, U>) {
				if constexpr (std::is_same_v<Str, T>)		return std::stod(data());
				if constexpr (std::is_same_v<Bool, T>)		return data() ? 1 : 0;
			}
		}
		if constexpr (std::is_integral_v<U>)				return as<iinf>().template as<U>();
		throw std::invalid_argument(str("Unsupported type in method as(): ") + typeid(U).name());
	}

	/* ---------- method: compare ---------- */
	template <typename ValueType> template <typename U>
	i8 Value<ValueType>::compare(const U &rhs) const {
		using T = Value<ValueType>;
		if constexpr (std::is_same_v<Str, T> and std::is_same_v<Str, U>)
			return data().compare(rhs.data());
		if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
			if (std::is_same_v<Float, T> or std::is_same_v<Float, U>) {
#if _LIBCPP_STD_VER > 17
				auto res = as<f64>() <=> rhs.template as<f64>();
				return res < 0 ? -1 : res > 0 ? 1 : 0;
#else
				f64 lv = as<f64>(), rv = rhs.template as<f64>();
				return lv < rv ? -1 : lv > rv ? 1 : 0;
#endif
			}
			return as<iinf>().compare(rhs.template as<iinf>());
		}
		throw std::invalid_argument(str("Unsupported type in method compare(): ") + typeid(U).name());
	}

	/* ---------- operator: -(pre) ---------- */
	template <typename ValueType>
	Object Value<ValueType>::operator - () const {
		using T = Value<ValueType>;
		if constexpr (std::is_same_v<Bool, T>)
			return Object(data() ? -1 : 0);
		if constexpr (is_arithmetic_storage_v<T>)
			return Object(-data());
		throw std::invalid_argument(str("Unsupported type in operator -(pre): ") + typeid(T).name());
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
			return Object(as<iinf>() + rhs.template as<iinf>());
		}
		throw std::invalid_argument(str("Unsupported type in operator +: ") + typeid(U).name());
	}

	/* ---------- operator: - ---------- */
	template <typename ValueType> template <typename U>
	Object Value<ValueType>::operator - (const U &rhs) const {
		using T = Value<ValueType>;
		if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
			if constexpr (std::is_same_v<Float, T> or std::is_same_v<Float, U>)
				return Object(as<f64>() - rhs.template as<f64>());
			return Object(as<iinf>() - rhs.template as<iinf>());
		}
		throw std::invalid_argument(str("Unsupported type in operator -: ") + typeid(U).name());
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
		throw std::invalid_argument(str("Unsupported type in operator *: ") + typeid(U).name());
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
		throw std::invalid_argument(str("Unsupported type in operator //: ") + typeid(U).name());
	}

	/* ---------- method: div ---------- */
	template <typename ValueType> template <typename U>
	Object Value<ValueType>::div(const U &rhs) const {
		using T = Value<ValueType>;
		if constexpr (is_arithmetic_storage_v<T> and is_arithmetic_storage_v<U>) {
			if constexpr (is_integral_storage_v<U>) {
				if (not rhs.template as<bool>())
					throw std::domain_error("ZeroDivisionError: float division by zero");
			}
			return Object(as<f64>() / rhs.template as<f64>());
		}
		throw std::invalid_argument(str("Unsupported type in operator /: ") + typeid(U).name());
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
		throw std::invalid_argument(str("Unsupported type in operator %: ") + typeid(U).name());
	}


}



using innerTypes::None;
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
		ptr = new innerTypes::Int(iinf(rhs));
	else if constexpr (std::is_same_v<T, Object>)
		ptr = rhs.ptr, rhs.ptr = nullptr;
	else throw std::invalid_argument(str("Unsupported type in constructor Object(): ") + typeid(rhs).name());
}
template <typename _Tp>
Object::Object(const _Tp &rhs) {
	using T = std::decay_t<_Tp>;
	if constexpr (innerTypes::in_typeset_v<T>)
		ptr = new innerTypes::Value<T>(rhs);
	else if constexpr (innerTypes::is_storage_v<T>)
		ptr = new T(rhs);
	else if constexpr (std::is_integral_v<T>)
		ptr = new innerTypes::Int(iinf(rhs));
	else if constexpr (std::is_same_v<T, Object>) {
		ptr = noneptr;
		if (auto p = rhs.template as_type<Int>())				ptr = new Int(*p);
		else if (auto p = rhs.template as_type<Str>()) 			ptr = new Str(*p);
		else if (auto p = rhs.template as_type<Bool>()) 		ptr = new Bool(*p);
		else if (auto p = rhs.template as_type<Float>()) 		ptr = new Float(*p);
	}
	else throw std::invalid_argument(str("Unsupported type in constructor Object(): ") + typeid(rhs).name());
}


/* ---------- method: as ---------- */
template <typename T> T Object::as() const {
	if (auto p = as_type<Int>())					return p->as<T>();
	if (auto p = as_type<Str>()) 					return p->as<T>();
	if (auto p = as_type<Bool>()) 					return p->as<T>();
	if (auto p = as_type<Float>()) 					return p->as<T>();
													return ptr->as<T>();
}

#endif
