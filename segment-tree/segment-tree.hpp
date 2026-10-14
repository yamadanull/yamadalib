#pragma once
#include <algorithm>
#include <cassert>
#include <vector>

template <typename Monoid>
struct SegmentTree {
	using X = typename Monoid::value_type;
	std::vector<X> dat;
	int N, LOG, size;

	SegmentTree() {}
	SegmentTree(int N) { build(N); }
	template <typename F>
	SegmentTree(int N, F init) { build(N, init); }
	template <std::ranges::input_range R>
	SegmentTree(const R& v) { build(v); }

	void build(int m) {
		build(m, [](int i) -> X { return Monoid::I(); });
	}
	template <std::ranges::input_range R>
	void build(const R& v) {
		build(v.size(), [&](int i) -> X { return v[i]; });
	}
	template <typename F>
	void build(int m, F init) {
		N = m, LOG = 1;
		while ((1 << LOG) < N) ++LOG;
		size = 1 << LOG;
		dat.assign(size << 1, Monoid::I());
		for (int i = 0; i < N; i++) dat[size + i] = init(i);
		for (int i = size - 1; i >= 1; i--) update(i);
	}

	X get(int i) const { return dat[size + i]; }
	std::vector<X> get() const { return {dat.begin() + size, dat.begin() + size + N}; }

	void update(int i) { dat[i] = Monoid::O(dat[2 * i], dat[2 * i + 1]); }
	void set(int i, const X x) {
		assert(i < N);
		dat[i += size] = x;
		while (i >>= 1) update(i);
	}

	void multiply(int i, const X x) {
		assert(i < N);
		i += size;
		dat[i] = Monoid::O(dat[i], x);
		while (i >>= 1) update(i);
	}

	X prod(int L, int R) const {
		assert(0 <= L && L <= R && R <= N);
		X vl = Monoid::I(), vr = Monoid::I();
		L += size, R += size;
		while (L < R) {
			if (L & 1) vl = Monoid::O(vl, dat[L++]);
			if (R & 1) vr = Monoid::O(dat[--R], vr);
			L >>= 1, R >>= 1;
		}
		return Monoid::O(vl, vr);
	}

	std::vector<int> prod_ids(int L, int R) const {
		assert(0 <= L && L <= R && R <= N);
		std::vector<int> I, J;
		L += size, R += size;
		while (L < R) {
			if (L & 1) I.emplace_back(L++);
			if (R & 1) J.emplace_back(--R);
			L >>= 1, R >>= 1;
		}
		std::ranges::reverse(J);
		I.resize(I.size() + J.size());
		for (int j = 0; j < (int)J.size(); j++) I[(int)I.size() - (int)J.size() + j] = J[j];
		return I;
	}

	X prod() const { return dat[1]; }
	template <typename... Args>
	X operator()(Args... args) { return prod(args...); }
	template <typename... Args>
	X operator[](Args... args) { return get(args...); }

	template <typename F>
	int max_right(int L, F check) const {
		assert(0 <= L && L <= N && check(Monoid::I()));
		if (L == N) return N;
		L += size;
		X sm = Monoid::I();
		do {
			while (L % 2 == 0) L >>= 1;
			if (!check(Monoid::O(sm, dat[L]))) {
				while (L < size) {
					L = 2 * L;
					if (check(Monoid::O(sm, dat[L]))) {
						sm = Monoid::O(sm, dat[L++]);
					}
				}
				return L - size;
			}
			sm = Monoid::O(sm, dat[L++]);
		} while ((L & -L) != L);
		return N;
	}

	template <typename F>
	int min_left(int R, F check) const {
		assert(0 <= R && R <= N && check(Monoid::I()));
		if (R == 0) return 0;
		R += size;
		X sm = Monoid::I();
		do {
			--R;
			while (R > 1 && (R % 2)) R >>= 1;
			if (!check(Monoid::O(dat[R], sm))) {
				while (R < size) {
					R = 2 * R + 1;
					if (check(Monoid::O(dat[R], sm))) {
						sm = Monoid::O(dat[R--], sm);
					}
				}
				return R + 1 - size;
			}
			sm = Monoid::O(dat[R], sm);
		} while ((R & -R) != R);
		return 0;
	}

	// prod_{l<=i<r} A[i xor x]
	X xor_prod(int l, int r, int xor_val) const {
		static_assert(Monoid::COMMUTATIVE);
		X x = Monoid::I();
		for (int k = 0; k < LOG + 1; ++k) {
			if (l >= r) break;
			if (l & 1) {
				x = Monoid::O(x, dat[(size >> k) + ((l++) ^ xor_val)]);
			}
			if (r & 1) {
				x = Monoid::O(x, dat[(size >> k) + ((--r) ^ xor_val)]);
			}
			l /= 2, r /= 2, xor_val /= 2;
		}
		return x;
	}
};
