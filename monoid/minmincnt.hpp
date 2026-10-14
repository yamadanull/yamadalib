#pragma once

namespace MONOID {

template <typename E, E INF = std::numeric_limits<E>::max()>
struct MinMincnt {
	using value_type = std::pair<E, E>;
	static constexpr value_type O(const value_type& x, const value_type& y) {
		auto [xmin, xmincnt] = x;
		auto [ymin, ymincnt] = y;
		if (xmin > ymin) return y;
		if (xmin < ymin) return x;
		return {xmin, xmincnt + ymincnt};
	}
	static constexpr value_type I() { return {INF, 0}; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
