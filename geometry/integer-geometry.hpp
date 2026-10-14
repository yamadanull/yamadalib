#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

struct Point {
	using T = __int128_t;
	T x, y;
	Point() : x(0), y(0) {}
	Point(T x_, T y_) : x(x_), y(y_) {}

	Point &operator+=(const Point &p) { this->x += p.x; this->y += p.y; return *this; }
	Point &operator-=(const Point &p) { this->x -= p.x; this->y -= p.y; return *this; }
	Point &operator*=(const long long &r) { this->x *= r; this->y *= r; return *this; }
	Point &operator/=(const long long &r) { this->x /= r; this->y /= r; return *this; }
	Point operator+(const Point &p) const { return Point(*this) += p; }
	Point operator-(const Point &p) const { return Point(*this) -= p; }
	Point operator*(long long &r) const { return Point(*this) *= r; }
	Point operator/(long long &r) const { return Point(*this) /= r; }
	Point operator-() const { return Point(-this->x, -this->y); }
	bool operator==(const Point &p) const { return x == p.x && y == p.y; }
	bool operator!=(const Point &p) const { return x != p.x || y != p.y; }
	bool operator<(const Point &p) const { return x == p.x ? y < p.y : x < p.x; }

	int pos() const {
		if (y < 0) return -1;
		if (y == 0 && 0 <= x) return 0;
		return 1;
	}

	friend std::istream &operator>>(std::istream &is, Point &p) {
		long long x, y;
		is >> x >> y;
		p.x = x, p.y = y;
		return is;
	}

	friend std::ostream &operator<<(std::ostream &os, const Point &p) {
		os << (long long)(p.x) << " " << (long long)(p.y);
		return os;
	}
};
using Points = std::vector<Point>;

Point::T dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
Point::T cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }

// sort by argument (-Pi ~ Pi)
void ArgumentSort(Points &v) {
	std::ranges::sort(v, [](Point a, Point b) {
		if (a.pos() != b.pos()) return a.pos() < b.pos();
		return cross(a, b) > 0;
	});
}

// 1 ... counterclockwise / 0 straight / -1 clockwise
int ccw(const Point &a, const Point &b, const Point &c) {
	Point::T t = cross(b - a, c - a);
	return t < 0 ? -1 : t == 0 ? 0 : 1;
}

// v must have sorted by x-coordinate
Points LowerHull(const Points &ps) {
	int N = (int)ps.size();
	for (int i = 0; i < N - 1; i++) assert(ps[i].x <= ps[i + 1].x);
	if (N <= 2) return ps;
	Points convex(N);
	int k = 0;
	for (int i = 0; i < N; convex[k++] = ps[i++]) {
		while (k >= 2 && ccw(convex[k - 2], convex[k - 1], ps[i]) <= 0) --k;
	}
	convex.resize(k);
	return convex;
}

Points UpperHull(const Points &ps) {
	int N = (int)ps.size();
	for (int i = 0; i < N - 1; i++) assert(ps[i].x <= ps[i + 1].x);
	if (N <= 2) return ps;
	Points convex(N);
	int k = 0;
	for (int i = 0; i < N; convex[k++] = ps[i++]) {
		while (k >= 2 && ccw(convex[k - 2], convex[k - 1], ps[i]) >= 0) --k;
	}
	convex.resize(k);
	return convex;
}

Points ConvexHull(Points ps) {
	std::ranges::sort(ps, std::less{});
	ps.erase(std::ranges::unique(ps).begin(), ps.end());
	int N = ps.size();
	if (N <= 2) return ps;
	Points convex(2 * N);
	int k = 0;
	for (int i = 0; i < N; convex[k++] = ps[i++]) {
		while (k >= 2 && ccw(convex[k - 2], convex[k - 1], ps[i]) <= 0) --k;
	}
	for (int i = N - 2, t = k + 1; i >= 0; convex[k++] = ps[i--]) {
		while (k >= t && ccw(convex[k - 2], convex[k - 1], ps[i]) <= 0) --k;
	}
	convex.resize(k - 1);
	return convex;
}

bool onSegment(Point a, Point b, Point p) { return ccw(a, b, p) == 0 and dot(p - a, p - b) <= 0; }
// 二つの閉線分 ab, cd が端点・重なりを含め交差するかを返す。
bool intersectSS(Point a, Point b, Point c, Point d) {
	int x = ccw(a, b, c), y = ccw(a, b, d);
	int z = ccw(c, d, a), w = ccw(c, d, b);
	if (x == 0 and onSegment(a, b, c)) return true;
	if (y == 0 and onSegment(a, b, d)) return true;
	if (z == 0 and onSegment(c, d, a)) return true;
	if (w == 0 and onSegment(c, d, b)) return true;
	return x * y < 0 and z * w < 0;
}

