#pragma once

// 長さN、要素が[L,R)の数列を列挙
vector<vector<int> > IncreasingSequence(int N, int L, int R, bool strict = true) {
	vector<vector<int> > ans;
	vector<int> cur;
	auto dfs = [&](auto&& self, int l, int len) {
		if (len == N) {
			ans.emplace_back(cur);
			return;
		}
		for (int i = l; i < R; i++) {
			cur.emplace_back(i);
			self(self, i + (int)strict, len + 1);
			cur.pop_back();
		}
	};
	dfs(dfs, L, 0);
	return ans;
}
