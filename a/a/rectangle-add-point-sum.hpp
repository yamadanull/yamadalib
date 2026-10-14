#pragma once

#include "../../data-structure/binary-indexed-tree.hpp"

#include <algorithm>

template <typename I, typename T, bool SMALL = true> // 準 O(H + W) が許されれば true
struct RectangleAddPointSum {
	std::vector<std::tuple<I, I, I, I>> rect;
	std::vector<T> A;
	std::vector<std::pair<int, int>> point;

	RectangleAddPointSum_Static() {}

	void add_query(I l, I r, I L, I R, T g) {
		rect.emplace_back(l, r, L, R);
		A.emplace_back(g);
	}

	void sum_query(I i, I j) { point.emplace_back(i, j); }

	std::vector<T> calc() {
		int N = rect.size(), Q = point.size();
		if (N == 0) return std::vector<T>(Q, T(0));

		auto [H, W] = [&]()-> std::pair<int, int> { // compress
			std::vector<I> cmph, cmpw;
			cmph.reserve(2 * N + Q);
			cmpw.reserve(2 * N + Q);
			for (auto&& [l, r, L, R] : rect) {
				cmph.emplace_back(l);
				cmph.emplace_back(r);
				cmpw.emplace_back(L);
				cmpw.emplace_back(R);
			}
			for (auto&& [i, j] : point) cmph.emplace_back(i), cmpw.emplace_back(j);
			if (!SMALL) {
				std::ranges::sort(cmph); cmph.erase(std::ranges::unique(cmph).begin(), cmph.end());
				std::ranges::sort(cmpw); cmpw.erase(std::ranges::unique(cmpw).begin(), cmpw.end());
				for (auto&& [l, r, L, R] : rect) {
					l = std::ranges::lower_bound(cmph, l) - cmph.begin();
					r = std::ranges::lower_bound(cmph, r) - cmph.begin();
					L = std::ranges::lower_bound(cmpw, L) - cmpw.begin();
					R = std::ranges::lower_bound(cmpw, R) - cmpw.begin();
				}
				for (auto&& [i, j] : point) {
					i = std::ranges::lower_bound(cmph, i) - cmph.begin();
					j = std::ranges::lower_bound(cmpw, j) - cmpw.begin();
				}
				return {cmph.size(), cmpw.size()};
			}

			I min_i = std::ranges::min(cmph);
			I min_j = std::ranges::min(cmpw);
			for (auto&& [l, r, L, R] : rect) {
				l -= min_i, r -= min_i;
				L -= min_j, R -= min_j;
			}
			for (auto&& [i, j] : point) { i = i - min_i, j = j - min_j; }
			return {std::ranges::max(cmph) - min_i + 1, std::ranges::max(cmpw) - min_j + 1};
		}();

		std::vector<std::vector<std::tuple<int, int, T>>> ADD(W);
		std::vector<std::vector<int>> CALC(W);
		for (int rec_i = 0; rec_i < N; rec_i++) {
			auto [l, r, L, R] = rect[rec_i];
			ADD[L].emplace_back(l, r, +A[rec_i]);
			ADD[R].emplace_back(l, r, -A[rec_i]);
		}
		for (int qi = 0; qi < Q; qi++) CALC[point[qi].second].emplace_back(qi);

		std::vector<T> ans(Q);
		BinaryIndexedTree<T> bit(H);
		for (int j = 0; j < W; j++) {
			for (auto&& [l, r, g] : ADD[j]) bit.add(l, g), bit.add(r, -g);
			for (auto&& qi : CALC[j]) ans[qi] = bit.sum(point[qi].first);
		}
		return ans;
	}
};
