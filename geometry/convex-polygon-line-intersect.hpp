#include "../dp/golden-section-search.hpp"
#include "line.hpp"

// 凸包を直線で切った時の交点を返す
// 未完成
pair<Point, Point> convex_polygon_line_intersect(const Polygon &U, const Line &l) {
	int N = U.size();
	assert(N >= 2);
	auto p0 = l.a;
	auto p1 = l.b;
	auto h = [&](int i) { return cross(U[i % N] - p0, p1 - p0); };
	auto g = [&](int i) { return min(h(i), Real(h(N - 1) - h(0)) / (N - 1) * (i - 1) + h(1)); };
	auto [i0, c0] = golden_section_search<true> (g, 0, N - 1);
	if (c0 > 0) return make_pair(Point(0, 0), Point(0, 0));
	auto [i1, c1] = golden_section_search<false> (h, x0 + 1, x0 + N - 1);
	return make_pair(Point(0, 0), Point(0, 0));
}
