#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

struct Mo {
	int DIV;
	std::vector<int> L, R, order;

	Mo(int N, int Q) : order(Q) {
		DIV = std::max<int>(1, 1.0 * N / std::max<double>(1.0, std::sqrt(Q * 2.0 / 3.0)));
		std::ranges::iota(order, 0);
	}

	void insert(int l, int r) { /* [l, r) */
		L.emplace_back(l);
		R.emplace_back(r);
	}

	template <typename AL, typename AR, typename DL, typename DR, typename REM>
	void run(const AL &add_l, const AR &add_r, const DL &del_l,
	         const DR &del_r, const REM &rem) {
		assert(L.size() == order.size());
		std::ranges::sort(order, [&](int a, int b) {
			int ablock = L[a] / DIV, bblock = L[b] / DIV;
			if (ablock != bblock) return ablock < bblock;
			if (ablock & 1) return R[a] < R[b];
			return R[a] > R[b];
		});
		int nl = 0, nr = 0;
		for (auto idx : order) {
			while (nl > L[idx]) add_l(--nl);
			while (nr < R[idx]) add_r(nr++);
			while (nl < L[idx]) del_l(nl++);
			while (nr > R[idx]) del_r(--nr);
			rem(idx);
		}
	}
};
