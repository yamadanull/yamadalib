#pragma once
#include "euler-tour.hpp"
#include "../misc/mo.hpp"

template <typename G, bool vertex = false>
struct MoTree {
	int N;
	EulerTour<G> et;
	[[maybe_unused]] std::vector<int> lcas;
	std::vector<int> U;
	Mo mo;

	MoTree (const G &g, int Q) : et(g), mo((int)g.size() * 2, Q) {
		N = g.size();
		U.resize(N * 2);
		for (int u = 0; u < N; u++) {
			auto [dw, up] = et.idx(u);
			U[dw] = U[up] = u;
		}
	}

	void insert(int u, int v){
		int l = et.idx(u).first, r = et.idx(v).first;
		if (l > r) std::swap(l, r);
		mo.insert(l + 1, r + 1);
		if constexpr (vertex) lcas.emplace_back(et.lca(u, v));
	}

	template<typename ADD, typename DEL, typename REM>
	void run(const ADD &add, const DEL &del, const REM &rem){
		std::vector<bool> flg(N, false);
		auto flp = [&](int t) {
			int u = U[t];
			if (flg[u]) del(U[t]), flg[u] = false;
			else        add(U[t]), flg[u] = true;
		};

		if constexpr (!vertex) mo.run(flp, flp, flp, flp, rem);
		else mo.run(flp, flp, flp, flp, [&](int qi) { add(lcas[qi]); rem(qi); del(lcas[qi]); });
	}
};

template <typename G> using MoTree_Vertex = MoTree<G, true>;
template <typename G> using MoTree_Edge = MoTree<G, false>;

