#ifndef Python_Interpreter_Support_Str
#define Python_Interpreter_Support_Str

#include "None.hpp"

namespace innerTypes {

class Str: public None {
	str value;

public:
	/* constructors */
	Str();
	explicit Str(str &&);

	explicit Str(const iinf &);
	explicit Str(const str &);
	explicit Str(const char *&&);
	explicit Str(bool);
	explicit Str(f64);

	/* destructor */
	~Str();

	// inline bool isStr() const override { return true; };

	Int asInt() const override;
	Str asStr() const override;
	Bool asBool() const override;
	Float asFloat() const override;

 	inline str& ref() { return value; };
	inline const str& data() const { return value; };



	/* comparisons */
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
