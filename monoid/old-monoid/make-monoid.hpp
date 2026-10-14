#pragma once

template <typename T, T (*op)(T, T), T (*ti)(), bool COMMUTATIVE = 0>
struct MyMonoid {
	using value_type = T;
	T a;
	constexpr MyMonoid &operator+=(const MyMonoid &b) { a = op(a, b); return *this; }
	constexpr MyMonoid operator+(const MyMonoid &b) const { return op(a, b); }
	constexpr bool operator==(const MyMonoid &b) const { return (*this).a == b.a; }
	constexpr bool operator!=(const MyMonoid &b) const { return (*this).a != b.a; }
	constexpr MyMonoid() : a(ti()) {}
	constexpr MyMonoid(T _a) : a(_a) {}
	constexpr operator T() const { return a; }
};

// h(f, g)(x) : g(f(x))
template <typename T, typename E, T (*f)(T, T), T (*g)(T, E), E (*h)(E, E),
          T (*ti)(), E (*ei)(), bool S_COMMUTATIVE = 0, bool F_COMMUTATIVE = 0>
struct MyActedMonoid : MyMonoid<T, f, ti, S_COMMUTATIVE> {
	using Base = MyMonoid<T, f, ti, S_COMMUTATIVE>;
	using Base::Base;
	using ActingMonoid = MyMonoid<E, h, ei, F_COMMUTATIVE>;
	constexpr MyActedMonoid &operator+=(const MyActedMonoid &b) { (*this).a = f(MyActedMonoid(*this), b); return *this; }
	constexpr MyActedMonoid operator+(const MyActedMonoid &b) const { return f(MyActedMonoid(*this), b); }
	constexpr MyActedMonoid &operator^=(const ActingMonoid &b) { (*this).a = g((*this).a, b); return *this; }
	constexpr MyActedMonoid operator^(const ActingMonoid &b) const { return g(MyActedMonoid(*this), b); }
	constexpr bool operator==(const MyActedMonoid &b) const { return (*this).a == b.a; }
	constexpr bool operator!=(const MyActedMonoid &b) const { return (*this).a != b.a; }
};
