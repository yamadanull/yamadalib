#pragma once

#include <immintrin.h>

struct bit_vector {
	using u32 = uint32_t;
	using i64 = int64_t;
	using u64 = uint64_t;

	static constexpr u32 w = 64;
	vector<u64> block;
	vector<u32> count;
	u32 N, zeros;

	inline u32 get(u32 i) const { return u32(block[i / w] >> (i % w)) & 1u; }
	inline void set(u32 i) { block[i / w] |= 1LL << (i % w); }

	bit_vector() {}
	bit_vector(int _N) { init(_N); }
	__attribute__((optimize("O3", "unroll-loops"))) void init(int _N) {
		N = zeros = _N;
		block.resize(N / w + 1, 0);
		count.resize(block.size(), 0);
	}

	__attribute__((target("popcnt"))) void build() {
		for (u32 i = 1; i < block.size(); ++i) count[i] = count[i - 1] + _mm_popcnt_u64(block[i - 1]);
		zeros = rank0(N);
	}

	inline u32 rank0(u32 i) const { return i - rank1(i); }
	__attribute__((target("bmi2,popcnt"))) inline u32 rank1(u32 i) const {
		return count[i / w] + _mm_popcnt_u64(_bzhi_u64(block[i / w], i % w));
	}
};

template <typename T, const int LOG = 30>
struct WaveletMatrix {
	using u32 = uint32_t;
	using i64 = int64_t;
	using u64 = uint64_t;

	int N;
	vector<T> A;
	array<bit_vector, LOG> bv;

	WaveletMatrix() = default;
	WaveletMatrix(u32 _N) : N(max<u32>(_N, 1)), A(N) {}
	WaveletMatrix(const vector<T> &_a) : N(_a.size()), A(_a) { build(); }

	__attribute__((optimize("O3"))) void build() {
		for (int i = 0; i < LOG; i++) bv[i] = bit_vector(N);
		vector<T> cur = A, nxt(N);
		for (int h = LOG - 1; h >= 0; --h) {
			for (int i = 0; i < N; ++i) if ((cur[i] >> h) & 1) bv[h].set(i);
			bv[h].build();
			array<decltype(begin(nxt)), 2> it{begin(nxt), begin(nxt) + bv[h].zeros};
			for (int i = 0; i < N; ++i) *it[bv[h].get(i)]++ = cur[i];
			swap(cur, nxt);
		}
		return;
	}

	void set(u32 i, const T &x) {
		assert(x >= 0);
		A[i] = x;
	}

	inline pair<u32, u32> succ0(int l, int r, int h) const {
		return make_pair(bv[h].rank0(l), bv[h].rank0(r));
	}

	inline pair<u32, u32> succ1(int l, int r, int h) const {
		u32 l0 = bv[h].rank0(l);
		u32 r0 = bv[h].rank0(r);
		u32 zeros = bv[h].zeros;
		return make_pair(l + zeros - l0, r + zeros - r0);
	}

	// return A[k]
	T access(u32 k) const {
		T ans = 0;
		for (int h = LOG - 1; h >= 0; --h) {
			u32 f = bv[h].get(k);
			ans |= f ? T(1) << h : 0;
			k = f ? bv[h].rank1(k) + bv[h].zeros : bv[h].rank0(k);
		}
		return ans;
	}

	// k-th (0-indexed) smallest number in A[l, r)
	T kth_smallest(u32 l, u32 r, u32 k) const {
		T ans = 0;
		for (int h = LOG - 1; h >= 0; --h) {
			u32 l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
			if (k < r0 - l0) l = l0, r = r0;
			else {
				k -= r0 - l0;
				ans |= (T)1 << h;
				l += bv[h].zeros - l0;
				r += bv[h].zeros - r0;
			}
		}
		return ans;
	}

	// k-th (0-indexed) largest number in A[l, r)
	T kth_largest(int l, int r, int k) { return kth_smallest(l, r, r - l - k - 1); }

	// count i s.t. (l <= i < r) && (v[i] < upper)
	int range_freq(int l, int r, T upper) {
		if (upper >= (T(1) << LOG)) return r - l;
		int ans = 0;
		for (int h = LOG - 1; h >= 0; --h) {
			bool f = (upper >> h) & 1;
			u32 l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
			if (f) {
				ans += r0 - l0;
				l += bv[h].zeros - l0;
				r += bv[h].zeros - r0;
			}
			else {
				l = l0;
				r = r0;
			}
		}
		return ans;
	}

	int range_freq(int l, int r, T lower, T upper) {
		return range_freq(l, r, upper) - range_freq(l, r, lower);
	}

	// max v[i] s.t. (l <= i < r) && (v[i] < upper)
	T prev_value(int l, int r, T upper) {
		int cnt = range_freq(l, r, upper);
		return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
	}

	// min v[i] s.t. (l <= i < r) && (lower <= v[i])
	T next_value(int l, int r, T lower) {
		int cnt = range_freq(l, r, lower);
		return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
	}
};
