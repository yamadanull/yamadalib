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

void print_edge(ostream &os, UnweightedGraph &g, bool origin_1 = true) {
	int N = g.size();
	for (int i = 0; i < N; ++i) {
		for (int j : g[i]) {
			if (i < j) 
				os << i + (int)origin_1 << " " << j + (int)origin_1 << "\n";
		}
	}
}

template <typename T>
void print_edge(ostream &os, WeightedGraph<T> &g, bool origin_1 = true) {
	int N = g.size();
	for (int i = 0; i < N; ++i) {
		for (edge e : g[i]) {
			if (i < e.to) 
				os << i + (int)origin_1 << " " << e.to + (int)origin_1 << " " << e.cost << "\n";
		}
	}
}

template <typename G>
void print(ostream &os, G &g, bool directed = false) {
	int N = g.size();
	int M = 0;
	for (int i = 0; i < N; ++i) {
		M += g[i].size();
	}
	if (!directed) M /= 2;
	os << N << " " << M << "\n";
	print_edge(os, g);
}
