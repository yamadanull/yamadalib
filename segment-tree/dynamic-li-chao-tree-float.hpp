#pragma once

#include "../data-structure/node-pool.hpp"

// 整数のみを扱う場合はそれ用のやつを使う
// Fractionライブラリも動作するが、クソ重いから使い物にならない
// 直線追加かつ非永続なら空間 Q でよい。
// evaluate を書き変えると、totally monotone な関数群にも使える
template <typename T, typename U, bool MINIMIZE = true, bool PERSISTENT = false, int MAX_DEPTH = 50>
struct DynamicLiChaoTreeFloat {
	struct FUNC {
		U a, b;
		U operator()(T x) { return a * x + b; }
	};
	std::vector<FUNC> funcs;
	static inline U evaluate(FUNC &f, T x) { return f(x); }

	struct Node {
		int fid;
		Node *l, *r;
	};
	using Ptr = Node *;
	Ptr cur_root;
	NodePool<Node> pool;
	T L, R;
	U INF;

	DynamicLiChaoTreeFloat(T L, T R, U INF = 9e18) : L(L), R(R), INF(INF), cur_root(nullptr) {}

	void reset() { funcs.clear(), pool.reset(); }

	Ptr new_root() { return nullptr; }

	Ptr new_node() {
		Ptr u = pool.create();
		u->fid = -1, u->l = u->r = nullptr;
		return u;
	}

	Ptr chmin(FUNC f) { return chmin(cur_root, f); }
	Ptr chmax(FUNC f) { return chmax(cur_root, f); }
	Ptr chmin(T xl, T xr, FUNC f) { return chmin(cur_root, xl, xr, f); }
	Ptr chmax(T xl, T xr, FUNC f) { return chmax(cur_root, xl, xr, f); }
	std::pair<U, int> query(T x) { return query(cur_root, x); }

	Ptr chmin(Ptr root, FUNC f) {
		static_assert(MINIMIZE);
		int fid = funcs.size();
		funcs.emplace_back(f);
		if (!root) root = new_node();
		return cur_root = add_line_rec(root, fid, L, R, 0);
	}
	Ptr chmax(Ptr root, FUNC f) {
		static_assert(!MINIMIZE);
		int fid = funcs.size();
		funcs.emplace_back(f);
		if (!root) root = new_node();
		return cur_root = add_line_rec(root, fid, L, R, 0);
	}

	// [xl, xr)
	Ptr chmin(Ptr root, T xl, T xr, FUNC f) {
		static_assert(MINIMIZE);
		int fid = funcs.size();
		funcs.emplace_back(f);
		if (!root) root = new_node();
		return cur_root = add_segment_rec(root, xl, xr, fid, L, R, 0);
	}
	// [xl, xr)
	Ptr chmax(Ptr root, T xl, T xr, FUNC f) {
		static_assert(!MINIMIZE);
		int fid = funcs.size();
		funcs.emplace_back(f);
		if (!root) root = new_node();
		return cur_root = add_segment_rec(root, xl, xr, fid, L, R, 0);
	}

	// (値・関数番号)
	std::pair<U, int> query(Ptr root, T x) {
		assert(L <= x && x < R);
		if (!root) return {INF, -1};
		return query_rec(root, x, L, R);
	}

	private:
	Ptr clone(Ptr u) {
		if (!u || !PERSISTENT) return u;
		return pool.clone(u);
	}

	inline U evaluate_inner(int fid, T x) {
		if (fid == -1) return INF;
		return evaluate(funcs[fid], x);
	}

	Ptr add_segment_rec(Ptr u, T xl, T xr, int fid, T node_l, T node_r, int dep) {
		if (dep > MAX_DEPTH) return nullptr;
		xl = std::max(xl, node_l);
		xr = std::min(xr, node_r);
		if (xl >= xr) return u;
		if (node_l < xl || xr < node_r) {
			u = clone(u);
			T node_m = (node_l + node_r) / 2;
			if (!u->l) u->l = new_node();
			if (!u->r) u->r = new_node();
			u->l = add_segment_rec(u->l, xl, xr, fid, node_l, node_m, dep + 1);
			u->r = add_segment_rec(u->r, xl, xr, fid, node_m, node_r, dep + 1);
			return u;
		}
		return add_line_rec(u, fid, node_l, node_r, dep + 1);
	}

	Ptr add_line_rec(Ptr u, int fid, T node_l, T node_r, int dep) {
		if (dep > MAX_DEPTH) return nullptr;
		int gid = u->fid;
		U fl = evaluate_inner(fid, node_l), fr = evaluate_inner(fid, node_r);
		U gl = evaluate_inner(gid, node_l), gr = evaluate_inner(gid, node_r);
		bool bl = (MINIMIZE ? fl < gl : gl < fl);
		bool br = (MINIMIZE ? fr < gr : gr < fr);
		if (bl && br) {
			u = clone(u);
			u->fid = fid;
			return u;
		}
		if (!bl && !br) return u;

		u = clone(u);
		T node_m = (node_l + node_r) / 2;
		auto fm = evaluate_inner(fid, node_m), gm = evaluate_inner(gid, node_m);
		bool bm = (MINIMIZE ? fm < gm : gm < fm);
		if (bm) {
			u->fid = fid;
			if (bl) {
				if (!u->r) u->r = new_node();
				u->r = add_line_rec(u->r, gid, node_m, node_r, dep + 1);
			} else {
				if (!u->l) u->l = new_node();
				u->l = add_line_rec(u->l, gid, node_l, node_m, dep + 1);
			}
		}
		if (!bm) {
			if (!bl) {
				if (!u->r) u->r = new_node();
				u->r = add_line_rec(u->r, fid, node_m, node_r, dep + 1);
			} else {
				if (!u->l) u->l = new_node();
				u->l = add_line_rec(u->l, fid, node_l, node_m, dep + 1);
			}
		}
		return u;
	}

	std::pair<U, int> query_rec(Ptr u, T x, T node_l, T node_r) {
		int fid = u->fid;
		std::pair<U, int> res = {evaluate_inner(fid, x), fid};
		T node_m = (node_l + node_r) / 2;
		if (x < node_m && u->l) {
			std::pair<U, int> res1 = query_rec(u->l, x, node_l, node_m);
			res = (MINIMIZE ? std::min(res, res1) : std::max(res, res1));
		}
		if (x >= node_m && u->r) {
			std::pair<U, int> res1 = query_rec(u->r, x, node_m, node_r);
			res = (MINIMIZE ? std::min(res, res1) : std::max(res, res1));
		}
		return res;
	}
};
