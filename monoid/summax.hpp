#pragma once

#include <algorithm>
#include <limits>

namespace MONOID {

template <typename E, E MNF = std::numeric_limits<E>::min()>
struct SumMax {
	using value_type = std::pair<E, E>;
	static constexpr value_type O(const value_type& x, const value_type& y) {
		return {x.first + y.first, std::max(x.second, y.second)};
	}
	static constexpr value_type I() { return {E(0), MNF}; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
