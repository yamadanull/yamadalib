#pragma once

#include <cassert>
#include <vector>

struct RollbackUnionFind {
	std::vector<int> data;
	std::vector<std::pair<int, int>> history;
	int inner_snap;

	RollbackUnionFind(int sz) : inner_snap(0) { data.assign(sz, -1); }

	bool unite(int x, int y) {
		x = find(x), y = find(y);
		history.emplace_back(x, data[x]);
		history.emplace_back(y, data[y]);
		if (x == y) return false;
		if (data[x] > data[y]) std::swap(x, y);
		data[x] += data[y];
		data[y] = x;
		return true;
	}

	int find(int k) {
		if (data[k] < 0) return k;
		return find(data[k]);
	}

	int same(int x, int y) { return find(x) == find(y); }

	int size(int k) { return (-data[find(k)]); }

	void undo() {
		data[history.back().first] = history.back().second;
		history.pop_back();
		data[history.back().first] = history.back().second;
		history.pop_back();
	}

	void snapshot() { inner_snap = int(history.size() >> 1); }

	int get_state() { return int(history.size() >> 1); }

	void rollback(int state = -1) {
		if (state == -1) state = inner_snap;
		state <<= 1;
		assert(state <= (int)history.size());
		while (state < (int)history.size()) undo();
	}
};
