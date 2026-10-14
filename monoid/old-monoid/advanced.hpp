#pragma once

#include "basic.hpp"

namespace Monoid {

template <typename U, U INF, bool TIE_IS_LEFT = 1>
struct MinIdx : Common<MinIdx<U, INF, TIE_IS_LEFT>, std::pair<U, U>> {
	static constexpr bool COMMUTE = 1;
	using value_type = std::pair<U, int>;
	using T = value_type;
	T a;
	constexpr MinIdx &operator+=(const MinIdx &b) {
		if (a.first > T(b).first) a = T(b);
		else if (a.first == T(b).first) {
			if (a.second < T(b).second) {
				if (!TIE_IS_LEFT) a = T(b);
			}
			else {
				if (TIE_IS_LEFT) a = T(b);
			}
		}
		return *this;
	}
	constexpr MinIdx() : a(INF, -1) {}
	constexpr MinIdx(T _a) : a(_a) {}
};

template <typename U, U MINF, bool TIE_IS_LEFT = 1>
struct MaxIdx : Common<MaxIdx<U, MINF, TIE_IS_LEFT>, std::pair<U, U>> {
	static constexpr bool COMMUTE = 1;
	using value_type = std::pair<U, int>;
	using T = value_type;
	T a;
	constexpr MaxIdx &operator+=(const MaxIdx &b) {
		if (a.first < T(b).first) a = T(b);
		else if (a.first == T(b).first) {
			if (a.second < T(b).second) {
				if (!TIE_IS_LEFT) a = T(b);
			}
			else {
				if (TIE_IS_LEFT) a = T(b);
			}
		}
		return *this;
	}
	constexpr MaxIdx() : a(MINF, 0) {}
	constexpr MaxIdx(T _a) : a(_a) {}
};

/* template <typename U, U INF> */
/* struct MinMincnt : Common<MinMincnt<U, INF>, std::pair<U, U>> { */
/* 	constexpr bool COMMUTE = 1; */
/* 	using value_type = std::pair<U, U>; */
/* 	using T = value_type; */
/* 	T a; */
/* 	constexpr MinMincnt &operator+=(const MinMincnt &b) { */
/* 		if (a.first > T(b).first) a = T(b); */
/* 		else a.second += T(b).second; */
/* 		return *this; */
/* 	} */
/* 	constexpr MinMincnt() { return {INF, 0}; } */
/* 	constexpr MinMincnt(T _a) : a(_a) {} */
/* }; */

template <typename U, U MINF>
struct MaxMaxcnt : Common<MaxMaxcnt<U, MINF>, std::pair<U, U>> {
	static constexpr bool COMMUTATIVE = 1;
	using value_type = std::pair<U, int>;
	using T = value_type;
	T a;
	constexpr MaxMaxcnt &operator+=(const MaxMaxcnt &b) {
		if (a.first < T(b).first) a = T(b);
		else a.second += T(b).second;
		return *this;
	}
	constexpr MaxMaxcnt() : a(MINF, 0) {}
	constexpr MaxMaxcnt(T _a) : a(_a) {}
};

} // namespace Monoid
