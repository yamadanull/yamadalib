#pragma once

template <typename T, T (*op)(T, T), T (*ti)(), bool COMMUTATIVE = 0>
struct MyMonoid {
	using value_type = T;
	static constexpr value_type O(const value_type& x, const value_type& y) { return op(x, y); }
	static constexpr value_type I() { return ti(); }
};

// h(f, g)(x) : g(f(x))
template <typename T, typename E, T (*f)(T, T), T (*g)(T, E, long long), E (*h)(E, E), T (*ti)(), E (*ei)(), bool X_COM = 0, bool A_COM = 0>
struct MyActedMonoid {
	using Monoid_X = MyMonoid<T, f, ti, X_COM>;
	using Monoid_A = MyMonoid<E, h, ei, A_COM>;
	using X = typename Monoid_X::value_type; // T
	using A = typename Monoid_A::value_type; // E
	static constexpr X O(const X& x, const A& a, const long long &size) { return g(x, a, size); }
};

