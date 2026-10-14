#pragma once

#include "../data-structure/node-pool.hpp"

template <typename AM, bool PERSISTENT = false>
struct DynamicLazySegmentTree {
	using MX = typename AM::Monoid_X;
	using MA = typename AM::Monoid_A;
	using X = typename MX::value_type;
	using A = typename MA::value_type;
	using ll = long long;
	struct Node {
		Node *l, *r;
		X sum;
		A laz;
	};

	NodePool<Node> pool;
	const ll L0, R0;
	using Ptr = Node *;
	using I = function<X(ll, ll)>;
	I init;
	Ptr cur_root;

	DynamicLazySegmentTree(ll L0, ll R0, I init = [](ll, ll) -> X { return MX::I(); })
		: L0(L0), R0(R0), init(init), cur_root(new_root()) {}
	template <typename T>
	DynamicLazySegmentTree(const std::vector<T> &dat)
		: L0(0), R0(dat.size()), init([](ll, ll) -> X { return MX::I(); }), cur_root(my_new(dat)) {}

	X prod(Ptr root, ll l, ll r) {
		if (l == r || !root) return MX::I();
		assert(L0 <= l && l < r && r <= R0);
		X sum = MX::I();
		_prod(root, L0, R0, l, r, sum, MA::I());
		return sum;
	}
	X prod(ll l, ll r) { return prod(cur_root, l, r); }
	X prod(Ptr root) { return root ? root->sum : MX::I(); }
	X prod() { return prod(cur_root); }
	template <typename... Args>
	X operator()(Args... args) { return prod(args...); }
	template <typename... Args>
	X operator[](Args... args) { return get_val(args...); }

	X get_val(ll i) { return get_val(cur_root, i); }
	A get_laz(ll i) { return get_laz(cur_root, i); }
	Ptr set_val(ll i, const X &sum) { return set_val(cur_root, i, sum); }
	Ptr multiply(ll i, const X &sum) { return multiply(cur_root, i, sum); }
	Ptr apply(ll l, ll r, const A &laz) { return apply(cur_root, l, r, laz); }
	template <typename G>
	ll max_right(ll L, G check) { return max_right(cur_root, L, check); }
	template <typename G>
	ll min_left(ll R, G check) { return min_left(cur_root, R, check); }

	X get_val(Ptr root, ll i) {
		ll L = L0, R = R0;
		while (L + 1 < R) {
			push(root, L, R);
			ll M = (L + R) / 2;
			if (i < M) {
				if (!root->l) return init(i, i + 1);
				root = root->l, R = M;
			}
			else {
				if (!root->r) return init(i, i + 1);
				root = root->r, L = M;
			}
		}
		return root->sum;
	}

	A get_laz(Ptr root, ll i) {
		if (!root) return MA::I();
		A laz = MA::I();
		_get_laz(root, L0, R0, i, laz);
		return laz;
	}

	Ptr set_val(Ptr root, ll i, const X &sum) {
		assert(root && L0 <= i && i < R0);
		return cur_root = _set_val(root, L0, R0, i, sum);
	}

	Ptr multiply(Ptr root, ll i, const X &sum) {
		assert(root && L0 <= i && i < R0);
		return cur_root = _multiply(root, L0, R0, i, sum);
	}

	Ptr apply(Ptr root, ll l, ll r, const A &laz) {
		if (l == r) return root;
		assert(root && L0 <= l && l < r && r <= R0);
		return cur_root = _apply(root, L0, R0, l, r, laz);
	}

	template <typename G>
	ll max_right(Ptr root, ll L, G check) {
		assert(root && L0 <= L && L <= R0 && check(MX::I()));
		X sum = MX::I();
		return _max_right(root, check, L0, R0, L, sum);
	}

	template <typename G>
	ll min_left(Ptr root, ll R, G check) {
		assert(root && L0 <= R && R <= R0 && check(MX::I()));
		X sum = MX::I();
		return _min_left(root, check, L0, R0, R, sum);
	}

	// memo(idx, val)
	template <typename MEMO>
	void enumerate(Ptr root, MEMO memo) {
		auto dfs = [&](auto &dfs, Ptr u, ll l, ll r, A laz) -> void {
			if (!u) return;
			if (r - l == 1) {
				memo(l, AM::O(u->sum, laz, 1));
				return;
			}
			ll m = (l + r) / 2;
			laz = MA::O(u->laz, laz);
			dfs(dfs, u->l, l, m, laz);
			dfs(dfs, u->r, m, r, laz);
		};
		dfs(dfs, root, L0, R0, MA::I());
	}

	// u[l:r) を apply(v[l:r), laz) で上書きしたものを返す
	Ptr copy_interval(Ptr u, Ptr v, ll l, ll r, A laz = MA::I()) {
		static_assert(PERSISTENT);
		if (u == v) return u;
		u = clone(u);
		_copy_interval(u, v, L0, R0, l, r, laz);
		return u;
	}

	private:
	Ptr new_root() { return my_new(L0, R0); }

	Ptr my_new(const X sum) {
		Ptr u = pool.create();
		u->l = u->r = nullptr;
		u->sum = sum, u->laz = MA::I();
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
		if (u->laz == MA::I()) return;
		u->l = (u->l ? clone(u->l) : my_new(l, m));
		u->r = (u->r ? clone(u->r) : my_new(m, r));
		u->l->sum = AM::O(u->l->sum, u->laz, m - l);
		u->r->sum = AM::O(u->r->sum, u->laz, r - m);
		u->l->laz = MA::O(u->l->laz, u->laz);
		u->r->laz = MA::O(u->r->laz, u->laz);
		u->laz = MA::I();
	}

