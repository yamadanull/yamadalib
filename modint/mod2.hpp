#pragma once

// UF with Potential、BITなどに突っ込む用
struct Mod2 {
	bool a;
	constexpr Mod2() : a(0) {}
	template <typename T>
	constexpr Mod2(T _a) : a(_a & 1) {}

	constexpr Mod2 &operator+=(const Mod2 &x) {
		a ^= x.a;
		return *this;
	}
	constexpr Mod2 &operator-=(const Mod2 &x) {
		a ^= x.a;
		return *this;
	}
	constexpr Mod2 &operator*=(const Mod2 &x) {
		a &= x.a;
		return *this;
	}
	constexpr Mod2 operator+(const Mod2 &x) const { return Mod2(*this) += x; }
	constexpr Mod2 operator-(const Mod2 &x) const { return Mod2(*this) += x; }
	constexpr Mod2 operator*(const Mod2 &x) const { return Mod2(*this) *= x; }
	constexpr Mod2 operator-() const { return a; }
	constexpr Mod2 operator+() const { return a; }
	constexpr bool operator==(const Mod2 &x) const { return !(a ^ x.a); }
	constexpr bool operator!=(const Mod2 &x) const { return a ^ x.a; }
	friend ostream &operator<<(ostream &os, const Mod2 &x) { return os << x.a; }
};
