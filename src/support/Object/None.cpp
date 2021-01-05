#include "Object.hpp"

namespace innerTypes {

None::None() = default;
None::~None() = default;


template <> Int None::as<Int>() const { return Int(); }
template <> Str None::as<Str>() const { return Str("None"); }
template <> Bool None::as<Bool>() const { return Bool(); }
template <> Float None::as<Float>() const { return Float(); }

}
