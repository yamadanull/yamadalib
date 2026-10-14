#pragma once

// 可換じゃなくても動く
template <typename Group, bool ROLLBACK = false>
struct UnionFindWithPotential {
	std::vector<int> dat;
	std::vector<Group> pot; // - P(par) + P(u) (if u is root, undefined)
	std::vector<std::pair<int, int>> hist;
	bool is_valid = true;
 
	UnionFindWithPotential(int N) : dat(N, -1), pot(N, Group()) {}
 
	int root(int u) { return dat[u] < 0 ? u : root(dat[u]); }
 
	// return - P(root(u)) + P(u)
	Group potential(int u) { return dat[u] < 0 ? Group() : potential(dat[u]) + pot[u]; }
	bool same(int u, int v) { return root(u) == root(v); }
	// return - P(v) + P(u)
	Group diff(int u, int v) { return -potential(v) + potential(u); }
 
	// s.t. -P(v) + P(u) = p
	// return Satisfiablility
	bool unite(int u, int v, Group p) {
		p = potential(v) + p - potential(u);
		u = root(u), v = root(v);
		if (u == v){
			if(p != Group()){
				if constexpr (ROLLBACK) hist.emplace_back(-1, is_valid);
				is_valid = false;
			}
			return p == Group();
		}
		if (dat[u] < dat[v]) std::swap(u, v), p = -p;
		if constexpr (ROLLBACK) {
			hist.emplace_back(u, dat[u]);
			hist.emplace_back(v, dat[v]);
		}
		dat[v] += dat[u];
		dat[u] = v;
		pot[u] = p;
		return true;
	}
 
	// return size of CC including u
	int size(int u) { return -dat[root(u)]; }
 
	void undo(){
		static_assert(ROLLBACK);
		assert(!hist.empty());
		auto [fi, se] = hist.back(); hist.pop_back();
		if (fi < 0) is_valid = se;
		else dat[fi] = se;
	}

	int get_time() { static_assert(ROLLBACK); return (int)hist.size(); }
	void rollback(int t = 0) {
		static_assert(ROLLBACK);
		assert(t <= (int)hist.size());
		while (t < (int)hist.size()) undo();
	}
};
