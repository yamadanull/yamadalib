#pragma once

#include "rbst-base.hpp"

namespace RBST{

template <typename T, typename E>
struct LazyReversibleRBSTNode {
	typename RBSTBase<LazyReversibleRBSTNode>::Ptr l, r;
	T key, sum; // 頂点内のlaz, rev反映済
	E laz;
	int cnt;
	bool rev;

	LazyReversibleRBSTNode(const T &t = T(), const E &e = E())
		: l(), r(), key(t), sum(t), laz(e), cnt(1), rev(false) {}
};

template <typename T, typename E, T (*f)(T, T), T (*g)(T, E), E (*h)(E, E),
		 T (*ti)(), E (*ei)(), T (*ts)(T), bool PERSISTENT = false>
struct LazyReversibleRBST : RBSTBase<LazyReversibleRBSTNode<T, E>> {
	using Node = LazyReversibleRBSTNode<T, E>;
	using base = RBSTBase<LazyReversibleRBSTNode<T, E>>;
	using base::merge;
	using base::split;
	using base::merge3;
	using base::split3;
	using base::clone;
	using base::count;
	using base::extract;
	using typename base::Ptr;

	LazyReversibleRBST() = default;

	// doesn't use "split" in case PERSISTENT
	T fold(Ptr root, int L, int R, bool rev = false) { // DO NOT TOUCH "rev"
		assert(root);
		assert(0 <= L && L <= R && R <= root->cnt);
		if (L == 0 && R == root->cnt) return root->sum;
		Ptr l_ptr = (rev ? root->r : root->l);
		Ptr r_ptr = (rev ? root->l : root->r);
		int l_siz = count(l_ptr);
		T ans = ti();
		if (L < l_siz) { // see Left
			T bns = fold(l_ptr, L, std::min(R, l_siz), rev ^ root->rev);
			ans = f(ans, g(bns, root->laz));
		}
		if (L <= l_siz && l_siz < R) ans = f(ans, root->key); // see here
		int offset = l_siz + 1;
		if (offset < R) { // see Right
			T bns = fold(r_ptr, std::max(offset, L) - offset, R - offset, rev ^ root->rev);
			ans = f(ans, g(bns, root->laz));
		}
		return ans;
	}
	T fold(Ptr root) { return (root ? root->sum : ti()); }

	T get_val(Ptr root, int k, bool rev = false, E laz = ei()) { // DO NOT TOUCH "rev" or "laz"
		Ptr l_ptr = (rev ? root->r : root->l);
		Ptr r_ptr = (rev ? root->l : root->r);
		int l_siz = count(l_ptr);
		if (k == l_siz) return g(root->key, laz); // k is here
		laz = h(root->laz, laz);
		rev ^= root->rev;
		if (k < l_siz) return get_val(l_ptr, k, rev, laz); // k is in Left
		return get_val(r_ptr, k - (l_siz + 1), rev, laz); // k is in Right
	}

	std::vector<T> get_all(Ptr root) {
		std::vector<T> ans;
		auto dfs = [&](auto &dfs, Ptr root, bool rev, E laz) -> void {
			if (!root) return;
			T bns = g(root->key, laz);
			laz = h(root->laz, laz);
			dfs(dfs, (rev ? root->r : root->l), rev ^ root->rev, laz); // go Left
			ans.eb(bns);
			dfs(dfs, (rev ? root->l : root->r), rev ^ root->rev, laz); // go Right
		};
		dfs(dfs, root, 0, ei());
		return ans;
	}

	// doesn't use "split" in case PERSISTENT
	Ptr apply(Ptr root, int L, int R, const E laz) {
		assert(root);
		assert(0 <= L && L <= R && R <= root->cnt);
		push(root);
		root = clone(root);
		if (L == 0 && R == root->cnt) { // apply all
			root->key = g(root->key, laz);
			root->sum = g(root->sum, laz);
			root->laz = laz;
			return root;
		}
		int l_siz = count(root->l);
		if (L < l_siz) root->l = apply(root->l, L, std::min(R, l_siz), laz); // need to see Left
		if (L <= l_siz && l_siz < R) root->key = g(root->key, laz); // apply here
		int offset = l_siz + 1;
		if (offset < R) root->r = apply(root->r, std::max(0, L - offset), R - offset, laz); // need to see Right
		return update(root);
	}
	Ptr apply(Ptr root, const E laz) {
		if (!root) return nullptr;
		return apply(root, 0, root->cnt, laz);
	}

