#pragma once

template <typename Flow, typename Cost, bool MAXIMIZE = false>
struct MinCostFlow {
	struct Edge {
		int src, dst;
		Flow flow, cap;
		Cost cost;
		int rev;

		Edge() = default;
		Edge(int src, int dst, Flow cap, Cost cost, int rev)
			: src(src), dst(dst), flow(0), cap(cap), cost(cost), rev(rev) {}
		Flow residual_cap() const { return cap - flow; }
	};

	struct EdgePtr {
		friend struct MinCostFlow;
		const MinCostFlow *itc;
		int u, ei;

		EdgePtr(const MinCostFlow *itc, const int _u, const int _ei) : itc(itc), u(_u), ei(_ei) {}
		[[nodiscard]] const Edge &edge() const { return itc->G[u][ei]; }
		[[nodiscard]] const Edge &rev() const {
			const Edge &e = edge();
			return itc->G[e.dst][e.rev];
		}

		EdgePtr() = default;
		[[nodiscard]] int src() const { return u; }
		[[nodiscard]] int dst() const { return edge().dst; }
		[[nodiscard]] int flow() const { return edge().flow; }
		[[nodiscard]] int lower() const { return -rev().cap; }
		[[nodiscard]] int upper() const { return edge().cap; }
		[[nodiscard]] int cost() const { return edge().cost; }
		[[nodiscard]] int gain() const { return -edge().cost; }
	};

	int N;
	std::vector<std::vector<Edge>> G;
	std::vector<Flow> b;

	MinCostFlow() : N(0) {}

	int add_vertex() {
		++N;
		G.resize(N);
		b.resize(N);
		return N - 1;
	}

	std::vector<int> add_vertices(const int siz) {
		std::vector<int> ret(siz);
		std::iota(ret.begin(), ret.end(), N);
		N += siz;
		G.resize(N);
		b.resize(N);
		return ret;
	}

	EdgePtr add_edge(const int src, const int dst, const Flow lower, const Flow upper, Cost cost) {
		assert(lower <= upper);
		const int ei = G[src].size();
		const int ej = (src == dst ? ei + 1 : G[dst].size());
		if constexpr (MAXIMIZE) cost *= -1;
		G[src].emplace_back(Edge(src, dst, upper, cost, ej));
		G[dst].emplace_back(Edge(dst, src, -lower, -cost, ei));
		return EdgePtr(this, src, ei);
	}

	EdgePtr add_edge(int src, int dst, Flow upper, Cost cost) {
		return add_edge(src, dst, (Flow)0, upper, cost);
	}

	void add_sup(int u, Flow f) { b[u] += f; }
	void add_dem(int u, Flow f) { b[u] -= f; }

	std::vector<Cost> pot;
	std::vector<Cost> dp; // distance
	std::vector<Edge *> par; // out-forrest.
	std::vector<int> S, T;

	// should be empty outside of dual()
	std::priority_queue<std::pair<Cost, int>, std::vector<std::pair<Cost, int>>, greater<>> pq;

	Edge &rev(Edge e) { return G[e.dst][e.rev]; }

	void push(Edge &e, const Flow f) {
		e.flow += f;
		G[e.dst][e.rev].flow -= f;
	}

	Cost simple_cost(const int src, const int dst, const Edge &e) { return e.cost + pot[src] - pot[dst]; }

