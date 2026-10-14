#pragma once

#include "../math/rational.hpp"

template <typename R>
struct FPointBase {
	using P = FPointBase;
	R x, y;
	FPointBase() : x(0), y(0) {}
	FPointBase(R _x, R _y) : x(_x), y(_y) {}
	template <typename T, typename U>
		FPointBase(const pair<T, U>& p) : x(p.first), y(p.second) {}

	P operator+(const P& r) const { return {x + r.x, y + r.y}; }
	P operator-(const P& r) const { return {x - r.x, y - r.y}; }
	P operator*(R r) const { return {x * r, y * r}; }
	P operator/(R r) const { return {x / r, y / r}; }

	P& operator+=(const P& r) { return (*this) = (*this) + r; }
	P& operator-=(const P& r) { return (*this) = (*this) - r; }
	P& operator*=(R r) { return (*this) = (*this) * r; }
	P& operator/=(R r) { return (*this) = (*this) / r; }

	bool operator<(const P& r) const { return x != r.x ? x < r.x : y < r.y; }
	bool operator==(const P& r) const { return x == r.x and y == r.y; }
	bool operator!=(const P& r) const { return !((*this) == r); }

	R real() const { return x; }
	R imag() const { return y; }
	friend R real(const P& p) { return p.x; }
	friend R imag(const P& p) { return p.y; }
	friend R dot(const P& l, const P& r) { return l.x * r.x + l.y * r.y; } // 内積
	friend R cross(const P& l, const P& r) { return l.x * r.y - l.y * r.x; } // 外積
	friend R norm(const P& p) { return p.x * p.x + p.y * p.y; }

	pair<R, bool> slope() {
		if (x == 0) return make_pair(0, false);
		return make_pair(y / x, true);
	}

	friend istream& operator>>(istream& is, P& p) {
		R a, b;
		is >> a >> b;
		p = P{a, b};
		return is;
	}
	friend ostream& operator<<(ostream& os, const P& p) {
		return os << p.x << " " << p.y;
	}
};

using FPoint = FPointBase<Fraction>;

// ccw, 点の進行方向
int ccw(const FPoint& a, const FPoint& b, const FPoint& c) {
	FPoint x = b - a, y = c - a;
	if (cross(x, y) > 0) return +1;                 // 反時計回り
	if (cross(x, y) < 0) return -1;                // 時計回り
	if (min(norm(x), norm(y)) == 0) return 0;  // c=a または c=b
	if (dot(x, y) < 0) return +2;                   // c-a-b の順で一直線
	if (norm(x) < norm(y)) return -2;                 // a-b-c の順で一直線
	return 0;                                         // a-c-b の順で一直線
}
