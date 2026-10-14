#pragma once

// g is undirected
template <typename Graph, typename F>
void EnumerateTriangles(Graph &g, F f) {
	int N = g.size();
	std::vector<std::vector<int>> h(N);
	for (int u = 0; u < N; u++) for (auto& v : g[u]) {
		if (g[u].size() > g[v].size()) continue;
		if (g[u].size() == g[v].size() && u > (int)v) continue;
		h[u].emplace_back(v);
	}

	std::vector<bool> seeing(N, 0);
	for (int u = 0; u < N; u++) {
		for (auto& v : h[u]) seeing[v] = 1;
		for (auto& v : h[u]) for (auto& w : h[v]) if (seeing[w]) f(u, v, w);
		for (auto& v : h[u]) seeing[v] = 0;
	}
}
