#pragma once

#include <algorithm>
#include <limits>

namespace MONOID {

template <typename E, E INF = std::numeric_limits<E>::max()>
struct Min {
	using value_type = E;
	static constexpr value_type O(const value_type& x, const value_type& y) { return std::min(x, y); }
	static constexpr value_type I() { return INF; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
