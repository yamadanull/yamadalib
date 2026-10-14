#pragma once

#include "convert-tree.hpp"
#include "heavy-light-decomposition.hpp"

namespace StaticTopTreeVertexBasedImpl {

enum Type { Vertex, Compress, Rake, Add_Edge, Add_Vertex };

template <typename G>
struct StaticTopTreeVertexBased {
	const HeavyLightDecomposition<G>& hld;
	std::vector<std::vector<int>> g;
	int root;     // 元の木の root
	int tt_root;  // top tree の root
	std::vector<int> P, L, R;
	std::vector<Type> T;

	StaticTopTreeVertexBased(const HeavyLightDecomposition<G>& _hld) : hld(_hld) {
		root = hld.root;
		g = rooted_tree(hld.g, root);
		int n = g.size();
		P.resize(n, -1), L.resize(n, -1), R.resize(n, -1);
		T.resize(n, Type::Vertex);
		build();
	}

	private:
	int add(int l, int r, Type t) {
		if (t == Type::Compress || t == Type::Rake) assert(l >= 0 && r >= 0);
		if (t == Type::Add_Edge) assert(l >= 0 && r < 0);
		assert(t != Type::Vertex && t != Type::Add_Vertex);
		int k = P.size();
		P.emplace_back(-1), L.emplace_back(l), R.emplace_back(r), T.emplace_back(t);
		if (l >= 0) P[l] = k;
		if (r >= 0) P[r] = k;
		return k;
	}
	int add2(int k, int l, int r, Type t) {
		assert(k < (int)g.size());
		assert(t == Type::Vertex || t == Type::Add_Vertex);
		if (t == Type::Vertex) assert(l < 0 && r < 0);
		else assert(l >= 0 && r < 0);
		P[k] = -1, L[k] = l, R[k] = r, T[k] = t;
		if (l >= 0) P[l] = k;
		if (r >= 0) P[r] = k;
		return k;
	}
	std::pair<int, int> merge(const std::vector<std::pair<int, int>>& A, Type t) {
		assert(!A.empty());
		if (A.size() == 1) return A[0];
		int sum_s = 0;
		for (auto& [_, s] : A) sum_s += s;
		std::vector<std::pair<int, int>> B, C;
		for (auto& [u, s] : A) {
			(sum_s > s ? B : C).emplace_back(u, s);
			sum_s -= s * 2;
		}
		auto [u, cnt_u] = merge(B, t);
		auto [v, cnt_v] = merge(C, t);
		return {add(u, v, t), cnt_u + cnt_v};
	}
	std::pair<int, int> compress(int u) {
		std::vector<std::pair<int, int>> chs;
		while (1) {
			chs.emplace_back(add_vertex(u));
			if (g[u].empty()) break;
			u = g[u][0];
		}
		return merge(chs, Type::Compress);
	}
	std::pair<int, int> rake(int u) {
		std::vector<std::pair<int, int>> chs;
		for (int ei = 1; ei < (int)g[u].size(); ei++) chs.emplace_back(add_edge(g[u][ei]));
		if (chs.empty()) return {-1, 0};
		return merge(chs, Type::Rake);
	}
	std::pair<int, int> add_edge(int u) {
		auto [v, cnt_v] = compress(u);
		return {add(v, -1, Type::Add_Edge), cnt_v};
	}
	std::pair<int, int> add_vertex(int u) {
		auto [rak_u, cnt] = rake(u);
		return {add2(u, rak_u, -1, rak_u < 0 ? Type::Vertex : Type::Add_Vertex), cnt + 1};
	}
	void build() {
		auto [tu, n] = compress(root);
		assert((int)g.size() == n);
		tt_root = tu;
	}
};

template <typename G, typename Path, typename Point, typename Vertex,
          typename Compress, typename Rake, typename Add_edge,
          typename Add_vertex>
struct DPonStaticTopTreeVertexBased {
	const StaticTopTreeVertexBased<G> tt;
	std::vector<Path> path;
	std::vector<Point> point;
	const Vertex vertex;
	const Compress compress;
	const Rake rake;
	const Add_edge add_edge;
	const Add_vertex add_vertex;

	DPonStaticTopTreeVertexBased(const HeavyLightDecomposition<G>& hld,
	                             const Vertex& _vertex, const Compress& _compress,
	                             const Rake& _rake, const Add_edge& _add_edge,
	                             const Add_vertex& _add_vertex)
		: tt(hld),
		  vertex(_vertex),
		  compress(_compress),
		  rake(_rake),
		  add_edge(_add_edge),
		  add_vertex(_add_vertex) {
		int n = tt.P.size();
		path.resize(n), point.resize(n);
		dfs(tt.tt_root);
	}

	Path get() { return path[tt.tt_root]; }
	void update(int k) { while (k >= 0) _update(k), k = tt.P[k]; }

	private:
	void _update(int k) {
		if (tt.T[k] == Type::Vertex) path[k] = vertex(k);
		else if (tt.T[k] == Type::Compress) path[k] = compress(path[tt.L[k]], path[tt.R[k]]);
		else if (tt.T[k] == Type::Rake) point[k] = rake(point[tt.L[k]], point[tt.R[k]]);
		else if (tt.T[k] == Type::Add_Edge) point[k] = add_edge(path[tt.L[k]]);
		else path[k] = add_vertex(point[tt.L[k]], k);
	}

	void dfs(int k) {
		if (tt.L[k] >= 0) dfs(tt.L[k]);
		if (tt.R[k] >= 0) dfs(tt.R[k]);
		_update(k);
	}
};

}  // namespace StaticTopTreeVertexBasedImpl

using StaticTopTreeVertexBasedImpl::DPonStaticTopTreeVertexBased;
using StaticTopTreeVertexBasedImpl::StaticTopTreeVertexBased;


// template
/*
	using Path = ;
	using Point = ;
	auto vertex = [&](int u) -> Path {
	};
	auto compress = [&](const Path& p, const Path& c) -> Path {
	};
	auto rake = [&](const Point& a, const Point& b) -> Point {
	};
	auto add_edge = [&](const Path& a) -> Point {
	};
	auto add_vertex = [&](const Point& a, int u) -> Path {
	};

	HeavyLightDecomposition hld{g};
	DPonStaticTopTreeVertexBased<vector<vector<int>>, Path, Point,
	                             decltype(vertex), decltype(compress), decltype(rake), decltype(add_edge),
	                             decltype(add_vertex)>
	                             dp(hld, vertex, compress, rake, add_edge, add_vertex);
*/

