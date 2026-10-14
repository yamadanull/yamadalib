using namespace yamada;

struct S_Mono {
	static constexpr bool COMMUTATIVE = 0;
	// WRITE!!
	using value_type =Mat<rig,2>;
	using T = value_type;
	T a;
	// WRITE!!
	constexpr S_Mono &operator+=(const S_Mono &b) {
		a*=b.a;
		return *this;
	}
	// WRITE!!
	constexpr S_Mono() : a(T::I()) {}
	constexpr S_Mono(T _a) : a(_a) {}
	constexpr S_Mono operator+(const S_Mono &b) const { return S_Mono(*this) += b; }
	constexpr operator T() const { return a; }
	constexpr bool operator==(const S_Mono &b) const {
		rep(i,2)rep(j,2){
			if(a[i][j]!=b.a[i][j])return 0;
		}
		return 1;
	}
	constexpr bool operator!=(const S_Mono &b) const {
		rep(i,2)rep(j,2){
			if(a[i][j]!=b.a[i][j])return 1;
		}
		return 0;
	}
};
