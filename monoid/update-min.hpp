#pragma once

#include "min.hpp"
#include "update.hpp"

namespace ACTED_MONOID {

template <typename E, E INF = std::numeric_limits<E>::max()>
struct Update_Min {
	using Monoid_X = MONOID::Min<E, INF>;
	using Monoid_A = MONOID::Update<E>;
	using X = typename Monoid_X::value_type; // E
	using A = typename Monoid_A::value_type; // optional<E>
	static constexpr X O(const X& x, const A& a, const long long) {
		return a.has_value() ? a.value() : x;
	}
};

} // namespace ACTED_MONOID

