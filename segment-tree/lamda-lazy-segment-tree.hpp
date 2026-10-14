#pragma once

// LazySegmentTree
template <typename T, typename E, typename F, typename G, typename H>
struct LazySegmentTree {
	int width, height;
	F f;
	G g;
	H h;
	T ti;
	E ei;
	vector<T> dat; // datはlazに作用されてない
	vector<E> laz;
	LazySegmentTree(int _n, F _f, G _g, H _h, T _ti, E _ei)
		: f(_f), g(_g), h(_h), ti(_ti), ei(_ei) { init(_n); }
	LazySegmentTree(const vector<T> &v, F _f, G _g, H _h, T _ti, E _ei)
		: f(_f), g(_g), h(_h), ti(_ti), ei(_ei) { init((int)v.size()); build(v); }

	void init(int _n) {
		width = 1;
		height = 0;
		while (width < _n) width <<= 1, height++;
		dat.assign(2 * width, ti);
		laz.assign(2 * width, ei);
	}
	void build(const vector<T> &v) {
		int _n = v.size();
		init(_n);
		for (int i = 0; i < _n; i++) dat[width + i] = v[i];
		for (int i = width - 1; i; i--)
			dat[i] = f(dat[(i << 1) | 0], dat[(i << 1) | 1]);
	}
	inline T reflected(int k) { return laz[k] == ei ? dat[k] : g(dat[k], laz[k]); }
	inline void push(int k) {
		if (laz[k] == ei) return;
		laz[(k << 1) | 0] = h(laz[(k << 1) | 0], laz[k]);
		laz[(k << 1) | 1] = h(laz[(k << 1) | 1], laz[k]);
		dat[k] = reflected(k);
		laz[k] = ei;
	}

	inline void thrust(int k) { for (int i = height; i; i--) push(k >> i); }
	inline void recalc(int k) { while (k >>= 1) dat[k] = f(reflected((k << 1) | 0), reflected((k << 1) | 1)); }
	void update(int a, int b, E x) {
		if (a >= b) return;
		thrust(a += width);
		thrust(b += width - 1);
		for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) laz[l] = h(laz[l], x), l++;
			if (r & 1) --r, laz[r] = h(laz[r], x);
		}
		recalc(a);
		recalc(b);
	}
	void set_val(int a, T x) {
		thrust(a += width);
		dat[a] = x;
		laz[a] = ei;
		recalc(a);
	}
	T get_val(int a) {
		thrust(a += width);
		return reflected(a);
	}
	T query(int a, int b) {
		if (a >= b) return ti;
		thrust(a += width);
		thrust(b += width - 1);
		T vl = ti, vr = ti;
		for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) vl = f(vl, reflected(l++));
			if (r & 1) vr = f(reflected(--r), vr);
		}
		return f(vl, vr);
	}
	T query() { return reflected(1); }

	template <class C>
	int max_right(int l, C check) {
		assert(0 <= l && l <= width);
		assert(check(ti));
		if (l == width) return width;
		l += width;
		thrust(l);
		T sm = ti;
		do {
			while (l % 2 == 0) l /= 2;
			if (!check(f(sm, reflected(l)))) {
				while (l < width) {
					push(l);
					l *= 2;
					if (check(f(sm, reflected(l)))) {
						sm = f(sm, reflected(l));
						l++;
					}
				}
				return l - width;
			}
			sm = f(sm, reflected(l));
			l++;
		} while ((l & -l) != l);
		return width;
	}

	template <class C>
	int min_left(int r, C check) {
		assert(0 <= r && r <= width);
		assert(check(ti));
		if (r == 0) return 0;
		r += width;
		thrust(r - 1);
		T sm = ti;
		do {
			r--;
			while (r > 1 && (r % 2)) r /= 2;
			if (!check(f(reflected(r), sm))) {
				while (r < width) {
					push(r);
					r = r * 2 + 1;
					if (check(f(reflected(r), sm))) {
						sm = f(reflected(r), sm);
						r--;
					}
				}
				return r + 1 - width;
			}
			sm = f(reflected(r), sm);
		} while((r & -r) != r);
		return 0;
	}
};
