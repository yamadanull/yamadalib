#pragma once

#include <vector>

using i128 = __int128_t;
struct Point {
	i128 x, y;
	Point(i128 X = 0, i128 Y = 0) : x(X), y(Y) {}
	Point& operator+=(Point p) { x += p.x; y += p.y; return *this; }
	Point& operator-=(Point p) { x -= p.x; y -= p.y; return *this; }
	friend Point operator+(Point p, Point q) { return p += q; }
	friend Point operator-(Point p, Point q) { return p -= q; }
	friend bool operator==(Point p, Point q) { return p.x == q.x and p.y == q.y; }
	friend bool operator<(Point p, Point q) { return p.x != q.x ? p.x < q.x : p.y < q.y; }
};
using Polygon = std::vector<Point>;

Point operator*(Point p, i128 c) { return {p.x * c, p.y * c}; }
Point operator/(Point p, i128 c) { return {p.x / c, p.y / c}; }

i128 dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
i128 cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
// 有向点列 a->b->c の向きを左折1・共線0・右折-1で返す。
int ccw(Point a, Point b, Point c) {
	i128 x = cross(b - a, c - a);
	return (x > 0) - (x < 0);
}

