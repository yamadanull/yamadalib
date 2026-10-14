using namespace yamada;

struct Mono {
	static constexpr bool COMMUTATIVE = 0;
	// WRITE!!
	using value_type =;
	using T = value_type;
	T a;
	// WRITE!!
	constexpr Mono &operator+=(const Mono &b) {
		return *this;
	}
	// WRITE!!
	constexpr Mono() : a() {}
	constexpr Mono(T _a) : a(_a) {}
	constexpr Mono operator+(const Mono &b) const { return Mono(*this) += b; }
	constexpr operator T() const { return a; }
	constexpr bool operator==(const Mono &b) const { return (*this).a == b.a; }
	constexpr bool operator!=(const Mono &b) const { return (*this).a != b.a; }
};
