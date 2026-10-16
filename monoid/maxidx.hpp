#pragma once

#include <limits>
#include <utility>

namespace MONOID {

template <typename E, E MNF = std::numeric_limits<E>::min(), bool tie_is_left = true>
struct MaxIdx {
	using value_type = std::pair<E, int>;
	static constexpr bool is_small(const value_type& x, const value_type& y) {
		if (x.first < y.first) return true;
		if (x.first > y.first) return false;
		return !tie_is_left xor x.second < y.second;
	}
	static constexpr value_type O(const value_type& x, const value_type& y) {
		return is_small(x, y) ? y : x;
	}
	static constexpr value_type I() { return {MNF, -1}; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
