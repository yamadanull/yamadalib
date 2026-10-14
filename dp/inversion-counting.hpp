#pragma once

#include "../data-structure/binary-indexed-tree.hpp"

// 転倒数
template <typename T>
long long inversion_counting(const vector<T>& v) {
	vector<T> xs{v};
	sort(begin(xs), end(xs));
	xs.erase(unique(begin(xs), end(xs)), end(xs));
	int s = xs.size();
	BinaryIndexedTree<long long> bit(s + 1);
	long long ans = 0;
	for (auto& x : v) {
		int i = lower_bound(begin(xs), end(xs), x) - begin(xs);
		if (i + 1 != s) ans += bit.sum(i + 1, s - 1);
		bit.add(i, 1);
	}
	return ans;
}

// 隣接 swap によって A を B に変えるのにかかる手数 (不可能 : -1)
template <typename T>
long long swap_distance(const vector<T>& A, const vector<T>& B) {
	if (A.size() != B.size()) return -1;
	int N = A.size();
	vector<pair<T, int>> Ai(N), Bi(N);
	for (int i = 0; i < N; i++) {
		Ai[i] = make_pair(A[i], i);
		Bi[i] = make_pair(B[i], i);
	}
	sort(begin(Ai), end(Ai));
	sort(begin(Bi), end(Bi));
	for (int i = 0; i < N; i++) {
		if (Ai[i].first != Bi[i].first) return -1;
	}
	vector<int> order(N);
	for (int i = 0; i < N; i++) {
		order[Ai[i].second] = Bi[i].second;
	}
	return inversion_counting(order);
}
