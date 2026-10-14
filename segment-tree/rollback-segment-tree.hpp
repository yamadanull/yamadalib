#pragma once

#include "../data-structure/rollback-array.hpp"

template <typename ActedMonoid>
struct RollbackLazySegmentTree {
	using MX = typename ActedMonoid::Monoid_X;
	using MA = typename ActedMonoid::Monoid_A;
	using X = typename MX::value_type;
	using A = typename MA::value_type;
	int N, LOG, size;
	RollbackArray<X> dat;
	RollbackArray<A> laz;

	RollbackLazySegmentTree() {}
	RollbackLazySegmentTree(int N) { build(N); }
	template <typename F>
	RollbackLazySegmentTree(int N, F init) { build(N, init); }
	template <typename T>
	RollbackLazySegmentTree(const std::vector<T>& v) { build(v); }

	void build(int m) {
		build(m, [](int) -> X { return MX::I(); });
	}
	template <typename T>
	void build(const std::vector<T>& v) {
		build(v.size(), [&](int i) -> X { return v[i]; });
	}
	template <typename F>
	void build(int m, F init) {
		N = m, LOG = 1;
		while ((1 << LOG) < N) ++LOG;
		size = 1 << LOG;
		dat = RollbackArray<X>(std::vector<X>(size << 1, MX::I()));
		laz = RollbackArray<A>(std::vector<A>(size, MA::I()));
		for (int i = 0; i < N; i++) dat.set(size + i, init(i));
		for (int i = size - 1; i >= 1; i--) update(i);
	}

	void update(int k) { dat.set(k, MX::O(dat.get(2 * k), dat.get(2 * k + 1))); }
	void set(int p, X x) {
		assert(0 <= p && p < N);
		p += size;
		for (int i = LOG; i >= 1; i--) push(p >> i);
		dat.set(p, x);
		for (int i = 1; i <= LOG; i++) update(p >> i);
	}
	void multiply(int p, const X& x) {
		assert(0 <= p && p < N);
		p += size;
		for (int i = LOG; i >= 1; i--) push(p >> i);
		dat.set(p, MX::O(dat.get(p), x));
		for (int i = 1; i <= LOG; i++) update(p >> i);
	}

	X get(int p) {
		assert(0 <= p && p < N);
		p += size;
		for (int i = LOG; i >= 1; i--) push(p >> i);
		return dat.get(p);
	}

	std::vector<X> get() {
		for (int k = 1; k < size; k++) push(k);
		auto tmp = dat.get_all();
		return {tmp.begin() + size, tmp.begin() + size + N};
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
			if (l & 1) xl = MX::O(xl, dat.get(l++));
			if (r & 1) xr = MX::O(dat.get(--r), xr);
			l >>= 1, r >>= 1;
		}
		return MX::O(xl, xr);
	}

	X prod() { return dat.get(1); }
	template <typename... Args>
	X operator()(Args... args) { return prod(args...); }

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
	int max_right(const F check, int l) {
		assert(0 <= l && l <= N);
		assert(check(MX::I()));
		if (l == N) return N;
		l += size;
		for (int i = LOG; i >= 1; i--) push(l >> i);
		X sm = MX::I();
		do {
			while (l % 2 == 0) l >>= 1;
			if (!check(MX::O(sm, dat.get(l)))) {
				while (l < size) {
					push(l);
					l = (2 * l);
					if (check(MX::O(sm, dat.get(l)))) {
						sm = MX::O(sm, dat.get(l++));
					}
				}
				return l - size;
			}
			sm = MX::O(sm, dat.get(l++));
		} while ((l & -l) != l);
		return N;
	}

	template <typename F>
	int min_left(const F check, int r) {
		assert(0 <= r && r <= N);
		assert(check(MX::I()));
		if (r == 0) return 0;
		r += size;
		for (int i = LOG; i >= 1; i--) push((r - 1) >> i);
		X sm = MX::I();
		do {
			r--;
			while (r > 1 && (r % 2)) r >>= 1;
			if (!check(MX::O(dat.get(r), sm))) {
				while (r < size) {
					push(r);
					r = (2 * r + 1);
					if (check(MX::O(dat.get(r), sm))) {
						sm = MX::O(dat.get(r--), sm);
					}
				}
				return r + 1 - size;
			}
			sm = MX::O(dat.get(r), sm);
		} while ((r & -r) != r);
		return 0;
	}

	pair<int, int> time() { return {dat.time(), laz.time()}; }
	void rollback(pair<int, int> t) { dat.rollback(t.fi), laz.rollback(t.se); }

	void push(int k) {
		if (laz.get(k) == MA::I()) return;
		apply_at(2 * k, laz.get(k)), apply_at(2 * k + 1, laz.get(k));
		laz.set(k, MA::I());
	}

	private:
	int topbit(int x) { return x == 0 ? -1 : 31 - __builtin_clz(x); }
	void apply_at(int k, A a) {
		long long sz = 1 << (LOG - topbit(k));
		dat.set(k, ActedMonoid::O(dat.get(k), a, sz));
		if (k < size) laz.set(k, MA::O(laz.get(k), a));
	}
};
