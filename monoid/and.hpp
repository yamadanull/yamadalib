#pragma once

namespace MONOID {

template <typename E>
struct And {
	using value_type = E;
	static constexpr value_type O(const value_type& x, const value_type& y) noexcept { return x & y; }
	static constexpr value_type I() { return value_type(-1); }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
