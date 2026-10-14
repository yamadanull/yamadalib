#pragma once

// https://miti-7.github.io/post/minimum-cost-flow-primal-network-simplex/
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
		[[nodiscard]] Flow residual_cap() const { return cap - flow; }
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
	std::vector<Cost> pot;
	std::vector<int> dep;
	std::vector<Edge *> par;

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

	EdgePtr add_edge(const int src, const int dst, const Flow upper, const Cost cost) {
		return add_edge(src, dst, (Flow)0, upper, cost);
	}

	void add_sup(const int u, const Flow f) { b[u] += f; }
	void add_dem(const int u, const Flow f) { b[u] -= f; }

	Edge &rev(Edge e) { return G[e.dst][e.rev]; }
	void push(Edge &e, const Flow f) { e.flow += f; G[e.dst][e.rev].flow -= f; }
	Cost reduced_cost(const int src, const int dst, const Edge &e) { return e.cost + pot[src] - pot[dst]; }

	std::pair<bool, Cost> solve() {
		for (auto &es : G) for (auto &e : es) { // make every edge restricted arc
			const Flow rcap0 = e.residual_cap();
			const Flow rcap1 = rev(e).residual_cap();
			if (rcap0 && rcap1) {
				push(e, rcap0);
				b[e.src] -= rcap0;
				b[e.dst] += rcap0;
			}
		}

		build_initial_tree();
		candidate_list_pivot_rule();

		bool ans = true;
		for (auto &e : G[N]) if (e.flow) ans = false;
		Cost bns = 0;
		for (const auto &es : G) for (const auto &e : es) bns += e.flow * e.cost;
		bns /= 2;
		if constexpr (MAXIMIZE) bns *= -1;

		pot.pop_back(); b.pop_back(); G.pop_back();
		for (auto &es : G) es.pop_back();
		return {ans, bns};
	}

	private:
	bool is_eligible(Edge *ep) {
		const int u = ep->src, v = ep->dst;
		if (u < N && ep == par[u]) return false;
		if (v < N && &rev(*ep) == par[v]) return false;
		if (ep->residual_cap() == 0) return false;
		return reduced_cost(u, v, *ep) < Cost(0);
	}

	void first_eligible_arc_pivot_rule() { // unused
		while (1) {
			bool end = true;
			for (const auto &es : G) for (const auto &e : es) {
				if (is_eligible(e)) {
					end = false;
					update_tree(&e);
				}
			}
			if (end) return;
		}
	}

	void candidate_list_pivot_rule() {
		int M = 0; for (const auto &es : G) M += es.size();
		const int BUCKET_SIZE = std::max(int(std::sqrt(double(M)) * 0.2), 10);
		const int CLEAN_LIMIT = std::max(int(BUCKET_SIZE * 0.1), 3);

		std::vector<Edge *> cand;
		const auto leftover_cleaner = [&]() -> bool {
			if (cand.empty()) return false;

			Cost best_val = 0;
			Edge *best_ep = nullptr;
			for (int i = 0; i < (int)cand.size(); i++) {
				const auto ep = cand[i];
				if (is_eligible(ep)) {
					Cost rcst = reduced_cost(ep->src, ep->dst, *ep);
					if (rcst < best_val) best_val = rcst, best_ep = ep;
				}
				else {
					std::swap(cand[i], cand.back());
					cand.pop_back();
					i--;
				}
			}
			if (best_val == 0) return false;
			update_tree(*best_ep);
			return true;
		};

		int U_START = 0, EI_START = 0;
		while (1) {
			for (int _ = 0; _ < CLEAN_LIMIT; _++) if (!leftover_cleaner()) break;
			cand.clear();

			Cost best_val = 0;
			Edge *best_ep = nullptr;
			int u = U_START, ei = EI_START; // degree >= 1 (for all vertex) now
			do {
				if (++ei >= (int)G[u].size()) u = (u + 1) % (N + 1), ei = 0;
				Edge *ep = &G[u][ei];

				if (is_eligible(ep)) {
					Cost rcst = reduced_cost(ep->src, ep->dst, *ep);
					if (rcst < best_val) best_val = rcst, best_ep = ep;
					cand.emplace_back(ep);
					if ((int)cand.size() == BUCKET_SIZE) break;
				}
			} while (!(u == U_START && ei == EI_START));

			U_START = u, EI_START = ei;
			if (cand.empty()) return;
			update_tree(*best_ep);
		}
	}


	std::vector<char> vis; // 0:unvisited, 1:updated, 2:not needed to updated
	void update_tree(Edge &E0) {
		const int U0 = E0.src;
		const int V0 = E0.dst;
		int LCA = -1;
		{ // Step1: find cycle and push flow
			Flow F_LIM = E0.residual_cap();
			int u = U0, v = V0;
			auto up_u = [&]() {
				Flow f_lim = rev(*par[u]).residual_cap();
				if (f_lim < F_LIM) F_LIM = f_lim;
				u = par[u]->dst;
			};
			auto up_v = [&]() {
				Flow f_lim = par[v]->residual_cap();
				if (f_lim < F_LIM) F_LIM = f_lim;
				v = par[v]->dst;
			};

			while (dep[u] > dep[v]) up_u();
			while (dep[v] > dep[u]) up_v();
			while (u != v) up_u(), up_v();
			LCA = u;
			if (F_LIM) {
				push(E0, F_LIM);
				for (u = U0; u != LCA; u = par[u]->dst) push(*par[u], -F_LIM);
				for (v = V0; v != LCA; v = par[v]->dst) push(*par[v], +F_LIM);
			}
		}

		// Step2: find leaving-arc
		int DEL_U = -1; // child of leaving-arc
		bool DEL_SIDE_is_U0 = true;
		for (int u = U0; u != LCA; u = par[u]->dst) if (rev(*par[u]).residual_cap() == 0) {
			DEL_U = u;
			break;
		}
		for (int v = V0; v != LCA; v = par[v]->dst) if (par[v]->residual_cap() == 0) {
			DEL_SIDE_is_U0 = false;
			DEL_U = v;
		}
		if (DEL_SIDE_is_U0 && E0.residual_cap() == 0) return; // leaving-arc is E0

		{ // Step3: update "par"
			int cur_u = (DEL_SIDE_is_U0 ? U0 : V0);
			Edge* cur_e = (DEL_SIDE_is_U0 ? &E0 : &rev(E0)); // new parent of "cur_u"
			while (1) {
				if (cur_u == DEL_U) { par[cur_u] = cur_e; break; }
				int nxt_u = par[cur_u]->dst;
				Edge* nxt_e = &rev(*par[cur_u]);
				par[cur_u] = cur_e;
				cur_u = nxt_u;
				cur_e = nxt_e;
			}
		}

		// Step4: update "pot" and "dep" (and "vis")
		// 多少綺麗にやるならこうしてN時間かける方針しか思いつかない それでもPrimal-Dualの倍速ぐらい
		// LC最速のyosupo実装はよくわからんことをしているけどあれは部分木サイズ時間になってそう
		vis.assign(N + 1, 0); vis[N] = 2;
		const Cost P_DIFF = reduced_cost(U0, V0, E0) * (DEL_SIDE_is_U0 ? -1 : 1);
		{
			int subroot = (DEL_SIDE_is_U0 ? U0 : V0);
			pot[subroot] += P_DIFF;
			dep[subroot] = dep[par[subroot]->dst] + 1;
			vis[subroot] = 1;
		}

		for (int u = 0; u < N; u++) if (vis[u] == 0) {
			int subroot = u;
			int len = 0;
			while (vis[subroot] == 0) subroot = par[subroot]->dst, ++len;
			if (vis[subroot] == 1) {
				int ndep = dep[subroot] + len;
				for (int cur = u; cur != subroot; cur = par[cur]->dst) {
					pot[cur] += P_DIFF;
					dep[cur] = ndep--;
				}
			}
			for (int cur = u; cur != subroot; cur = par[cur]->dst) vis[cur] = vis[subroot];
		}
	}

	void build_initial_tree() {
		G.resize(N + 1);
		b.resize(N + 1);
		pot.resize(N + 1);
		par.resize(N);
		dep.assign(N + 1, 1); dep[N] = 0;

		Cost INFcost = 1;
		for (const auto &es : G) for (const auto &e : es) INFcost += (e.cost > 0 ? e.cost : -e.cost);

		for (int u = 0; u < N; u++) {
			if (b[u] >= 0) {
				add_edge(u, N, 0, b[u] + 1, INFcost);
				pot[u] = -INFcost;
			}
			else {
				add_edge(N, u, 0, -b[u], INFcost);
				pot[u] = INFcost;
			}
			push(G[u].back(), b[u]);
			b[N] += b[u], b[u] = 0;
			par[u] = &G[u].back();
		}
	}

	std::tuple<bool, Cost, Flow> solve(const int s, const int t) {
		assert(s != t);
		Flow INFflow = std::abs(b[s]);
		for (const auto &e : G[s]) INFflow += std::max(e.cap, static_cast<Flow>(0));

		add_edge(t, s, 0, INFflow, 0);
		{
			auto [fn, ans] = solve();
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
		const Cost ans = solve().second;
		b[s] -= INFflow; G[s].pop_back();
		b[t] += INFflow; G[t].pop_back();
		return {1, ans, b[t]};
	}
};

template <typename Flow, typename Cost>
using MaxGainFlow = MinCostFlow<Flow, Cost, true>;