	bool dual(const Flow delta = 1) {
		dp.assign(N, Cost(-1));
		par.assign(N, nullptr);
		S.erase(std::remove_if(S.begin(), S.end(), [&](const int u) { return b[u] < +delta; }), S.end());
		T.erase(std::remove_if(T.begin(), T.end(), [&](const int u) { return b[u] > -delta; }), T.end());

		for (const int s : S) pq.emplace(dp[s] = 0, s);
		Cost FARTHEST = 0;
		int T_cnt = 0;
		while (!pq.empty()) {
			const auto [d, u] = pq.top();
			pq.pop();
			if (dp[u] < d) continue;
			FARTHEST = d;
			if (b[u] <= -delta) ++T_cnt;
			if (T_cnt >= (int)T.size()) break;
			for (auto &e : G[u]) if (e.residual_cap() >= delta) {
				const int v = e.dst;
				const Cost D = d + simple_cost(u, v, e);
				if (dp[v] < Cost(0) || dp[v] > D) {
					pq.emplace(dp[v] = D, v);
					par[v] = &e;
				}
			}
		}
		pq = decltype(pq)();
		for (int u = 0; u < N; ++u) {
			Cost add = FARTHEST;
			if (dp[u] >= Cost(0)) add = std::min(dp[u], add);
			pot[u] += add;
		}
		return T_cnt > 0;
	}

	void primal(const Flow delta = 1) {
		for (const int t : T) if (dp[t] >= Cost(0)) {
			Flow f = -b[t];
			int cur = t;
			while (par[cur]) {
				f = std::min(f, par[cur]->residual_cap());
				cur = par[cur]->src;
			}
			f = std::min(f, b[cur]);
			if (f < delta) continue;

			cur = t;
			while (par[cur]) {
				auto &e = *par[cur];
				push(e, f);
				const int nxt = par[cur]->src;
				par[cur] = nullptr;
				cur = nxt;
			}
			b[t] += f;
			b[cur] -= f;
		}
	}

	void saturate_negative(const Flow delta) {
		S.clear();
		T.clear();
		for (auto &es : G) for (auto &e : es) {
			const Flow rcap = e.residual_cap();
			if (rcap >= delta && simple_cost(e.src, e.dst, e) < 0) {
				push(e, rcap);
				b[e.src] -= rcap;
				b[e.dst] += rcap;
			}
		}
		for (int u = 0; u < N; ++u) if (b[u] != 0) {
			(b[u] > 0 ? S : T).emplace_back(u);
		}
	}

	template <bool SCALING = false>
	std::pair<bool, Cost> solve() {
		pot.resize(N);
		for (auto &es : G) for (auto &e : es) {
			const Flow rcap = e.residual_cap();
			if (rcap < 0) {
				push(e, rcap);
				b[e.src] -= rcap;
				b[e.dst] += rcap;
			}
		}

		Flow delta = 2;
		if constexpr (SCALING) {
			Flow INFflow = 1;
			for (const auto &es : G) for (const auto &e : es) INFflow = std::max(INFflow, e.residual_cap());
			while (delta <= INFflow) delta *= 2;
		}
		for (delta /= 2; delta; delta /= 2) {
			saturate_negative(delta);
			while (dual(delta)) primal(delta);
		}

		Cost ans = 0;
		for (const auto &es : G) for (const auto &e : es) ans += e.flow * e.cost;
		ans /= 2;
		if constexpr (MAXIMIZE) ans *= -1;
		return {S.empty() && T.empty(), ans};
	}

	template <bool SCALING = false>
	std::tuple<bool, Cost, Flow> solve(const int s, const int t) {
		assert(s != t);
		Flow INFflow = std::abs(b[s]);
		for (const auto &e : G[s]) INFflow += std::max(e.cap, static_cast<Flow>(0));

		add_edge(t, s, 0, INFflow, 0);
		{
			auto [fn, ans] = solve<SCALING>();
			if (!fn) {
				G[s].pop_back();
				G[t].pop_back();
				return {0, ans, 0};
			}
		}

		INFflow = std::abs(b[s]);
		for (const auto &e : G[s]) INFflow += e.residual_cap();
		b[s] += INFflow;
		b[t] -= INFflow;
		const Cost ans = solve<SCALING>().second;
		b[s] -= INFflow; G[s].pop_back();
		b[t] += INFflow; G[t].pop_back();
		return {1, ans, b[t]};
	}
};

template <typename Flow, typename Cost>
using MaxGainFlow = MinCostFlow<Flow, Cost, true>;
