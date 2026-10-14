#pragma once

#include "update.hpp"
#include "maxmaxcnt.hpp"

namespace ACTED_MONOID {

template <typename E, E MNF = std::numeric_limits<E>::min()>
struct Update_MaxMaxcnt {
	using Monoid_X = MONOID::MaxMaxcnt<E, MNF>;
	using Monoid_A = MONOID::Update<E>;
	using X = typename Monoid_X::value_type; // pair<E, E>
	using A = typename Monoid_A::value_type; // optional<E>
	static constexpr X O(const X& x, const A& a, const long long &size) {
		if (!a.has_value()) return x;
		return {a.value(), size};
	}
};

} // namespace ACTED_MONOID

