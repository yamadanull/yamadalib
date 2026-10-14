#pragma once

template <typename T, typename E>
struct WeightedInterval {
	struct Segment {
		T R = T(0);
		E W = E(0);

		Segment() = default;
		Segment(T _R) : R(_R) {}
		Segment(T _R, E _W) : R(_R), W(_W) {}

		Segment &operator=(const T &x) {
			R = x;
			return *this;
		}

		friend bool operator<(const Segment& x, const Segment& y) { return x.R < y.R; }
		operator T() const { return R; }
	};

	map<T, Segment> st;
	WeightedInterval() = default;

	using const_it = typename map<T, Segment>::const_iterator;
	const_it begin() const { return st.begin(); }
	const_it end() const { return st.end(); }
	const_it lower_bound(T x) const {
		auto it = st.lower_bound(x);
		if (it != st.begin() && x < T(prev(it)->second)) return prev(it);
		return it;
	}
	const_it upper_bound(T x) const { return st.upper_bound(x); }
	const_it erase(const_it it) { return st.erase(it); }

	// xが範囲内である場合に、その区間に対応するポインタを返す
	// 範囲外ならend()を返す
	const_it find(T x, bool Broadly = false) {
		auto it = lower_bound(x);
		if (Broadly)
			if (it != begin() && T(prev(it)->second) == x)
				return prev(it);
		if (it == end()) return end();
		auto [l, r] = *it;
		if (l <= x && x < (T)r) return it;
		return end();
	}

	void overwrite(T l, T r, E w) {
		if (!(l < r)) return;
		cut(l);
		cut(r);
		auto L = lower_bound(l);
		auto R = lower_bound(r);
		while (L != R) {
			L = erase(L);
		}
		st[l] = Segment(r, w);
		joint(l);
		joint(r);
	}

	void insert(T l, T r, E w) {
		if (!(l < r)) return;
		auto I = cutout_empty(l, r);
		for(auto&& [l, rw] : I.st) {
			st[l] = Segment(rw.R, w);
		}
	}

	void erase(T l, T r) {
		if (!(l < r)) return;
		cut(l); cut(r);
		auto L = lower_bound(l);
		auto R = lower_bound(r);
		while (L != R) {
			L = erase(L);
		}
	}

	WeightedInterval<T, E> cutout(T l, T r) {
		if (!(l < r)) return WeightedInterval<T, E>();
		WeightedInterval<T, E> ans;
		bool cutl = cut(l);
		bool cutr = cut(r);
		auto L = lower_bound(l);
		auto R = lower_bound(r);
		while (L != R) {
			ans.st[L->first] = L->second;
			++L;
		}
		if(cutl) joint(l);
		if(cutr) joint(r);
		return ans;
	}

	WeightedInterval<T, E> cutout_empty(T l, T r) {
		if (!(l < r)) return WeightedInterval<T, E>();
		move_right(l);
		move_left(r);
		if (!(l < r)) return WeightedInterval<T, E>();
		auto L = lower_bound(l);
		auto R = lower_bound(r);
		vector<T> P;
		P.emplace_back(l);
		while (L != R) {
			P.emplace_back(L->first);
			P.emplace_back(T(L->second));
			++L;
		}
		P.emplace_back(r);

		WeightedInterval<T, E> ans;
		for (int i = 0; i < P.size(); i += 2) {
			ans.st[P[i]] = Segment(P[i + 1]);
		}
		return ans;
	}

	void move_left(T& i, bool Broadly = true) {
		auto it = find(i, Broadly);
		if (it != end()) i = it->first;
	}

	void move_right(T& i) {
		auto it = find(i);
		if (it != end()) i = T(it->second);
	}

	private:
	bool cut(T i) {
		auto it = lower_bound(i);
		if (it == end()) return false;
		auto [l, r] = *it;
		if (l < i && i < r.R) {
			erase(it);
			st[l] = Segment(i, r.W);
			st[i] = r;
			return true;
		}
		return false;
	}

	// cutで入れた余計な切れ目を治療する
	void joint(T i) {
		auto it = lower_bound(i);
		assert(it != begin());
		assert(it != end());
		auto [l, rw] = *prev(it);
		auto [L, Rw] = *it;
		assert(rw.R == L && L == i);
		if (rw.W == Rw.W){
			erase(it);
			st[l] = Rw.R;
		}
	}
};
