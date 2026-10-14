#pragma once

#include "../math/affine-transformation.hpp"

namespace MONOID {

template <typename mint>
struct AffineMonoid {
	using value_type = Affine<mint>;
	static constexpr value_type O(const value_type& x, const value_type& y) noexcept { return y(x); }
	static constexpr value_type inverse(const value_type &x) { return x.inverse(); }
	static constexpr value_type I() { return Affine<mint>(1, 0); }
	static constexpr bool COMMUTATIVE = false;
};

} // namespace monoid
