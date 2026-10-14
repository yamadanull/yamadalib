#pragma once

#include "graph-template.hpp"

// 無向グラフの場合多重辺NG 多重辺の管理が必要な場合は自分で
template <typename G>
vector<pair<int, int>> CycleDetection(const G& g, bool directed = true) {
	for (int i = 0; i < (int)g.size(); i++) for (auto j : g[i]) if (i == j) {
		vector<pair<int, int>> ans;
		ans.emplace_back(i, i);
		return ans;
	}

	vector<int> belong(g.size(), -1);
	vector<bool> vis(g.size(), 0);
	vector<pair<int, int>> ans;
	bool finished = 0;

	auto dfs = [&](auto rec, int u, int leader, int par) -> int {
		belong[u] = leader;
		vis[u] = 1;
		for (auto& v : g[u]) {
			if (finished) return -1;
			if (!directed && v == par) continue;
			if (belong[v] == belong[u]) {
				ans.emplace_back(u, v);
				return v;
			}
			if (vis[v]) continue;
			int nx = rec(rec, v, leader, u);
			if (nx != -1) {
				ans.emplace_back(u, v);
				if (u == nx) {
					finished = 1;
					return -1;
				}
				return nx;
			}
		}
		belong[u] = -1;
		return -1;
	};

	for (int i = 0; i < (int)g.size(); i++) {
		if (vis[i]) continue;
		dfs(dfs, i, i, -1);

		if (finished) {
			reverse(ans.begin(), ans.end());
			return ans;
		}
	}
	return vector<pair<int, int>>{};
}
