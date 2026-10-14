#pragma once

// 区間の集合というよりも数字の集合を扱う構造体

// 定義されている必要のあるもの->
// bool operator<(T, T)
// bool operator<=(T, T)
// bool operator==(T, T)
template <typename T>
struct Interval {
	map<T, T> st;
	Interval() = default;

	using const_it = typename map<T, T>::const_iterator;
	const_it begin() const { return st.begin(); }
	const_it end() const { return st.end(); }
	const_it lower_bound(T x) const {
		auto it = st.lower_bound(x);
		if (it != st.begin() && x < prev(it)->second) return prev(it);
		return it;
	}
	const_it upper_bound(T x) const { return st.upper_bound(x); }
	const_it erase(const_it it) { return st.erase(it); }

	// xが範囲内である場合に、その区間に対応するポインタを返す
	// 範囲外ならend()を返す
	const_it find(T x, bool Broadly = false) {
		auto it = lower_bound(x);
		if (Broadly)
			if (it != begin() && prev(it)->second == x)
				return prev(it);
		if (it == end()) return it;
		auto [l, r] = *it;
		if (l <= x && x < r) return it;
		return end();
	}


	void insert(T l, T r) {
		if (!(l < r)) return;
		move_left(l);
		move_right(r);
		auto L = lower_bound(l);
		auto R = lower_bound(r);
		while (L != R) {
			L = erase(L);
		}
		st[l] = r;
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

	Interval<T> cutout(T l, T r) {
		if (!(l < r)) return Interval<T>();
		Interval<T> ans;
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

	Interval<T> cutout_empty(T l, T r) {
		move_right(l);
		move_left(r);
		if (!(l < r)) return Interval<T>();
		auto L = lower_bound(l);
		auto R = lower_bound(r);
		vector<T> P;
		P.emplace_back(l);
		while (L != R) {
			P.emplace_back(L->first);
			P.emplace_back(L->second);
			++L;
		}
		P.emplace_back(r);

		Interval<T> ans;
		for (int i = 0; i < (int)P.size(); i += 2) {
			ans.st[P[i]] = P[i + 1];
		}
		return ans;
	}

	void move_left(T& i, bool Broadly = true) {
		auto it = find(i, Broadly);
		if (it != end()) i = it->first;
	}

	void move_right(T& i) {
		auto it = find(i);
		if (it != end()) i = it->second;
	}

	Interval<T> &operator+=(const Interval<T> &I) {
		for (auto& [l, r] : I.st) {
			this->insert(l, r);
		}
		return (*this);
	}

	Interval<T> &operator*=(const Interval<T> &I) {
		Interval<T> ans;
		for (auto& [l, r] : I.st) {
			Interval<T> J = this->cutout(l, r);
			for (auto& [L, R] : J.st) {
				ans.st[L] = R;
			}
		}
		return (*this) = ans;
	}

	Interval<T> operator+(const Interval<T> &I) {return Interval(*this) += I; }
	Interval<T> operator*(const Interval<T> &I) {
		Interval<T> ans;
		for (auto& [l, r] : I.st) {
			Interval<T> J = this->cutout(l, r);
			for (auto& [L, R] : J.st) {
				ans.st[L] = R;
			}
		}
		return ans;
	}

	private:
	bool cut(T i) {
		auto it = lower_bound(i);
		if (it == end()) return false;
		auto [l, r] = *it;
		if (l < i && i < r) {
			erase(it);
			st[l] = i;
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
		auto [l, r] = *prev(it);
		auto [L, R] = *it;
		assert(r == L);
		erase(it);
		st[l] = R;
	}
};


// 追加で定義されている必要のあるもの->
// T operator+=(T)
// T operator-(T, T)
// int(0)のキャスト
template <typename T>
T Interval_sum(Interval<T> m) {
	T ans = T(0);
	for (auto [L, R] : m.st) {
		ans += R - L;
	}
	return ans;
}
