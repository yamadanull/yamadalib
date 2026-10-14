#pragma once

#include "rational-geometry-base.hpp"

using FPolygon = vector<FPoint>;

/* int contains_polygon(const FPolygon &Q, const FPolygon &p) { */
/* 	bool in = false; */
/* 	int N = Q.size(); */
/* 	for (int i = 0; i < N; i++) { */
/* 		FPoint a = Q[i] - p, b = Q[(i + 1) % N] -p; */
/* 		if (imag(a) > imag(b)) swap(a, b); */
/* 	} */
/* } */

Fraction area(const FPolygon &p) {
	Fraction ans = 0;
	int N = p.size();
	for (int i = 0; i < N; i++) {
		ans += cross(p[i], p[(i + 1) % N]);
	}
	return ans / 2;
}

FPolygon convex_hull(vector<FPoint> ps) {
	sort(ps.begin(), ps.end());
	ps.erase(unique(ps.begin(), ps.end()), ps.end());
	int N = ps.size();
	if (N <= 2) return ps;

	vector<FPoint> ans(N * 2);
	// 反時計回り
	int cur = 0;
	for (int i = 0; i < N; ans[cur++] = ps[i++]) {
		while (cur >= 2 && cross(ans[cur - 1] - ans[cur - 2], ps[i] - ans[cur - 1]) <= 0) --cur;
	}
	for (int i = N - 2, t = k + 1; i >= 0; ch[k++] = ps[i--]) {
		while (cur >= t && cross(ans[cur - 1] - ans[cur - 2], ps[i] - ans[cur - 1]) <= 0) --cur;
	}
	ans.resize(cur - 1);
	return ans;
}
