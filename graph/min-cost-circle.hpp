#pragma once

#include "graph-template.hpp"
#include "../shortest-path/dijkstra-with-restore.hpp"

// Undirected Graph
template <typename T>
pair<T, vector<int>> MinCostCircle(WeightedGraph<T> g, int st) {
	auto d = dijkstra_restore(g, st);
	int N = g.size();
	WeightedGraph<T> t(N);
	for (int v = 0; v < N; v++) {
		int u = d[v].second;
		if (u >= 0) t[u].emplace_back(v, d[v].first - d[u].first);
	}

	vector<int> label(N, -1);
	label[st] = st;
	for (auto& e : t[st]) {
		function<void(int)> dfs = [&](int u) {
			assert(u != st);
			label[u] = e;
			for (auto& v : t[u]) dfs(v);
		}; dfs(e);
	}

	tuple<T, int, int> ans = make_tuple(-1, -1, -1);
	for (int u = 0; u < N; u++) for (auto& v : g[u]) {
		if (label[u] < 0 || label[v] < 0) continue;
		if (label[u] == label[v]) continue;
		if (v == d[u].second || u == d[v].second) continue;
		tuple<T, int, int> bns = make_tuple(d[u].first + d[v].first + v.cost, u, v);
		if (get<0>(ans) == -1) ans = bns;
		else ans = min(ans, bns);
	}

	if (get<0>(ans) == -1) return make_pair(-1, vector<int>());
	vector<int> cns, dns;
	for (int v = get<1>(ans); v != st; v = d[v].second) cns.emplace_back(v);
	for (int v = get<2>(ans); v != st; v = d[v].second) dns.emplace_back(v);
	reverse(cns.begin(), cns.end());
	vector<int> bns{st};
	for (auto& v : cns) bns.emplace_back(v);
	for (auto& v : dns) bns.emplace_back(v);
	return make_pair(get<0>(ans), bns);
}

pair<int, vector<int>> MinCostCircle(UnweightedGraph g, int st) {
	int N = g.size();
	WeightedGraph<int> G(N);
	for (int u = 0; u < N; u++) for (auto& v : g[u]) G[u].emplace_back(v, 1);
	return MinCostCircle<int> (G, st);
}
