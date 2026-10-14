#pragma once

#include "orderedmap-base.hpp"

template <typename T, bool multi = false>
struct SetNode {
	using Ptr = typename RBSTBase<SetNode>::Ptr;
	Ptr l, r;
	T key;
	int cnt;

	SetNode(const T& k = T()) : l(), r(), key(k), cnt(1) {}
};

template <typename T, bool multi = false>
struct Set : MapBase<SetNode<T, multi>, multi> {
	using base = MapBase<SetNode<T, multi>, multi>;
	using Ptr = typename base::Ptr;

	Set() : base() {}

	// keysはソートされている必要があることに注意！
	Set(std::vector<T> &keys) {
		int N = keys.size();
		if (N == 0) {
			base();
			return;
		}

		std::vector<Ptr> ps(N);
		int idx = 0;
		auto dfs = [&](auto&& self, int pos)->void{
			if (N <= pos) return;
			int lpos = pos * 2 + 1;
			int rpos = pos * 2 + 2;
			self(self, lpos);
			ps[pos] = base::base::my_new(keys[idx]); ++idx;
			self(self, rpos);

			if (lpos < N) {
				ps[pos]->l = ps[lpos];
				ps[pos]->cnt += ps[lpos]->cnt;
			}
			if (rpos < N) {
				ps[pos]->r = ps[rpos];
				ps[pos]->cnt += ps[rpos]->cnt;
			}
		}; dfs(dfs, 0);

		base::root = ps[0];
	}

	void insert(T &key) { base::insert_key(key); }
};
