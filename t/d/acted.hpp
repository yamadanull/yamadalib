/* #include "../../monoid/basic.hpp" */
using namespace yamada;

struct S_Mono {
	static constexpr bool COMMUTATIVE = 0;
	// WRITE!!
	using value_type =;
	using T = value_type;
	T a;
	// WRITE!!
	constexpr S_Mono &operator+=(const S_Mono &b) {
		if(a.first<T(b).first)a=T(b);
		else if(a.first==b.fi)a.se+=T(b).se;
		return *this;
	}
	// WRITE!!
	constexpr S_Mono() : a() {}
	constexpr S_Mono(T _a) : a(_a) {}
	constexpr S_Mono operator+(const S_Mono &b) const { return S_Mono(*this) += b; }
	constexpr operator T() const { return a; }
	constexpr bool operator==(const S_Mono &b) const { return (*this).a == b.a; }
	constexpr bool operator!=(const S_Mono &b) const { return (*this).a != b.a; }
};

/* struct F_Mono { */
/* 	static constexpr bool COMMUTATIVE = 0; */
/* 	// WRITE!! */
/* 	using value_type =; */
/* 	using T = value_type; */
/* 	T a; */
/* 	// WRITE!! */
/* 	constexpr F_Mono &operator+=(const F_Mono &b) { */
/* 		return *this; */
/* 	} */
/* 	// WRITE!! */
/* 	constexpr F_Mono() : a() {} */
/* 	constexpr F_Mono(T _a) : a(_a) {} */
/* 	constexpr F_Mono operator+(const F_Mono &b) const { return F_Mono(*this) += b; } */
/* 	constexpr operator T() const { return a; } */
/* 	constexpr bool operator==(const F_Mono &b) const { return (*this).a == b.a; } */
/* 	constexpr bool operator!=(const F_Mono &b) const { return (*this).a != b.a; } */
/* }; */

/* struct AM : ActedMonoid::CRTP<AM, S_Mono> { */
/* 	using Base = ActedMonoid::CRTP<AM, S_Mono>; */
/* 	using Base::Base; */
/* 	using ActingMonoid = F_Mono; */
/* 	// WRITE!! */
/* 	constexpr AM &operator^=(const ActingMonoid &b) { */
/* 		return *this; */
/* 	} */
/* 	constexpr AM operator^(const ActingMonoid &b) const { return AM(*this) ^= b; } */
/* }; */

