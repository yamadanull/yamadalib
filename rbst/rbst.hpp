#pragma once

#include "rbst-base.hpp"

template <typename T>
struct RBSTNode {
	typename RBSTBase<RBSTNode>::Ptr l, r;
	T key;
	int cnt;
	RBSTNode(const T &t = T()) : l(), r(), key(t), cnt(1) {}
};

template <typename T, bool PERSISTENT = false>
struct RBST : RBSTBase<RBSTNode<T>> {
	using base = RBSTBase<RBSTNode<T>>;
	using typename base::Ptr;

	protected:
	Ptr update(Ptr t) override {
		push(t);
		t->cnt = 1;
		if (t->l) t->cnt += t->l->cnt;
		if (t->r) t->cnt += t->r->cnt;
		return t;
	}
	void push(Ptr) override {}
	Ptr clone(Ptr p) override {
		if constexpr (!PERSISTENT) return p;
		if (!p) return p;
		return base::pool.clone(p);
	}
};
