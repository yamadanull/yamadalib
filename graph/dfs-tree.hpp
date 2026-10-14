#pragma once

template <typename G>
G DfsTree(G& g, int root = 0) {
	G ret(g.size());
	vector<bool> vis(g.size());

	function<void(int)> dfs = [&](int i) {
		vis[i] = true;
		for (auto& e : g[i]) if (!vis[e]) {
			ret[i].emplace_back(e);
			ret[e].emplace_back(e);
			ret[e].back() = i;
			dfs(e);
		}
	}; dfs(root);
	return ret;
}