// 多角形 P の符号付き面積の 2 倍を返す。反時計回りなら正。
Point::T SignedArea2(const Points& P) {
	Point::T ans = 0;
	for (int i = 0; i < (int)P.size(); i++) ans += cross(P[i], P[(i + 1) % P.size()]);
	return ans;
}
// P が面積を持つ凸多角形かを返す。頂点順は時計・反時計のどちらでもよい。
bool isConvex(const Points& P) {
	int direction = 0;
	for (int i = 0; i < (int)P.size(); i++) {
		int d = ccw(P[i], P[(i + 1) % P.size()], P[(i + 2) % P.size()]);
		if (d and direction and d != direction) return false;
		if (d) direction = d;
	}
	return direction != 0;
}
// 単純多角形 P に対する p の位置を外部0・辺上1・内部2で返す。
int Contains(const Points& P, Point p) {
	bool in = false;
	for (int i = 0; i < (int)P.size(); i++) {
		Point a = P[i] - p, b = P[(i + 1) % P.size()] - p;
		if (onSegment(a, b, Point())) return 1;
		if (a.y > b.y) std::swap(a, b);
		if (a.y <= 0 and b.y > 0 and cross(a, b) > 0) in = !in;
	}
	return in ? 2 : 0;
}

// 単純格子多角形 P の {内部格子点数, 境界格子点数} を Pick の定理で返す。
std::pair<Point::T, Point::T> LatticePoints(const Points& P) {
	Point::T area2 = abs(SignedArea2(P)), boundary = 0;
	for (int i = 0; i < (int)P.size(); i++) {
		Point d = P[i] - P[(i + 1) % P.size()];
		boundary += std::gcd(abs(d.x), abs(d.y));
	}
	return {(area2 - boundary + 2) / 2, boundary};
}

// 依存: geometry/Geometry2D_integer.cpp
// 反時計回り凸多角形の Minkowski sum。各入力に重複終点がないこと。O(N + M)
// 使いどころ: 二つの凸図形から一点ずつ選んだベクトル和全体を、凸多角形として構成する場合。
// 具体例: 一点集合 A={(1, 2)}, B={(3, 4)} の Minkowski 和は {(4, 6)}。
// 使い方:
// Points C = MinkowskiSum(A, B); は {a+b | a in A, b in B} の凸多角形を返す。
// A, B は境界順の凸多角形で、先頭点を末尾に重ねない。時計回りでも内部で反転する。
// NormalizeConvexPolygon(P) は向きと開始点だけを正規化し、非凸入力を凸包には直さない。
// 同方向の連続辺を持つ入力では、必要なら事前に凸包を取って冗長点を除く。
// 凸多角形 P を反時計回りにし、y 最小・次に x 最小の頂点を先頭へ移す。
Points NormalizeConvexPolygon(Points P) {
	if (P.size() <= 1) return P;
	if (SignedArea2(P) < 0) std::ranges::reverse(P);
	// 辺列 merge の始点となる y 最小・次に x 最小の頂点を選ぶ。
	int s = std::ranges::min_element(P, [](auto a, auto b) { return a.y != b.y ? a.y < b.y : a.x < b.x; }) - P.begin();
	std::ranges::rotate(P, P.begin() + s);
	return P;
}

// 二つの凸多角形 A, B の Minkowski 和を境界順の凸多角形として返す。
Points MinkowskiSum(Points A, Points B) {
	if (A.empty() or B.empty()) return {};
	A = NormalizeConvexPolygon(A); B = NormalizeConvexPolygon(B);
	if (A.size() == 1) {
		for (Point& p : B) p += A[0];
		return B;
	}
	if (B.size() == 1) {
		for (Point& p : A) p += B[0];
		return A;
	}
	std::vector<Point> ea(A.size()), eb(B.size());
	for (int i = 0; i < (int)A.size(); i++) ea[i] = A[(i + 1) % A.size()] - A[i];
	for (int i = 0; i < (int)B.size(); i++) eb[i] = B[(i + 1) % B.size()] - B[i];
	Points ans = {A[0] + B[0]};
	int i = 0, j = 0;
	while (i < (int)ea.size() or j < (int)eb.size()) {
		Point d;
		if (j == (int)eb.size() or (i < (int)ea.size() and cross(ea[i], eb[j]) > 0)) d = ea[i++];
		else if (i == (int)ea.size() or cross(ea[i], eb[j]) < 0) d = eb[j++];
		else d = ea[i++] + eb[j++];
		ans.emplace_back(ans.back() + d);
	}
	ans.pop_back();
	return ans;
}
