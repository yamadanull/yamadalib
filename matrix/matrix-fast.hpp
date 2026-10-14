#pragma once
#include "inverse-matrix.hpp"

template <typename mint, int H, int W>
struct Matrix {
	using Array = std::array<std::array<mint, W>, H>;
	Array A;

	Matrix() : A() {
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) (*this)[i][j] = mint();
	}
	Matrix(mint a) : A() {
		if (a != mint()) {
			assert(H == W);
			for (int i = 0; i < H; i++) A[i][i] = a;
		}
	}

	int height() const { return H; }
	int width() const { return W; }
	inline const std::array<mint, W> &operator[](int k) const { return A[k]; }
	inline std::array<mint, W> &operator[](int k) { return A[k]; }
	static Matrix I() {
		assert(H == W);
		Matrix mat;
		for (int i = 0; i < H; i++) mat[i][i] = 1;
		return (mat);
	}

	Matrix &operator+=(const Matrix &B) {
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) A[i][j] += B[i][j];
		return (*this);
	}

	Matrix &operator-=(const Matrix &B) {
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) A[i][j] -= B[i][j];
		return (*this);
	}

	Matrix &operator*=(const Matrix &B) {
		assert(H == W);
		Matrix C;
		for (int i = 0; i < H; i++) {
			for (int k = 0; k < H; k++) {
				for (int j = 0; j < H; j++) C[i][j] += A[i][k] * B[k][j];
			}
		}
		A.swap(C.A);
		return (*this);
	}

	Matrix &operator/=(const Matrix &B) {
		assert(H == W);
		(*this) *= B.inverse();
		return (*this);
	}

	Matrix &operator^=(long long k) {
		Matrix B = Matrix::I();
		while (k > 0) {
			if (k & 1) B *= *this;
			*this *= *this;
			k >>= 1LL;
		}
		A.swap(B.A);
		return (*this);
	}

	Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }
	Matrix operator-(const Matrix &B) const { return (Matrix(*this) -= B); }
    Matrix operator-() const { return Matrix() - Matrix(*this); }
	Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }
	Matrix operator/(const Matrix &B) const { return (Matrix(*this) /= B); }
	Matrix operator^(const long long k) const { return (Matrix(*this) ^= k); }

	bool operator==(const Matrix &B) const {
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) if (A[i][j] != B[i][j]) return false;
		return true;
	}

	bool operator!=(const Matrix &B) const {
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) if (A[i][j] != B[i][j]) return true;
		return false;
	}

	friend ostream &operator<<(ostream &os,const Matrix &p) {
		for (int i = 0; i < H; i++) {
			os << "[";
			for (int j = 0; j < W; j++) {
				os << p[i][j] << (j + 1 == W ? "]\n" : ",");
			}
		}
		return (os);
	}

	mint determinant(int n = -1) const {
		if (n == -1) n = H;
		Matrix B(*this);
		mint ret = 1;
		for (int i = 0; i < n; i++) {
			int idx = -1;
			for (int j = i; j < n; j++) if (B[j][i] != 0) {
				idx = j;
				break;
			}
			if (idx == -1) return 0;
			if (i != idx) {
				ret *= mint(-1);
				swap(B[i], B[idx]);
			}
			ret *= B[i][i];
			mint inv = mint(1) / B[i][i];
			for (int j = 0; j < n; j++) {
				B[i][j] *= inv;
			}
			for (int j = i + 1; j < n; j++) {
				mint a = B[j][i];
				if (a == 0) continue;
				for (int k = i; k < n; k++) {
					B[j][k] -= B[i][k] * a;
				}
			}
		}
		return (ret);
	}

	Matrix inverse() const {
		assert(H == W && H > 0);
		int N = H;
		assert(N > 0);

		vector<vector<mint>> M(N, vector<mint>(2 * N));
		for (int i = 0; i < N; i++) M[i][N + i] = 1;
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) M[i][j] = A[i][j];

		auto [rank, det] = GaussElimination(M, N, true);
		assert(rank == N);

		Matrix<mint, H, W> ans(N);
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) ans[i][j] = M[i][j + N];
		return ans;
	}
};
