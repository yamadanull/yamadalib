#pragma once

#include <algorithm>
#include <limits>

namespace MONOID {

template <typename E, E MNF = std::numeric_limits<E>::min(), E INF = std::numeric_limits<E>::max()>
struct MinMax {
	using value_type = std::pair<E, E>;
	static constexpr value_type O(const value_type& x, const value_type& y) {
		return {std::min(x.first, y.first), std::max(x.second, y.second)};
	}
	static constexpr value_type I() { return {INF, MNF}; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
