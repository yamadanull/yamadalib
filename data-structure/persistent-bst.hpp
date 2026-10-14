#pragma once

#include "../internal/internal-type-traits.hpp"

ENABLE_HAS_FUNCTION(push);

/*
Nyaan's RBST と違う点は大雑把に
・葉っぱのみが元の配列である こっちのがセグ木に近い
・子ノードをポインタではなく vector 上のidxで管理する系
・コンストラクタに最大サイズを投げる必要がある？
*/
template <typename Node>
struct WBLTBase { // 永続前提？
	using T = decltype(Node::dat);
	using C = decltype(Node::cnt);
	vector<Node> G; // 0 は nullptr を表現
	int top;
	static constexpr double ALPHA = 0.292;
	bool too_heavy(C u, C v) { return v < ALPHA * (u + v); } // u に偏っているか

	WBLTBase(int cnt = 1) : G(cnt), top(1) {}

	const Node& operator[](int u) { return G[u]; }

	template <typename... Args>
	int alloc(Args... args) {
		G[top] = Node(args...);
		return top++;
	}
	bool almost_full() const { return top >= int(G.size()) * 0.95; }
	void reset() { top = 1; }

	void push([[maybe_unused]] int u) {
		if constexpr (has_push_v<Node>) G[u].push(G.data(), top);
	}
	pair<int, int> cut(int t) { push(t); return {G[t].l, G[t].r}; }
	int join(int u, int v) {
		int t = alloc(u, v);
		G[t].pull(G.data());
		return t;
	}

	int merge(int u, int v) {
		if (!u || !v) return u + v;
		if (too_heavy(G[u].cnt, G[v].cnt)) {
			auto [u0, u1] = cut(u);
			if (too_heavy(G[u1].cnt + G[v].cnt, G[u0].cnt)) {
				auto [u10, u11] = cut(u1);
				return merge(merge(u0, u10), merge(u11, v));
			}
			return merge(u0, merge(u1, v));
		}
		if (too_heavy(G[v].cnt, G[u].cnt)) {
			auto [v0, v1] = cut(v);
			if (too_heavy(G[u].cnt + G[v0].cnt, G[v1].cnt)) {
				auto [v00, v01] = cut(v0);
				return merge(merge(u, v00), merge(v01, v1));
			}
			return merge(merge(u, v0), v1);
		}
		return join(u, v);
	}
	pair<int, int> split(int t, C k) {
		if (!t or !k) return {0, t};
		if (k >= G[t].cnt) return {t, 0};
		auto [u, v] = cut(t);
		if (k <= G[u].cnt) {
			auto [u0, u1] = split(u, k);
			return {u0, merge(u1, v)};
		}
		else {
			auto [v0, v1] = split(v, k - G[u].cnt);
			return {merge(u, v0), v1};
		}
	}
	int shrink(int t, C k) {
		if (!t or !k) return 0;
		if (k >= G[t].cnt) return t;
		auto [u, v] = cut(t);
		if (k <= G[u].cnt) return shrink(u, k);
		return merge(u, shrink(v, k - G[u].cnt));
	}

	// bool check(int t): G[t] 内数列の bool 値の総and
	template <typename F>
	int shrink_max_right(int t, F check) {
		if (!t) return 0;
		if (check(t)) return t;
		auto [u, v] = cut(t);
		if (!check(u)) return shrink_max_right(u, check);
		return merge(u, shrink_max_right(v, check));
	}
	int k_times(int t, C k) { // k 個連結
		if (!t or !k) return 0;
		if (k == 1) return t;
		if (k % 2 == 0) {
			int half = k_times(t, k / 2);
			return join(half, half);
		}
		auto dfs = [&](auto rc, C s) -> pair<int, int> {
			if (s == 2) return {t, join(t, t)};
			if (s % 2 == 0) {
				auto [u, v] = rc(rc, s / 2);
				return {join(v, u), join(v, v)};
			}
			else {
				auto [u, v] = rc(rc, (s + 1) / 2);
				return {join(u, u), join(v, u)};
			}
		};
		return dfs(dfs, k).second;
	}
	// 0-indexed, 配列外参照は壊れる
	int kth_element(int u, C k) {
		push(u);
		if (!G[u].l) return u;
		if (k < G[G[u].l].cnt) return kth_element(G[u].l, k);
		return kth_element(G[u].r, k - G[G[u].l].cnt);
	}

	int build(const vector<T>& A, int L = -1, int R = -1) {
		if (L == -1) L = 0, R = A.size();
		if (L == R) return 0;
		if (L + 1 == R) return alloc(A[L]);
		int M = (L + R) / 2;
		return join(build(A, L, M), build(A, M, R));
	}

	virtual vector<T> dump(int t) {
		if (!t) return {};
		vector<T> res;
		auto dfs = [&](auto rc, int u) -> void {
			if (!G[u].l) {
				res.push_back(G[u].dat);
				return;
			}
			rc(rc, G[u].l);
			rc(rc, G[u].r);
		};
		dfs(dfs, t);
		return res;
	}
};

// ただの数列 値のマージとかはしない
namespace RopeImpl {
template <typename T, typename C>
struct Node {
	int l;
	union { int r; T dat; };
	C cnt;
	Node() = default;
	Node(T _dat) : l(0), dat(_dat), cnt(1) {}
	Node(int _l, int _r) : l(_l), r(_r) {}
	void pull(Node* G) { cnt = G[l].cnt + G[r].cnt; }
};

template <typename T, typename C = int>
using Rope = WBLTBase<Node<T, C>>;
}  // namespace RopeImpl

