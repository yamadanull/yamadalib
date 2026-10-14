#pragma once

#include "wavelet-matrix.hpp"

template <typename T, typename sum_T = T, const int LOG = 30>
struct WaveletMatrixSum : WaveletMatrix<T, LOG> {
	using u32 = int32_t;
	array<vector<sum_T>, LOG> sums;
	vector<sum_T> acc;
	using WM = WaveletMatrix<T, LOG>;
	using WM::A;
	using WM::bv;
	using WM::N;
	using WM::WaveletMatrix;
	void build() = delete;

	WaveletMatrixSum(const vector<T> &_a) : acc(_a.size() + 1) {
		N = _a.size();
		A = _a;
		build2();
		for (int i = 0; i < N; i++) acc[i + 1] = acc[i] + A[i];
	}

	__attribute__((optimize("O3"))) void build2() {
		for (int i = 0; i < LOG; i++) bv[i] = bit_vector(N), sums[i].assign(N + 1, sum_T());
		vector<T> cur = A, nxt(N);
		for (int h = LOG - 1; h >= 0; --h) {
			for (int i = 0; i < N; ++i) if ((cur[i] >> h) & 1) bv[h].set(i);
			bv[h].build();
			array<decltype(begin(nxt)), 2> it{begin(nxt), begin(nxt) + bv[h].zeros};
			for (int i = 0; i < N; ++i) *it[bv[h].get(i)]++ = cur[i];
			swap(cur, nxt);
			for (int i = 0; i < N; i++) sums[h][i + 1] = sums[h][i] + cur[i];
		}
	}

	sum_T bottom_k_sum(int l, int r, int k) {
		sum_T ans = 0;
		for (int h = LOG - 1; h >= 0; --h) {
			u32 l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
			if (k < r0 - l0) {
				l = l0, r = r0;
			}
			else {
				ans += sums[h][r0] - sums[h][l0];
				k -= r0 - l0;
				l += bv[h].zeros - l0;
				r += bv[h].zeros - r0;
			}
		}
		ans += sums[0][l + k] - sums[0][l];
		return ans;
	}
	sum_T top_k_sum(int l, int r, int k) {
		return acc[r] - acc[l] - bottom_k_sum(l, r, r - l - k);
	}

	sum_T range_sum(int l, int r, T upper) {
		int c = WM::range_freq(l, r, upper);
		return bottom_k_sum(l, r, c);
	}

	sum_T range_sum(int l, int r, T lower, T upper) {
		return range_sum(l, r, upper) - range_sum(l, r, lower);
	}
};
