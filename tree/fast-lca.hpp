#pragma once

template <typename G>
struct FastLCA {
	using P = pair<int, int>;
	struct RMQ {
		P INF = {1 << 30, -1};
		int N;
		vector<vector<P>> table;
		RMQ() {}
		RMQ(const vector<P> &v) : N(v.size()) {
			int b = 1;
			while ((1 << b) <= N) ++b;
			table.push_back(v);
			for (int i = 1; i < b; i++) {
				table.emplace_back(vector<P>(N, INF));
				for (int j = 0; j + (1 << i) <= N; j++) {
					table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
				}
			}
		}
		// [l, r)
		P prod(int l, int r) {
			assert(0 <= l and l <= r and r <= N);
			if (l == r) return INF;
			int b = 31 - __builtin_clz(r - l);
			return min(table[b][l], table[b][r - (1 << b)]);
		}
	};

	FastLCA(G &g, int root = 0) {
		int N = g.size();
		u_to_time.resize(N);
		depth.resize(N);
		vector<P> init(N);

		int time = 0;
		auto dfs=[&](auto&& dfs, int u, int p, int dep)->void{
			depth[u] = dep;
			u_to_time[u] = time++;
			init[u_to_time[u]] = {dep, p};
			for (auto& v : g[u]) if ((int)v != p) {
				dfs(dfs, v, u, dep + 1);
			}
		}; dfs(dfs, root, -1, 0);

		seg = RMQ(init);
	}

	int get(int u, int v) {
		int l = u_to_time[u];
		int r = u_to_time[v];
		if(l > r) swap(l, r), swap(u, v);
		int ans = seg.prod(l + 1, r + 1).second;
		if (ans < 0) return u;
		return ans;
	}

	inline int operator()(int u, int v) { return get(u, v); }

	int dist(int u, int v){
		int l = get(u, v);
		return depth[v] + depth[u] - depth[l] * 2;
	}

	private:
	vector<int> u_to_time, depth;
	RMQ seg;
};