namespace PersistentWBLTImpl {
template <typename T, T (*f)(T, T), typename C>
struct Node {
	int l, r;
	T dat;
	C cnt;
	Node() = default;
	Node(T _dat) : l(0), dat(_dat), cnt(1) {}
	Node(int _l, int _r) : l(_l), r(_r) {}
	void pull(Node* G) {
		dat = f(G[l].dat, G[r].dat);
		cnt = G[l].cnt + G[r].cnt;
	}
};

template <typename T, T (*f)(T, T), T (*ti)(), typename C = int>
struct PersistentWBLT : WBLTBase<Node<T, f, C>> {
	using Base = WBLTBase<Node<T, f, C>>;
	using Base::G;
	using Base::push;

	PersistentWBLT(int cnt = 1) : Base(cnt) {}

	T prod(int u, C l, C r) {
		if (!u or l >= r) return ti();
		if (!G[u].l) return (l <= 0 and 0 < r) ? G[u].dat : ti();
		C l_cnt = G[G[u].l].cnt, r_cnt = G[G[u].r].cnt;
		l = clamp<C>(l, 0, l_cnt + r_cnt), r = clamp<C>(r, 0, l_cnt + r_cnt);
		if (l >= r) return ti();
		if (r - l == l_cnt + r_cnt) return G[u].dat;
		if (r <= l_cnt) return prod(G[u].l, l, r);
		if (l_cnt <= l) return prod(G[u].r, l - l_cnt, r - l_cnt);
		return f(prod(G[u].l, l, l_cnt), prod(G[u].r, 0, r - r_cnt));
	}
};

};  // namespace PersistentWBLTImpl

namespace PersistentLazyWBLTImpl {
template <typename T, typename E, T (*f)(T, T), T (*g)(T, E), E (*h)(E, E), E (*ei)(), typename C = int>
struct Node {
	int l, r;
	T dat;
	E laz;
	C cnt;
	Node() = default;
	Node(T _dat) : l(0), dat(_dat), laz(ei()), cnt(1) {}
	Node(int _l, int _r) : l(_l), r(_r), laz(ei()) {}
	void pull(Node* G) {
		dat = f(G[l].dat, G[r].dat);
		cnt = G[l].cnt + G[r].cnt;
	}
	void push(Node* G, int& top) {
		if (!l or laz == ei()) return;
		G[top] = G[l], G[top + 1] = G[r];
		l = top, r = top + 1, top += 2;
		G[l].dat = g(G[l].dat, laz), G[l].laz = h(G[l].laz, laz);
		G[r].dat = g(G[r].dat, laz), G[r].laz = h(G[r].laz, laz);
		laz = ei();
	}
};

template <typename T, typename E, T (*f)(T, T), T (*g)(T, E), E (*h)(E, E), T (*ti)(), E (*ei)(), typename C = int>
struct PersistentLazyWBLT : WBLTBase<Node<T, E, f, g, h, ei, C>> {
	using Base = WBLTBase<Node<T, E, f, g, h, ei, C>>;
	static_assert(has_push_v<Node<T, E, f, g, h, ei, C>>);
	using Base::join;
	using Base::G;
	using Base::push;
	using Base::top;
	PersistentLazyWBLT(int cnt) : Base(cnt) {}

	T prod(int u, C L, C R) {
		if (!u or L >= R) return ti();
		push(u);
		if (!G[u].l) return (L <= 0 and 0 < R) ? G[u].dat : ti();
		C l_cnt = G[G[u].l].cnt, r_cnt = G[G[u].r].cnt;
		L = clamp<C>(L, 0, l_cnt + r_cnt), R = clamp<C>(R, 0, l_cnt + r_cnt);
		if (L >= R) return ti();
		if (R - L == l_cnt + r_cnt) return G[u].dat;
		if (R <= l_cnt) return prod(G[u].l, L, R);
		if (l_cnt <= L) return prod(G[u].r, L - l_cnt, R - l_cnt);
		return f(prod(G[u].l, L, l_cnt), prod(G[u].r, 0, R - r_cnt));
	}

	int affect(int u, E laz) {
		if (!u) return u;
		G[top] = G[u];
		G[top].dat = g(G[top].dat, laz);
		G[top].laz = h(G[top].laz, laz);
		return top++;
	}

	int apply(int u, C L, C R, E laz) {
		if (!u or L >= R) return u;
		push(u);
		if (!G[u].l) return (L <= 0 and 0 < R) ? affect(u, laz) : u;
		C l_cnt = G[G[u].l].cnt, r_cnt = G[G[u].r].cnt;
		L = clamp<C>(L, 0, l_cnt + r_cnt), R = clamp<C>(R, 0, l_cnt + r_cnt);
		if (L >= R) return u;
		if (R - L == l_cnt + r_cnt) return affect(u, laz);
		if (R <= l_cnt) return join(apply(G[u].l, L, R, laz), G[u].r);
		if (l_cnt <= L) return join(G[u].l, apply(G[u].r, L - l_cnt, R - l_cnt, laz));
		return join(apply(G[u].l, L, l_cnt, laz), apply(G[u].r, 0, R - l_cnt, laz));
	}

	int apply(int u, E laz) {
		if (!u) return u;
		return apply(u, 0, G[u].cnt, laz);
	}

	vector<T> dump(int t) override {
		if (!t) return {};
		vector<T> res;
		auto dfs = [&](auto rc, int u, E laz) -> void {
			if (!G[u].l) {
				res.push_back(g(G[u].dat, laz));
				return;
			}
			laz = h(G[u].laz, laz);
			rc(rc, G[u].l, laz);
			rc(rc, G[u].r, laz);
		};
		dfs(dfs, t, ei());
		return res;
	}
};
};  // namespace PersistentLazyWBLTImpl

using RopeImpl::Rope;
using PersistentWBLTImpl::PersistentWBLT;
using PersistentLazyWBLTImpl::PersistentLazyWBLT;
