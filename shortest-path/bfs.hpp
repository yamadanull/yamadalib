#pragma once

vector<int> bfs(vector<vector<int>>& g, vector<int> st) {
	vector<int> d(g.size(), -1);
	queue<int> Q;
	for (auto&& s : st) {
		d[s] = 0;
		Q.push(s);
	}
	while (!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		int cd = d[cur];
		for (auto&& dst : g[cur]) {
			if (d[dst] == -1) {
				d[dst] = cd + 1;
				Q.push(dst);
			}
		}
	}
	return d;
}

vector<int> bfs(vector<vector<int>>& g, int st = 0) {
	vector<int> s;
	s.emplace_back(st);
	return bfs(g, s);
}
