#pragma once

#include "basic.hpp"

namespace Monoid {

template <typename T>
struct Xor : Common<Xor<T>, T> {
	static constexpr bool COMMUTE = 1;
	using value_type = T;
	T a;
	constexpr Xor &operator+=(const Xor &b) {
		a ^= T(b);
		return *this;
	}
	constexpr Xor &operator-=(const Xor &b) {
		a ^= T(b);
		return *this;
	}
	constexpr Xor() : a(0) {}
	constexpr Xor(T _a) : a(_a) {}
};

template <typename T>
struct And : Common<And<T>, T> {
	static constexpr bool COMMUTE = 1;
	using value_type = T;
	T a;
	constexpr And &operator+=(const And &b) {
		a &= T(b);
		return *this;
	}
	constexpr And() : a(-1) {}
	constexpr And(T _a) : a(_a) {}
};

template <typename T>
struct Or : Common<Or<T>, T> {
	static constexpr bool COMMUTE = 1;
	using value_type = T;
	T a;
	constexpr Or &operator+=(const Or &b) {
		a |= T(b);
		return *this;
	}
	constexpr Or() : a(0) {}
	constexpr Or(T _a) : a(_a) {}
};

template <typename T>
struct Multiply : Common<Multiply<T>, T> {
	static constexpr bool COMMUTE = 1;
	using value_type = T;
	T a;
	constexpr Multiply &operator+=(const Multiply &b) {
		a *= T(b);
		return *this;
	}
	constexpr Multiply &operator-=(const Multiply &b) {
		a /= T(b);
		return *this;
	}
	constexpr Multiply() : a(1) {}
	constexpr Multiply(T _a) : a(_a) {}
};

} // namespace Monoid

