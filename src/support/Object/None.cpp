#include "Object.hpp"

namespace innerTypes {

None::None() = default;
None::~None() = default;


Int None::asInt() const { return Int(); }
Str None::asStr() const { return Str("None"); }
Bool None::asBool() const { return Bool(); }
Float None::asFloat() const { return Float(); }

}
