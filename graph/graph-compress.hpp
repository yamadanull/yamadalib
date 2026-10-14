#pragma once

#include "graph-template.hpp"
#include "../misc/compress.hpp"
#include "../data-structure/union-find-fast.hpp"

template <typename T, typename Graph>
struct SubGraph {
	compress<T> comp;
	Graph g;
	SubGraph(Graph& G, vector<T>& v) : comp(v), g(v.size()) {
		for (int i = 0; i < (int)comp.size(); ++i) {
			int src = comp[i];
			for (auto E : G[src]) {
				int dst = comp((int)E);
				auto e = E;
				if (dst >= 0) g[i].emplace_back(e = dst);
			}
		}
	}
};

template <typename Graph>
vector<SubGraph<int, Graph>> ConnectedComponents(Graph& G) {
	int N = (int)G.size();
	UnionFindFast uf(N);
	for (int i = 0; i < N; ++i) {
		for (auto e : G[i]) uf.unite(i, e);
	}

	auto groups = uf.groups();
	vector<SubGraph<int, Graph>> ans;
	for (auto group : groups) {
		ans.emplace_back(G, group);
	}
	return ans;
}
