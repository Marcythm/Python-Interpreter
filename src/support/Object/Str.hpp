#ifndef Python_Interpreter_Support_Str
#define Python_Interpreter_Support_Str

#include "None.hpp"

namespace innerTypes {

class Str: public None {
public:
	using value_type = str;
private:
	value_type value;

public:
	/* constructors */
	Str();
	explicit Str(value_type &&);

	explicit Str(const iinf &);
	explicit Str(const value_type &);
	explicit Str(const char *&&);
	explicit Str(bool);
	explicit Str(f64);

	/* destructor */
	~Str();


	template <typename T> T as() const;

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

	template <typename T> Object operator + (const T &) const;
	template <typename T> Object operator * (const T &) const;
};

}

#endif
