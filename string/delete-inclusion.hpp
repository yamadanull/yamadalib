#pragma once

#include "z-algorithm.hpp"

vector<string> DeleteInclusion(vector<string> &S, bool delete_longer) {
	auto check = [](string &S, string &T)->bool{ // TがSを包含するか
		int N = S.size();
		int M = T.size();
		if (N > M) return false;
		auto za = z_algorithm(S + T);
		for (int i = N; i <= M; i++) {
			if (za[i] >= N) return true;
		}
		return false;
	};

	int N = S.size();
	vector<bool> fn(N, true);
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) if (i != j) {
		if(check(S[i], S[j])) (delete_longer? fn[j]: fn[i]) = false;
	}
	vector<string> ans;
	for (int i = 0; i < N; i++) if(fn[i]) ans.emplace_back(S[i]);
	return ans;
}
