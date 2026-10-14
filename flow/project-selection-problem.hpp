#pragma once

// 1, 2, 3-variable submodular optimization 
template<class COST>
struct ProjectSelection {
	// constructors
	ProjectSelection() : N(2), S(0), T(0), OFFSET(0) {}
	ProjectSelection(int n, COST inf = numeric_limits<COST>::max() / 2)
		: N(n), S(n), T(n + 1), OFFSET(0), INF(inf), list(n + 2) {}

	// initializer
	void init(int n, COST inf = numeric_limits<COST>::max() / 2) {
		N = n, S = n, T = n + 1;
		OFFSET = 0, INF = inf;
		list.clear();
		list.resize(N + 2);
		pos.clear();
	}

	// add constant cost
	void add_cost(COST cost) { OFFSET += cost; }

	// add 1-variable submodular function
	void add_single_cost(int xi, COST false_cost, COST true_cost) {
		assert(0 <= xi && xi < N);
		if (false_cost >= true_cost) {
			OFFSET += true_cost;
			add_edge(S, xi, false_cost - true_cost);
		} else {
			OFFSET += false_cost;
			add_edge(xi, T, true_cost - false_cost);
		}
	}

	// add "project selection" constraint
	// v0 = F, v1 = T: strictly prohibited
	void add_constraint01(int v0, int v1) {
		assert(0 <= v0 && v0 < N);
		assert(0 <= v1 && v1 < N);
		add_edge(v1, v0, INF);
	}

	// add "project selection" penalty
	// v0 = F, v1 = T: cost C
	void add_penalty01(int v0, int v1, COST C) {
		assert(0 <= v0 && v0 < N);
		assert(0 <= v1 && v1 < N);
		assert(C >= 0);
		add_edge(v1, v0, C);
	}

	// add both True profit
	// xi = T, xj = T: profit P (cost -P)
	void add_profit11(int xi, int xj, COST P) {
		assert(0 <= xi && xi < N);
		assert(0 <= xj && xj < N);
		assert(P >= 0);
		OFFSET -= P;
		add_edge(S, xi, P);
		add_edge(xi, xj, P);
	}

	// add both False profit
	// xi = F, xj = F: profit P (cost -P)
	void add_profit00(int xi, int xj, COST P) {
		assert(0 <= xi && xi < N);
		assert(0 <= xj && xj < N);
		assert(P >= 0);
		OFFSET -= P;
		add_edge(xj, T, P);
		add_edge(xi, xj, P);
	}

	// add general 2-variable submodular function
	// (xi, xj) = (F, F): A, (F, T): B
	// (xi, xj) = (T, F): C, (T, T): D
	void add_submodular_function(int xi, int xj, COST A, COST B, COST C, COST D) {
		assert(0 <= xi && xi < N);
		assert(0 <= xj && xj < N);
		assert(B + C >= A + D);  // assure submodular function
		OFFSET += A;
		add_single_cost(xi, 0, D - B);
		add_single_cost(xj, 0, B - A);
		add_penalty01(xj, xi, B + C - A - D);
	}

	// add all True profit
	// y = F: not gain profit (= cost is P), T: gain profit (= cost is 0)
	// y: T, xi: F is prohibited
	void add_profit_all1(const vector<int> &xs, COST P) {
		assert(P >= 0);
		int y = (int)list.size();
		list.resize(y + 1);
		OFFSET -= P;
		add_edge(S, y, P);
		for (auto xi : xs) {
			assert(xi >= 0 && xi < N);
			add_edge(y, xi, INF);
		}
	}

	// add all False profit
	// y = F: gain profit (= cost is 0), T: not gain profit (= cost is P)
	// xi = T, y = F is prohibited
	void add_profit_all0(const vector<int> &xs, COST P) {
		assert(P >= 0);
		int y = (int)list.size();
		list.resize(y + 1);
		OFFSET -= P;
		add_edge(y, T, P);
		for (auto xi : xs) {
			assert(xi >= 0 && xi < N);
			add_edge(xi, y, INF);
		}
	}

