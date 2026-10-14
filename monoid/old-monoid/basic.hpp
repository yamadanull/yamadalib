#pragma once

namespace Monoid {

template <typename Derived, typename T>
struct Common {
	constexpr Derived operator+(const Derived &b) const { Derived r = static_cast<const Derived&>(*this); return r += b; }
	constexpr Derived operator-(const Derived &b) const { Derived r = static_cast<const Derived&>(*this); return r -= b; }
	constexpr Derived operator-() const { return Derived() - static_cast<const Derived&>(*this); }
	constexpr operator T() const { return static_cast<const Derived&>(*this).a; }
	constexpr bool operator==(const Derived &b) const { return static_cast<const Derived&>(*this).a == b.a; }
	constexpr bool operator!=(const Derived &b) const { return static_cast<const Derived&>(*this).a != b.a; }
};

template <typename T>
struct Plus : Common<Plus<T>, T> {
	static constexpr bool COMMUTATIVE = 1;
	using value_type = T;
	T a;
	constexpr Plus &operator+=(const Plus &b) {
		a += T(b);
		return *this;
	}
	constexpr Plus &operator-=(const Plus &b) {
		a -= T(b);
		return *this;
	}
	constexpr Plus() : a() {}
	constexpr Plus(T _a) : a(_a) {}
};

template <typename T, T MINF>
struct Max : Common<Max<T, MINF>, T> {
	static constexpr bool COMMUTATIVE = 1;
	using value_type = T;
	T a;
	constexpr Max &operator+=(const Max &b) {
		a = std::max(a, T(b));
		return *this;
	}
	constexpr Max() : a(MINF) {}
	constexpr Max(T _a) : a(_a) {}
};

template <typename T, T INF>
struct Min : Common<Min<T, INF>, T> {
	static constexpr bool COMMUTATIVE = 1;
	using value_type = T;
	T a;
	constexpr Min &operator+=(const Min &b) {
		a = std::min(a, T(b));
		return *this;
	}
	constexpr Min() : a(INF) {}
	constexpr Min(T _a) : a(_a) {}
};

template <typename T, T UNUSED_VALUE>
struct Update : Common<Update<T, UNUSED_VALUE>, T> {
	static constexpr bool COMMUTATIVE = 0;
	using value_type = T;
	T a;
	constexpr Update &operator+=(const Update &b) {
		if (T(b) != UNUSED_VALUE) a = T(b);
		return *this;
	}
	constexpr Update() : a(UNUSED_VALUE) {}
	constexpr Update(T _a) : a(_a) {}
};

template <typename MonoidBase>
struct CntMonoid { // コンテスト中にこれを直接扱うのは、頭が爆発するので非推奨
	static constexpr bool COMMUTATIVE = MonoidBase::COMMUTATIVE;
	using value_type = typename std::pair<int, MonoidBase>;
	using T = value_type;
	using T_Base = typename MonoidBase::value_type;
	T a;
	constexpr CntMonoid &operator+=(const CntMonoid &b) {
		a.first += T(b).first;
		a.second += T(b).second;
		return *this;
	}
	constexpr CntMonoid() : a(0, MonoidBase()) {}
	constexpr CntMonoid(T _a) : a(_a) {}
	constexpr CntMonoid(T_Base _a) : a(1, _a) {}
	constexpr CntMonoid operator+(const CntMonoid &b) const { return CntMonoid(*this) += b; }
	constexpr operator T() const { return a; }
	constexpr operator T_Base() const { return T_Base(a.second); }
	constexpr bool operator==(const CntMonoid &b) const { return CntMonoid(*this).a == b.a; }
	constexpr bool operator!=(const CntMonoid &b) const { return CntMonoid(*this).a != b.a; }
};

template <typename mint>
struct Affine : Common<Affine<mint>, std::pair<mint, mint>> {
	static constexpr bool COMMUTE = 0;
	using value_type = std::pair<mint, mint>;
	using T = value_type;
	T a;
	constexpr Affine &operator+=(const Affine &b) {
		a.first *= T(b).first;
		a.second *= T(b).first;
		a.second += T(b).second;
		return *this;
	}
	constexpr Affine() : a(1, 0) {}
	constexpr Affine(T _a) : a(_a) {}
	constexpr Affine(mint fi, mint se) : a({fi, se}) {}
};

} // namespace Monoid

