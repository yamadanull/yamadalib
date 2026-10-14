#pragma once

template <typename T, typename F>
struct AbstractUnionFindWithPotential {
	vector<int> dat;
	vector<T> pot;
	const F f;
	const F finv;
	const T I;

	UnionFindWithPotential(int N, F _f, F _finv const T &I_) 
		: dat(N, -1), pot(N, T()), f(_f), finv(_finv), I(I_) {}

	int root(int x) {
		if (dat[x] < 0) return x;
		int r = root(dat[x]);
		pot[x] += pot[dat[x]];
		return dat[x] = r;
	}

	// return P(x) - P(root(x))
	T potential(int x) {
		root(x);
		return pot[x];
	}

	bool same(int x, int y) { return root(x) == root(y); }

	// return P(x) - P(y)
	T diff(int x, int y) {
		return potential(x) - potential(y);
	}

	// s.t. P(x) = P(y) + p
	// return Satisfiablility
	bool merge(int x, int y, T p) {
		p += potential(y) - potential(x);
		x = root(x), y = root(y);
		if (x == y) return p == T();
		if (dat[x] < dat[y]) swap(x, y), p = -p;
		dat[y] += dat[x];
		dat[x] = y;
		pot[x] = p;
		return true;
	}

	// return size of CC including x
	int size(int x) { return -dat[root(x)]; }
};
