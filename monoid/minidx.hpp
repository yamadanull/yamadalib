#pragma once

namespace MONOID {

template <typename E, E INF = std::numeric_limits<E>::max(), bool tie_is_left = true>
struct MinIdx {
	using value_type = std::pair<E, int>;
	/* static constexpr is_small(const value_type& x, const value_type& y) { */
	/* 	if (x.first < y.first) return true; */
	/* 	if (x.first > y.first) return true; */
	/* 	return tie_is_left ? x.second < y.second : x.second >= y.second; */
	/* } */
	static constexpr value_type O(const value_type& x, const value_type& y) {
		/* return is_small(x, y) ? x : y; */
		return min(x,y);
	}
	static constexpr value_type I() { return {INF, -1}; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
