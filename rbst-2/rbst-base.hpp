#pragma once

#include "../data-structure/node-pool.hpp"

// RBSTそのものではなく、RBSTを操作する関数の集合体
template <typename Node>
struct RBSTBase {
	using Ptr = Node *;
	NodePool<Node> pool;
	template <typename... Args>
	Ptr my_new(Args... args) {
		Ptr c = pool.create();
		*c = Node(args...);
		return c;
	}
	void reset() { pool.reset(); }
	inline void my_del(Ptr t) { pool.destroy(t); }
	inline Ptr new_root() const { return nullptr; }
	int size(Ptr t) const { return count(t); }

	Ptr merge(Ptr l, Ptr r) {
		if (!l || !r) return l ? l : r;
		if (int((rng() * (l->cnt + r->cnt)) >> 32) < l->cnt) {
			push(l);
			l = clone(l);
			l->r = merge(l->r, r);
			return update(l);
		}
		else {
			push(r);
			r = clone(r);
			r->l = merge(l, r->l);
			return update(r);
		}
	}
	Ptr merge3(Ptr x, Ptr y, Ptr z) { return merge(merge(x, y), z); }

	std::pair<Ptr, Ptr> split(Ptr root, int k) {
		if (!root) return {nullptr, nullptr};
		push(root);
		if (k <= count(root->l)) { // decompose left
			auto [x, y] = split(root->l, k);
			root = clone(root);
			root->l = y;
			return {x, update(root)};
		}
		else { // decompose right
			auto [x, y] = split(root->r, k - count(root->l) - 1);
			root = clone(root);
			root->r = x;
			return {update(root), y};
		}
	}

	std::tuple<Ptr, Ptr, Ptr> split3(Ptr root, int L, int R) {
		Ptr nm, nr;
		std::tie(root, nr) = split(root, R);
		std::tie(root, nm) = split(root, L);
		return {root, nm, nr};
	}

	Ptr build(int l, int r, const std::vector<decltype(Node::key)> &init) {
		if (l >= r) return nullptr;
		if (l + 1 == r) return my_new(init[l]);
		int m = (l + r) >> 1;
		Ptr pm = my_new(init[m]);
		if (l < m) pm->l = build(l, m, init);
		if (m + 1 < r) pm->r = build(m + 1, r, init);
		return update(pm);
	}
	Ptr build(const std::vector<decltype(Node::key)> &init) { return build(0, (int)init.size(), init); }

	template <typename... Args>
	Ptr insert(Ptr root, int k, const Args &... args) {
		auto [x, y] = split(root, k);
		return merge3(x, my_new(args...), y);
	}

	Ptr erase(Ptr root, int k) {
		auto [x, y, z] = split3(root, k, k + 1);
		my_del(y);
		return merge(x, z);
	}

	template <typename F>
	Ptr max_ok(Ptr root, const F &check) {
		if (!root) return nullptr;
		push(root);
		if (!check(root->key)) return max_ok(root->l, check);
		auto res = max_ok(root->r, check);
		return res ? res : root;
	}

	template <typename F>
	Ptr min_ng(Ptr root, const F &check) {
		if (!root) return nullptr;
		push(root);
		if (check(root->key)) return min_ng(root->r, check);
		auto res = min_ng(root->l, check);
		return res ? res : root;
	}

	template <typename F>
	int count_ok(Ptr root, const F &check) {
		if (!root) return 0;
		push(root);
		if (!check(root->key)) return count_ok(root->l, check);
		int ans = 1;
		if (root->l) ans += root->l->cnt;
		ans += count_ok(root->r, check);
		return ans;
	}

	// 最後に check(s) が成り立つところまでを左としてsplit
	template <typename F>
	std::pair<Ptr, Ptr> split_max_right(Ptr& root, const F &check) {
		if (!root) return {nullptr, nullptr};
		push(root);
		root = clone(root);
		if (check(root->key)) {
			auto [u0, u1] = split_max_right(root->r, check);
			root->r = u0;
			return {update(root), u1};
		}
		else {
			auto [u0, u1] = split_max_right(root->l, check);
			root->l = u1;
			return {u0, update(root)};
		}
	}

	template <typename F>
	void enumerate(Ptr& root, F f) {
		if (!root) return;
		auto dfs = [&](auto&& self, Ptr u)->void{
			if (!u) return;
			push(u);
			self(self, u->l);
			f(u);
			self(self, u->r);
		}; dfs(dfs, root);
	}

	Ptr kth_element(Ptr u, int k) {
		while (u) {
			push(u);
			if (u->l && u->l->cnt > k) u = u->l;
			else {
				if (u->l) k -= u->l->cnt;
				if (k == 0) return u;
				k -= 1;
				u = u->r;
			}
		}
		return nullptr;
	}

	Ptr back(Ptr u) {
		while (u) {
			push(u);
			if (u->r) u = u->r;
			else return u;
		}
		return nullptr;
	}

	Ptr front(Ptr u) {
		while (u) {
			push(u);
			if (u->l) u = u->l;
			else return u;
		}
		return nullptr;
	}

	// 以下、順序付き用
	template <typename F>
	Ptr merge(Ptr u, Ptr v, F comp){
		Ptr ans = new_root();
		while (u) { // u's min <= v's min
			Ptr vmin = front(v);
			auto [u0, u1] = split_max_right(u, [&](Ptr w){ return vmin ? !comp(vmin, w) : 1; });
			ans = merge(ans, u0);
			u = u1;
			std::swap(u, v);
		}
		ans = merge(ans,v);
		return ans;
	};

	template <typename F, typename... Args>
	std::pair<Ptr, int> insert(Ptr root, F comp, const Args &... args) {
		auto p = my_new(args...);
		auto [lp, rp] = split_max_right(root, [&](auto &y) -> bool { return comp(y, p->key); });
		int bns = count(lp);
		return {merge3(lp, p, rp), bns};
	}

	template <typename F>
	Ptr erase(Ptr root, F comp, decltype(Node::key) x) {
		auto [p0, p12] = split_max_right(root, [&](auto &y) ->bool { return comp(y, x); });
		auto [p1, p2] = split_max_right(p12, [&](auto &y) ->bool { return comp(x, y); });
		return merge(p0, p1);
	}

	static uint64_t rng() { // https://ja.wikipedia.org/wiki/Xorshift
		static uint64_t x_ = 88172645463325252ULL;
		return x_ ^= x_ << 7, x_ ^= x_ >> 9, x_ & 0xFFFFFFFFull;
	}
	inline int count(const Ptr t) const { return t ? t->cnt : 0; }
	virtual void push(Ptr) = 0;
	virtual Ptr update(Ptr) = 0;
	virtual Ptr clone(Ptr) = 0;
};
