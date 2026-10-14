#pragma once

namespace MONOID {

template <typename mint>
struct Mul {
	using value_type = mint;
	static constexpr value_type O(const value_type& x, const value_type& y) noexcept { return x * y; }
	static constexpr value_type inverse(const value_type &x) noexcept { return mint(1) / x; }
	static constexpr value_type I() { return value_type(1); }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
