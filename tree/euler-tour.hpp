#pragma once
#include "../graph/graph-template.hpp"

template <typename G>
struct EulerTour {
private:
	struct RMQ {
		int n, s;
		using P = std::pair<int, int>;
		std::vector<P> seg;
		P UNIT = P(1 << 30, -1);

		RMQ(int N) : n(N), s(1) {
			while (s < N) s <<= 1;
			seg.assign(2 * s, UNIT);
		}

		void set(int k, P x) { seg[k + s] = x; }

		P operator[](int k) const { return seg[k + s]; }

		void build() {
			for (int k = s - 1; k > 0; k--) {
				seg[k] = std::min(seg[2 * k], seg[2 * k + 1]);
			}
		}

		P prod(int a, int b) const {
			P R = UNIT;
			for (a += s, b += s; a < b; a >>= 1, b >>= 1) {
				if (a & 1) R = std::min(R, seg[a++]);
				if (b & 1) R = std::min(R, seg[--b]);
			}
			return R;
		}

		int size() const { return n; }
	};

	std::vector<int> down, up;
	RMQ seg;

	void init(const G &g, int root) {
		int T = 0;
		dfs(g, root, -1, 0, T);
		if (T < seg.size()) seg.set(T++, {-1, -1});

		for (int u = 0; u < (int)g.size(); u++) if (down[u] == -1) {
			seg.set(T++, {-1, -1});
			dfs(g, u, -1, 0, T);
			if (T < seg.size()) seg.set(T++, {-1, -1});
		}
		seg.build();
	}

	void dfs(const G &g, int u, int p, int dep, int &T) {
		down[u] = T;
		seg.set(T++, {dep, u});
		for (auto &v : g[u]) if (v != p) {
			dfs(g, v, u, dep + 1, T);
		}
		up[u] = T;
		if (p != -1) seg.set(T++, {dep - 1, p});
	}

public:
	// remind : because of additional node,
	// DS on tour should reserve 2 * n nodes.
	EulerTour(const G &g, int root = 0) : down(g.size(), -1), up(g.size(), -1), seg(2 * g.size()) {
		init(g, root);
	}

	std::pair<int, int> idx(int i) const { return {down[i], up[i]}; }

	int lca(int a, int b) const {
		if (down[a] > down[b]) std::swap(a, b);
		return seg.prod(down[a], down[b] + 1).second;
	}

	template <typename F>
	void node_query(int a, int b, const F &f) {
		int l = lca(a, b);
		f(down[l], down[a] + 1);
		f(down[l] + 1, down[b] + 1);
	}

	template <typename F>
	void edge_query(int a, int b, const F &f) {
		int l = lca(a, b);
		f(down[l] + 1, down[a] + 1);
		f(down[l] + 1, down[b] + 1);
	}

	template <typename F>
	void subtree_query(int a, const F &f) {
		f(down[a], up[a]);
	}

	int size() const { return seg.size(); }
};
