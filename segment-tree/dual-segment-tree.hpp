#pragma once

template <typename E, typename H>
struct DualSegmentTree {
	private:
	int n, log;
	H h;
	vector<E> laz;
	E ei;

	inline void eval(int k) {
		if (laz[k] != ei) {
			laz[2 * k + 0] = h(laz[2 * k + 0], laz[k]);
			laz[2 * k + 1] = h(laz[2 * k + 1], laz[k]);
			laz[k] = ei;
		}
	}

	inline void thrust(int k) {
		for (int i = log; i; i--) eval(k >> i);
	}

	public:
	DualSegmentTree(int _n, H _h, E _ei) : h(_h), ei(_ei) {
		n = 1;
		log = 0;
		while (n < _n) n <<= 1, log++;
		laz.assign(2 * n, ei);
	}

	E get(int k) {
		thrust(k += n);
		return laz[k];
	}

	E operator[](int k) { return get(k); }

	void update(int a, int b, const E x) {
		thrust(a += n);
		thrust(b += n - 1);
		for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) laz[l] = h(laz[l], x), l++;
			if (r & 1) --r, laz[r] = h(laz[r], x);
		}
	}
};

