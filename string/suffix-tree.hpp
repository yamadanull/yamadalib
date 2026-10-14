#pragma once

#include "../tree/cartesian-tree.hpp"

// https://twitter.com/maspy_stars/status/1565901414236205057
// 各ノードは、suffix array での長方形領域と見なして、グラフおよび、領域データを作る。
// [tree, LRDU]
// treeのroot (LRDU: 0,N,0,0) は頂点0 頂点番号は部分文字列の辞書順
// Suffix Array の添字 [L, R) 内の LCP が U
// Multi Suffix Array にも対応
pair<vector<vector<int>>, vector<tuple<int, int, int, int>>> SuffixTree(vector<int> &lcp, vector<int> &len) {
	vector<tuple<int, int, int, int>> ans;
	vector<pair<int, int>> edges;
	int N = lcp.size();
	if (N == 1) { // 空文字列
		vector<vector<int>> g(1);
		ans.emplace_back(0, 1, 0, 0);
		return {g, ans};
	}

	ans.emplace_back(0, N, 0, 0);
	CartesianTree CT(lcp);
	// Suffix Array の添字 [L, R) 内の LCP が U
	auto dfs = [&](auto& dfs, int u, int sa_i, int D) ->void{
		auto [L, R] = CT.range[sa_i];
		R = min(R + 1, N);
		int U = lcp[sa_i];
		if (D < U) {
			edges.emplace_back(u, ans.size());
			u = ans.size();
			ans.emplace_back(L, R, D, U);
		}

		if (CT.lch[sa_i] == -1) {
			if (U < len[sa_i]) {
				edges.emplace_back(u, ans.size());
				ans.emplace_back(sa_i, sa_i + 1, U, len[sa_i]);
			}
		}
		else dfs(dfs, u, CT.lch[sa_i], U);

		if (CT.rch[sa_i] == -1) {
			if (sa_i < N - 1 && U < len[sa_i + 1]) {
				edges.emplace_back(u, ans.size());
				ans.emplace_back(sa_i + 1, sa_i + 2, U, len[sa_i + 1]);
			}
		}
		else dfs(dfs, u, CT.rch[sa_i], U);
	}; dfs(dfs, 0, CT.root, 0);

	vector<vector<int>> g(ans.size());
	for (auto&& [u, v]: edges) g[u].emplace_back(v);
	return {g, ans};
}
