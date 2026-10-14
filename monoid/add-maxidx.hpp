#pragma once

#include "add.hpp"
#include "maxidx.hpp"

namespace ACTED_MONOID {

template <typename E, E MNF = std::numeric_limits<E>::min(), bool tie_is_left = true>
struct Add_MaxIdx {
	using Monoid_X = MONOID::MaxIdx<E, MNF, tie_is_left>;
	using Monoid_A = MONOID::Add<E>;
	using X = typename Monoid_X::value_type; // pair<E, int>
	using A = typename Monoid_A::value_type; // E
	static constexpr X O(const X& x, const A& a, const long long) {
		if (x.first == MNF) return x;
		return {x.first + a, x.second};
	}
};

} // namespace ACTED_MONOID

