#pragma once

#include "../misc/rng.hpp"
#include "miller-rabin.hpp"

template <typename T>
T RandomPrime(T L = 1 << 29, T R = 1 << 30, int iter = 1 << 20) {
	while(iter--) {
		T ans = randint(L, R);
		if (is_prime(ans)) return ans;
	}
	return -1;
}
