#pragma once

namespace MONOID {

template <typename E>
struct Gcd {
	using value_type = E;
	static constexpr value_type O(const value_type& x, const value_type& y) { return std::gcd(x, y); }
	static constexpr value_type I() { return 0; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
