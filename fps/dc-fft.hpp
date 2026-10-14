#pragma once

// 多分定数倍ゴミだからテンプレ用としてしか使えないかも
template <typename mint, typename fps>
vector<mint> DCFFT_pattern2(vector<fps> &L, vector<int> &La, fps &f, int fa, vector<fps> &R, vector<int> &Ra) {
	int N = L.size(); assert((int)R.size() == N && (int)La.size() == N && (int)Ra.size() == N);

	vector<int> Lb(N), Rb(N);
	for (int i = 0; i < N; i++) {
		Lb[i] = La[i] + L[i].size() - 1;
		Rb[i] = Rb[i] + R[i].size() - 1;
	}

	vector<int> LaS(N + 1), LbS(N + 1), RaS(N + 1), RbS(N + 1);
	for (int i = 0; i < N; i++) {
		LaS[i + 1] = LaS[i] + La[i]; LbS[i + 1] = LbS[i] + Lb[i];
		RaS[i + 1] = RaS[i] + Ra[i]; RbS[i + 1] = RbS[i] + Rb[i];
	}

	// Rが全部同じとかの場合、二項係数で直接求めたりすることで手数少なく定数倍改善可能
	// R_i = 1 (any i) の場合、dfsRとmemoは丸ごと削除可能
	map<pair<int, int>, fps> memo;
	auto dfsR = [&](auto&& self, int l, int r) -> fps{ // return: 各区間のRの総積
		if (l + 1 == r) {
			if (l > 0)memo[make_pair(l, r)] = R[l];
			return R[l];
		}
		int m = (l + r) / 2;
		auto ans = self(self, l, m) * self(self, m, r);
		if (l > 0) memo[make_pair(l, r)] = ans;
		return ans;
	}; dfsR(dfsR, 0, N);

	auto cutout = [](fps &f, int fa, int a, int b) -> pair<fps, int> {
		int fb = fa + f.size() - 1;
		a = max(fa, a);
		b = min(fb, b);
		if (a > b) return make_pair(fps(), 0);
		fps ans(b - a + 1);
		for (int i = 0; i <= b - a; i++) ans[i] = f[i + (a - fa)];
		return make_pair(ans, a);
	};

	vector<mint> ans(N);
	auto dfsL = [&](auto&& self, int l, int r, fps g, int ga) -> fps{ // return: 各区間のLの総積
		if (l + 1 == r){
			int gb = ga + g.size() - 1;
			if (ga <= 0 && 0 <= gb) ans[l] = g[-ga];
			return L[l]; // Lが動的に求まる場合、ここ(とLb)を書き換える
		}

		int cuta = 1e9, cutb = -1e9;
		for (int i = l; i < r; i++) {
			int a = (LaS[i] - LaS[l]) + (RaS[r] - RaS[i + 1]);
			int b = (LbS[i] - LbS[l]) + (RbS[r] - RbS[i + 1]);
			cuta = min(cuta, -b);
			cutb = max(cutb, -a);
		}

		auto [cur, cura] = cutout(g, ga, cuta, cutb);
		int m = (l + r) / 2;
		auto ret = self(self, l, m, cur * memo[make_pair(m, r)], cura + RaS[r] - RaS[m]);
		ret *= self(self, m, r, cur * ret, cura + LaS[m] - LaS[l]);
		return ret;
	}; dfsL(dfsL, 0, N, f, fa);

	return ans;
}
