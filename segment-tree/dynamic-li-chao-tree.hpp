#pragma once
#include "../data-structure/node-pool.hpp"

// 整数のみ扱える（ここ重要）
// 直線追加かつ非永続なら空間 Q でよい。
// 関数は T -> U。[L, R) 上 f が overflow しないように注意。
// evaluate を書き変えると、totally monotone な関数群にも使える
template <typename T, typename U, U INF, bool MINIMIZE = true, bool PERSISTENT = false>
struct DynamicLiChaoTree {
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

	DynamicLiChaoTree(T L, T R) : L(L), R(R), cur_root(nullptr) {}

	void reset() { funcs.clear(), pool.reset(); }

	Ptr new_root() { return nullptr; }

	Ptr new_node() {
		Ptr c = pool.create();
		c->fid = -1, c->l = c->r = nullptr;
		return c;
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
		return cur_root = add_line_rec(root, fid, L, R);
	}
	Ptr chmax(Ptr root, FUNC f) {
		static_assert(!MINIMIZE);
		int fid = funcs.size();
		funcs.emplace_back(f);
		if (!root) root = new_node();
		return cur_root = add_line_rec(root, fid, L, R);
	}

	// [xl, xr)
	Ptr chmin(Ptr root, T xl, T xr, FUNC f) {
		static_assert(MINIMIZE);
		int fid = funcs.size();
		funcs.emplace_back(f);
		if (!root) root = new_node();
		return cur_root = add_segment_rec(root, xl, xr, fid, L, R);
	}
	// [xl, xr)
	Ptr chmax(Ptr root, T xl, T xr, FUNC f) {
		static_assert(!MINIMIZE);
		int fid = funcs.size();
		funcs.emplace_back(f);
		if (!root) root = new_node();
		return cur_root = add_segment_rec(root, xl, xr, fid, L, R);
	}

	// (値・関数番号)
	std::pair<U, int> query(Ptr root, T x) {
		assert(L <= x && x < R);
		if (!root) return {INF, -1};
		return query_rec(root, x, L, R);
	}

	private:
	Ptr clone(Ptr c) {
		if (!c || !PERSISTENT) return c;
		return pool.clone(c);
	}

	inline U evaluate_inner(int fid, T x) {
		if (fid == -1) return INF;
		return evaluate(funcs[fid], x);
	}

	Ptr add_segment_rec(Ptr c, T xl, T xr, int fid, T node_l, T node_r) {
		xl = std::max(xl, node_l);
		xr = std::min(xr, node_r);
		if (xl >= xr) return c;
		if (node_l < xl || xr < node_r) {
			c = clone(c);
			T node_m = (node_l + node_r) / 2;
			if (!c->l) c->l = new_node();
			if (!c->r) c->r = new_node();
			c->l = add_segment_rec(c->l, xl, xr, fid, node_l, node_m);
			c->r = add_segment_rec(c->r, xl, xr, fid, node_m, node_r);
			return c;
		}
		return add_line_rec(c, fid, node_l, node_r);
	}

	Ptr add_line_rec(Ptr c, int fid, T node_l, T node_r) {
		int gid = c->fid;
		U fl = evaluate_inner(fid, node_l), fr = evaluate_inner(fid, node_r - 1);
		U gl = evaluate_inner(gid, node_l), gr = evaluate_inner(gid, node_r - 1);
		bool bl = (MINIMIZE ? fl < gl : gl < fl);
		bool br = (MINIMIZE ? fr < gr : gr < fr);
		if (bl && br) {
			c = clone(c);
			c->fid = fid;
			return c;
		}
		if (!bl && !br) return c;

		c = clone(c);
		T node_m = (node_l + node_r) / 2;
		auto fm = evaluate_inner(fid, node_m), gm = evaluate_inner(gid, node_m);
		bool bm = (MINIMIZE ? fm < gm : gm < fm);
		if (bm) {
			c->fid = fid;
			if (bl) {
				if (!c->r) c->r = new_node();
				c->r = add_line_rec(c->r, gid, node_m, node_r);
			} else {
				if (!c->l) c->l = new_node();
				c->l = add_line_rec(c->l, gid, node_l, node_m);
			}
		}
		if (!bm) {
			if (!bl) {
				if (!c->r) c->r = new_node();
				c->r = add_line_rec(c->r, fid, node_m, node_r);
			} else {
				if (!c->l) c->l = new_node();
				c->l = add_line_rec(c->l, fid, node_l, node_m);
			}
		}
		return c;
	}

	std::pair<U, int> query_rec(Ptr c, T x, T node_l, T node_r) {
		int fid = c->fid;
		std::pair<U, int> res = {evaluate_inner(fid, x), fid};
		T node_m = (node_l + node_r) / 2;
		if (x < node_m && c->l) {
			std::pair<U, int> res1 = query_rec(c->l, x, node_l, node_m);
			res = (MINIMIZE ? std::min(res, res1) : std::max(res, res1));
		}
		if (x >= node_m && c->r) {
			std::pair<U, int> res1 = query_rec(c->r, x, node_m, node_r);
			res = (MINIMIZE ? std::min(res, res1) : std::max(res, res1));
		}
		return res;
	}
};
