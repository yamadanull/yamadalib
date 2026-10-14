#pragma once

template <typename flow_t>
struct Dinic {
	const flow_t INF;

	struct edge {
		int to;
		flow_t cap;
		int rev;
		bool isrev;
		int idx;
	};

	vector<vector<edge>> g;
	vector<int> min_cost, iter;

	Dinic(int N) : INF(numeric_limits<flow_t>::max()), g(N) {}

	void add_edge(int from, int to, flow_t cap, int idx = -1) {
		g[from].emplace_back((edge) {to, cap, (int) g[to].size(), false, idx});
		g[to].emplace_back((edge) {from, 0, (int) g[from].size() - 1, true, idx});
	}

	bool bfs(int s, int t) {
		min_cost.assign(g.size(), -1);
		queue< int > que;
		min_cost[s] = 0;
		que.push(s);
		while (!que.empty() && min_cost[t] == -1) {
			int p = que.front();
			que.pop();
			for (auto &e : g[p]) {
				if (e.cap > 0 && min_cost[e.to] == -1) {
					min_cost[e.to] = min_cost[p] + 1;
					que.push(e.to);
				}
			}
		}
		return min_cost[t] != -1;
	}

	flow_t dfs(int idx, const int t, flow_t flow) {
		if (idx == t) return flow;
		for (int &i = iter[idx]; i < g[idx].size(); i++) {
			edge &e = g[idx][i];
			if (e.cap > 0 && min_cost[idx] < min_cost[e.to]) {
				flow_t d = dfs(e.to, t, min(flow, e.cap));
				if (d > 0) {
					e.cap -= d;
					g[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	flow_t max_flow(int s, int t) {
		flow_t flow = 0;
		while (bfs(s, t)) {
			iter.assign(g.size(), 0);
			flow_t f = 0;
			while ((f = dfs(s, t, INF)) > 0) flow += f;
		}
		return flow;
	}

	void output() {
		for (int i = 0; i < g.size(); i++) {
			for (auto &e : g[i]) {
				if (e.isrev) continue;
				auto &rev_e = g[e.to][e.rev];
				cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
			}
		}
	}
};
