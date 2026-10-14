#pragma once

#include "../data-structure/node-pool.hpp"

template <typename T, typename E, T (*f)(T, T), T (*g)(T, E), E (*h)(E, E),
		 T (*ti)(), E (*ei)(), bool PERSISTENT = false>
struct DynamicLazySegmentTree {
	using ll = long long;
	struct Node {
		Node *l, *r;
		T sum;
		E laz;
	};

	NodePool<Node> pool;
	const ll L0, R0;
	using Ptr = Node *;
	using I = function<T(ll, ll)>;
	I init;
	Ptr root;

	DynamicLazySegmentTree(ll L0, ll R0, I init = [](ll, ll) -> T { return ti(); })
		: L0(L0), R0(R0), init(init), root(new_root()) {}
	DynamicLazySegmentTree(const std::vector<T> &dat)
		: L0(0), R0(dat.size()), init([](ll, ll) -> T { return ti(); }), root(my_new(dat)) {}

	T fold(Ptr u, ll l, ll r) {
		if (l == r || !u) return ti();
		assert(L0 <= l && l < r && r <= R0);
		T sum = ti();
		_fold(u, L0, R0, l, r, sum, ei());
		return sum;
	}
	T fold(ll l, ll r) { return fold(root, l, r); }
	T fold(Ptr u) { return u ? u->sum : ti(); }
	T fold() { return fold(root); }

	T get_val(Ptr u, ll x) {
		ll L = L0, R = R0;
		while (L + 1 < R) {
			push(u, L, R);
			ll M = (L + R) / 2;
			if (x < M) {
				if (!u->l) return init(x, x + 1);
				u = u->l, R = M;
			}
			else {
				if (!u->r) return init(x, x + 1);
				u = u->r, L = M;
			}
		}
		return u->sum;
	}
	T get_val(ll x) { return get_val(root, x); }

	E get_laz(Ptr u, ll i) {
		if (!u) return ei();
		E e = ei();
		_get_laz(u, L0, R0, i, e);
		return e;
	}
	E get_laz(ll i) { return get(root, i); }


	Ptr set_val(Ptr u, ll i, const T &sum) {
		assert(u && L0 <= i && i < R0);
		return root = _set_val(u, L0, R0, i, sum);
	}
	Ptr set_val(ll i, const T &sum) { return set_val(root, i, sum); }

	Ptr multiply(Ptr u, ll i, const T &sum) {
		assert(u && L0 <= i && i < R0);
		return root = _multiply(u, L0, R0, i, sum);
	}
	Ptr multiply(ll i, const T &sum) { return multiply(root, i, sum); }

	Ptr apply(Ptr u, ll l, ll r, const E &a) {
		if (l == r) return u;
		assert(u && L0 <= l && l < r && r <= R0);
		return root = _apply(u, L0, R0, l, r, a);
	}
	Ptr apply(ll l, ll r, const E &a) { return apply(root, l, r, a); }

	template <typename C>
	ll max_right(Ptr u, C check, ll L) {
		assert(u && L0 <= L && L <= R0 && check(ti()));
		T sum = ti();
		return _max_right(u, check, L0, R0, L, sum);
	}

	template <typename C>
	ll min_left(Ptr u, C check, ll R) {
		assert(u && L0 <= R && R <= R0 && check(ti()));
		T sum = ti();
		return _min_left(u, check, L0, R0, R, sum);
	}

	// memo(idx, val)
	template <typename MEMO>
	void enumerate(Ptr u, MEMO memo) {
		auto dfs = [&](auto &dfs, Ptr u, ll l, ll r, E laz) -> void {
			if (!u) return;
			if (r - l == 1) {
				memo(l, g(u->sum, laz));
				return;
			}
			ll m = (l + r) / 2;
			laz = h(u->laz, laz);
			dfs(dfs, u->l, l, m, laz);
			dfs(dfs, u->r, m, r, laz);
		};
		dfs(dfs, u, L0, R0, ei());
	}

	// u[l:r) を apply(v[l:r), laz) で上書きしたものを返す
	Ptr copy_interval(Ptr u, Ptr v, ll l, ll r, E laz = ei()) {
		if (u == v) return u;
		u = clone(u);
		_copy_interval(u, v, L0, R0, l, r, laz);
		return u;
	}

