#pragma once

#include "suffix-array.hpp"

// first: Suffix Array
// second: LCPArray
pair<vector<pair<int, int>>, vector<int>> MultiSuffixArray (vector<string> &S) {
	int N = S.size();
	string all;
	vector<int> st(N);
	for (int i = 0; i < N; i++) {
		st[i] = all.size();
		all += S[i] + "$";
	}
	SuffixArray sa_all(all);
	vector<int> lcp = LCPArray(sa_all).LCP;
	lcp.erase(lcp.begin(), lcp.begin() + N + 1);
	vector<pair<int, int>> sa(sa_all.size() - N - 1);

	for (int ni = 0; ni < (int)sa.size(); ni++){
		int pos = sa_all[ni + N + 1];
		int i = upper_bound(st.begin(), st.end(), pos) - st.begin() - 1;
		int j = pos - st[i];
		sa[ni] = {i, j};
		lcp[ni] = min(lcp[ni], (int)S[i].size() - j);
	}
	for (int ni = 0; ni < (int)lcp.size() - 1; ni++){
		lcp[ni] = min(lcp[ni], (int)S[sa[ni].first].size() - sa[ni].second);
		lcp[ni] = min(lcp[ni], (int)S[sa[ni + 1].first].size() - sa[ni + 1].second);
	}

	return {sa, lcp};
}

