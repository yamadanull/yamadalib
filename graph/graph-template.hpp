#pragma once

#include <vector>
#include <iostream>

template <typename T>
struct edge {
	int src, to;
	T cost;

	edge(int _to, T _cost) : src(-1), to(_to), cost(_cost) {}
	edge(int _src, int _to, T _cost) : src(_src), to(_to), cost(_cost) {}

	edge &operator=(const int &x) {
		to = x;
		return *this;
	}

	operator int() const { return to; }
};
template <typename T>
using Edges = std::vector<edge<T>>;
template <typename T>
using WeightedGraph = std::vector<Edges<T>>;
using UnweightedGraph = std::vector<std::vector<int>>;

// Input of (Unweighted) Graph
UnweightedGraph graph(int N, int M = -1, bool is_directed = false, bool is_1origin = true) {
	UnweightedGraph g(N);
	if (M == -1) M = N - 1;
	for (int _ = 0; _ < M; _++) {
		int x, y;
		std::cin >> x >> y;
		if (is_1origin) x--, y--;
		g[x].push_back(y);
		if (!is_directed) g[y].push_back(x);
	}
	return g;
}

// Input of Weighted Graph
template <typename T>
WeightedGraph<T> wgraph(int N, int M = -1, bool is_directed = false, bool is_1origin = true) {
	WeightedGraph<T> g(N);
	if (M == -1) M = N - 1;
	for (int _ = 0; _ < M; _++) {
		int x, y; std::cin >> x >> y;
		T c; std::cin >> c;
		if (is_1origin) x--, y--;
		g[x].emplace_back(x, y, c);
		if (!is_directed) g[y].emplace_back(y, x, c);
	}
	return g;
}
