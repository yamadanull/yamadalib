#pragma once

#include "min.hpp"
#include "add.hpp"

namespace ACTED_MONOID {

template <typename E, E INF = std::numeric_limits<E>::max()>
struct Add_Min {
	using Monoid_X = MONOID::Min<E, INF>;
	using Monoid_A = MONOID::Add<E>;
	using X = typename Monoid_X::value_type; // E
	using A = typename Monoid_A::value_type; // E
	static constexpr X O(const X& x, const A& a, const long long) { return x + a; }
};

} // namespace ACTED_MONOID

