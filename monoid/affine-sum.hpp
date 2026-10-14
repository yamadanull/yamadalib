#pragma once

#include "add.hpp"
#include "affine.hpp"

namespace ACTED_MONOID {

template <typename mint>
struct Affine_Sum {
	using Monoid_X = MONOID::Add<mint>;
	using Monoid_A = MONOID::AffineMonoid<mint>;
	using X = typename Monoid_X::value_type; // mint
	using A = typename Monoid_A::value_type; // AffineMonoid<mint>
	static constexpr X O(const X& x, const A& a, const long long &size) {
		return x * a.a + mint(size) * a.b;
	}
};

} // namespace ACTED_MONOID

