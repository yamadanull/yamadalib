using namespace yamada;

struct Mono {
	static constexpr bool COMMUTATIVE = 1;
	// WRITE!!
	using value_type =pl;
	using T = value_type;
	T a;
	// WRITE!!
	constexpr Mono &operator+=(const Mono &b) {
		if(a.first<T(b).first)a=T(b);
		else if(a.first==T(b).fi)a.se+=T(b).se;
		return *this;
	}
	// WRITE!!
	constexpr Mono() : a(mkp(-infLL,0)) {}
	constexpr Mono(T _a) : a(_a) {}
	constexpr Mono operator+(const Mono &b) const { return Mono(*this) += b; }
	constexpr operator T() const { return a; }
	constexpr bool operator==(const Mono &b) const { return (*this).a == b.a; }
	constexpr bool operator!=(const Mono &b) const { return (*this).a != b.a; }
};
