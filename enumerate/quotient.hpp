#pragma once

// f(L, R, q) : x / y == q (L <= y && y < R)
template <typename T, typename F>
void QuotientEnumerate(T x, F f) {
	for (T R = x, L, q; R; R = L) {
		q = x / R, L = x / (q + 1);
		f(L + 1, R + 1, q);
	}
}
