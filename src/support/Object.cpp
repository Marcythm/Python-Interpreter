#include "Object.hpp"

const innerTypes::None Object::NONE;
innerTypes::None *const Object::noneptr(const_cast<innerTypes::None*>(&NONE));

/* ---------- construtors ---------- */
Object::Object(): ptr(noneptr) {}
Object::Object(Object &&rhs): ptr(rhs.ptr) { rhs.ptr = nullptr; }
Object::Object(const Object &rhs): ptr(noneptr) {
	if (auto p = rhs.as_type<Int>())				ptr = new Int(*p);
	else if (auto p = rhs.as_type<Str>()) 			ptr = new Str(*p);
	else if (auto p = rhs.as_type<Bool>()) 			ptr = new Bool(*p);
	else if (auto p = rhs.as_type<Float>()) 		ptr = new Float(*p);
}

/* ---------- destructor ---------- */
Object::~Object() { if (ptr != noneptr) delete ptr; }

/* ---------- method: compare ---------- */
i8 Object::compare(const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return p->compare(*q);
		if (auto q = rhs.as_type<Bool>()) 			return p->compare(*q);
		if (auto q = rhs.as_type<Float>())			return p->compare(*q);
	} else if (auto p = as_type<Str>()) {
		if (auto q = rhs.as_type<Str>())			return p->compare(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->compare(*q);
		if (auto q = rhs.as_type<Bool>())			return p->compare(*q);
		if (auto q = rhs.as_type<Float>())			return p->compare(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->compare(*q);
		if (auto q = rhs.as_type<Bool>())			return p->compare(*q);
		if (auto q = rhs.as_type<Float>())			return p->compare(*q);
	}
	throw std::invalid_argument("Unsupported type in method compare()");
}

/* ---------- operator: = ---------- */

Object& Object::operator = (const Object &rhs) {
	this->~Object();
	if (auto p = rhs.as_type<Int>())				ptr = new Int(*p);
	else if (auto p = rhs.as_type<Str>()) 			ptr = new Str(*p);
	else if (auto p = rhs.as_type<Bool>()) 			ptr = new Bool(*p);
	else if (auto p = rhs.as_type<Float>()) 		ptr = new Float(*p);
	else 											ptr = noneptr;
	return *this;
}
Object& Object::operator = (Object &&rhs) {
	this->~Object();
	ptr = rhs.ptr; rhs.ptr = nullptr;
	return *this;
}

/* ---------- operator: not ---------- */
bool Object::operator not () const {
	if (auto p = as_type<Int>())					return not (p->as<bool>());
	if (auto p = as_type<Str>())					return not (p->as<bool>());
	if (auto p = as_type<Bool>())					return not (p->as<bool>());
	if (auto p = as_type<Float>())					return not (p->as<bool>());
	throw std::invalid_argument("Unsupported type in operator -(pre)");
}

/* ---------- operator: -(pre) ---------- */
Object Object::operator - () const {
	if (auto p = as_type<Float>())					return Object(-p->data());
	if (auto p = as_type<Int>())					return Object(-p->data());
	if (auto p = as_type<Bool>())					return Object(p->data() ? -1 : 0);
	throw std::invalid_argument("Unsupported type in operator -(pre)");
}

/* ---------- operator: + ---------- */
Object Object::operator + (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator+(*q);
		if (auto q = rhs.as_type<Bool>()) 			return p->operator+(*q);
		if (auto q = rhs.as_type<Float>())			return p->operator+(*q);
	} else if (auto p = as_type<Str>()) {
		if (auto q = rhs.as_type<Str>())			return p->operator+(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator+(*q);
		if (auto q = rhs.as_type<Bool>())			return p->operator+(*q);
		if (auto q = rhs.as_type<Float>())			return p->operator+(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator+(*q);
		if (auto q = rhs.as_type<Bool>())			return p->operator+(*q);
		if (auto q = rhs.as_type<Float>())			return p->operator+(*q);
	}
	throw std::invalid_argument("Unsupported type in operator +");
}

/* ---------- operator: - ---------- */
Object Object::operator - (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator-(*q);
		if (auto q = rhs.as_type<Bool>()) 			return p->operator-(*q);
		if (auto q = rhs.as_type<Float>())			return p->operator-(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator-(*q);
		if (auto q = rhs.as_type<Bool>())			return p->operator-(*q);
		if (auto q = rhs.as_type<Float>())			return p->operator-(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator-(*q);
		if (auto q = rhs.as_type<Bool>())			return p->operator-(*q);
		if (auto q = rhs.as_type<Float>())			return p->operator-(*q);
	}
	throw std::invalid_argument("Unsupported type in operator -");
}

/* ---------- operator: * ---------- */
Object Object::operator * (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator*(*q);
		if (auto q = rhs.as_type<Str>())			return p->operator*(*q);
		if (auto q = rhs.as_type<Bool>()) 			return p->operator*(*q);
		if (auto q = rhs.as_type<Float>())			return p->operator*(*q);
	} else if (auto p = as_type<Str>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator*(*q);
		if (auto q = rhs.as_type<Bool>())			return p->operator*(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator*(*q);
		if (auto q = rhs.as_type<Str>())			return p->operator*(*q);
		if (auto q = rhs.as_type<Bool>())			return p->operator*(*q);
		if (auto q = rhs.as_type<Float>())			return p->operator*(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator*(*q);
		if (auto q = rhs.as_type<Bool>())			return p->operator*(*q);
		if (auto q = rhs.as_type<Float>())			return p->operator*(*q);
	}
	throw std::invalid_argument("Unsupported type in operator *");
}

/* ---------- operator: / ---------- */
Object Object::operator / (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator/(*q);
		if (auto q = rhs.as_type<Bool>()) 			return p->operator/(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator/(*q);
		if (auto q = rhs.as_type<Bool>())			return p->operator/(*q);
	}
	throw std::invalid_argument("Unsupported type in operator //");
}

/* ---------- method: div ---------- */
Object Object::div(const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return p->div(*q);
		if (auto q = rhs.as_type<Bool>()) 			return p->div(*q);
		if (auto q = rhs.as_type<Float>())			return p->div(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->div(*q);
		if (auto q = rhs.as_type<Bool>())			return p->div(*q);
		if (auto q = rhs.as_type<Float>())			return p->div(*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return p->div(*q);
		if (auto q = rhs.as_type<Bool>())			return p->div(*q);
		if (auto q = rhs.as_type<Float>())			return p->div(*q);
	}
	throw std::invalid_argument("Unsupported type in operator /");
}

/* ---------- operator: % ---------- */
Object Object::operator % (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator%(*q);
		if (auto q = rhs.as_type<Bool>()) 			return p->operator%(*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return p->operator%(*q);
		if (auto q = rhs.as_type<Bool>())			return p->operator%(*q);
	}
	throw std::invalid_argument("Unsupported type in operator %");
}