	private:
	Ptr new_root() { return my_new(L0, R0); }

	Ptr my_new(const T sum) {
		Ptr u = pool.create();
		u->l = u->r = nullptr;
		u->sum = sum, u->laz = ei();
		return u;
	}

	Ptr my_new(ll l, ll r) { return my_new(init(l, r)); }
	Ptr my_new() { return my_new(L0, R0); }
	void my_del(Ptr u) { delete u; }

	Ptr clone(Ptr u) {
		if constexpr (!PERSISTENT) return u;
		if (!u) return u;
		return pool.clone(u);
	}

	void push(Ptr u, ll l, ll r) {
		assert(r - l >= 2);
		ll m = (l + r) / 2;
		if (u->laz == ei()) return;
		u->l = (u->l ? clone(u->l) : my_new(l, m));
		u->l->sum = g(u->l->sum, u->laz);
		u->l->laz = h(u->l->laz, u->laz);
		u->r = (u->r ? clone(u->r) : my_new(m, r));
		u->r->sum = g(u->r->sum, u->laz);
		u->r->laz = h(u->r->laz, u->laz);
		u->laz = ei();
	}

	void _copy_interval(Ptr u, Ptr v, ll l, ll r, ll ql, ll qr, E a) {
		// u[ql, qr) <- apply(v[ql, qr), a)
		// u is already updated
		assert(u);
		ql = std::max(ql, l);
		qr = std::min(qr, r);
		if (ql >= qr) return;
		if (l == ql && r == qr) { // terminus
			if (v) {
				u->sum = g(v->sum, a), u->laz = h(v->laz, a);
				u->l = v->l, u->r = v->r;
			}
			else {
				u->sum = g(init(l, r), a), u->laz = a;
				u->l = nullptr, u->r = nullptr;
			}
			return;
		}
		// push
		ll m = (l + r) / 2;
		u->l = (u->l ? clone(u->l) : my_new());
		u->r = (u->r ? clone(u->r) : my_new());
		u->l->sum = g(u->l->sum, u->laz);
		u->l->laz = h(u->l->laz, u->laz);
		u->r->sum = g(u->r->sum, u->laz);
		u->r->laz = h(u->r->laz, u->laz);
		u->laz = ei();
		if (v) a = h(v->laz, a);
		_copy_interval(u->l, (v && v->l ? v->l : nullptr), l, m, ql, qr, a);
		_copy_interval(u->r, (v && v->r ? v->r : nullptr), m, r, ql, qr, a);
		u->sum = f(u->l->sum, u->r->sum);
	}

	Ptr my_new(const std::vector<T> &dat) {
		assert(L0 == 0 && R0 == dat.size());
		auto dfs = [&](auto &dfs, ll l, ll r) -> Ptr {
			if (l == r) return nullptr;
			if (r == l + 1) return my_new(dat[l]);
			ll m = (l + r) / 2;
			Ptr l_root = dfs(dfs, l, m), r_root = dfs(dfs, m, r);
			T sum = f(l_root->sum, r_root->sum);
			Ptr root = my_new(sum);
			root->l = l_root, root->r = r_root;
			return root;
		};
		return dfs(dfs, 0, dat.size());
	}

	Ptr _set_val(Ptr u, ll l, ll r, ll i, const T &sum) {
		if (r == l + 1) {
			u = clone(u);
			u->sum = sum;
			u->laz = ei();
			return u;
		}
		push(u, l, r);
		ll m = (l + r) / 2;
		if (!u->l) u->l = my_new(l, m);
		if (!u->r) u->r = my_new(m, r);

		u = clone(u);
		if (i < m) {
			u->l = _set_val(u->l, l, m, i, sum);
		} else {
			u->r = _set_val(u->r, m, r, i, sum);
		}
		u->sum = f(u->l->sum, u->r->sum);
		return u;
	}

	Ptr _multiply(Ptr u, ll l, ll r, ll i, const T &sum) {
		if (r == l + 1) {
			u = clone(u);
			u->sum = f(u->sum, sum);
			u->laz = ei();
			return u;
		}
		push(u, l, r);
		ll m = (l + r) / 2;
		if (!u->l) u->l = my_new(l, m);
		if (!u->r) u->r = my_new(m, r);

		u = clone(u);
		if (i < m) {
			u->l = _multiply(u->l, l, m, i, sum);
		} else {
			u->r = _multiply(u->r, m, r, i, sum);
		}
		u->sum = f(u->l->sum, u->r->sum);
		return u;
	}

