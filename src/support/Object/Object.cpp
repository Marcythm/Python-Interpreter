#include "Object.hpp"

using innerTypes::None;
using innerTypes::Int;
using innerTypes::Str;
using innerTypes::Bool;
using innerTypes::Float;

const None Object::NONE;


/* ---------- construtors ---------- */

Object::Object(): ptr(const_cast<None*>(&NONE)) {}
Object::Object(const Object &rhs): Object() {
	if (auto p = rhs.as_type<Int>()) 				ptr = new Int(*p);
	else if (auto p = rhs.as_type<Str>()) 			ptr = new Str(*p);
	else if (auto p = rhs.as_type<Bool>()) 			ptr = new Bool(*p);
	else if (auto p = rhs.as_type<Float>()) 		ptr = new Float(*p);
}
Object::Object(Object &&rhs): ptr(rhs.ptr) { rhs.ptr = nullptr; }

Object::Object(const iinf &rhs): ptr(new Int(rhs)) {}
Object::Object(const str &rhs): ptr(new Str(rhs)) {}
Object::Object(const char *rhs): ptr(new Str(rhs)) {}
Object::Object(bool rhs): ptr(new Bool(rhs)) {}
Object::Object(f64 rhs): ptr(new Float(rhs)) {}

/* ---------- destructor ---------- */
Object::~Object() { delete ptr; }



/* ---------- comparison operators ---------- */
i8 Object::compare(const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>()) 			return p->compare(*q);
		else if (auto q = rhs.as_type<Bool>()) 		return p->compare(*q);
		else if (auto q = rhs.as_type<Float>())		return p->compare(*q);
	} else if (auto p = as_type<Str>()) {
		if (auto q = rhs.as_type<Str>())			return p->compare(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->compare(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->compare(*q);
		else if (auto q = rhs.as_type<Float>())		return p->compare(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->compare(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->compare(*q);
		else if (auto q = rhs.as_type<Float>())		return p->compare(*q);
	}
	throw std::invalid_argument("");
}

/* ---------- assignment operators ---------- */

Object& Object::operator = (const Object &rhs) {
	if (auto p = rhs.as_type<Int>()) 				ptr = new Int(*p);
	else if (auto p = rhs.as_type<Str>()) 			ptr = new Str(*p);
	else if (auto p = rhs.as_type<Bool>()) 			ptr = new Bool(*p);
	else if (auto p = rhs.as_type<Float>()) 		ptr = new Float(*p);
	else 											ptr = const_cast<None*>(&NONE);
	return *this;
}
Object& Object::operator = (Object &&rhs) {
	ptr = rhs.ptr; rhs.ptr = nullptr;
	return *this;
}

Object Object::operator + (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>()) 			return p->operator+(*q);
		else if (auto q = rhs.as_type<Bool>()) 		return p->operator+(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator+(*q);
	} else if (auto p = as_type<Str>()) {
		if (auto q = rhs.as_type<Str>())			return p->operator+(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator+(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->operator+(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator+(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator+(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->operator+(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator+(*q);
	}
	throw std::invalid_argument("");
}

Object Object::operator - (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>()) 			return p->operator-(*q);
		else if (auto q = rhs.as_type<Bool>()) 		return p->operator-(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator-(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator-(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->operator-(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator-(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator-(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->operator-(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator-(*q);
	}
	throw std::invalid_argument("");
}

Object Object::operator * (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>()) 			return p->operator*(*q);
		else if (auto q = rhs.as_type<Str>())		return p->operator*(*q);
		else if (auto q = rhs.as_type<Bool>()) 		return p->operator*(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator*(*q);
	} else if (auto p = as_type<Str>()) {
		if (auto q = rhs.as_type<Int>()) 			return p->operator*(*q);
		else if (auto q = rhs.as_type<Bool>()) 		return p->operator*(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator*(*q);
		else if (auto q = rhs.as_type<Str>())		return p->operator*(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->operator*(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator*(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator*(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->operator*(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator*(*q);
	}
	throw std::invalid_argument("");
}

Object Object::operator / (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>()) 			return p->operator/(*q);
		else if (auto q = rhs.as_type<Bool>()) 		return p->operator/(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator/(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator/(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->operator/(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator/(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator/(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->operator/(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator/(*q);
	}
	throw std::invalid_argument("");
}

Object Object::div(const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>()) 			return p->div(*q);
		else if (auto q = rhs.as_type<Bool>()) 		return p->div(*q);
		else if (auto q = rhs.as_type<Float>())		return p->div(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->div(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->div(*q);
		else if (auto q = rhs.as_type<Float>())		return p->div(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->div(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->div(*q);
		else if (auto q = rhs.as_type<Float>())		return p->div(*q);
	}
	throw std::invalid_argument("");
}

Object Object::operator % (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>()) 			return p->operator%(*q);
		else if (auto q = rhs.as_type<Bool>()) 		return p->operator%(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator%(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator%(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->operator%(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator%(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator%(*q);
		else if (auto q = rhs.as_type<Bool>())		return p->operator%(*q);
		else if (auto q = rhs.as_type<Float>())		return p->operator%(*q);
	}
	throw std::invalid_argument("");
}
