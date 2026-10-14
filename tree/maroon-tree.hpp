#pragma once
#include "../data-structure/union-find-fast.hpp"

template <typename T>
std::pair<T, std::vector<int> > maroonTree (int N, std::vector<T> &C0, std::vector<T> &C1, std::vector<int> &par) {
	using S = tuple<T, T, int>;
	auto S_comp = [&](const S& U, const S& V)->bool{
		auto [c0, c1, u] = U;
		auto [d0, d1, v] = V;
		if (d0 == 0 && d1 == 0) return false;
		if (c0 == 0 && c1 == 0) return true;
		return c0 * d1 < c1 * d0;
	};

	std::priority_queue<S, std::vector<S>, decltype(S_comp)> pq(S_comp);
	for (int i = 0; i < N; ++i) pq.emplace(C0[i], C1[i], i);

	std::vector<std::list<int> > seq(N);
	for (int i = 0; i < N; ++i) seq[i].emplace_back(i);
	auto f = [&](int x, int y) {
		seq[x].splice(seq[x].end(), seq[y]);
	};
	auto g = [&](int x, int y) {
		seq[x].splice(seq[x].end(), seq[y]);
		swap(seq[x], seq[y]);
	};

	UnionFindFast uf(N);
	T ans = 0;

	while(!pq.empty()){
		auto [c0, c1, s] = pq.top();
		pq.pop();
		s = uf.find(s);
		if (c0 != C0[s]) continue;
		if (c1 != C1[s]) continue;

		int p = par[s];
		if (p == -1) continue;
		p = uf.find(p);
		T d0 = C0[p];
		T d1 = C1[p];
		ans += c0 * d1;

		uf.unite(p, s, f, g);
		int root = uf.find(s);
		par[root] = par[p];
		C0[root] = c0 + d0;
		C1[root] = c1 + d1;
		pq.emplace(make_tuple(C0[root], C1[root], root));
	}

	int root = uf.find(0);
	std::vector<int> bns;
	for (auto &p : seq[root]) bns.emplace_back(p);
	return {ans, bns};
}
