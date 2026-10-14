#pragma once

// T: val type
// U: kind type
template <int K, typename T, typename U = int, U UNUSED_VALUE = -1, bool CHMIN = true>
struct ChminTopK {

	ChminTopK() {
		for (int i = 0; i < K; i++) A[i].second = UNUSED_VALUE;
	}
	ChminTopK(T val, U key) {
		if constexpr (!CHMIN) val = -val;
		A[0] = {val, key};
		for (int i = 1; i < K; i++) A[i].second = UNUSED_VALUE;
	}
	ChminTopK(array<pair<T, U>, K> &A) : A(A) {}

	bool apply(T val, U key) {
		if constexpr (!CHMIN) val = -val;
		if (key == UNUSED_VALUE) return false;
		int same_i = K - 1;
		int mid = -1;
		for (int i = K - 1; i >= 0; i--) {
			if (A[i].second == UNUSED_VALUE || A[i].first > val) mid = i;
			if (A[i].second == key) {
				if (A[i].first <= val) return false;
				same_i = i;
			}
		}
		if (mid < 0) return false;
		for (int i = same_i; i >= mid + 1; i--) A[i] = A[i - 1];
		A[mid] = {val, key};
		return true;
	}

	void apply(ChminTopK &B) {
		for (auto& [val, key] : B.A) apply(val * (CHMIN ? 1 : -1), key);
	}

	pair<T, U> operator[](int k) const {
		assert(0 <= k && k < K);
		if constexpr (CHMIN) return A[k];
		return {-A[k].first, A[k].second};
	}

	array<pair<T, U>, K> get_all() const {
		if constexpr (CHMIN) return A;
		auto ans = A;
		for (auto& a : ans) a.first = -a.first;
		return ans;
	}

	void print() const {
		for (int i = 0; i < K; i++) {
			cout << i << " th: " << A[i].first * (CHMIN ? 1 : -1) << " " << A[i].second << "\n";
		}
	}

	private:
	array<pair<T, U>, K> A;
};

template <int K, typename T, typename U = int, U UNUSED_VALUE = -1>
using ChmaxTopK = ChminTopK<K, T, U, UNUSED_VALUE, false>;
