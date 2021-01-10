#include "Object.hpp"

const innerTypes::NoneType Object::None;
innerTypes::BaseType *const Object::noneptr(const_cast<innerTypes::NoneType*>(&None));

/* ---------- construtors ---------- */
Object::Object(): ptr(noneptr) {}
Object::Object(Object &&rhs): ptr(rhs.ptr) { rhs.ptr = noneptr; }
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
		if (auto q = rhs.as_type<Int>())			return innerTypes::compare(*p, *q);
		if (auto q = rhs.as_type<Bool>()) 			return innerTypes::compare(*p, *q);
		if (auto q = rhs.as_type<Float>())			return innerTypes::compare(*p, *q);
	} else if (auto p = as_type<Str>()) {
		if (auto q = rhs.as_type<Str>())			return innerTypes::compare(*p, *q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return innerTypes::compare(*p, *q);
		if (auto q = rhs.as_type<Bool>())			return innerTypes::compare(*p, *q);
		if (auto q = rhs.as_type<Float>())			return innerTypes::compare(*p, *q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return innerTypes::compare(*p, *q);
		if (auto q = rhs.as_type<Bool>())			return innerTypes::compare(*p, *q);
		if (auto q = rhs.as_type<Float>())			return innerTypes::compare(*p, *q);
	}
	throw std::invalid_argument("unsupported argument type(s) in method compare()");
}

/* ---------- operator: == ---------- */
bool Object::operator == (const Object &rhs) const {
	if (is_type<NoneType>() or rhs.is_type<NoneType>())
		return is_type<NoneType>() and rhs.is_type<NoneType>();
	if (is_type<Str>() xor rhs.is_type<Str>())
		return false;
	return compare(rhs) == 0;
}

/* ---------- operator: = ---------- */

Object& Object::operator = (const Object &rhs) {
	if (this == &rhs) return *this;
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
	ptr = rhs.ptr; rhs.ptr = noneptr;
	return *this;
}

/* ---------- operator: not ---------- */
Object Object::operator not () const {
	if (auto p = as_type<Int>())					return Object(not (p->as<bool>()));
	if (auto p = as_type<Str>())					return Object(not (p->as<bool>()));
	if (auto p = as_type<Bool>())					return Object(not (p->as<bool>()));
	if (auto p = as_type<Float>())					return Object(not (p->as<bool>()));
													return Object(true);
}

/* ---------- operator: -(pre) ---------- */
Object Object::operator - () const {
	if (auto p = as_type<Int>())					return Object(-p->data());
	if (auto p = as_type<Bool>())					return Object(p->data() ? -1 : 0);
	if (auto p = as_type<Float>())					return Object(-p->data());
	throw std::invalid_argument("unsupported operand type(s) in operator -(pre)");
}

/* ---------- operator: + ---------- */
Object Object::operator + (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) + (*q);
		if (auto q = rhs.as_type<Bool>()) 			return (*p) + (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) + (*q);
	} else if (auto p = as_type<Str>()) {
		if (auto q = rhs.as_type<Str>())			return (*p) + (*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) + (*q);
		if (auto q = rhs.as_type<Bool>())			return (*p) + (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) + (*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) + (*q);
		if (auto q = rhs.as_type<Bool>())			return (*p) + (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) + (*q);
	}
	throw std::invalid_argument("unsupported operand type(s) in operator +");
}

/* ---------- operator: - ---------- */
Object Object::operator - (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) - (*q);
		if (auto q = rhs.as_type<Bool>()) 			return (*p) - (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) - (*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) - (*q);
		if (auto q = rhs.as_type<Bool>())			return (*p) - (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) - (*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) - (*q);
		if (auto q = rhs.as_type<Bool>())			return (*p) - (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) - (*q);
	}
	throw std::invalid_argument("unsupported operand type(s) in operator -");
}

/* ---------- operator: * ---------- */
Object Object::operator * (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) * (*q);
		if (auto q = rhs.as_type<Str>())			return (*p) * (*q);
		if (auto q = rhs.as_type<Bool>()) 			return (*p) * (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) * (*q);
	} else if (auto p = as_type<Str>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) * (*q);
		if (auto q = rhs.as_type<Bool>())			return (*p) * (*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) * (*q);
		if (auto q = rhs.as_type<Str>())			return (*p) * (*q);
		if (auto q = rhs.as_type<Bool>())			return (*p) * (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) * (*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) * (*q);
		if (auto q = rhs.as_type<Bool>())			return (*p) * (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) * (*q);
	}
	throw std::invalid_argument("unsupported operand type(s) in operator *");
}

/* ---------- operator: / ---------- */
Object Object::operator / (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) / (*q);
		if (auto q = rhs.as_type<Bool>()) 			return (*p) / (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) / (*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) / (*q);
		if (auto q = rhs.as_type<Bool>())			return (*p) / (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) / (*q);
	} else if (auto p = as_type<Float>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) / (*q);
		if (auto q = rhs.as_type<Bool>())			return (*p) / (*q);
		if (auto q = rhs.as_type<Float>())			return (*p) / (*q);
	}
	throw std::invalid_argument("unsupported operand type(s) in operator /");
}

/* ---------- method: div ---------- */
Object Object::div(const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return innerTypes::div(*p, *q);
		if (auto q = rhs.as_type<Bool>()) 			return innerTypes::div(*p, *q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return innerTypes::div(*p, *q);
		if (auto q = rhs.as_type<Bool>())			return innerTypes::div(*p, *q);
	}
	throw std::invalid_argument("unsupported operand type(s) in operator //");
}

/* ---------- operator: % ---------- */
Object Object::operator % (const Object &rhs) const {
	if (auto p = as_type<Int>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) % (*q);
		if (auto q = rhs.as_type<Bool>()) 			return (*p) % (*q);
	} else if (auto p = as_type<Bool>()) {
		if (auto q = rhs.as_type<Int>())			return (*p) % (*q);
		if (auto q = rhs.as_type<Bool>())			return (*p) % (*q);
	}
	throw std::invalid_argument("unsupported operand type(s) in operator %");
}