	Ptr set_val(Ptr root, int k, const T &val) {
		if (!root) return root;
		push(root);
		int l_siz = count(root->l);
		if (k < l_siz) { // k is in Left
			root = clone(root);
			root->l = set_val(root->l, k, val);
			return update(root);
		}
		else if (k == l_siz) { // k is here
			root = clone(root);
			root->key = val;
			return update(root);
		}
		else { // k is in Right
			root = clone(root);
			root->r = set_val(root->r, k - (l_siz + 1), val);
			return update(root);
		}
	}

	Ptr reverse(Ptr root, int L, int R) {
		assert(root);
		assert(0 <= L && L <= R && R <= root->cnt);
		if (R - L <= 1) return root;
		auto [x, y, z] = split3(root, L, R);
		y->rev ^= 1;
		y->sum = ts(y->sum);
		std::swap(y->l, y->r);
		return merge3(x, y, z);
	}

	Ptr multiply(Ptr root, int k, const T &val) {
		if (!root) return root;
		push(root);
		int l_siz = count(root->l);
		root = clone(root);
		if (k < l_siz) { // k is in Left
			root->l = multiply(root->l, k, val);
			return update(root);
		}
		else if (k == l_siz) { // k is here
			root->key = f(root->key, val);
			return update(root);
		}
		else { // k is in Right
			root->r = multiply(root->r, k - (l_siz + 1), val);
			return update(root);
		}
	}

	// u[L:R) <- apply(v[L:R), laz)
	Ptr copy_interval(Ptr u, Ptr v, int L, int R, E laz = ei()) {
		assert(PERSISTENT);
		assert(u); assert(v);
		Ptr m = extract(v, L, R);
		propagate(m, laz);
		return merge3(extract(u, 0, L), m, extract(u, R, u->cnt));
	}

	inline T sum(const Ptr t) const { return t ? t->sum : ti(); }

	Ptr update(Ptr t) override { // doesn't change tree shape
		push(t);
		t->cnt = 1;
		t->sum = t->key;
		if (t->l) t->cnt += t->l->cnt, t->sum = f(t->l->sum, t->sum);
		if (t->r) t->cnt += t->r->cnt, t->sum = f(t->sum, t->r->sum);
		return t;
	}

	void push(Ptr t) override { // only copy child
		if (t->rev || t->laz != ei()) t->l = clone(t->l), t->r = clone(t->r);
		if (t->rev) {
			toggle(t->l);
			toggle(t->r);
			t->rev = false;
		}
		if (t->laz != ei()) {
			propagate(t->l, t->laz);
			propagate(t->r, t->laz);
			t->laz = ei();
		}
	}

	Ptr clone(Ptr n) override {
		if constexpr (!PERSISTENT) return n;
		if (!n) return n;
		return base::pool.clone(n);
	}

	void toggle(Ptr t) {
		if (!t) return;
		swap(t->l, t->r);
		t->sum = ts(t->sum);
		t->rev ^= true;
	}

	void propagate(Ptr t, const E &laz) {
		if (!t) return;
		t->laz = h(t->laz, laz);
		t->key = g(t->key, laz);
		t->sum = g(t->sum, laz);
	}
};

template <typename T>
T g(T l, bool) { return l; }
bool h(bool, bool) { return false; }
bool ei() { return false; }

template <typename T, T (*f)(T, T), T (*ti)(), T (*ts)(T), bool PERSISTENT = false>
using ReversibleRBSTSum = LazyReversibleRBST<T, bool, f, g, h, ti, ei, ts, PERSISTENT>;

}  // namespace RBST

using RBST::LazyReversibleRBST;
using RBST::ReversibleRBSTSum;
