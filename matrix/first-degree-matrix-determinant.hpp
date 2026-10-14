#pragma once

#include "characteristric-polynomial.hpp"

// det(M0 + xM1)
template <typename mint>
vector<mint> FirstDegreeMatrixDeterminant(vector<vector<mint>>& M0, vector<vector<mint>>& M1) {
	const int N = M0.size();
	int multiply_by_x = 0;
	mint detAdetBinv = 1;
	for (int p = 0; p < N; ++p) {
		int pivot = -1;
		for (int r = p; r < N; ++r) if (M1[r][p] != mint()) {
			pivot = r;
			break;
		}
		if (pivot < 0) {
			++multiply_by_x;
			if (multiply_by_x > N) return std::vector<mint>(N + 1);
			for (int r = 0; r < p; ++r) {
				mint v = M1[r][p];
				M1[r][p] = 0;
				for (int i = 0; i < N; ++i) M0[i][p] -= v * M0[i][r];
			}
			for (int i = 0; i < N; ++i) swap(M0[i][p], M1[i][p]);
			--p;
			continue;
		}

		if (pivot != p) {
			M1[pivot].swap(M1[p]);
			M0[pivot].swap(M0[p]);
			detAdetBinv *= -1;
		}

		mint v = M1[p][p], vinv = v.inverse();
		detAdetBinv *= v;
		for (int c = 0; c < N; ++c) {
			M0[p][c] *= vinv;
			M1[p][c] *= vinv;
		}

		for (int r = 0; r < N; ++r) {
			if (r == p) continue;
			mint v = M1[r][p];
			for (int c = 0; c < N; ++c) {
				M0[r][c] -= M0[p][c] * v;
				M1[r][c] -= M1[p][c] * v;
			}
		}
	}

	for (auto &vec : M0) for (auto &x : vec) x = -x;
	auto poly = CharacteristicPolynomial(M0);
	for (auto &x : poly) x *= detAdetBinv * (N % 2 ? -1 : 1);

	poly.erase(poly.begin(), poly.begin() + multiply_by_x);
	poly.resize(N + 1);
	return poly;
}
