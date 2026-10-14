#pragma once
#include <vector>
#include <cassert>

template <typename ActedMonoid>
struct LazySegmentTree {
	using MX = typename ActedMonoid::Monoid_X;
	using MA = typename ActedMonoid::Monoid_A;
	using X = typename MX::value_type;
	using A = typename MA::value_type;
	int N, LOG, size;
	std::vector<X> dat;
	std::vector<A> laz;
	std::vector<bool> has_laz;

	LazySegmentTree() {}
	LazySegmentTree(int N) { build(N); }
	template <typename F>
	LazySegmentTree(int N, F init) { build(N, init); }
	template <std::ranges::input_range R>
	LazySegmentTree(const R& v) { build(v); }

	void build(int m) {
		build(m, [](int i) -> X { return MX::I(); });
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
		dat.assign(size << 1, MX::I());
		laz.assign(size, MA::I());
		has_laz.assign(size, false);
		for (int i = 0; i < N; i++) dat[size + i] = init(i);
		for (int i = size - 1; i >= 1; i--) update(i);
	}

	void update(int k) { dat[k] = MX::O(dat[2 * k], dat[2 * k + 1]); }
	void set(int p, X x) {
		assert(0 <= p && p < N);
		p += size;
		for (int i = LOG; i >= 1; i--) push(p >> i);
		dat[p] = x;
		for (int i = 1; i <= LOG; i++) update(p >> i);
	}
	void multiply(int p, const X& x) {
		assert(0 <= p && p < N);
		p += size;
		for (int i = LOG; i >= 1; i--) push(p >> i);
		dat[p] = MX::O(dat[p], x);
		for (int i = 1; i <= LOG; i++) update(p >> i);
	}

	X get(int p) {
		assert(0 <= p && p < N);
		p += size;
		for (int i = LOG; i >= 1; i--) push(p >> i);
		return dat[p];
	}

	std::vector<X> get() {
		for (int k = 0; k < size; k++) push(k);
		return {dat.begin() + size, dat.begin() + size + N};
	}

	X prod(int l, int r) {
		assert(0 <= l && l <= r && r <= N);
		if (l == r) return MX::I();
		l += size, r += size;
		for (int i = LOG; i >= 1; i--) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push((r - 1) >> i);
		}
		X xl = MX::I(), xr = MX::I();
		while (l < r) {
			if (l & 1) xl = MX::O(xl, dat[l++]);
			if (r & 1) xr = MX::O(dat[--r], xr);
			l >>= 1, r >>= 1;
		}
		return MX::O(xl, xr);
	}

	X prod() { return dat[1]; }
	template <typename... Args>
	X operator()(Args... args) { return prod(args...); }
	template <typename... Args>
	X operator[](Args... args) { return get(args...); }

	void apply(int l, int r, A a) {
		assert(0 <= l && l <= r && r <= N);
		if (l == r) return;
		l += size, r += size;
		for (int i = LOG; i >= 1; i--) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push((r - 1) >> i);
		}
		int l2 = l, r2 = r;
		while (l < r) {
			if (l & 1) apply_at(l++, a);
			if (r & 1) apply_at(--r, a);
			l >>= 1, r >>= 1;
		}
		l = l2, r = r2;
		for (int i = 1; i <= LOG; i++) {
			if (((l >> i) << i) != l) update(l >> i);
			if (((r >> i) << i) != r) update((r - 1) >> i);
		}
	}

	template <typename F>
	int max_right(int l, const F check) {
		assert(0 <= l && l <= N);
		assert(check(MX::I()));
		if (l == N) return N;
		l += size;
		for (int i = LOG; i >= 1; i--) push(l >> i);
		X sm = MX::I();
		do {
			while (l % 2 == 0) l >>= 1;
			if (!check(MX::O(sm, dat[l]))) {
				while (l < size) {
					push(l);
					l = (2 * l);
					if (check(MX::O(sm, dat[l]))) {
						sm = MX::O(sm, dat[l++]);
					}
				}
				return l - size;
			}
			sm = MX::O(sm, dat[l++]);
		} while ((l & -l) != l);
		return N;
	}

	template <typename F>
	int min_left(int r, const F check) {
		assert(0 <= r && r <= N);
		assert(check(MX::I()));
		if (r == 0) return 0;
		r += size;
		for (int i = LOG; i >= 1; i--) push((r - 1) >> i);
		X sm = MX::I();
		do {
			r--;
			while (r > 1 && (r % 2)) r >>= 1;
			if (!check(MX::O(dat[r], sm))) {
				while (r < size) {
					push(r);
					r = (2 * r + 1);
					if (check(MX::O(dat[r], sm))) {
						sm = MX::O(dat[r--], sm);
					}
				}
				return r + 1 - size;
			}
			sm = MX::O(dat[r], sm);
		} while ((r & -r) != r);
		return 0;
	}

	// l <= i xor (xor_val) < r となる i 全体に apply
	void apply_xor_range(int l, int r, int xor_val, A a) {
		assert(!(N & (N - 1)));
		assert(0 <= xor_val && xor_val < N);
		assert(0 <= l && l <= r && r <= N);

		auto dfs = [&](auto& dfs, int idx, int seg_l, int seg_r) -> void {
			if (l <= seg_l && seg_r <= r) {
				return apply_at(idx, a);
			}
			if (r <= seg_l || seg_r <= l) return;
			push(idx);
			int seg_m = (seg_l + seg_r) / 2;
			int bit = (seg_r - seg_l) / 2;
			int left = 2 * idx + 0, right = 2 * idx + 1;
			if (xor_val & bit) std::swap(left, right);
			dfs(dfs, left, seg_l, seg_m);
			dfs(dfs, right, seg_m, seg_r);
			update(idx);
		};
		dfs(dfs, 1, 0, N);
	}

	private:
	inline int msb(const int &a) { return a ? 31 - __builtin_clz(a) : -1; }
	void apply_at(int k, A a) {
		long long sz = 1 << (LOG - msb(k));
		dat[k] = ActedMonoid::O(dat[k], a, sz);
		if (k < size) has_laz[k] = 1, laz[k] = MA::O(laz[k], a);
	}
	void push(int k) {
		if (!has_laz[k]) return;
		has_laz[k] = 0;
		apply_at(2 * k, laz[k]), apply_at(2 * k + 1, laz[k]);
		laz[k] = MA::I();
	}
};
