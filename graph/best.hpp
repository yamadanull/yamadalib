#pragma once

#include "../modulo/binomial.hpp"
#include "../matrix/matrix.hpp"
#include "../data-structure/union-find-fast.hpp"

// 有向オイラー閉路の数（辺ラベルあり）
// オイラーグラフでなくても大丈夫
// gは隣接行列
template <typename mint>
mint BEST(vector<vector<int>> g, Binomial<mint>& binom) {
	vector<int> cmp; // オイラーグラフ化に必要な頂点
	{
		const int N = g.size();
		vector<bool> fn(N);
		vector<int> indeg(N), oudeg(N);
		UnionFindFast uf(N);

		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) if(g[i][j] != 0) {
			uf.unite(i, j);
			indeg[j] += g[i][j];
			oudeg[i] += g[i][j];
			fn[i] = fn[j] = true;
		}
		for (int i = 0; i < N; i++) if(indeg[i] != oudeg[i]) return 0;
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
			if(!uf.same(i, j) && fn[i] && fn[j]) return 0;
		}
		for (int i = 0; i < N; i++) if (fn[i]) cmp.emplace_back(i);
		if (cmp.empty()) return 1;
		if (cmp.size() == 1) return binom.fac(g[cmp[0]][cmp[0]] - 1);
	}

	const int N = cmp.size();
	{ // gをオイラーグラフ化
		vector<vector<int>> G(N, vector<int>(N));
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
			G[i][j] = g[cmp[i]][cmp[j]];
		}
		g=G;
	}

	Matrix<mint> A(N);
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) if (i != j) {
		A[i][j] -= g[i][j];
		A[i][i] += g[i][j];
	}

	mint ans = A.cofactor(0, 0);
	for (int i = 0; i < N; i++) ans *= binom.fac(A[i][i].get() + g[i][i] - 1);
	return ans;
}
