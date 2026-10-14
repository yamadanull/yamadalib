#pragma once

// Gは連結グラフである必要がある
// 有向なもりを返す
template <typename Graph>
Graph UndirectedNamori(Graph G) {
	int N = G.size();
	int M = 0;
	Graph g(N);

	queue<int> q;
	vector<int> cnt(N);
	for (int i = 0; i < N; i++) {
		cnt[i] = G[i].size();
		if (G[i].size() == 1) q.push(i);
	}

	vector<bool> decom(N);
	while(!q.empty()) {
		int pos = q.front(); q.pop();
		for (auto& e : G[pos]) if (!decom[e]) {
			g[pos].emplace_back(e); ++M;
			if (--cnt[e] == 1) q.push(e);
		}
		decom[pos] = true;
	}

	auto dfs = [&](auto&& self, int pos, int par)->void{
		if (M == N) return;
		for (auto& e: G[pos]) if (e != par && !decom[e]) {
			g[pos].emplace_back(e); ++M;
			if (M == N) return;
			self(self, e, pos);
			if (M == N) return;
		}
	};

	for (int i = 0; i < N; i++) if (!decom[i]) {
		dfs(dfs, i, -1);
		break;
	}
	return g;
}
