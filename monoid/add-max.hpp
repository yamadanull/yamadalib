#pragma once

#include "add.hpp"
#include "max.hpp"

namespace ACTED_MONOID {

template <typename E, E MNF = std::numeric_limits<E>::min()>
struct Add_Max {
	using Monoid_X = MONOID::Max<E, MNF>;
	using Monoid_A = MONOID::Add<E>;
	using X = typename Monoid_X::value_type; // E
	using A = typename Monoid_A::value_type; // E
	static constexpr X O(const X& x, const A& a, const long long) {
		return x == MNF ? x : x + a;
	}
};

} // namespace ACTED_MONOID

