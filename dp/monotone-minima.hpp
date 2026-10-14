#pragma once

#include <functional>
#include <vector>
using namespace std;

// NxM 行列がある
// m_i := argmin_j (A_{i,j}) が単調増加であるときに m_i を列挙する
// f(i, j, k) :
// A[i][j] と A[i][k] を比較 (j < k が保証されている)
// A[i][j] <= A[i][k] のとき true を返す関数を入れる (等号はどちらでもよい)
vector<int> monotone_minima(int N, int M, const function<bool(int, int, int)>& f) {
	vector<int> res(N);
	auto dfs = [&](auto rc, int L, int R, int l, int r) -> void {
		if (L == R) return;
		int i = (L + R) / 2;
		int m = l;
		for (int k = l + 1; k < r; k++) if (!f(i, m, k)) m = k;
		res[i] = m;
		rc(rc, L, i, l, m + 1);
		rc(rc, i + 1, R, m, r);
	};
	dfs(dfs, 0, N, 0, M);
	return res;
}

// NxM 行列がある
// m_i := argmin_j (A_{i,j}) が単調増加であるときに m_i を列挙する
// A(i, j) : A[i][j] を返す関数
template <typename T>
vector<int> monotone_minima(int N, int M, const function<T(int, int)>& A) {
	function<bool(int, int, int)> f = [&](int i, int j, int k) -> bool {
		return A(i, j) <= A(i, k);
	};
	return monotone_minima(N, M, f);
}
