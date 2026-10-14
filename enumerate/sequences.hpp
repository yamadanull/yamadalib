#pragma once

// f(vector<int>)
// 長さN、要素が[L,R)の単調増加数列を列挙
// ベル数
template <typename F>
void LengthFixedSequences(int N, bool strict, int L, int R, F f) {
	vector<int> cur(N);
	int cur_i = 0;
	auto dfs = [&](auto&& self, int l)->void{
		if (cur_i == N) { f(cur); return; }

		for (int i = l; i < R; i++) {
			cur[cur_i++] = i;
			self(self, i + (int)strict);
			--cur_i;
		}
	}; dfs(dfs, L);
}

// f(vector<int>)
// sumの分割を列挙 引数の各区間は閉区間
// MONOTONE = 0 : 重複組み合わせ
// MONOTONE = 1 : 分割数
template <bool MONOTONE, typename F>
void SumFixedSequences(int sum, int len_min, int len_max, int val_L, int val_R, F f) {
	assert(val_L > 0);
	vector<int> cur;
	auto dfs = [&](auto&& self, int rem, int lim)->void{
		if (rem == 0) { f(cur); return; }
		if ((int)cur.size() == len_max) return;

		int l = max(val_L, (rem + len_max - (int)cur.size() - 1) / (len_max - (int)cur.size()));
		int r = min(rem, lim);
		if ((int)cur.size() + 1 < len_min) {
			int nr = rem - (len_min - (int)cur.size() - 1) * val_L;
			r = min(r, nr);
		}
		for (int i = l; i <= r; i++) {
			cur.emplace_back(i);
			self(self, rem - i, (MONOTONE ? i : val_R));
			cur.pop_back();
		}
	}; dfs(dfs, sum, val_R);
}
template <bool MONOTONE, typename F>
void SumFixedSequences(int sum, int len_min, int len_max, F f) {
	return SumFixedSequences<MONOTONE>(sum, len_min, len_max, 1, 1e9, f);
}
template <bool MONOTONE, typename F>
void SumFixedSequences(int sum, F f) {
	return SumFixedSequences<MONOTONE>(sum, 1, 1e9, f);
}
