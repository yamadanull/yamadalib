#pragma once

#include "rational-geometry-base.hpp"

// Ax+By=C
struct FLine {
	Fraction A, B, C;

	FLine() = default;
	FLine(const FPoint &a, const FPoint &b) {
		assert(a != b);
		if (a.x == b.x) {
			A = 1;
			B = 0;
			C = a.x;
		}
		else {
			FPoint r = a - b;
			A = -(r.y / r.x);
			B = 1;
			C = A * a.x + B * a.y;
		}
	}

	FLine(const Fraction &_A, const Fraction &_B, const Fraction &_C) : A(_A), B(_B), C(_C) {
		assert(_A != 0 || _B != 0);
	}

	pair<Fraction, bool> slope() const {
		if (B == 0) return make_pair(0, false);
		return make_pair(-(A / B), true);
	}

	pair<Fraction, bool> section() const {
		if (B == 0) return make_pair(C / A, false);
		return make_pair(C / B, true);
	}

	pair<Fraction, bool> F(Fraction x) {
		if (B == 0) return make_pair(0, false);
		return make_pair(slope().first * x + section().first, true);
	}

	friend bool operator==(const FLine& l, const FLine& m) {
		return l.slope() == m.slope() && l.section() == m.section();
	}

	friend bool operator<(const FLine& l, const FLine& m) {
		auto [a0, a0_bool] = l.slope();
		auto [a1, a1_bool] = m.slope();
		if (!a0_bool && !a1_bool) {
			return l.section().first < m.section().first;
		}
		if (!a0_bool) return false;
		if (!a1_bool) return true;
		if (a0 == a1) return l.section().first < m.section().first;
		return a0 < a1;
	}
};

pair<FPoint, bool> cross_point(FLine &l, FLine &m) {
	auto [a, a_bool] = l.slope();
	auto [c, c_bool] = m.slope();
	if (make_pair(a, a_bool) == make_pair(c, c_bool)) return make_pair(FPoint(), false);
	if (!a_bool) {
		Fraction X = l.section().first;
		Fraction Y = m.F(X).first;
		return make_pair(FPoint(X, Y), true);
	}
	if (!c_bool) {
		Fraction X = m.section().first;
		Fraction Y = l.F(X).first;
		return make_pair(FPoint(X, Y), true);
	}
	Fraction b = l.section().first;
	Fraction d = m.section().first;
	Fraction X = -(b - d) / (a - c);
	Fraction Y = l.F(X).first;
	return make_pair(FPoint(X, Y), true);
}
