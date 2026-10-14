#pragma once

// return [N, A, B] (A * i + B (0 <= i < N))
// 直接使うことはないはず
template <typename T>
vector<tuple<T, T, T>> ModofLinearDecompositionSub(T N, T M, T A, T B) {
	assert(A >= 1);
	T K = (A * (N - 1) + B) / M;
	vector<T> d(K + 2);
	for (int k = 0; k <= K; k++) {
		if (M * k - B + A - 1 <= 0) continue;
		d[k] = (M * k - B + A - 1) / A;
	}
	d[K + 1] = N;

	vector<tuple<T, T, T>> ans;
	for (int k = 0; k <= K; k++) {
		T L = d[k], R = d[k + 1];
		if (L == R) continue;
		T b = (A * L + B) % M;
		ans.emplace_back(R - L, A, b);
	}
	return ans;
}

// return [N, A, B] (A * i + B (0 <= i < N))
// sqrt(M)
template <typename T>
vector<tuple<T, T, T>> ModofLinearDecomposition(T N, T M, T A, T B, bool rev_ok = true) {
	assert(N >= 1 && M >= 1 && A >= 0 && B >= 0);
	assert(__gcd(M, A) == 1); assert(N <= M);
	A %= M; B %= M;

	const T DIV = sqrt(N);
	if (DIV >= N || DIV == 1) {
		vector<tuple<T, T, T>> ans(N);
		for (int i = 0; i < N; i++) ans[i] = make_tuple(1, 1, (A * i + B) % M);
		return ans;
	}
	vector<pair<T, int>> es;
	for (int i = 0; i < DIV; i++) es.emplace_back((A * i + B) % M, i);
	sort(es.begin(), es.end());

	pair<T, int> hd = make_pair(M, 2e9);
	for (int i = 0; i < es.size() - 1; i++) {
		T h = es[i + 1].first - es[i].first;
		int d = es[i + 1].second - es[i].second;
		hd = min(hd, make_pair(h, d));
	}

	auto [a, m] = hd;
	bool isrev = false;
	// 減少列を取り出すはめになる場合、一旦ひっくり返して増加列を取り出すことにする
	if(m < 0) {
		m *= -1;
		B += A * (N - 1); B %= M;
		A = (M - A) % M;
		isrev = true;
	}

	vector<tuple<T, T, T>> ans;
	for (int st = 0; st < m; st++) {
		T b = (A * st + B) % M;
		T n = N / m + (st < N % m);
		auto bns = ModofLinearDecompositionSub(n, M, a, b);
		for (auto& e : bns) ans.emplace_back(e);
	}

	// 等差数列(modなし)をひっくり返す
	if (isrev && !rev_ok) for (auto& [n, a, b] : ans) { b += a * (n - 1); a *= -1; };
	return ans;
}
