#pragma once

template <typename fps>
pair<fps, fps> DifferenceConvolution(fps& F, fps G) {
	int N = F.size();
	int M = G.size();
	reverse(G.begin(), G.end());
	fps H = F * G;
	fps ans(N); // Gの添字でFを左にスライド
	for (int i = M - 1; i < H.size(); i++) ans[i + 1 - M] = H[i];
	fps bns(M); // Fの添字でGを左にスライド
	for (int i = M - 1; i >= 0; i--) bns[M - 1 - i] = H[i];
	return make_pair(ans, bns);
}
