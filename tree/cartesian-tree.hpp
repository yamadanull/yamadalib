#pragma once

#include <vector>
#include <cassert>
/*
   辞書順で高さを unique して、木にしている。
   極大長方形アルゴリズムで線形時間構築。
 */
template <typename T, bool ROOT_IS_MIN = 1>
struct CartesianTree {
	int N;
	std::vector<T>& A;
	std::vector<std::pair<int, int>> range;
	std::vector<int> lch, rch, par;
	int root;

	CartesianTree(std::vector<T>& A) : N(A.size()), A(A) {
		range.assign(N, {-1, -1});
		lch.assign(N, -1);
		rch.assign(N, -1);
		par.assign(N, -1);
		if (N == 1) {
			range[0] = {0, 1};
			root = 0;
			return;
		}
		auto is_smaller = [&](int i, int j) -> bool {
			if (ROOT_IS_MIN) return (A[i] < A[j]) || (A[i] == A[j] && i < j);
			return (A[i] > A[j]) || (A[i] == A[j] && i < j);
		};
		std::vector<int> st;
		for (int i = 0; i < N; i++) {
			while (!st.empty() && is_smaller(i, st.back())) {
				lch[i] = st.back();
				st.pop_back();
			}
			range[i].first = (st.empty() ? 0 : st.back() + 1);
			st.emplace_back(i);
		}
		st.clear();
		for (int i = N - 1; i >= 0; i--) {
			while (!st.empty() && is_smaller(i, st.back())) {
				rch[i] = st.back();
				st.pop_back();
			}
			range[i].second = (st.empty() ? N : st.back());
			st.emplace_back(i);
		}
		for (int i = 0; i < N; i++) if (lch[i] != -1) par[lch[i]] = i;
		for (int i = 0; i < N; i++) if (rch[i] != -1) par[rch[i]] = i;
		for (int i = 0; i < N; i++) if (par[i] == -1) root = i;
	}

	// (l, r, h)
	std::tuple<int, int, T> maximum_rectangle(int i) {
		auto [l, r] = range[i];
		return {l, r, A[i]};
	}

	// (l, r, h)
	T max_rectangle_area() {
		assert(ROOT_IS_MIN);
		T ans = 0;
		for (int i = 0; i < N; i++) {
			auto [l, r, h] = maximum_rectangle(i);
			ans = max(ans, (r - l) * h);
		}
		return ans;
	}

	long long count_subrectangle(bool baseline) {
		assert(ROOT_IS_MIN);
		long long ans = 0;
		for (int i = 0; i < N; i++) {
			auto [l, r, h] = maximum_rectangle(i);
			long long x = (baseline ? h : h * (h + 1) / 2);
			ans += x * (i - l + 1) * (r - i);
		}
		return ans;
	}
};
