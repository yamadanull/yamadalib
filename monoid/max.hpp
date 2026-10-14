#pragma once

#include <algorithm>
#include <limits>

namespace MONOID {

template <typename E, E MNF = std::numeric_limits<E>::min()>
struct Max {
	using value_type = E;
	static constexpr value_type O(const value_type& x, const value_type& y) { return std::max(x, y); }
	static constexpr value_type I() { return MNF; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
