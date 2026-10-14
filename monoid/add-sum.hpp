#pragma once

#include "add.hpp"

namespace ACTED_MONOID {

template <typename E>
struct Add_Sum {
	using Monoid_X = MONOID::Add<E>;
	using Monoid_A = MONOID::Add<E>;
	using X = typename Monoid_X::value_type; // E
	using A = typename Monoid_A::value_type; // E
	static constexpr X O(const X& x, const A& a, const long long &size) {
		return x + a * E(size);
	}
};

} // namespace ACTED_MONOID

