#pragma once

namespace MONOID {

template <typename E>
struct Add {
	using value_type = E;
	static constexpr value_type O(const value_type& x, const value_type& y) noexcept { return x + y; }
	static constexpr value_type inverse(const value_type &x) noexcept { return -x; }
	static constexpr value_type power(const value_type& x, long long n) noexcept { return value_type(n) * x; }
	static constexpr value_type I() { return value_type(0); }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