	void _copy_interval(Ptr u, Ptr v, ll l, ll r, ll ql, ll qr, A laz) {
		// u[ql, qr) <- apply(v[ql, qr), laz)
		// u is already updated
		assert(u);
		ql = std::max(ql, l);
		qr = std::min(qr, r);
		if (ql >= qr) return;
		if (l == ql && r == qr) { // terminus
			if (v) {
				u->sum = AM::O(v->sum, laz, r - l);
				u->laz = MA::O(v->laz, laz);
				u->l = v->l, u->r = v->r;
			}
			else {
				u->sum = AM::O(init(l, r), laz, r - l);
				u->laz = laz;
				u->l = nullptr, u->r = nullptr;
			}
			return;
		}
		// push
		ll m = (l + r) / 2;
		u->l = (u->l ? clone(u->l) : my_new());
		u->r = (u->r ? clone(u->r) : my_new());
		u->l->sum = AM::O(u->l->sum, u->laz, m - l);
		u->l->laz = MA::O(u->l->laz, u->laz);
		u->r->sum = AM::O(u->r->sum, u->laz, r - m);
		u->r->laz = MA::O(u->r->laz, u->laz);
		u->laz = MA::I();
		if (v) laz = MA::O(v->laz, laz);
		_copy_interval(u->l, (v && v->l ? v->l : nullptr), l, m, ql, qr, laz);
		_copy_interval(u->r, (v && v->r ? v->r : nullptr), m, r, ql, qr, laz);
		u->sum = MX::O(u->l->sum, u->r->sum);
	}

	template <typename T>
	Ptr my_new(const std::vector<T> &dat) {
		assert(L0 == 0 && R0 == dat.size());
		auto dfs = [&](auto &dfs, ll l, ll r) -> Ptr {
			if (l == r) return nullptr;
			if (r == l + 1) return my_new(X(dat[l]));
			ll m = (l + r) / 2;
			Ptr l_root = dfs(dfs, l, m), r_root = dfs(dfs, m, r);
			X sum = MX::O(l_root->sum, r_root->sum);
			Ptr cur_root = my_new(sum);
			cur_root->l = l_root, cur_root->r = r_root;
			return cur_root;
		};
		return dfs(dfs, 0, dat.size());
	}

	Ptr _set_val(Ptr u, ll l, ll r, ll i, const X &sum) {
		if (r == l + 1) {
			u = clone(u);
			u->sum = sum;
			u->laz = MA::I();
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
		u->sum = MX::O(u->l->sum, u->r->sum);
		return u;
	}

	Ptr _multiply(Ptr u, ll l, ll r, ll i, const X &sum) {
		if (r == l + 1) {
			u = clone(u);
			u->sum = MX::O(u->sum, sum);
			u->laz = MA::I();
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
		u->sum = MX::O(u->l->sum, u->r->sum);
		return u;
	}

	void _prod(Ptr u, ll l, ll r, ll ql, ll qr, X &sum, A laz) {
		ql = std::max(ql, l);
		qr = std::min(qr, r);
		if (ql >= qr) return;
		if (!u) {
			sum = MX::O(sum, AM::O(init(ql, qr), laz, qr - ql));
			return;
		}
		if (l == ql && r == qr) {
			sum = MX::O(sum, AM::O(u->sum, laz, qr - ql));
			return;
		}
		ll m = (l + r) / 2;
		laz = MA::O(u->laz, laz);
		_prod(u->l, l, m, ql, qr, sum, laz);
		_prod(u->r, m, r, ql, qr, sum, laz);
	}

	Ptr _apply(Ptr u, ll l, ll r, ll ql, ll qr, const A &laz) {
		if (!u) u = my_new(l, r);
		ql = std::max(ql, l);
		qr = std::min(qr, r);
		if (ql >= qr) return u;
		if (l == ql && r == qr) {
			u = clone(u);
			u->sum = AM::O(u->sum, laz, qr - ql);
			u->laz = MA::O(u->laz, laz);
			return u;
		}
		push(u, l, r);
		ll m = (l + r) / 2;
		u = clone(u);
		u->l = _apply(u->l, l, m, ql, qr, laz);
		u->r = _apply(u->r, m, r, ql, qr, laz);
		u->sum = MX::O(u->l->sum, u->r->sum);
		return u;
	}

	template <typename G>
	ll _max_right(Ptr u, const G &check, ll l, ll r, ll ql, X &sum) {
		if (r <= ql) return r;
		if (!u) u = my_new(l, r);
		ql = std::max(ql, l);
		if (l == ql && check(MX::O(sum, u->sum))) {
			sum = MX::O(sum, u->sum);
			return r;
		}
		if (r == l + 1) return l;
		push(u, l, r);
		ll m = (l + r) / 2;
		ll k = _max_right(u->l, check, l, m, ql, sum);
		if (k < m) return k;
		return _max_right(u->r, check, m, r, ql, sum);
	}

	template <typename G>
	ll _min_left(Ptr u, const G &check, ll l, ll r, ll qr, X &sum) {
		if (qr <= l) return l;
		if (!u) u = my_new(l, r);
		qr = std::min(qr, r);
		if (r == qr && check(MX::O(u->sum, sum))) {
			sum = MX::O(u->sum, sum);
			return l;
		}
		if (r == l + 1) return r;
		push(u, l, r);
		ll m = (l + r) / 2;
		ll k = _min_left(u->r, check, m, r, qr, sum);
		if (m < k) return k;
		return _min_left(u->l, check, l, m, qr, sum);
	}

	void _get_laz(Ptr u, ll l, ll r, ll i, A &laz) {
		if (!u) return;
		laz = MA::O(u->laz, laz);
		if (r == l + 1) return;
		ll m = (l + r) / 2;
		if (i < m) return _get_laz(u->l, l, m, i, laz);
		_get_laz(u->r, m, r, i, laz);
	}
};
