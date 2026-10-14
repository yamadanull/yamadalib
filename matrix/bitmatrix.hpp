#pragma once

#include "../data-structure/dynamic-bitset.hpp"

struct BitOrMatrix {

	vector<BitSet> A;

	BitOrMatrix(int n, int m) : A(n, BitSet(m)) {}
	BitOrMatrix(int n) : A(n, BitSet(n)) {}

	int H() const { return A.size(); }
	int W() const { return A[0].size(); }

	inline BitSet &operator[](int k) { return A[k]; }

	static BitOrMatrix I(int n) {
		BitOrMatrix mat(n);
		for (int i = 0; i < n; i++) mat[i].set(i);
		return (mat);
	}

	BitOrMatrix &operator+=(BitOrMatrix &B) {
		int n = H(), m = W();
		assert(n == B.H() && m == B.W());
		for (int i = 0; i < n; i++) (*this)[i] |= B[i];
		return (*this);
	}

	BitOrMatrix &operator*=(BitOrMatrix &B) {
		int n = H(), m = B.W(), p = W();
		assert(p == B.H());
		BitOrMatrix tB(m, p);

		for (int i = 0; i < p; i++)
			for (int j = 0; j < m; j++) tB[j][i] = B[i][j];

		BitOrMatrix C(n, m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) C[i][j] = ((A[i] & tB[j]).count() > 0);

		A.swap(C.A);
		return (*this);
	}

	BitOrMatrix &operator^=(long long k) {
		BitOrMatrix B = BitOrMatrix::I(H());
		while (k > 0) {
			if (k & 1) B *= *this;
			*this *= *this;
			k >>= 1LL;
		}
		A.swap(B.A);
		return (*this);
	}

	BitOrMatrix operator+(BitOrMatrix &B) const { return (BitOrMatrix(*this) += B); }
	BitOrMatrix operator*(BitOrMatrix &B) const { return (BitOrMatrix(*this) *= B); }
	BitOrMatrix operator^(const long long k) const { return (BitOrMatrix(*this) ^= k); }

	bool operator==(BitOrMatrix &B) const {
		assert(H() == B.H() && W() == B.W());
		for (int i = 0; i < H(); i++)
			if (A[i] != B[i]) return false;
		return true;
	}

	bool operator!=(BitOrMatrix &B) const {
		assert(H() == B.H() && W() == B.W());
		for (int i = 0; i < H(); i++)
			if (A[i] != B[i]) return true;
		return false;
	}
};

struct BitXorMatrix {

	vector<BitSet> A;

	BitXorMatrix(int n, int m) : A(n, BitSet(m)) {}
	BitXorMatrix(int n) : A(n, BitSet(n)) {}

	int H() const { return A.size(); }
	int W() const { return A[0].size(); }

	inline BitSet &operator[](int k) { return A[k]; }

	static BitXorMatrix I(int n) {
		BitXorMatrix mat(n);
		for (int i = 0; i < n; i++) mat[i].set(i);
		return (mat);
	}

	BitXorMatrix &operator+=(BitXorMatrix &B) {
		int n = H(), m = W();
		assert(n == B.H() && m == B.W());
		for (int i = 0; i < n; i++) (*this)[i] |= B[i];
		return (*this);
	}

	BitXorMatrix &operator*=(BitXorMatrix &B) {
		int n = H(), m = B.W(), p = W();
		assert(p == B.H());
		BitXorMatrix tB(m, p);

		for (int i = 0; i < p; i++)
			for (int j = 0; j < m; j++) tB[j][i] = B[i][j];

		BitXorMatrix C(n, m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) C[i][j] = ((A[i] & tB[j]).count() & 1);

		A.swap(C.A);
		return (*this);
	}

	BitXorMatrix &operator^=(long long k) {
		BitXorMatrix B = BitXorMatrix::I(H());
		while (k > 0) {
			if (k & 1) B *= *this;
			*this *= *this;
			k >>= 1LL;
		}
		A.swap(B.A);
		return (*this);
	}

	BitXorMatrix operator+(BitXorMatrix &B) const { return (BitXorMatrix(*this) += B); }
	BitXorMatrix operator*(BitXorMatrix &B) const { return (BitXorMatrix(*this) *= B); }
	BitXorMatrix operator^(const long long k) const { return (BitXorMatrix(*this) ^= k); }

	bool operator==(BitXorMatrix &B) const {
		assert(H() == B.H() && W() == B.W());
		for (int i = 0; i < H(); i++)
			if (A[i] != B[i]) return false;
		return true;
	}

	bool operator!=(BitXorMatrix &B) const {
		assert(H() == B.H() && W() == B.W());
		for (int i = 0; i < H(); i++)
			if (A[i] != B[i]) return true;
		return false;
	}
};

std::pair<int, int> BitSweep(BitXorMatrix &a, int pivot_end = -1, bool diagonalize = false) {
	int H = a.H(), W = a.W(), rank = 0, det = 1;
	if (pivot_end == -1) pivot_end = W;

	for (int j = 0; j < pivot_end; j++) {
		int idx = -1;
		for (int i = rank; i < H; i++) if(a[i][j] == 1) { idx = i; break; }

		if(idx == -1) { det = 0; continue; }
		if(rank != idx) { det = -det; swap(a[rank], a[idx]); }
		det *= a[rank][j];
		
		int is = diagonalize ? 0 : rank + 1;
		for (int i = is; i < H; i++) {
			if (i == rank) continue;
			if (a[i][j]) a[i] ^= a[rank];
		}
		++rank;
	}

	return make_pair(rank, det);
}
