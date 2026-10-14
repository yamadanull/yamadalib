#pragma once

#include <functional>
#include <utility>
using namespace std;

#include "stern-brocot-tree.hpp"

// 分子と分母が INF 以下である非負の既約分数のうち次のものを返す
// first : f(x) が false である最大の既約分数 x
// second : f(x) が true である最小の既約分数 x
// ただし
// - f(0) = true の場合は (0/1, 0/1) を返す
// - true になる分数が存在しない場合は (?, 1/0) を返す
// - INF = 0 の場合は (0/1, 1/0) を返す
template <typename I>
pair<pair<I, I>, pair<I, I>> binary_search_on_stern_brocot_tree(
		function<bool(pair<I, I>)> f, const I &INF) {
	// INF >= 0
	assert(0 <= INF);
	SternBrocotTreeNode<I> m;
	if (INF == 0) return {m.lower_bound(), m.upper_bound()};
	if (f(make_pair(0, 1))) return {m.lower_bound(), m.lower_bound()};

	// INF 条件を超える or f(m) = return_value である
	auto ikisugi = [&](bool return_value)->bool {
		return max(m.x, m.y) > INF or f(m.get()) == return_value;
	};

	for (bool going_left = ikisugi(true); true; going_left ^= 1) {
		if (going_left) {
			// f(M) = true -> (L, M] に答えがある
			// (f(L * b + M) = false) or (INF 超え) になる b の最小は？
			I stride = 1;
			for (; true; stride *= 2) {
				m.go_left(stride);
				if (ikisugi(false)) {
					m.go_parent(stride);
					break;
				}
			}
			for (stride /= 2; stride != 0; stride /= 2) {
				m.go_left(stride);
				if (ikisugi(false)) m.go_parent(stride);
			}
			m.go_left(1);
		}
		else {
			// f(M) = false -> (M, R] に答えがある
			// (f(M + R * b) = true) or (INF 超え) になる b の最小は？
			I stride = 1;
			for (; true; stride *= 2) {
				m.go_right(stride);
				if (ikisugi(true)) {
					m.go_parent(stride);
					break;
				}
			}
			for (stride /= 2; stride != 0; stride /= 2) {
				m.go_right(stride);
				if (ikisugi(true)) m.go_parent(stride);
			}
			m.go_right(1);
		}
		if (max(m.get().first, m.get().second) > INF)
			return {m.lower_bound(), m.upper_bound()};
	}
}
