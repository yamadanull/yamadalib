#pragma once

template <typename F, typename block, int DIV>
struct SquareRootDecomposition {
	int N;
	vector<block> sq;
	F f;
	typename block::T ti;
	vector<pair<int, int>> idx;
	SquareRootDecomposition(int N_, F merge_, typename block::T _ti) : N(N_), sq(N / DIV + 1), f(merge_), ti(_ti) {
		for (int i = 0; i < (int)sq.size(); i++) sq[i].init(i);
		idx.resize(N + 1);
		for (int i = 0; i <= N; i++) idx[i] = make_pair(i / DIV, i % DIV);
	}

	void update(int l, int r, typename block::E x) {
		auto [Li, Lj] = idx[l];
		auto [Ri, Rj] = idx[r];
		if (Li == Ri) {
			sq[Li].update_part(Lj, Rj, x);
		}
		else {
			sq[Li].update_part(Lj, DIV, x);
			for (int i = Li + 1; i < Ri; i++) sq[i].update_all(x);
			sq[Ri].update_part(0, Rj, x);
		}
	}

	void update(int pos, typename block::E x) {
		auto [i, j] = idx[pos];
		sq[i].update(j, x);
	}

	typename block::T query(int l, int r) {
		auto [Li, Lj] = idx[l];
		auto [Ri, Rj] = idx[r];
		if (Li == Ri) return sq[Li].query_part(Lj, Rj);

		typename block::T ans = ti;
		ans = f(ans, sq[Li].query_part(Lj, DIV));
		for (int i = Li + 1; i < Ri; i++) ans = f(ans, sq[i].query_all());
		ans = f(ans, sq[Ri].query_part(0, Rj));
		return ans;
	}
};

/**
 * @brief 平方分割
 * @docs docs/data-structure/sqrt-dec.md
 */
