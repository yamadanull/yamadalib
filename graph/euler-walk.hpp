#pragma once

template <bool DIRECTED = false>
pair<vector<int>, vector<int>> EulerWalk(vector<pair<int, int>> &es, int S = -1) {
	int M = es.size(); if (M == 0) return {{max(0, S)}, {}};
	int N = S + 1; for (auto&& [u, v] : es) N = max(N, max(u, v) + 1);

	vector<int> deg(N);
	for (auto&& [u, v] : es) {
		if constexpr (DIRECTED) deg[u]++, deg[v]--;
		else deg[u]++, deg[v]++;
	}

	if constexpr (DIRECTED) { // 条件1:次数
		for (int i = 0; i < N; i++) if (abs(deg[i]) >= 2) return {{}, {}};
		int cnt = 0;
		for (int i = 0; i < N; i++) if (abs(deg[i]) == 1) ++cnt;
		if (cnt >= 3) return {{}, {}};
	}
	else {
		int cnt = 0;
		for (int i = 0; i < N; i++) if (deg[i] & 1) ++cnt;
		if (cnt >= 3) return {{}, {}};
	}

	if (S < 0) {
		if constexpr (DIRECTED) {
			S = max_element(deg.begin(), deg.end()) - deg.begin();
			if (deg[S] == 0) S = (M == 0 ? 0 : es[0].first);
		}
		else {
			S = [&]() -> int {
				for (int i = 0; i < N; i++) if (deg[i] & 1) return i;
				return M == 0 ? 0 : es[0].first;
			}();
		}
	}

	vector<vector<int>> ei_lists(N);
	for (int i = 0; i < M; i++) {
		auto [u, v] = es[i];
		ei_lists[u].emplace_back(i);
		if constexpr (!DIRECTED) {
			if (u != v) ei_lists[v].emplace_back(i);
		}
	}

	vector<int> ans, bns, progress(N);
	vector<bool> used(M);
	vector<int> st_vi{S}, st_ei{-1};
	while (!st_vi.empty()) {
		int u = st_vi.back();
		if (progress[u] < ei_lists[u].size()) {
			int ei = ei_lists[u][progress[u]++];
			if (used[ei]) continue;
			used[ei] = true;

			auto [v0, v1] = es[ei];
			int v = (DIRECTED ? v1 : (v0 == u ? v1 : v0));
			st_vi.emplace_back(v);
			st_ei.emplace_back(ei);
		}
		else {
			ans.emplace_back(st_vi.back()); st_vi.pop_back();
			bns.emplace_back(st_ei.back()); st_ei.pop_back();
		}
	}

	if (ans.size() != M + 1) return {{}, {}}; // 条件2:連結
	reverse(ans.begin(), ans.end());
	bns.pop_back(); reverse(bns.begin(), bns.end());
	return {ans, bns};
}

