#pragma once

#include <algorithm>
#include <limits>

namespace MONOID {

template <typename E, E INF = std::numeric_limits<E>::max()>
struct SumMin {
	using value_type = std::pair<E, E>;
	static constexpr value_type O(const value_type& x, const value_type& y) {
		return {x.first + y.first, std::min(x.second, y.second)};
	}
	static constexpr value_type I() { return {E(0), INF}; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
