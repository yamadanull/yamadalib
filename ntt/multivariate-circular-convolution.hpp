#pragma once
//
#include <cassert>
#include <unordered_map>
#include <vector>
using namespace std;

#include "../fps/formal-power-series.hpp"
#include "../internal/internal-math.hpp"
#include "../math/constexpr-primitive-root.hpp"
#include "../modint/arbitrary-modint.hpp"
#include "../prime/fast-factorize.hpp"
#include "chirp-z.hpp"
#include "multidimensional-ntt.hpp"

template <typename mint>
FormalPowerSeries<mint> multivariate_circular_convolution(
		const FormalPowerSeries<mint>& f, const FormalPowerSeries<mint>& g,
		const vector<int>& base, bool using_crt = false) {
	using fps = FormalPowerSeries<mint>;

	int prod = 1;
	for (auto& b : base) prod *= b;
	assert((int)f.size() == prod && (int)g.size() == prod);

	vector<int> primes;
	if (using_crt){
		for (int p = 900000000 / prod * prod + 1; (int)primes.size() < 3; p += prod) {
			if (is_prime(p)) primes.emplace_back(p);
		}
	}
	else {
		primes.emplace_back(mint::get_mod());
	}

	vector<vector<int>> buf;
	using submint = ArbitraryModIntBase<20230528>;
	for (int p : primes) {
		submint::set_mod(p);
		int proot = constexpr_primitive_root(p);
		unordered_map<int, pair<submint, submint>> len_to_W;
		for (auto& b : base) if (!len_to_W.count(b)) {
			submint w = submint{proot}.pow((p - 1) / b);
			submint iw = w.inverse();
			len_to_W[b] = {w, iw};
		}

		const int border = 5;
		auto dft = [&](vector<submint>& v, bool rev) -> void {
			int n = v.size();
			auto& val = len_to_W[n];
			submint w = rev ? val.second : val.first;
			if (n < border) {
				vector<submint> u(n);
				for (int i = 0; i < n; ++i)
					for (int j = 0; j < n; ++j)
						u[i] += v[j] * w.pow((i * j) % n);
				v.swap(u);
			}
			else {
				auto res = ChirpZ<FormalPowerSeries<submint>>({begin(v), end(v)}, w);
				v = vector<submint>{begin(res), end(res)};
			}
		};
		MultidimensionalFourierTransform<submint> mdft(base, dft);

		FormalPowerSeries<submint> s(prod), t(prod);
		for (int i = 0; i < prod; i++) s[i] = f[i].get(), t[i] = g[i].get();
		mdft.fft(s), mdft.fft(t);
		for (int i = 0; i < prod; i++) s[i] *= t[i];
		mdft.fft(s, true);
		submint iprod = submint{prod}.inverse();
		vector<int> res;
		for (auto& x : s) res.emplace_back((x * iprod).get());
		buf.emplace_back(res);
	}

	fps h;
	if (!using_crt) {
		for (auto& x : buf[0]) h.emplace_back(mint(x));
		return h;
	}

	auto m = mint::get_mod();
	vector<__int128_t> rem(3), mod(3);
	for (int j = 0; j < 3; j++) mod[j] = primes[j];
	for (int i = 0; i < prod; i++) {
		for (int j = 0; j < 3; j++) rem[j] = buf[j][i];
		h.emplace_back(internal::crt(rem, mod).first % m);
	}
	return h;
}

/**
 * @brief 多変数巡回畳み込み
 */
