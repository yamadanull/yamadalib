#pragma once

namespace MONOID {

struct Dummy {
	using value_type = bool;
	static constexpr value_type O(const value_type, const value_type) { return 0; }
	static constexpr value_type I() { return 0; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