namespace ActedMonoid {

using namespace Monoid;

template <typename Derived, typename Base>
struct CRTP : Base {
	using Base::Base;
	constexpr Derived& operator+=(const Derived& b) { Base::operator+=(b); return static_cast<Derived&>(*this); };
	constexpr Derived operator+(const Derived& b) const { Derived r = static_cast<const Derived&>(*this); return r += b; }
	constexpr bool operator==(const Derived &b) const { return static_cast<const Derived&>(*this).a == b.a; }
	constexpr bool operator!=(const Derived &b) const { return static_cast<const Derived&>(*this).a != b.a; }
};

template <typename T, T MINF>
struct Add_Max : CRTP<Add_Max<T, MINF>, Max<T, MINF>> {
	using Base = CRTP<Add_Max<T, MINF>, Max<T, MINF>>;
	using Base::Base;
	using ActingMonoid = Plus<T>;
	constexpr Add_Max<T, MINF> &operator^=(const ActingMonoid &b) {
		this->a += T(b);
		return *this;
	}
	constexpr Add_Max<T, MINF> operator^(const ActingMonoid &b) { return Add_Max<T, MINF>(*this) ^= b; }
};

template <typename T, T INF>
struct Add_Min : CRTP<Add_Min<T, INF>, Min<T, INF>> {
	using Base = CRTP<Add_Min<T, INF>, Min<T, INF>>;
	using Base::Base;
	using ActingMonoid = Plus<T>;
	constexpr Add_Min<T, INF> &operator^=(const ActingMonoid &b) {
		this->a += T(b);
		return *this;
	}
	constexpr Add_Min<T, INF> operator^(const ActingMonoid &b) { return Add_Min<T, INF>(*this) ^= b; }
};

template <typename T>
struct Add_Sum : CRTP<Add_Sum<T>, CntMonoid<Plus<T>>> {
	using Base = CRTP<Add_Sum<T>, CntMonoid<Plus<T>>>;
	using Base::Base;
	using ActingMonoid = Plus<T>;
	constexpr Add_Sum<T> &operator^=(const ActingMonoid &b) {
		(this->a).second += T(b) * (this->a).first;
		return *this;
	}
	constexpr Add_Sum<T> operator^(const ActingMonoid &b) { return Add_Sum(*this) ^= b; }
};

template <typename T, T MINF>
struct Update_Max : CRTP<Update_Max<T, MINF>, Max<T, MINF>> {
	using Base = CRTP<Update_Max<T, MINF>, Max<T, MINF>>;
	using Base::Base;
	using ActingMonoid = Update<T, MINF>;
	constexpr Update_Max<T, MINF> &operator^=(const ActingMonoid &b) {
		if (T(b) != MINF) this->a = T(b);
		return *this;
	}
	constexpr Update_Max<T, MINF> operator^(const ActingMonoid &b) { return Update_Max<T, MINF>(*this) ^= b; }
};

template <typename T, T INF>
struct Update_Min : CRTP<Update_Min<T, INF>, Min<T, INF>> {
	using Base = CRTP<Update_Min<T, INF>, Min<T, INF>>;
	using Base::Base;
	using ActingMonoid = Update<T, INF>;
	constexpr Update_Min<T, INF> &operator^=(const ActingMonoid &b) {
		if (T(b) != INF) this->a = T(b);
		return *this;
	}
	constexpr Update_Min<T, INF> operator^(const ActingMonoid &b) { return Update_Min<T, INF>(*this) ^= b; }
};

template <typename T, T UNUSED_VALUE>
struct Update_Sum : CRTP<Update_Sum<T, UNUSED_VALUE>, CntMonoid<Plus<T>>> {
	using Base = CRTP<Update_Sum<T, UNUSED_VALUE>, CntMonoid<Plus<T>>>;
	using Base::Base;
	using ActingMonoid = Update<T, UNUSED_VALUE>;
	constexpr Update_Sum<T, UNUSED_VALUE> &operator^=(const ActingMonoid &b) {
		if (T(b) != UNUSED_VALUE) (this->a).second = T(b) * (this->a).first;
		return *this;
	}
	constexpr Update_Sum<T, UNUSED_VALUE> operator^(const ActingMonoid &b) { return Update_Sum<T, UNUSED_VALUE>(*this) ^= b; }
};

template <typename mint>
struct Affine_Sum : CRTP<Affine_Sum<mint>, CntMonoid<Plus<mint>>> {
	using Base = CRTP<Affine_Sum<mint>, CntMonoid<Plus<mint>>>;
	using Base::Base;
	using ActingMonoid = Affine<mint>;
	constexpr Affine_Sum<mint> &operator^=(const ActingMonoid &b) {
		((this->a).second).a *= b.a.first;
		((this->a).second).a += b.a.second * (this->a).first;
		return *this;
	}
	constexpr Affine_Sum<mint> operator^(const ActingMonoid &b) { return Affine_Sum<mint>(*this) ^= b; }
};

} // namespace ActedMonoid
