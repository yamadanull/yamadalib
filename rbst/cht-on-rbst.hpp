#pragma once

#include "rbst.hpp"

// PNT: 点の型
template <typename PNT, bool LOWER = true>
struct CHTonRBST : RBST<pair<PNT, PNT>> {
	using typename RBST<pair<PNT, PNT>>::Ptr;
	using T = typename PNT::T;

	void insert(Ptr &root, PNT A, T INF) {
		auto [p, q] = this->split_max_right(root, [&](Ptr p) { return p->key.first.x < A.x; });
		if(p && q){
			auto L = this->kth_element(p, p->cnt - 1)->key.first;
			auto R = this->kth_element(q, 0)->key.first;
			if (cross(A - L, R - A) * (LOWER ? 1 : -1) <= 0){
				root = this->merge(p, q);
				return;
			}
		}

		while (q) {
			auto top = this->kth_element(q, 0);
			auto [B, C] = top->key;
			if (cross(B - A, C - B) * (LOWER ? 1 : -1) <= 0) this->erase(q, 0); // A==Bもこれで削除できる
			else break;
		}

		while (p && p->cnt >= 2) {
			auto top = this->kth_element(p, p->cnt - 2);
			auto [C, B] = top->key;
			if (cross(B - C, A - B) * (LOWER ? 1 : -1) <= 0) this->erase(p, p->cnt - 1);
			else break;
		}

		Point R = (q ? this->kth_element(q, 0)->key.first : Point(A.x + 1, INF));
		auto r = this->my_new(make_pair(A, R));
		if (p) {
			auto top = this->kth_element(p, p->cnt-1);
			top->key.second = A;
		}
		root = this->merge(this->merge(p, r), q);
	}
};
