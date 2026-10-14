#pragma once
#include "../modulo/binomial.hpp"
#include "../modint/montgomery-modint.hpp"
#include "../fps/arbitrary-fps.hpp"
#include "../fps/taylor-shift.hpp"

template <typename T, typename mint, int PQMAX>
struct ExtendFloorSum {
	using fps = FormalPowerSeries<mint>;
	Binomial<mint> binom;
	array<fps, PQMAX + 1> cof;

	ExtendFloorSum() {
		fps B = Bernoulli(PQMAX);
		B[1] = binom.inv(2);

		for (int k = 0; k <= PQMAX; k++) {
			cof[k].resize(k + 2);
			for (int i = 1; i <= k + 1; i++) {
				cof[k][i] = binom(k + 1, i) * B[k + 1 - i] * binom.inv(k + 1);
			}
			if (k > 0) cof[k] = TaylorShift(cof[k], mint(-1), binom);
		}
	}

	fps Bernoulli(int N) {
		fps f(N + 1);
		for (int i = 0; i <= N; i++) f[i] = binom.finv(i + 1);
		f = f.inv(N + 1);
		for (int i = 0; i <= N; i++) f[i] *= binom.fac(i);
		return f;
	}

	mint S(int k, T N) {
		if (N == 0) return mint(0);
		if (k == 0) return N;
		mint ans = 0;
		mint n = 1;
		for (auto& c : cof[k]) {
			ans += c * n;
			n *= N;
		}
		return ans;
	}

	array<array<mint, PQMAX + 1>, PQMAX + 1> f(T N, T M, T A, T B) {
		T FloorA = A / M;
		T FloorB = B / M;
		A %= M, B %= M;
		array<array<mint, PQMAX + 1>, PQMAX + 1> bns;
		if (A == 0) {
			for (int p = 0; p <= PQMAX; p++) {
				mint SpN = S(p, N);
				mint BMpow = 1;
				T BM = B / M;
				for (int q = 0; q <= PQMAX - p; q++) {
					bns[p][q] = SpN * BMpow;
					BMpow *= BM;
				}
			}
		}
		else {
			T K = (A * (N - 1) + B) / M;
			auto F = f(K, A, M, M - B + A - 1);
			T d_Kp1 = N;

			for (int p = 0; p <= PQMAX; p++) {
				bns[p][0] = S(p, N);
				for (int q = 1; q <= PQMAX - p; q++) {

					bns[p][q] = mint(K).pow(q) * S(p, d_Kp1);
					for (int i = 0; i <= q - 1; i++) {
						mint cns = 0;
						for (int j = 0; j <= p + 1; j++) {
							cns += cof[p][j] * F[i][j];
						}
						bns[p][q] -= cns * binom(q, i);
					}
				}
			}
		}

		array<mint, PQMAX + 1> apow, bpow;
		apow[0] = bpow[0] = 1;
		for (int i = 1; i <= PQMAX; i++) {
			apow[i] = apow[i - 1] * FloorA;
			bpow[i] = bpow[i - 1] * FloorB;
		}

		array<array<mint, PQMAX + 1>, PQMAX + 1> ans;
		for (int p = 0; p <= PQMAX; p++) {
			ans[p][0] = bns[p][0];
			for (int q = 1; q <= PQMAX - p; q++) for (int x = 0; x <= q; x++) for (int y = 0; y <= x; y++) {
				mint cns = binom(q, x) * binom(x, y);
				cns *= apow[y] * bpow[x - y] * bns[p + y][q - x];
				ans[p][q] += cns;
			}
		}
		return ans;
	}
};

template <typename T, typename mint, int P, int Q>
mint extend_sum_of_floor(T N, T M, T A, T B) {
	ExtendFloorSum<T, mint, P + Q> gfs;
	return gfs.f(N, M, A, B)[P][Q];
}
