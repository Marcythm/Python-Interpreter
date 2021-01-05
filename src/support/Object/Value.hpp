#ifndef Python_Interpreter_Support_Int
#define Python_Interpreter_Support_Int

#include "../BigInt/iinf.hpp"

namespace innerTypes {

/* ---------- trait: in_typeset ---------- */
template <typename T>
			struct in_typeset 							{	static constexpr bool value = false;	};
template <> struct in_typeset<iinf> 					{	static constexpr bool value = true; 	};
template <> struct in_typeset<str>						{	static constexpr bool value = true; 	};
template <> struct in_typeset<bool>						{	static constexpr bool value = true;		};
template <> struct in_typeset<f64>						{	static constexpr bool value = true; 	};

/* ---------- trait: is_storage ---------- */
template <typename T>
			struct is_storage 							{	static constexpr bool value = false;	};
template <typename T>
			struct is_storage<Value<T>> 				{	static constexpr bool value = in_typeset_v<T>; 	};

/* ---------- trait: is_integral_type ---------- */
template <typename T>
			struct is_integral_type						{	static constexpr bool value = false;	};
template <> struct is_integral_type<iinf>				{	static constexpr bool value = true;		};
template <> struct is_integral_type<bool>				{	static constexpr bool value = true;		};

/* ---------- trait: is_integral_storage ---------- */
template <typename T>
			struct is_integral_storage					{	static constexpr bool value = false;	};
template <typename T>
			struct is_integral_storage<Value<T>>		{	static constexpr bool value = is_integral_type_v<T>;	};

/* ---------- trait: is_arithmetic_type ---------- */
template <typename T>
			struct is_arithmetic_type					{	static constexpr bool value = false;	};
template <> struct is_arithmetic_type<iinf>				{	static constexpr bool value = true;		};
template <> struct is_arithmetic_type<bool>				{	static constexpr bool value = true;		};
template <> struct is_arithmetic_type<f64>				{	static constexpr bool value = true;		};

/* ---------- trait: is_arithmetic_storage ---------- */
template <typename T>
			struct is_arithmetic_storage				{	static constexpr bool value = false;	};
template <typename T>
			struct is_arithmetic_storage<Value<T>>		{	static constexpr bool value = is_arithmetic_type_v<T>;	};




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
	explicit Value(Value &&rhs): value(std::move(rhs.value)) {}
	explicit Value(const Value &rhs): value(rhs.value) {}

	/* destructor */
	~Value() = default;

	inline value_type& ref() { return value; }
	inline const value_type& data() const { return value; }

	template <typename T> T as() const;

	Value& operator = (Value &&rhs) { value = std::move(rhs.value); }
	Value& operator = (const Value &rhs) = default;

	/* comparison operators */
	template <typename T> i8 compare(const T &) const;
	template <typename T> inline bool operator == (const T &rhs) const { return compare(rhs) == 0; };
	template <typename T> inline bool operator != (const T &rhs) const { return compare(rhs) != 0; };
	template <typename T> inline bool operator <  (const T &rhs) const { return compare(rhs) <  0; };
	template <typename T> inline bool operator >  (const T &rhs) const { return compare(rhs) >  0; };
	template <typename T> inline bool operator <= (const T &rhs) const { return compare(rhs) <= 0; };
	template <typename T> inline bool operator >= (const T &rhs) const { return compare(rhs) >= 0; };

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

#endif
