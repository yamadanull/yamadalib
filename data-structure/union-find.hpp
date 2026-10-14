#pragma once

#include <vector>
#include <ranges>

struct UnionFind {
	std::vector<int> data, nxt;
	UnionFind(int N) : data(N, -1), nxt(std::views::iota(0, N) | std::ranges::to<std::vector>()) {}

	int find(int k) { return data[k] < 0 ? k : data[k] = find(data[k]); }

	int unite(int x, int y) {
		if ((x = find(x)) == (y = find(y))) return false;
		if (data[x] > data[y]) std::swap(x, y);
		data[x] += data[y];
		data[y] = x;
		std::swap(nxt[x], nxt[y]);
		return true;
	}

	// f(x, y) : x に y をマージ
	template <typename F>
	int unite(int x, int y, const F &f) {
		if ((x = find(x)) == (y = find(y))) return false;
		if (data[x] > data[y]) std::swap(x, y);
		data[x] += data[y];
		data[y] = x;
		f(x, y);
		std::swap(nxt[x], nxt[y]);
		return true;
	}

	// g(x, y) : y に x をマージ
	template <typename F, typename G>
	int unite(int x, int y, const F &f, const G &g) {
		if ((x = find(x)) == (y = find(y))) return false;
		if (data[x] > data[y]) {
			g(x, y);
			std::swap(x, y);
		}
		else f(x, y);
		data[x] += data[y];
		data[y] = x;
		return true;
	}

	int size(int k) { return -data[find(k)]; }

	int same(int x, int y) { return find(x) == find(y); }

	std::vector<int> enumerate(int i) {
		std::vector<int> res{i};
		for (int j = nxt[i]; j != i; j = nxt[j]) res.push_back(j);
		return res;
	}

	std::vector<std::vector<int>> groups() {
		std::vector<std::vector<int>> ret;
		std::vector<bool> vis(data.size());
		for (int u = 0; u < (int)data.size(); ++u) if (!vis[u]) {
			ret.emplace_back(enumerate(u));
			for (auto& v : ret.back()) vis[v] = 1;
		}
		return ret;
	}
};
