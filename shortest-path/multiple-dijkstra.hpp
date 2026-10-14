#pragma once

#include "../graph/graph-template.hpp"

template <typename T>
vector<pair<tuple<T, int, int>, tuple<T, int, int> > > dijkstra (WeightedGraph<T>& g, vector<vector<int> > start) {
	using V = tuple<T, int, int, int>;
	int N = (int)g.size();
	vector<int> cnt(N, 0);
	vector<T> d0(N, (T)-1);
	vector<T> d1(N, (T)-1);
	vector<int> home0(N, -1);
	vector<int> home1(N, -1);
	vector<int> anc0(N, -1);
	vector<int> anc1(N, -1);
	priority_queue<V, vector<V>, greater<V> > Q;
	for (int home = 0; home < (int)start.size(); ++home) {
		for (auto v : start[home]) {
			Q.emplace(make_tuple((T)0, home, v, v));
		}
	}
	while(!Q.empty()) {
		auto [d, home, anc, cur] = Q.top();
		Q.pop();
		if (cnt[cur] == 0) {
			d0[cur] = d;
			home0[cur] = home;
			anc0[cur] = anc;
		}
		else if (cnt[cur] == 1 && home0[cur] != home) {
			d1[cur] = d;
			home1[cur] = home;
			anc1[cur] = anc;
		}
		else continue;
		++cnt[cur];
		for (auto dst : g[cur]) {
			Q.emplace(make_tuple(d + dst.cost, home, anc, dst));
		}
	}
	vector<pair<tuple<T, int, int>, tuple<T, int, int> > > ret(N);
	for (int i = 0; i < N; ++i) {
		ret[i] = make_pair(make_tuple(d0[i], home0[i], anc0[i]), make_tuple(d1[i], home1[i], anc1[i]));
	}
	return ret;
}
