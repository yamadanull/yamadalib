using namespace yamada;

struct Group {
	static constexpr bool COMMUTE = 1;
	// WRITE!!
	using value_type =;
	using T = value_type;
	T a;
	// WRITE!!
	constexpr Group &operator+=(const Group &b) {
		return *this;
	}
	// WRITE!!
	constexpr Group &operator-=(const Group &b) {
		return *this;
	}
	// WRITE!!
	constexpr Group() : a() {}
	constexpr Group operator+(const Group &b) const { return Group(*this) += b; }
	constexpr Group operator-(const Group &b) const { return Group(*this) -= b; }
	constexpr Group operator-() const { return Group() - Group(*this); }
	constexpr Group(T _a) : a(_a) {}
	constexpr operator T() const { return a; }
	constexpr bool is_identity() const { return a == Group().a; }
};