	// add general 3-variable submodular function
	// (xi, xj, xk) = (F, F, F): cost A
	// (xi, xj, xk) = (F, F, T): cost B
	// (xi, xj, xk) = (F, T, F): cost C
	// (xi, xj, xk) = (F, T, T): cost D
	// (xi, xj, xk) = (T, F, F): cost E
	// (xi, xj, xk) = (T, F, T): cost F
	// (xi, xj, xk) = (T, T, F): cost G
	// (xi, xj, xk) = (T, T, T): cost H
	void add_submodular_function(int xi, int xj, int xk,
			COST A, COST B, COST C, COST D,
			COST E, COST F, COST G, COST H) {
		assert(0 <= xi && xi < N);
		assert(0 <= xj && xj < N);
		assert(0 <= xk && xk < N);
		COST P = (A + D + F + G) - (B + C + E + H);
		COST P12 = (C + E) - (A + G), P13 = (D + G) - (C + H);
		COST P21 = (D + F) - (B + H), P23 = (B + C) - (A + D);
		COST P31 = (B + E) - (A + F), P32 = (F + G) - (E + H);
		assert(P12 >= 0 && P21 >= 0);
		assert(P23 >= 0 && P32 >= 0);
		assert(P31 >= 0 && P13 >= 0);
		if (P >= 0) {
			OFFSET += A;
			add_single_cost(xi, 0, F - B);
			add_single_cost(xj, 0, G - E);
			add_single_cost(xk, 0, D - C);
			add_penalty01(xi, xj, P12);
			add_penalty01(xj, xk, P23);
			add_penalty01(xk, xi, P31);
			add_profit_all1({xi, xj, xk}, P);
		} else {
			OFFSET += H;
			add_single_cost(xi, C - G, 0);
			add_single_cost(xj, B - D, 0);
			add_single_cost(xk, E - F, 0);
			add_penalty01(xj, xi, P21);
			add_penalty01(xk, xj, P32);
			add_penalty01(xi, xk, P13);
			add_profit_all0({xi, xj, xk}, -P);
		}
	}

	// solve
	COST solve() { return dinic() + OFFSET; }

	// reconstruct the optimal assignment
	// call after calclating flow !
	vector<bool> reconstruct() {
		vector<bool> res(N, false), seen(list.size(), false);
		queue<int> que;
		seen[S] = true;
		que.push(S);
		while (!que.empty()) {
			int v = que.front();
			que.pop();
			for (const auto &e : list[v]) {
				if (e.cap && !seen[e.to]) {
					if (e.to < N) res[e.to] = true;
					seen[e.to] = true;
					que.push(e.to);
				}
			}
		}
		return res;
	}

	// debug
	friend ostream& operator << (ostream& s, const ProjectSelection &g) {
		const auto &edges = g.get_edges();
		for (const auto &e : edges) s << e << endl;
		return s;
	}

	private:
	// edge class
	struct Edge {
		// core members
		int rev, from, to;
		COST cap, icap, flow;

		// constructor
		Edge(int r, int f, int t, COST c)
			: rev(r), from(f), to(t), cap(c), icap(c), flow(0) {}
		void reset() { cap = icap, flow = 0; }

		// debug
		friend ostream& operator << (ostream& s, const Edge& E) {
			return s << E.from << "->" << E.to << '(' << E.flow << '/' << E.icap << ')';
		}
	};

	// inner data
	int N, S, T;
	COST OFFSET, INF;
	vector<vector<Edge>> list;
	vector<pair<int,int>> pos;

	// add edge
	Edge &get_rev_edge(const Edge &e) {
		if (e.from != e.to) return list[e.to][e.rev];
		else return list[e.to][e.rev + 1];
	}
	Edge &get_edge(int i) {
		return list[pos[i].first][pos[i].second];
	}
	const Edge &get_edge(int i) const {
		return list[pos[i].first][pos[i].second];
	}
	vector<Edge> get_edges() const {
		vector<Edge> edges;
		for (int i = 0; i < (int)pos.size(); ++i) {
			edges.push_back(get_edge(i));
		}
		return edges;
	}
	void add_edge(int from, int to, COST cap) {
		if (!cap) return;
		pos.emplace_back(from, (int)list[from].size());
		list[from].push_back(Edge((int)list[to].size(), from, to, cap));
		list[to].push_back(Edge((int)list[from].size() - 1, to, from, 0));
	}

	// Dinic's algorithm
	COST dinic(COST limit_flow) {
		COST current_flow = 0;
		vector<int> level((int)list.size(), -1), iter((int)list.size(), 0);

		// Dinic BFS
		auto bfs = [&]() -> void {
			level.assign((int)list.size(), -1);
			level[S] = 0;
			queue<int> que;
			que.push(S);
			while (!que.empty()) {
				int v = que.front();
				que.pop();
				for (const Edge &e : list[v]) {
					if (level[e.to] < 0 && e.cap > 0) {
						level[e.to] = level[v] + 1;
						if (e.to == T) return;
						que.push(e.to);
					}
				}
			}
		};

		// Dinic DFS
		auto dfs = [&](auto self, int v, COST up_flow) {
			if (v == T) return up_flow;
			COST res_flow = 0;
			for (int &i = iter[v]; i < (int)list[v].size(); ++i) {
				Edge &e = list[v][i], &re = get_rev_edge(e);
				if (level[v] >= level[e.to] || e.cap == 0) continue;
				COST flow = self(self, e.to, min(up_flow - res_flow, e.cap));
				if (flow <= 0) continue;
				res_flow += flow;
				e.cap -= flow, e.flow += flow;
				re.cap += flow, re.flow -= flow;
				if (res_flow == up_flow) break;
			}
			return res_flow;
		};

		// flow
		while (current_flow < limit_flow) {
			bfs();
			if (level[T] < 0) break;
			iter.assign((int)iter.size(), 0);
			while (current_flow < limit_flow) {
				COST flow = dfs(dfs, S, limit_flow - current_flow);
				if (!flow) break;
				current_flow += flow;
			}
		}
		return current_flow;
	};
	COST dinic() { return dinic(numeric_limits<COST>::max() / 2); }
};

