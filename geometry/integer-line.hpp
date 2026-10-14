#pragma once

#include "integer-geometry.hpp"
#include "../math-fast/gcd.hpp"

// Ax + By = C
struct Line {
	using T = long long;
	using lld = long double;

	T A, B, C;
	lld inf, minf;

	Line(T a, T b, T c) {
		assert(a != 0 || b != 0);
		build(a, b, c);
	}

	Line(Point p, Point q) {
		assert(p != q);
		T a = p.y - q.y;
		T b = q.x - p.x;
		T c = a * p.x + b * p.y;
		build(a, b, c);
	}

	void build(T a, T b, T c) {
		inf = std::numeric_limits<lld>::max();
		minf = std::numeric_limits<lld>::min();
		if (b < 0 || (b == 0 && a < 0)) {
			a *= -1;
			b *= -1;
			c *= -1;
		}
		T g = gcd(a, b);
		g = gcd(g, c);
		A = a / g;
		B = b / g;
		C = c / g;
	}

	lld slope() const {
		if (B == 0) return inf;
		return -(lld)A / B;
	}
	lld section() const {
		if (B == 0) return inf;
		return (lld)C / B;
	}

	friend bool operator==(const Line &l, const Line &m) {
		return (l.A == m.A && l.B == m.B && l.C == m.C);
	}
	friend bool operator<(const Line &l, const Line &m) {
		return make_tuple(l.A, l.B, l.C) < make_tuple(m.A, m.B, m.C);
	}
};
