#pragma once

#include "../misc/mo.hpp"
#include "binomial.hpp"

// multipoint calc sum(C(N, m)) s.t. m < M
template <typename mint>
std::vector<mint> multipoint_binomial_sum(const std::vector<std::pair<int, int>>& qs, Binomial<mint> &C) {
	int N = 2; for (auto& p : qs) N = std::max(N, p.first);
	int Q = qs.size();
	Mo mo(N, Q);
	for (auto& p : qs) {
		assert(p.second <= p.first);
		assert(p.first <= N);
		mo.insert(p.second, p.first);
	}
	std::vector<mint> ans(Q);
	mint cur = 0;
	int n = 0, m = 0;
	auto dec_m = [&](int) { cur -= C(n, --m); };
	auto inc_n = [&](int) { cur += cur - C(n++, m - 1); };
	auto inc_m = [&](int) { cur += C(n, m++); };
	auto dec_n = [&](int) { cur = (cur + C(--n, m - 1)) * C.inv(2); };
	auto query = [&](int i) { ans[i] = cur; };
	mo.run(dec_m, inc_n, inc_m, dec_n, query);
	return ans;
}

// multipoint calc {sum(C(N, m)), sum(m * C(N, m))} s.t. m < M
template <typename mint>
std::pair<std::vector<mint>, std::vector<mint>>
multipoint_binomial_sum2(const std::vector<std::pair<int, int>>& qs, Binomial<mint> &C) {
	int N = 2; for (auto& p : qs) N = std::max(N, p.first);
	int Q = qs.size();
	Mo mo(N,Q); for (auto& [n, m] : qs) mo.insert(m, n);

	std::vector<mint> ans0(Q), ans1(Q);
	int n = 0, m = 0;
	mint cur(0), dur(0);
	auto dec_m = [&](int) {
		--m;
		cur -= C(n, m);
		dur -= C(n, m) * m;
	};
	auto inc_n = [&](int) {
		dur += dur + cur - C(n, m - 1) * m;
		cur += cur - C(n, m - 1);
		++n;
	};
	auto inc_m = [&](int) {
		cur += C(n, m);
		dur += C(n, m) * m;
		++m;
	};
	auto dec_n = [&](int) {
		--n;
		cur = (cur + C(n, m - 1)) * C.inv(2);
		dur = (dur - cur + C(n, m - 1) * m) * C.inv(2);
	};
	auto query = [&](int i) { ans0[i] = cur; ans1[i] = dur; };

	mo.run(dec_m, inc_n, inc_m, dec_n, query);
	return {ans0, ans1};
}

template <typename mint>
std::vector<mint> multipoint_binomial_sum(const std::vector<std::pair<int, int>>& qs) {
	Binomial<mint> C;
	return multipoint_binomial_sum(qs, C);
}

template <typename mint>
std::pair<std::vector<mint>, std::vector<mint>>
multipoint_binomial_sum2(const std::vector<std::pair<int, int>>& qs) {
	Binomial<mint> C;
	return multipoint_binomial_sum2(qs, C);
}
