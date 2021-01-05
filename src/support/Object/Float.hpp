#ifndef Python_Interpreter_Support_Float
#define Python_Interpreter_Support_Float

#include "None.hpp"

namespace innerTypes {

class Float: public None {
	f64 value;

public:
	/* constructors */
	Float();

	explicit Float(const iinf &);
	explicit Float(const str &);
	explicit Float(const char *&&);
	explicit Float(bool);
	explicit Float(f64);

	/* destructor */
	~Float();

	// inline bool isFloat() const override { return true; };

	Int asInt() const override;
	Str asStr() const override;
	Bool asBool() const override;
	Float asFloat() const override;

	inline f64& ref() { return value; };
	inline const f64& data() const { return value; };



	/* comparison operators */
	template <typename T> i8 compare(const T &) const;
	template <typename T> inline bool operator == (const T &rhs) const { return compare(rhs) == 0; };
	template <typename T> inline bool operator != (const T &rhs) const { return compare(rhs) != 0; };
	template <typename T> inline bool operator < (const T &rhs) const { return compare(rhs) < 0; };
	template <typename T> inline bool operator > (const T &rhs) const { return compare(rhs) > 0; };
	template <typename T> inline bool operator <= (const T &rhs) const { return compare(rhs) <= 0; };
	template <typename T> inline bool operator >= (const T &rhs) const { return compare(rhs) >= 0; };

	template <typename T> Object operator = (const T &) const;

	template <typename T> Object operator + (const T &) const;
	template <typename T> Object operator - (const T &) const;
	template <typename T> Object operator * (const T &) const;
	template <typename T> Object operator / (const T &) const;
	template <typename T> Object div(const T &) const;
	template <typename T> Object operator % (const T &) const;
};

}

#endif
