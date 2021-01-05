#ifndef Python_Interpreter_Support_Bool
#define Python_Interpreter_Support_Bool

#include "None.hpp"

namespace innerTypes {

class Bool: public None {
	bool value;

public:
	/* constructors */
	Bool();

	explicit Bool(const iinf &);
	explicit Bool(const str &);
	explicit Bool(const char *&&);
	explicit Bool(bool);
	explicit Bool(f64);

	/* destructor */
	~Bool();

	// inline bool isBool() const override { return true; };

	Int asInt() const override;
	Str asStr() const override;
	Bool asBool() const override;
	Float asFloat() const override;

	inline bool& ref() { return value; };
	inline const bool& data() const { return value; };



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
