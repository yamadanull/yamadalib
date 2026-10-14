#pragma once

#include <vector>
using namespace std;

#include "monotone-minima.hpp"

// A は下に凸, B は自由
template <typename T>
vector<T> convex_min_plus_convolution(const vector<T>& A, const vector<T>& B) {
	int N = A.size(), M = B.size();
	if (N == 0 || M == 0) return {};
	auto argmin = monotone_minima(N + M - 1, M, [&](int i, int j, int k) {
		if (i < k) return true;
		if (i - j >= N) return false;
		return A[i - j] + B[j] <= A[i - k] + B[k];
	});
	vector<T> C(N + M - 1);
	for (int i = 0; i < N + M - 1; i++) {
		int j = argmin[i];
		C[i] = A[i - j] + B[j];
	}
	return C;
}

// A は上に凸（＝凹）, B は自由
template <typename T>
vector<T> concave_max_plus_convolution(const vector<T>& A, const vector<T>& B) {
	int N = A.size(), M = B.size();
	if (N == 0 || M == 0) return {};
	auto argmin = monotone_minima(N + M - 1, M, [&](int i, int j, int k) {
		if (i < k) return true;
		if (i - j >= N) return false;
		return A[i - j] + B[j] >= A[i - k] + B[k];
	});
	vector<T> C(N + M - 1);
	for (int i = 0; i < N + M - 1; i++) {
		int j = argmin[i];
		C[i] = A[i - j] + B[j];
	}
	return C;
}

template <typename T>
vector<T> convex_convex_minplus_convolution(vector<T> &A, vector<T> &B) {
	int N = A.size(), M = B.size();
	if (N == 0 || M == 0) return {};
	vector<T> C(N + M - 1);
	C[0] = A[0] + B[0];
	for (int ci = 1, ai = 0, bi = 0; ci < N + M - 1; ci++) {
		if (bi == M - 1 || (ai < N - 1 && A[ai + 1] + B[bi] < A[ai] + B[bi + 1])) C[ci] = A[++ai] + B[bi];
		else C[ci] = A[ai] + B[++bi];
	}
	return C;
}

template <typename T>
vector<T> concave_concave_maxplus_convolution(vector<T> &A, vector<T> &B) {
	int N = A.size(), M = B.size();
	if (N == 0 || M == 0) return {};
	vector<T> C(N + M - 1);
	C[0] = A[0] + B[0];
	for (int ci = 1, ai = 0, bi = 0; ci < N + M - 1; ci++) {
		if (bi == M - 1 || (ai < N - 1 && A[ai] + B[bi + 1] < A[ai + 1] + B[bi])) C[ci] = A[++ai] + B[bi];
		else C[ci] = A[ai] + B[++bi];
	}
	return C;
}
