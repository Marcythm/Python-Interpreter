#ifndef Python_Interpreter_Support_Int
#define Python_Interpreter_Support_Int

#include "None.hpp"
#include "iinf.hpp"

namespace innerTypes {

class Int: public None {
public:
	using value_type = iinf;
private:
	value_type value;

public:
	/* constructors */
	Int();
	explicit Int(value_type &&);
	explicit Int(const value_type &);
	// explicit Int(const str &);
	// explicit Int(const char *&&);
	// explicit Int(bool);
	// explicit Int(f64);

	/* destructor */
	~Int();


	template <typename T> T as() const;

	inline iinf& ref() { return value; }
	inline const iinf& data() const { return value; }



	/* comparison operators */
	template <typename T> i8 compare(const T &) const;
	template <typename T> inline bool operator == (const T &rhs) const { return compare(rhs) == 0; };
	template <typename T> inline bool operator != (const T &rhs) const { return compare(rhs) != 0; };
	template <typename T> inline bool operator < (const T &rhs) const { return compare(rhs) < 0; };
	template <typename T> inline bool operator > (const T &rhs) const { return compare(rhs) > 0; };
	template <typename T> inline bool operator <= (const T &rhs) const { return compare(rhs) <= 0; };
	template <typename T> inline bool operator >= (const T &rhs) const { return compare(rhs) >= 0; };

	template <typename T> Object operator + (const T &) const;
	template <typename T> Object operator - (const T &) const;
	template <typename T> Object operator * (const T &) const;
	template <typename T> Object operator / (const T &) const;
	template <typename T> Object div(const T &) const;
	template <typename T> Object operator % (const T &) const;
};

}

#endif