// K-value Two Variable Monge Function Optimization 
/*
   X[i] = 0, 1, ..., K-1 -> (x[i][1], ..., x[i][K-1])

   X[i] < d -> x[i][d] = 1
   X[i] = d -> x[i][1] = 0, ..., x[i][d] = 0, x[i][d+1] = 1, ..., x[i][K] = 1

   X[i] = 0   -> (1, 1, 1, ..., 1, 1)
   X[i] = 1   -> (0, 1, 1, ..., 1, 1)
   X[i] = 2   -> (0, 0, 1, ..., 1, 1)
   ...
   X[i] = K-2 -> (0, 0, 0, ..., 0, 1)
   X[i] = K-1 -> (0, 0, 0, ..., 0, 0)
 */

template<class COST>
struct K_ProjectSelection {
	// inner data
	int N, N01;
	COST INF;
	vector<int> ks;  // size of x[i]
	vector<vector<int>> x;  // index of x[i][k] in normal submodular optimization
	ProjectSelection<COST> g;

	// constructors
	K_ProjectSelection() {}
	K_ProjectSelection(int N, int K, COST inf = numeric_limits<COST>::max() / 2) {
		vector<int> ks(N, K);
		init(ks, inf);
	}
	K_ProjectSelection(const vector<int> &ks, COST inf = numeric_limits<COST>::max() / 2) {
		init(ks, inf);
	}
	void init(const vector<int> &iks, COST inf = numeric_limits<COST>::max() / 2) {
		N = (int)iks.size(), INF = inf, ks = iks, N01 = 0;
		x.resize(N);
		for (int i = 0; i < N; i++) {
			assert(ks[i] >= 2);
			x[i].assign(ks[i], 0);
			for (int k = 1; k < ks[i]; k++) x[i][k] = N01++;
		}
		g.init(N01, INF);
		for (int i = 0; i < N; i++) {
			for (int k = 1; k < ks[i] - 1; k++) {
				g.add_constraint01(x[i][k + 1], x[i][k]);
			}
		}
	}

	// add constant cost
	void add_cost(COST cost) { g.add_cost(cost); }

	// add 1-variable function
	void add_single_cost(int xi, const vector<COST> &cost) {
		assert(0 <= xi && xi < N);
		assert((int)cost.size() == ks[xi]);
		g.add_cost(cost[ks[xi] - 1]);
		for (int k = 1; k < ks[xi]; k++) {
			g.add_single_cost(x[xi][k], 0, cost[k-1] - cost[k]);
		}
	}

	// add 2-variable Monge function
	// cost[i][j]+cost[i+1][j+1] <= cost[i+1][j]+cost[i][j+1]
	void add_monge_function(int xi, int xj, vector<vector<COST>> cost) {
		assert(0 <= xi && xi < N);
		assert(0 <= xj && xj < N);
		assert(xi != xj);
		assert(cost.size() == ks[xi]);
		assert(cost[0].size() == ks[xj]);
		vector<COST> icost(ks[xi]), jcost(ks[xj]);
		for (int ki = 0; ki < ks[xi]; ki++) {
			icost[ki] = cost[ki][0];
			for (int kj = 0; kj < ks[xj]; kj++) cost[ki][kj] -= icost[ki];
		}
		for (int kj = 0; kj < ks[xj]; kj++) {
			jcost[kj] = cost[0][kj];
			for (int ki = 0; ki < ks[xi]; ki++) cost[ki][kj] -= jcost[kj];
		}
		add_single_cost(xi, icost), add_single_cost(xj, jcost);
		for (int ki = 1; ki < ks[xi]; ki++) {
			for (int kj = 1; kj < ks[xj]; kj++) {
				COST c = cost[ki][kj] - cost[ki][kj-1] - cost[ki-1][kj] + cost[ki-1][kj-1];
				assert(c <= 0);
				g.add_profit00(x[xi][ki], x[xj][kj], -c);
			}
		}
	}

	// solve
	COST solve() { return g.solve(); }

	// reconstruct the optimal assignment
	// call after calclating flow !
	vector<int> reconstruct() {
		vector<int> res(N, 0);
		vector<bool> tres = g.reconstruct();
		for (int i = 0; i < N; i++) for (int ki = 1; ki < ks[i]; ki++) {
			res[i] += not tres[x[i][ki]];
		}
		return res;
	}
};
