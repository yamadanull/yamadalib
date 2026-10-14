#pragma once

#include "max.hpp"
#include "update.hpp"

namespace ACTED_MONOID {

template <typename E, E MNF = std::numeric_limits<E>::min()>
struct Update_Max {
	using Monoid_X = MONOID::Max<E, MNF>;
	using Monoid_A = MONOID::Update<E>;
	using X = typename Monoid_X::value_type; // E
	using A = typename Monoid_A::value_type; // optional<E>
	static constexpr X O(const X& x, A& a, const long long) {
		return a.has_value() ? a.value() : x;
	}
};

} // namespace ACTED_MONOID

