#pragma once

#include "add.hpp"
#include "update.hpp"

namespace ACTED_MONOID {

template <typename E>
struct Update_Sum {
	using Monoid_X = MONOID::Add<E>;
	using Monoid_A = MONOID::Update<E>;
	using X = typename Monoid_X::value_type; // E
	using A = typename Monoid_A::value_type; // optional<E>
	static constexpr X O(const X& x, const A& a, const long long &size) {
		return a.has_value() ? a.value() * E(size) : x;
	}
};

} // namespace ACTED_MONOID

