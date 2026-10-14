#pragma once

#include <optional>

namespace MONOID {

template <typename T>
struct Update {
	using value_type = std::optional<T>;
	static constexpr value_type O(const value_type& x, const value_type& y) { return y.has_value() ? y : x; }
	static constexpr value_type I() { return std::nullopt; }
	static constexpr bool COMMUTATIVE = false;
};

} // namespace monoid
