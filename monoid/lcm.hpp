#pragma once

namespace MONOID {

template <typename E, E INF = std::numeric_limits<E>::max()>
struct Lcm {
	using value_type = E;
	static constexpr value_type O(const value_type& x, const value_type& y) {
		if (x == INF || y == INF) return INF;
		x /= std::gcd(x, y);
		if (x >= INF / y) return INF;
		return x * y;
	}
	static constexpr value_type I() { return 1; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
