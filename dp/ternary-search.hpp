#pragma once

template <typename T, typename E, bool get_min = true>
pair<T, E> TernarySearch(T L, T R, const function<E(T)>& f, int iter = 100) {
	while (iter--) {
		T m1 = (L * 2 + R) / 3;
		T m2 = (L + R * 2) / 3;
		if ((f(m1) < f(m2)) ^ get_min) L = m1;
		else R = m2;
	}
	return make_pair(L, f(L));
}
