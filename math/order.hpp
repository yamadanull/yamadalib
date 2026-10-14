#pragma once

#include "../prime/fast-factorize.hpp"

struct Order {
	using FactorizedForm = std::vector<std::pair<long long, int>>;

	Order(long long p) {
		_mod = p;
		{ // calc "_fac"
			auto pc = factor_count(_mod - 1);
			for (auto& [p, c] : pc) _fac.emplace_back(p, c);
		}
		_n = _fac.size();
		_prod.resize(_n + 1);
		_prod[0] = 1;
		for (size_t i = 0; i < _n; ++i) {
			auto [pf, e] = _fac[i];
			long long pow_pf = 1;
			while (e--) pow_pf *= pf;
			_prod[i + 1] = _prod[i] * pow_pf;
		}
	}

	long long query(long long x) const {
		return _n == 0 ? 1 : _query(0, _n, x);
	}

	private:
	long long _mod;
	size_t _n;
	FactorizedForm _fac;
	std::vector<long long> _prod;

	long long _modpow(long long x, long long k) const {
		long long res = 1;
		for (; k; k >>= 1) {
			if (k & 1) res = __int128_t(res) * x % _mod;
			x = __int128_t(x) * x % _mod;
		}
		return res;
	}

	int _get_exponent(size_t i, long long x) const {
		const auto &[p, e] = _fac[i];
		for (int j = 0; j < e; ++j) {
			if (x == 1) return j;
			x = _modpow(x, p);
		}
		return e;
	}

	long long _query(size_t l, size_t r, long long x) const {
		long long res = 1;
		if (r - l == 1) {
			long long p = _fac[l].first;
			int f = _get_exponent(l, x);
			while (f--) res *= p;
			return res;
		}
		const size_t m = (l + r) >> 1;
		res *= _query(l, m, _modpow(x, _prod[r] / _prod[m]));
		res *= _query(m, r, _modpow(x, _prod[m] / _prod[l]));
		return res;
	}
};
