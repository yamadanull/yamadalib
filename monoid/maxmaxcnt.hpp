#pragma once

namespace MONOID {

template <typename E, E MNF = std::numeric_limits<E>::min()>
struct MaxMaxcnt {
	using value_type = std::pair<E, E>;
	static constexpr value_type O(const value_type& x, const value_type& y) {
		auto [xmax, xmaxcnt] = x;
		auto [ymax, ymaxcnt] = y;
		if (xmax > ymax) return x;
		if (xmax < ymax) return y;
		return {xmax, xmaxcnt + ymaxcnt};
	}
	static constexpr value_type I() { return {MNF, 0}; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
