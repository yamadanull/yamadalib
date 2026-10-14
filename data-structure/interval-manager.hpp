#pragma once

template <typename T>
struct Interval {
	map<T, T> st;
	Interval() = default;

	using const_iterator = typename map<T, T>::const_iterator;
	const_iterator begin() const { return st.begin(); }
	const_iterator end() const { return st.end(); }
	const_iterator lower_bound(T x) const {
		auto it = st.lower_bound(x);
		if (it == st.begin() || prev(it)->second <= x) return it;
		return prev(it);
	}
	const_iterator erase(const_iterator it) { return st.erase(it); }

	void insert(T l, T r) { st[l] = r; }

	void erase(T l, T r) {
		auto L = st.upper_bound(l), R = st.upper_bound(r);
		if (L != st.begin() && l <= prev(L)->second) --L;
		if (L == R) return;
		T nl = min(l, L->first), nr = max(r, prev(R)->second);
		st.erase(L, R);
		if (nl < l) st[nl] = l;
		if (r < nr) st[r] = nr;
	}

	void cut(T i) {
		auto it = lower_bound(i);
		if (it == end()) return;
		auto [l, r] = *it;
		if (l < i && i < r) {
			st.erase(it);
			st[l] = i;
			st[i] = r;
		}
	}
};

template <typename T, typename F>
struct WeightedInterval {
	map<T, T> st;
	map<T, F> W;
	WeightedInterval() = default;

	using const_iterator = typename map<T, T>::const_iterator;
	const_iterator begin() const { return st.begin(); }
	const_iterator end() const { return st.end(); }
	const_iterator lower_bound(T x) const {
		auto it = st.lower_bound(x);
		if (it == st.begin() || prev(it)->second <= x) return it;
		return prev(it);
	}
	const_iterator erase(const_iterator it) { return st.erase(it); }

	F get(T i) {
		auto it = lower_bound(i);
		auto [l, r] = *it;
		assert(l <= i && i < r);
		return W[l];
	}

	void insert(T l, T r, F w) { st[l] = r; W[l] = w; }

	void erase(T l, T r) {
		cut(l); cut(r);
		auto L = st.upper_bound(l), R = st.upper_bound(r);
		if (L != st.begin() && l <= prev(L)->second) --L;
		if (L == R) return;
		T nl = min(l, L->first), nr = max(r, prev(R)->second);
		st.erase(L, R);
		if (nl < l) st[nl] = l;
		if (r < nr) st[r] = nr;
	}

	void cut(T i) {
		auto it = lower_bound(i);
		if (it == end()) return;
		auto [l, r] = *it;
		if (l < i && i < r) {
			st.erase(it);
			st[l] = i;
			st[i] = r;
			W[i] = W[l];
		}
	}
};
