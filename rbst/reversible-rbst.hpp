#pragma once

#include "../lct/reversible-bbst-base.hpp"
#include "rbst-base.hpp"

template <typename T>
struct ReversibleRBSTNode {
	using Ptr = ReversibleRBSTNode *;
	Ptr l, r, p;
	T key, sum;
	int cnt;
	bool rev;

	ReversibleRBSTNode(const T &t = T())
		: l(), r(), p(), key(t), sum(t), cnt(1), rev(false) {}
};

template <typename T, T (*f)(T, T), T (*ts)(T)>
struct ReversibleRBST : ReversibleBBST<RBSTBase<ReversibleRBSTNode<T>>, ReversibleRBSTNode<T>, T, f, ts> {
	using Node = ReversibleRBSTNode<T>;
};

/**
 * @brief 反転可能Splay Tree
 */