	void _fold(Ptr u, ll l, ll r, ll ql, ll qr, T &sum, E laz) {
		ql = std::max(ql, l);
		qr = std::min(qr, r);
		if (ql >= qr) return;
		if (!u) {
			sum = f(sum, g(init(ql, qr), laz));
			return;
		}
		if (l == ql && r == qr) {
			sum = f(sum, g(u->sum, laz));
			return;
		}
		ll m = (l + r) / 2;
		laz = h(u->laz, laz);
		_fold(u->l, l, m, ql, qr, sum, laz);
		_fold(u->r, m, r, ql, qr, sum, laz);
	}

	Ptr _apply(Ptr u, ll l, ll r, ll ql, ll qr, const E &a) {
		if (!u) u = my_new(l, r);
		ql = std::max(ql, l);
		qr = std::min(qr, r);
		if (ql >= qr) return u;
		if (l == ql && r == qr) {
			u = clone(u);
			u->sum = g(u->sum, a);
			u->laz = h(u->laz, a);
			return u;
		}
		push(u, l, r);
		ll m = (l + r) / 2;
		u = clone(u);
		u->l = _apply(u->l, l, m, ql, qr, a);
		u->r = _apply(u->r, m, r, ql, qr, a);
		u->sum = f(u->l->sum, u->r->sum);
		return u;
	}

	template <typename C>
	ll _max_right(Ptr u, const C &check, ll l, ll r, ll ql, T &sum) {
		if (r <= ql) return r;
		if (!u) u = my_new(l, r);
		ql = std::max(ql, l);
		if (l == ql && check(f(sum, u->sum))) {
			sum = f(sum, u->sum);
			return r;
		}
		if (r == l + 1) return l;
		push(u, l, r);
		ll m = (l + r) / 2;
		ll k = _max_right(u->l, check, l, m, ql, sum);
		if (k < m) return k;
		return _max_right(u->r, check, m, r, ql, sum);
	}

	template <typename C>
	ll _min_left(Ptr u, const C &check, ll l, ll r, ll qr, T &sum) {
		if (qr <= l) return l;
		if (!u) u = my_new(l, r);
		qr = std::min(qr, r);
		if (r == qr && check(f(u->sum, sum))) {
			sum = f(u->sum, sum);
			return l;
		}
		if (r == l + 1) return r;
		push(u, l, r);
		ll m = (l + r) / 2;
		ll k = _min_left(u->r, check, m, r, qr, sum);
		if (m < k) return k;
		return _min_left(u->l, check, l, m, qr, sum);
	}

	void _get_laz(Ptr u, ll l, ll r, ll i, E &e) {
		if (!u) return;
		e = h(u->laz, e);
		if (r == l + 1) return;
		ll m = (l + r) / 2;
		if (i < m) return _get_laz(u->l, l, m, i, e);
		_get_laz(u->r, m, r, i, e);
	}
};

namespace DynamicSegmentTreeImpl {
template <typename T>
T g(T l, bool) { return l; }
bool h(bool, bool) { return false; }
bool ei() { return false; }

template <typename T, T (*f)(T, T), T (*ti)(), bool PERSISTENT = false>
using DynamicSegmentTree = DynamicLazySegmentTree<T, bool, f, g, h, ti, ei, PERSISTENT>;
}  // namespace DynamicSegmentTreeImpl

namespace DynamicDualSegmentTreeImpl {
bool f(bool, bool) { return false; }
template <typename E>
bool g(bool, E e) { return e; }
bool ti() { return false; }

template <typename E, E (*h)(E, E), E (*ei)(), bool PERSISTENT = false>
using DynamicDualSegmentTree = DynamicLazySegmentTree<bool, E, f, g, h, ti, ei, PERSISTENT>;
} // namespace DynamicDualSegmentTreeImpl

using DynamicSegmentTreeImpl::DynamicSegmentTree;
using DynamicDualSegmentTreeImpl::DynamicDualSegmentTree;
