#pragma once

#include "../misc/all.hpp"
#include "../graph/graph-template.hpp"
#include "../data-structure/union-find.hpp"

UnweightedGraph randtree(int N) {
	UnionFind d(N);
	UnweightedGraph g(N);
	while (d.size(0) < N) {
		int u = randint(0, N);
		int v = randint(0, N);
		if (d.unite(u, v)) {
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
	}
	return g;
}

template <typename T>
WeightedGraph<T> randwtree(int N, T min_weight = 1, T max_weight = 3) {
	UnionFind d(N);
	WeightedGraph<T> g(N);
	while (d.size(0) < N) {
		int u = randint(0, N);
		int v = randint(0, N);
		T c = randint(min_weight, max_weight + 1);
		if(d.unite(u, v)) {
			g[u].emplace_back(edge(u, v, c));
			g[v].emplace_back(edge(v, u, c));
		}
	}
	return g;
}

UnweightedGraph randgraph(int N, int M) {
	assert(N - 1 <= M);
	assert(N * (N - 1) / 2 >= M);
	auto g = randtree(N);
	map<pair<int, int>, bool> mp;
	for (int i = 0; i < N; i++) for (auto& e : g[i]) mp[make_pair(i,e)] = true;

	int m = N - 1;
	while (m < M) {
		int u = randint(0, N);
		int v = randint(0, N);
		if (u != v && !mp.count(make_pair(u, v))){
			++m;
			mp[make_pair(u, v)] = true;
			mp[make_pair(v, u)] = true;
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
	}
	return g;
}

void print_edge(UnweightedGraph &g, bool origin_1 = true) {
	int N = g.size();
	for (int i = 0; i < N; ++i)
		for (int j : g[i])
			if (i < j) 
				cout << i + (int)origin_1 << " " << j + (int)origin_1 << "\n";
}

template <typename T>
void print_edge(WeightedGraph<T> &g, bool origin_1 = true) {
	int N = g.size();
	for (int i = 0; i < N; ++i)
		for (edge e : g[i])
			if (i < e.to) 
				cout << i + (int)origin_1 << " " << e.to + (int)origin_1 << " " << e.cost << "\n";
}

template <typename G>
void print_graph(G &g, bool directed = false) {
	int N = g.size();
	int M = 0;
	for (int i = 0; i < N; ++i) {
		M += g[i].size();
	}
	if (!directed) M /= 2;
	cout << N << " " << M << "\n";
	print_edge(g);
}
