// Begin include: "../../template/template.hpp"
using namespace std;

// intrinstic
#include <immintrin.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfenv>
#include <cfloat>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <streambuf>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// Begin include: "util.hpp"
namespace yamada {
using ll = long long;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;
using lld = long double;

template <typename T>
using V = vector<T>;
template <typename T>
using VV = vector<vector<T>>;
template <typename T>
using VVV = vector<vector<vector<T>>>;
template <typename T>
using VVVV = vector<vector<vector<vector<T>>>>;
using vl = vector<long long>;
using vd = V<double>;
using vs = V<string>;
using vvl = vector<vector<long long>>;
using vvvl = vector<vector<vector<long long>>>;
using vvvvl = vector<vector<vector<vector<long long>>>>;
template <typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxpq = priority_queue<T, vector<T>, less<T>>;

template <typename T, typename U>
struct P : pair<T, U> {
	template <typename... Args>
	P(Args... args) : pair<T, U>(args...) {}

	using pair<T, U>::first;
	using pair<T, U>::second;

	P &operator+=(const P &r) {
		first += r.first;
		second += r.second;
		return *this;
	}
	P &operator-=(const P &r) {
		first -= r.first;
		second -= r.second;
		return *this;
	}
	P &operator*=(const P &r) {
		first *= r.first;
		second *= r.second;
		return *this;
	}
	template <typename S>
	P &operator*=(const S &r) {
		first *= r, second *= r;
		return *this;
	}
	P operator+(const P &r) const { return P(*this) += r; }
	P operator-(const P &r) const { return P(*this) -= r; }
	P operator*(const P &r) const { return P(*this) *= r; }
	template <typename S>
	P operator*(const S &r) const {
		return P(*this) *= r;
	}
	P operator-() const { return P{-first, -second}; }
};

using pl = P<ll, ll>;
using vp = V<pl>;
using vvp = VV<pl>;

constexpr int inf = 1001001001;
constexpr long long infLL = 4004004004004004004LL;

template <typename T, typename U>
inline bool amin(T &x, U y) { return (y < x) ? (x = y, true) : false; }
template <typename T, typename U>
inline bool amax(T &x, U y) { return (x < y) ? (x = y, true) : false; }

template <typename T>
inline T Max(const vector<T> &v) { return *max_element(begin(v), end(v)); }
template <typename T>
inline T Min(const vector<T> &v) { return *min_element(begin(v), end(v)); }
template <typename T>
inline long long Sum(const vector<T> &v) { return accumulate(begin(v), end(v), T(0)); }

template <typename T>
int lb(const vector<T> &v, const T &a) { return lower_bound(begin(v), end(v), a) - begin(v); }
template <typename T>
int ub(const vector<T> &v, const T &a) { return upper_bound(begin(v), end(v), a) - begin(v); }

constexpr long long TEN(int n) {
	long long ret = 1, x = 10;
	for (; n; x *= x, n >>= 1) ret *= (n & 1 ? x : 1);
	return ret;
}

template <typename T>
vector<T> mkrui(const vector<T> &v, bool rev = false) {
	vector<T> ret(v.size() + 1);
	if (rev) {
		for (int i = int(v.size()) - 1; i >= 0; i--) ret[i] = v[i] + ret[i + 1];
	} else {
		for (int i = 0; i < int(v.size()); i++) ret[i + 1] = ret[i] + v[i];
	}
	return ret;
};

template <typename T>
vector<T> mkuni(const vector<T> &v) {
	vector<T> ret(v);
	sort(ret.begin(), ret.end());
	ret.erase(unique(ret.begin(), ret.end()), ret.end());
	return ret;
}

template <typename F>
vector<int> mkord(int N, F f) {
	vector<int> ord(N);
	iota(begin(ord), end(ord), 0);
	sort(begin(ord), end(ord), f);
	return ord;
}

template <typename T>
vector<int> mkinv(vector<T> &v) {
	int max_val = *max_element(begin(v), end(v));
	vector<int> inv(max_val + 1, -1);
	for (int i = 0; i < (int)v.size(); i++) inv[v[i]] = i;
	return inv;
}

vector<int> mkiota(int n) {
	vector<int> ret(n);
	iota(begin(ret), end(ret), 0);
	return ret;
}

template <typename T>
T mkrev(const T &v) {
	T w{v};
	reverse(begin(w), end(w));
	return w;
}

template <typename T>
bool nxp(T &v) { return next_permutation(begin(v), end(v)); }

// 返り値の型は入力の T に依存
// i 要素目 : [0, a[i])
template <typename T>
vector<vector<T>> product(const vector<T> &a) {
	vector<vector<T>> ret;
	vector<T> v;
	auto dfs = [&](auto rc, int i) -> void {
		if (i == (int)a.size()) {
			ret.push_back(v);
			return;
		}
		for (int j = 0; j < a[i]; j++) v.push_back(j), rc(rc, i + 1), v.pop_back();
	};
	dfs(dfs, 0);
	return ret;
}

template <typename T, typename U>
vector<U> Digit(T a, const U &x, int siz = -1) {
	vector<U> ret;
	while (a > 0) {
		ret.emplace_back(a % x);
		a /= x;
	}
	if (siz >= 0) while ((int)ret.size() < siz) ret.emplace_back(0);
	return ret;
}

// F : function(void(T&)), mod を取る操作
// T : 整数型のときはオーバーフローに注意する
template <typename T>
T Power(T a, long long n, const T &I, const function<void(T &)> &f) {
	T res = I;
	for (; n; f(a = a * a), n >>= 1) {
		if (n & 1) f(res = res * a);
	}
	return res;
}
// T : 整数型のときはオーバーフローに注意する
template <typename T>
T Power(T a, long long n, const T &I = T{1}) {
	return Power(a, n, I, function<void(T &)>{[](T &) -> void {}});
}

template <typename T>
T Rev(const T &v) {
	T res = v;
	reverse(begin(res), end(res));
	return res;
}

template <typename T>
vector<T> Transpose(const vector<T> &v) {
	using U = typename T::value_type;
	if(v.empty()) return {};
	int H = v.size(), W = v[0].size();
	vector res(W, T(H, U{}));
	for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) res[j][i] = v[i][j];
	return res;
}

template <typename T>
vector<T> Rotate(const vector<T> &v, int clockwise = true) {
	using U = typename T::value_type;
	int H = v.size(), W = v[0].size();
	vector res(W, T(H, U{}));
	for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) {
		if (clockwise) res[W - 1 - j][i] = v[i][j];
		else res[j][H - 1 - i] = v[i][j];
	}
	return res;
}

template <typename T, typename F>
T bisect(T ok, T bad, F pred) {
	if (ok == bad) return ok;
	while (bad - ok > 1) { T mid = ok + (bad - ok) / 2; (pred(mid) ? ok : bad) = mid; } 
	return bad;
}

template <typename T, typename F>
T bisect_double(T ok, T bad, F pred, int iter = 100) {
	if (ok == bad) return ok;
	while (iter--) { T mid = ok + (bad - ok) / 2; (pred(mid) ? ok : bad) = mid; } 
	return bad;
}

template <typename T>
bool inLR(T L, T x, T R){ return (L <= x && x < R); }

bool YESNO(bool b) { std::cout << (b ? "YES\n" : "NO\n"); return b; }
bool YesNo(bool b) { std::cout << (b ? "Yes\n" : "No\n"); return b; }

template <typename mint>
std::string toFraction(mint a, int M) {
	for (int deno = 1; deno <= M; deno++) {
		mint inv = ((mint)deno).inverse();
		for (int nume = -M; nume <= M; nume++) {
			mint val = inv * nume;
			if (val == a) {
				if (deno == 1) return std::to_string(nume);
				return std::to_string(nume) + "/" + std::to_string(deno);
			}
		}
	}
	return "NF";
}

template <typename mint>
void mout(mint a, int M = 100) { std::cout << toFraction(a, M) << "\n"; }
template <typename mint>
void mout(std::vector<mint> A, int M = 100) {
	for (int i = 0; i < (int)A.size(); i++) {
		std::cout << toFraction(A[i], M) << (i == (int)A.size() - 1 ? "\n" : " ");
	}
}

bool is_square(uint64_t n) {
	if (n < 2) return true;
	uint64_t r = static_cast<uint64_t>(sqrtl(static_cast<long double>(n)));
	if (r * r == n) return true;
	++r;
	return r * r == n;
}

template <typename T>
struct CumulativeSum {
	std::vector<T> S;
	CumulativeSum(std::vector<T> &A) {
		int N = A.size();
		S.resize(N + 1);
		for (int i = 0; i < N; i++) S[i + 1] = S[i] + A[i];
	}

	T query(int l, int r) { return (l <= r ? S[r] - S[l] : (T)0); }
	T get_val(int i) { return S[i + 1] - S[i]; }
};

template <typename T>
T Floor(T a, T b) { return a / b - (a % b && (a ^ b) < 0); }
template <typename T>
T Ceil(T a, T b) { return a / b + (a % b && (a ^ b) >= 0); }

} // namespace yamada

// End include: "util.hpp"
// Begin include: "bitop.hpp"
namespace yamada {
__attribute__((target("popcnt"))) inline int popcnt(const u64 &a) {
  return __builtin_popcountll(a);
}
inline int lsb(const u64 &a) { return a ? __builtin_ctzll(a) : 64; }
inline int ctz(const u64 &a) { return a ? __builtin_ctzll(a) : 64; }
inline int msb(const u64 &a) { return a ? 63 - __builtin_clzll(a) : -1; }
template <typename T>
inline int gbit(const T &a, int i) {
  return (a >> i) & 1;
}
template <typename T>
inline void sbit(T &a, int i, bool b) {
  if (gbit(a, i) != b) a ^= T(1) << i;
}
constexpr long long PW(int n) { return 1LL << n; }
constexpr long long MSK(int n) { return (1LL << n) - 1; }
}  // namespace yamada
// End include: "bitop.hpp"
// Begin include: "inout.hpp"
namespace yamada {

template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
	os << p.first << " " << p.second;
	return os;
}
template <typename T, typename U>
istream &operator>>(istream &is, pair<T, U> &p) {
	is >> p.first >> p.second;
	return is;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
	int s = (int)v.size();
	for (int i = 0; i < s; i++) os << (i ? " " : "") << v[i];
	return os;
}
template <typename T>
istream &operator>>(istream &is, vector<T> &v) {
	for (auto &x : v) is >> x;
	return is;
}

istream &operator>>(istream &is, __int128_t &x) {
	string S;
	is >> S;
	x = 0;
	int flag = 0;
	for (auto &c : S) {
		if (c == '-') {
			flag = true;
			continue;
		}
		x *= 10;
		x += c - '0';
	}
	if (flag) x = -x;
	return is;
}

istream &operator>>(istream &is, __uint128_t &x) {
	string S;
	is >> S;
	x = 0;
	for (auto &c : S) {
		x *= 10;
		x += c - '0';
	}
	return is;
}

ostream &operator<<(ostream &os, __int128_t x) {
	if (x == 0) return os << 0;
	if (x < 0) os << '-', x = -x;
	string S;
	while (x) S.push_back('0' + x % 10), x /= 10;
	reverse(begin(S), end(S));
	return os << S;
}
ostream &operator<<(ostream &os, __uint128_t x) {
	if (x == 0) return os << 0;
	string S;
	while (x) S.push_back('0' + x % 10), x /= 10;
	reverse(begin(S), end(S));
	return os << S;
}

void in() {}
template <typename T, class... U>
void in(T &t, U &...u) {
	cin >> t;
	in(u...);
}

void out() { cout << "\n"; }
template <typename T, class... U, char sep = ' '>
void out(const T &t, const U &...u) {
	cout << t;
	if (sizeof...(u)) cout << sep;
	out(u...);
}

struct IoSetupYamada {
	IoSetupYamada() {
		cin.tie(nullptr);
		ios::sync_with_stdio(false);
		cout << fixed << setprecision(15);
		cerr << fixed << setprecision(7);
	}
} iosetupyamada;

}  // namespace yamada
// End include: "inout.hpp"
// Begin include: "macro.hpp"
#define each(x, v) for (auto&& x : v)
#define each2(x, y, v) for (auto&& [x, y] : v)
#define each3(x, y, z, v) for (auto&& [x, y, z] : v)
#define all(v) (v).begin(), (v).end()

#define rep1(a) for (long long _ = 0; _ < (long long)(a); ++_)
#define rep2(i, a) for (long long i = 0; i < (long long)(a); ++i)
#define rep3(i, a, b) for (long long i = a; i < (long long)(b); ++i)
#define rep4(i, a, b, c) for (long long i = a; i < (long long)(b); i += c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)

#define rep1r(a) for (long long i = (long long)(a)-1; i >= 0LL; --i)
#define rep2r(i, a) for (long long i = (long long)(a)-1; i >= 0LL; --i)
#define rep3r(i, a, b) for (long long i = (long long)(b)-1; i >= (long long)(a); --i)
#define overload3(a, b, c, d, ...) d
#define repr(...) overload3(__VA_ARGS__, rep3r, rep2r, rep1r)(__VA_ARGS__)

#define eb emplace_back
#define mkp make_pair
#define mkt make_tuple
#define fi first
#define se second

#define vv(type, name, h, ...)  \
	vector<vector<type> > name(h, vector<type>(__VA_ARGS__))
#define vvv(type, name, h, w, ...) \
	vector<vector<vector<type>>> name( \
			h, vector<vector<type>>(w, vector<type>(__VA_ARGS__)))
#define vvvv(type, name, a, b, c, ...)  \
	vector<vector<vector<vector<type>>>> name( \
			a, vector<vector<vector<type>>>( \
				b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))

#define ini(...)   \
	int __VA_ARGS__; \
	in(__VA_ARGS__)
#define inl(...)         \
	long long __VA_ARGS__; \
	in(__VA_ARGS__)
#define ins(...)      \
	string __VA_ARGS__; \
	in(__VA_ARGS__)
#define in2(s, t)                           \
	for (int i = 0; i < (int)s.size(); i++) { \
		in(s[i], t[i]);                         \
	}
#define in3(s, t, u)                        \
	for (int i = 0; i < (int)s.size(); i++) { \
		in(s[i], t[i], u[i]);                   \
	}
#define in4(s, t, u, v)                     \
	for (int i = 0; i < (int)s.size(); i++) { \
		in(s[i], t[i], u[i], v[i]);             \
	}
#define die(...)             \
	do {                       \
		yamada::out(__VA_ARGS__);\
		return;                  \
	} while (0)
// End include: "macro.hpp"

namespace yamada {
void solve();
}
int main() { yamada::solve(); }
// End include: "../../template/template.hpp"
// Begin include: "../../math/rational.hpp"

#include <cassert>
#include <numeric>
#include <vector>
using namespace std;

// Begin include: "../internal/internal-type-traits.hpp"

#include <type_traits>
using namespace std;

namespace internal {
template <typename T>
using is_broadly_integral =
    typename conditional_t<is_integral_v<T> || is_same_v<T, __int128_t> ||
                               is_same_v<T, __uint128_t>,
                           true_type, false_type>::type;

template <typename T>
using is_broadly_signed =
    typename conditional_t<is_signed_v<T> || is_same_v<T, __int128_t>,
                           true_type, false_type>::type;

template <typename T>
using is_broadly_unsigned =
    typename conditional_t<is_unsigned_v<T> || is_same_v<T, __uint128_t>,
                           true_type, false_type>::type;

#define ENABLE_VALUE(x) \
  template <typename T> \
  constexpr bool x##_v = x<T>::value;

ENABLE_VALUE(is_broadly_integral);
ENABLE_VALUE(is_broadly_signed);
ENABLE_VALUE(is_broadly_unsigned);
#undef ENABLE_VALUE

#define ENABLE_HAS_TYPE(var)                                   \
  template <class, class = void>                               \
  struct has_##var : false_type {};                            \
  template <class T>                                           \
  struct has_##var<T, void_t<typename T::var>> : true_type {}; \
  template <class T>                                           \
  constexpr auto has_##var##_v = has_##var<T>::value;

#define ENABLE_HAS_VAR(var)                                     \
  template <class, class = void>                                \
  struct has_##var : false_type {};                             \
  template <class T>                                            \
  struct has_##var<T, void_t<decltype(T::var)>> : true_type {}; \
  template <class T>                                            \
  constexpr auto has_##var##_v = has_##var<T>::value;

}  // namespace internal
// End include: "../internal/internal-type-traits.hpp"
// Begin include: "../math-fast/gcd.hpp"

#include <algorithm>
using namespace std;

namespace BinaryGCDImpl {
using u64 = unsigned long long;
using i8 = char;

u64 binary_gcd(u64 a, u64 b) {
  if (a == 0 || b == 0) return a + b;
  i8 n = __builtin_ctzll(a);
  i8 m = __builtin_ctzll(b);
  a >>= n;
  b >>= m;
  n = min(n, m);
  while (a != b) {
    u64 d = a - b;
    i8 s = __builtin_ctzll(d);
    bool f = a > b;
    b = f ? b : a;
    a = (f ? d : -d) >> s;
  }
  return a << n;
}

using u128 = __uint128_t;
// a > 0
int ctz128(u128 a) {
  u64 lo = a & u64(-1);
  return lo ? __builtin_ctzll(lo) : 64 + __builtin_ctzll(a >> 64);
}
u128 binary_gcd128(u128 a, u128 b) {
  if (a == 0 || b == 0) return a + b;
  i8 n = ctz128(a);
  i8 m = ctz128(b);
  a >>= n;
  b >>= m;
  n = min(n, m);
  while (a != b) {
    u128 d = a - b;
    i8 s = ctz128(d);
    bool f = a > b;
    b = f ? b : a;
    a = (f ? d : -d) >> s;
  }
  return a << n;
}

}  // namespace BinaryGCDImpl

long long binary_gcd(long long a, long long b) {
  return BinaryGCDImpl::binary_gcd(abs(a), abs(b));
}
__int128_t binary_gcd128(__int128_t a, __int128_t b) {
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  return BinaryGCDImpl::binary_gcd128(a, b);
}

/**
 * @brief binary GCD
 */
// End include: "../math-fast/gcd.hpp"

// T : 値, U : 比較用
template <typename T, typename U>
struct RationalBase {
	using R = RationalBase;
	using Key = T;
	T x, y;
	RationalBase() : x(0), y(1) {}
	template <typename T1>
	RationalBase(const T1& _x) : RationalBase<T, U>(_x, T1{1}) {}
	template <typename T1, typename T2>
	RationalBase(const pair<T1, T2>& _p)
		: RationalBase<T, U>(_p.first, _p.second) {}
	template <typename T1, typename T2>
	RationalBase(const T1& _x, const T2& _y) : x(_x), y(_y) {
		assert(y != 0);
		if (y == -1) x = -x, y = -y;
		if (y != 1) {
			T g;
			if constexpr (internal::is_broadly_integral_v<T>) {
				if constexpr (sizeof(T) == 16) {
					g = binary_gcd128(x, y);
				} else {
					g = binary_gcd(x, y);
				}
			} else {
				g = gcd(x, y);
			}
			if (g != 0) x /= g, y /= g;
			if (y < 0) x = -x, y = -y;
		}
	}
	// y = 0 の代入も認める
	static R raw(T _x, T _y) {
		R r;
		r.x = _x, r.y = _y;
		return r;
	}
	friend R operator+(const R& l, const R& r) {
		if (l.y == r.y) return R{l.x + r.x, l.y};
		return R{l.x * r.y + l.y * r.x, l.y * r.y};
	}
	friend R operator-(const R& l, const R& r) {
		if (l.y == r.y) return R{l.x - r.x, l.y};
		return R{l.x * r.y - l.y * r.x, l.y * r.y};
	}
	friend R operator*(const R& l, const R& r) { return R{l.x * r.x, l.y * r.y}; }
	friend R operator/(const R& l, const R& r) { return R{l.x * r.y, l.y * r.x}; }
	R& operator+=(const R& r) { return (*this) = (*this) + r; }
	R& operator-=(const R& r) { return (*this) = (*this) - r; }
	R& operator*=(const R& r) { return (*this) = (*this) * r; }
	R& operator/=(const R& r) { return (*this) = (*this) / r; }
	R operator-() const { return raw(-x, y); }
	R inverse() const {
		assert(x != 0);
		R r = raw(y, x);
		if (r.y < 0) r.x = -r.x, r.y = -r.y;
		return r;
	}
	R pow(long long p) const {
		R res{1}, base{*this};
		while (p) {
			if (p & 1) res *= base;
			base *= base;
			p >>= 1;
		}
		return res;
	}
	friend bool operator==(const R& l, const R& r) {
		return l.x == r.x && l.y == r.y;
	};
	friend bool operator!=(const R& l, const R& r) {
		return l.x != r.x || l.y != r.y;
	};
	friend bool operator<(const R& l, const R& r) {
		return U{l.x} * r.y < U{l.y} * r.x;
	};
	friend bool operator<=(const R& l, const R& r) { return l < r || l == r; }
	friend bool operator>(const R& l, const R& r) {
		return U{l.x} * r.y > U{l.y} * r.x;
	};
	friend bool operator>=(const R& l, const R& r) { return l > r || l == r; }
	friend ostream& operator<<(ostream& os, const R& r) {
		os << r.x;
		if (r.x != 0 && r.y != 1) os << "/" << r.y;
		return os;
	}

	// T にキャストされるので T が bigint の場合は to_ll も要る
	T to_mint(T mod) const {
		assert(mod != 0);
		T a = y, b = mod, u = 1, v = 0, t;
		while (b > 0) {
			t = a / b;
			swap(a -= t * b, b);
			swap(u -= t * v, v);
		}
		return U((u % mod + mod) % mod) * x % mod;
	}

	long double to_lld() const {
		return (long double)x / y;
	}
};

using Rational = RationalBase<long long, __int128_t>;
using Fraction = Rational;
// End include: "../../math/rational.hpp"
// Begin include: "../../math/bigint-all.hpp"

// Begin include: "rational-binomial.hpp"

// Begin include: "rational.hpp"

// End include: "rational.hpp"

template <typename R = Rational>
struct Binomial_rational {
  vector<R> fc;
  Binomial_rational(int = 0) { fc.emplace_back(1); }
  void extend() {
    int n = fc.size();
    R nxt = fc.back() * n;
    fc.push_back(nxt);
  }
  R fac(int n) {
    if (n < 0) return 0;
    while ((int)fc.size() <= n) extend();
    return fc[n];
  }
  R finv(int n) {
    if (n < 0) return 0;
    return fac(n).inverse();
  }
  R inv(int n) {
    if (n < 0) return -inv(-n);
    return R{1, max(n, 1)};
  }
  R C(int n, int r) {
    if (n < 0 or r < 0 or n < r) return R{0};
    return fac(n) * finv(n - r) * finv(r);
  }
  R operator()(int n, int r) { return C(n, r); }
  template <typename I>
  R multinomial(const vector<I>& r) {
    static_assert(is_integral<I>::value == true);
    int n = 0;
    for (auto& x : r) {
      if (x < 0) return R{0};
      n += x;
    }
    R res = fac(n);
    for (auto& x : r) res *= finv(x);
    return res;
  }

  template <typename I>
  R operator()(const vector<I>& r) {
    return multinomial(r);
  }
  
  R P(int n, int r) {
    if (n < 0 || n < r || r < 0) return R(0);
    return fac(n) * finv(n - r);
  }
  // [x^r] 1 / (1-x)^n
  R H(int n, int r) {
    if (n < 0 || r < 0) return R(0);
    return r == 0 ? 1 : C(n + r - 1, r);
  }
};
// End include: "rational-binomial.hpp"
// Begin include: "rational-fps.hpp"

// Begin include: "rational-binomial.hpp"

// End include: "rational-binomial.hpp"
// Begin include: "rational.hpp"

// End include: "rational.hpp"

template <typename R = Rational>
struct FormalPowerSeries_rational : vector<R> {
  using vector<R>::vector;
  using fps = FormalPowerSeries_rational;

  fps &operator+=(const fps &r) {
    if (r.size() > this->size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];
    return *this;
  }

  fps &operator+=(const R &r) {
    if (this->empty()) this->resize(1);
    (*this)[0] += r;
    return *this;
  }

  fps &operator-=(const fps &r) {
    if (r.size() > this->size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];
    return *this;
  }

  fps &operator-=(const R &r) {
    if (this->empty()) this->resize(1);
    (*this)[0] -= r;
    return *this;
  }

  fps &operator*=(const fps &r) {
    int n = this->size() + r.size() - 1;
    fps f(n);
    for (int i = 0; i < (int)this->size(); i++) {
      for (int j = 0; j < (int)r.size(); j++) {
        f[i + j] += (*this)[i] * r[j];
      }
    }
    return *this = f;
  }

  fps &operator*=(const R &v) {
    for (int k = 0; k < (int)this->size(); k++) (*this)[k] *= v;
    return *this;
  }

  fps &operator/=(const fps &r) {
    if (this->size() < r.size()) {
      this->clear();
      return *this;
    }
    int n = this->size() - r.size() + 1;
    fps f(*this), g(r);
    g.shrink();
    R coeff = g.back().inverse();
    for (auto &x : g) x *= coeff;
    int deg = (int)f.size() - (int)g.size() + 1;
    int gs = g.size();
    fps quo(deg);
    for (int i = deg - 1; i >= 0; i--) {
      quo[i] = f[i + gs - 1];
      for (int j = 0; j < gs; j++) f[i + j] -= quo[i] * g[j];
    }
    *this = quo * coeff;
    this->resize(n, R(0));
    return *this;
  }

  fps &operator%=(const fps &r) {
    *this -= *this / r * r;
    shrink();
    return *this;
  }

  fps operator+(const fps &r) const { return fps(*this) += r; }
  fps operator+(const R &v) const { return fps(*this) += v; }
  fps operator-(const fps &r) const { return fps(*this) -= r; }
  fps operator-(const R &v) const { return fps(*this) -= v; }
  fps operator*(const fps &r) const { return fps(*this) *= r; }
  fps operator*(const R &v) const { return fps(*this) *= v; }
  fps operator/(const fps &r) const { return fps(*this) /= r; }
  fps operator%(const fps &r) const { return fps(*this) %= r; }
  fps operator-() const {
    fps ret(this->size());
    for (int i = 0; i < (int)this->size(); i++) ret[i] = -(*this)[i];
    return ret;
  }

  void shrink() {
    while (this->size() && this->back() == R(0)) this->pop_back();
  }

  fps rev() const {
    fps ret(*this);
    reverse(begin(ret), end(ret));
    return ret;
  }

  fps dot(fps r) const {
    fps ret(min(this->size(), r.size()));
    for (int i = 0; i < (int)ret.size(); i++) ret[i] = (*this)[i] * r[i];
    return ret;
  }

  // 前 sz 項を取ってくる。sz に足りない項は 0 埋めする
  fps pre(int sz) const {
    fps ret(begin(*this), begin(*this) + min((int)this->size(), sz));
    if ((int)ret.size() < sz) ret.resize(sz);
    return ret;
  }

  fps operator>>(int sz) const {
    if ((int)this->size() <= sz) return {};
    fps ret(*this);
    ret.erase(ret.begin(), ret.begin() + sz);
    return ret;
  }

  fps operator<<(int sz) const {
    fps ret(*this);
    ret.insert(ret.begin(), sz, R(0));
    return ret;
  }

  fps diff() const {
    const int n = (int)this->size();
    fps ret(max(0, n - 1));
    R one(1), coeff(1);
    for (int i = 1; i < n; i++) {
      ret[i - 1] = (*this)[i] * coeff;
      coeff += one;
    }
    return ret;
  }

  fps integral() const {
    const int n = (int)this->size();
    fps ret(n + 1);
    for (int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / (i + 1);
    return ret;
  }

  R eval(R x) const {
    R r = 0, w = 1;
    for (auto &v : *this) r += w * v, w *= x;
    return r;
  }

  fps inv(int deg = -1) const {
    assert((*this)[0] != R(0));
    if (deg == -1) deg = (*this).size();
    fps ret{R(1) / (*this)[0]};
    for (int i = 1; i < deg; i <<= 1) {
      ret = (ret + ret - ret * ret * (*this).pre(i << 1)).pre(i << 1);
    }
    return ret.pre(deg);
  }
  fps log(int deg = -1) const {
    assert(!(*this).empty() && (*this)[0] == R(1));
    if (deg == -1) deg = (int)this->size();
    return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
  }
  fps exp(int deg = -1) const {
    assert((*this).size() == 0 || (*this)[0] == R(0));
    if (deg == -1) deg = (int)this->size();
    fps ret{R(1)};
    for (int i = 1; i < deg; i <<= 1) {
      ret = (ret * (pre(i << 1) + R(1) - ret.log(i << 1))).pre(i << 1);
    }
    return ret.pre(deg);
  }
  fps pow(int64_t k, int deg = -1) const {
    const int n = (int)this->size();
    if (deg == -1) deg = n;
    if (k == 0) {
      fps ret(deg);
      if (deg) ret[0] = 1;
      return ret;
    }
    for (int i = 0; i < n; i++) {
      if ((*this)[i] != R(0)) {
        R rev = R(1) / (*this)[i];
        fps ret = (((*this * rev) >> i).log(deg) * k).exp(deg);
        ret *= (*this)[i].pow(k);
        ret = (ret << (i * k)).pre(deg);
        if ((int)ret.size() < deg) ret.resize(deg, R(0));
        return ret;
      }
      if (__int128_t(i + 1) * k >= deg) return fps(deg, R(0));
    }
    return fps(deg, R(0));
  }
};
// End include: "rational-fps.hpp"
// Begin include: "rational.hpp"

// End include: "rational.hpp"
//
// Begin include: "bigint-rational.hpp"

// Begin include: "bigint-gcd.hpp"

#include <numeric>
using namespace std;

// Begin include: "../math-fast/gcd.hpp"

// End include: "../math-fast/gcd.hpp"
// Begin include: "bigint.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

// Begin include: "../internal/internal-type-traits.hpp"

// End include: "../internal/internal-type-traits.hpp"
// Begin include: "../ntt/arbitrary-ntt.hpp"

// Begin include: "../modint/montgomery-modint.hpp"

template <uint32_t mod>
struct LazyMontgomeryModInt {
  using mint = LazyMontgomeryModInt;
  using i32 = int32_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 ret = mod;
    for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
    return ret;
  }

  static constexpr u32 r = get_r();
  static constexpr u32 n2 = -u64(mod) % mod;
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");
  static_assert(r * mod == 1, "this code has bugs.");

  u32 a;

  constexpr LazyMontgomeryModInt() : a(0) {}
  constexpr LazyMontgomeryModInt(const int64_t &b)
      : a(reduce(u64(b % mod + mod) * n2)){};

  static constexpr u32 reduce(const u64 &b) {
    return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
  }

  constexpr mint &operator+=(const mint &b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator-=(const mint &b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator*=(const mint &b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  constexpr mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
  constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
  constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
  constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
  constexpr bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr bool operator!=(const mint &b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr mint operator-() const { return mint() - mint(*this); }
  constexpr mint operator+() const { return mint(*this); }

  constexpr mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  constexpr mint inverse() const {
    int x = get(), y = mod, u = 1, v = 0, t = 0, tmp = 0;
    while (y > 0) {
      t = x / y;
      x -= t * y, u -= t * v;
      tmp = x, x = y, y = tmp;
      tmp = u, u = v, v = tmp;
    }
    return mint{u};
  }

  friend ostream &operator<<(ostream &os, const mint &b) {
    return os << b.get();
  }

  friend istream &operator>>(istream &is, mint &b) {
    int64_t t;
    is >> t;
    b = LazyMontgomeryModInt<mod>(t);
    return (is);
  }

  constexpr u32 get() const {
    u32 ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static constexpr u32 get_mod() { return mod; }
};
// End include: "../modint/montgomery-modint.hpp"
// Begin include: "./ntt.hpp"

template <typename mint>
struct NTT {
  static constexpr uint32_t get_pr() {
    uint32_t _mod = mint::get_mod();
    using u64 = uint64_t;
    u64 ds[32] = {};
    int idx = 0;
    u64 m = _mod - 1;
    for (u64 i = 2; i * i <= m; ++i) {
      if (m % i == 0) {
        ds[idx++] = i;
        while (m % i == 0) m /= i;
      }
    }
    if (m != 1) ds[idx++] = m;

    uint32_t _pr = 2;
    while (1) {
      int flg = 1;
      for (int i = 0; i < idx; ++i) {
        u64 a = _pr, b = (_mod - 1) / ds[i], r = 1;
        while (b) {
          if (b & 1) r = r * a % _mod;
          a = a * a % _mod;
          b >>= 1;
        }
        if (r == 1) {
          flg = 0;
          break;
        }
      }
      if (flg == 1) break;
      ++_pr;
    }
    return _pr;
  };

  static constexpr uint32_t mod = mint::get_mod();
  static constexpr uint32_t pr = get_pr();
  static constexpr int level = __builtin_ctzll(mod - 1);
  mint dw[level], dy[level];

  void setwy(int k) {
    mint w[level], y[level];
    w[k - 1] = mint(pr).pow((mod - 1) / (1 << k));
    y[k - 1] = w[k - 1].inverse();
    for (int i = k - 2; i > 0; --i)
      w[i] = w[i + 1] * w[i + 1], y[i] = y[i + 1] * y[i + 1];
    dw[1] = w[1], dy[1] = y[1], dw[2] = w[2], dy[2] = y[2];
    for (int i = 3; i < k; ++i) {
      dw[i] = dw[i - 1] * y[i - 2] * w[i];
      dy[i] = dy[i - 1] * w[i - 2] * y[i];
    }
  }

  NTT() { setwy(level); }

  void fft4(vector<mint> &a, int k) {
    if ((int)a.size() <= 1) return;
    if (k == 1) {
      mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      return;
    }
    if (k & 1) {
      int v = 1 << (k - 1);
      for (int j = 0; j < v; ++j) {
        mint ajv = a[j + v];
        a[j + v] = a[j] - ajv;
        a[j] += ajv;
      }
    }
    int u = 1 << (2 + (k & 1));
    int v = 1 << (k - 2 - (k & 1));
    mint one = mint(1);
    mint imag = dw[1];
    while (v) {
      // jh = 0
      {
        int j0 = 0;
        int j1 = v;
        int j2 = j1 + v;
        int j3 = j2 + v;
        for (; j0 < v; ++j0, ++j1, ++j2, ++j3) {
          mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];
          mint t0p2 = t0 + t2, t1p3 = t1 + t3;
          mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
          a[j0] = t0p2 + t1p3, a[j1] = t0p2 - t1p3;
          a[j2] = t0m2 + t1m3, a[j3] = t0m2 - t1m3;
        }
      }
      // jh >= 1
      mint ww = one, xx = one * dw[2], wx = one;
      for (int jh = 4; jh < u;) {
        ww = xx * xx, wx = ww * xx;
        int j0 = jh * v;
        int je = j0 + v;
        int j2 = je + v;
        for (; j0 < je; ++j0, ++j2) {
          mint t0 = a[j0], t1 = a[j0 + v] * xx, t2 = a[j2] * ww,
               t3 = a[j2 + v] * wx;
          mint t0p2 = t0 + t2, t1p3 = t1 + t3;
          mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
          a[j0] = t0p2 + t1p3, a[j0 + v] = t0p2 - t1p3;
          a[j2] = t0m2 + t1m3, a[j2 + v] = t0m2 - t1m3;
        }
        xx *= dw[__builtin_ctzll((jh += 4))];
      }
      u <<= 2;
      v >>= 2;
    }
  }

  void ifft4(vector<mint> &a, int k) {
    if ((int)a.size() <= 1) return;
    if (k == 1) {
      mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      return;
    }
    int u = 1 << (k - 2);
    int v = 1;
    mint one = mint(1);
    mint imag = dy[1];
    while (u) {
      // jh = 0
      {
        int j0 = 0;
        int j1 = v;
        int j2 = v + v;
        int j3 = j2 + v;
        for (; j0 < v; ++j0, ++j1, ++j2, ++j3) {
          mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];
          mint t0p1 = t0 + t1, t2p3 = t2 + t3;
          mint t0m1 = t0 - t1, t2m3 = (t2 - t3) * imag;
          a[j0] = t0p1 + t2p3, a[j2] = t0p1 - t2p3;
          a[j1] = t0m1 + t2m3, a[j3] = t0m1 - t2m3;
        }
      }
      // jh >= 1
      mint ww = one, xx = one * dy[2], yy = one;
      u <<= 2;
      for (int jh = 4; jh < u;) {
        ww = xx * xx, yy = xx * imag;
        int j0 = jh * v;
        int je = j0 + v;
        int j2 = je + v;
        for (; j0 < je; ++j0, ++j2) {
          mint t0 = a[j0], t1 = a[j0 + v], t2 = a[j2], t3 = a[j2 + v];
          mint t0p1 = t0 + t1, t2p3 = t2 + t3;
          mint t0m1 = (t0 - t1) * xx, t2m3 = (t2 - t3) * yy;
          a[j0] = t0p1 + t2p3, a[j2] = (t0p1 - t2p3) * ww;
          a[j0 + v] = t0m1 + t2m3, a[j2 + v] = (t0m1 - t2m3) * ww;
        }
        xx *= dy[__builtin_ctzll(jh += 4)];
      }
      u >>= 4;
      v <<= 2;
    }
    if (k & 1) {
      u = 1 << (k - 1);
      for (int j = 0; j < u; ++j) {
        mint ajv = a[j] - a[j + u];
        a[j] += a[j + u];
        a[j + u] = ajv;
      }
    }
  }

  void ntt(vector<mint> &a) {
    if ((int)a.size() <= 1) return;
    fft4(a, __builtin_ctz(a.size()));
  }

  void intt(vector<mint> &a) {
    if ((int)a.size() <= 1) return;
    ifft4(a, __builtin_ctz(a.size()));
    mint iv = mint(a.size()).inverse();
    for (auto &x : a) x *= iv;
  }

  vector<mint> multiply(const vector<mint> &a, const vector<mint> &b) {
    int l = a.size() + b.size() - 1;
    if (min<int>(a.size(), b.size()) <= 40) {
      vector<mint> s(l);
      for (int i = 0; i < (int)a.size(); ++i)
        for (int j = 0; j < (int)b.size(); ++j) s[i + j] += a[i] * b[j];
      return s;
    }
    int k = 2, M = 4;
    while (M < l) M <<= 1, ++k;
    setwy(k);
    vector<mint> s(M);
    for (int i = 0; i < (int)a.size(); ++i) s[i] = a[i];
    fft4(s, k);
    if (a.size() == b.size() && a == b) {
      for (int i = 0; i < M; ++i) s[i] *= s[i];
    } else {
      vector<mint> t(M);
      for (int i = 0; i < (int)b.size(); ++i) t[i] = b[i];
      fft4(t, k);
      for (int i = 0; i < M; ++i) s[i] *= t[i];
    }
    ifft4(s, k);
    s.resize(l);
    mint invm = mint(M).inverse();
    for (int i = 0; i < l; ++i) s[i] *= invm;
    return s;
  }

  void ntt_doubling(vector<mint> &a) {
    int M = (int)a.size();
    auto b = a;
    intt(b);
    mint r = mint(1), zeta = mint(pr).pow((mint::get_mod() - 1) / (M << 1));
    for (int i = 0; i < M; i++) b[i] *= r, r *= zeta;
    ntt(b);
    copy(begin(b), end(b), back_inserter(a));
  }
};
// End include: "./ntt.hpp"

namespace ArbitraryNTT {
using i64 = int64_t;
using u128 = __uint128_t;
constexpr int32_t m0 = 167772161;
constexpr int32_t m1 = 469762049;
constexpr int32_t m2 = 754974721;
using mint0 = LazyMontgomeryModInt<m0>;
using mint1 = LazyMontgomeryModInt<m1>;
using mint2 = LazyMontgomeryModInt<m2>;
constexpr int r01 = mint1(m0).inverse().get();
constexpr int r02 = mint2(m0).inverse().get();
constexpr int r12 = mint2(m1).inverse().get();
constexpr int r02r12 = i64(r02) * r12 % m2;
constexpr i64 w1 = m0;
constexpr i64 w2 = i64(m0) * m1;

template <typename T, typename submint>
vector<submint> mul(const vector<T> &a, const vector<T> &b) {
  static NTT<submint> ntt;
  vector<submint> s(a.size()), t(b.size());
  for (int i = 0; i < (int)a.size(); ++i) s[i] = i64(a[i] % submint::get_mod());
  for (int i = 0; i < (int)b.size(); ++i) t[i] = i64(b[i] % submint::get_mod());
  return ntt.multiply(s, t);
}

template <typename T>
vector<int> multiply(const vector<T> &s, const vector<T> &t, int mod) {
  auto d0 = mul<T, mint0>(s, t);
  auto d1 = mul<T, mint1>(s, t);
  auto d2 = mul<T, mint2>(s, t);
  int n = d0.size();
  vector<int> ret(n);
  const int W1 = w1 % mod;
  const int W2 = w2 % mod;
  for (int i = 0; i < n; i++) {
    int n1 = d1[i].get(), n2 = d2[i].get(), a = d0[i].get();
    int b = i64(n1 + m1 - a) * r01 % m1;
    int c = (i64(n2 + m2 - a) * r02r12 + i64(m2 - b) * r12) % m2;
    ret[i] = (i64(a) + i64(b) * W1 + i64(c) * W2) % mod;
  }
  return ret;
}

template <typename mint>
vector<mint> multiply(const vector<mint> &a, const vector<mint> &b) {
  if (a.size() == 0 && b.size() == 0) return {};
  if (min<int>(a.size(), b.size()) < 128) {
    vector<mint> ret(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); ++i)
      for (int j = 0; j < (int)b.size(); ++j) ret[i + j] += a[i] * b[j];
    return ret;
  }
  vector<int> s(a.size()), t(b.size());
  for (int i = 0; i < (int)a.size(); ++i) s[i] = a[i].get();
  for (int i = 0; i < (int)b.size(); ++i) t[i] = b[i].get();
  vector<int> u = multiply<int>(s, t, mint::get_mod());
  vector<mint> ret(u.size());
  for (int i = 0; i < (int)u.size(); ++i) ret[i] = mint(u[i]);
  return ret;
}

template <typename T>
vector<u128> multiply_u128(const vector<T> &s, const vector<T> &t) {
  if (s.size() == 0 && t.size() == 0) return {};
  if (min<int>(s.size(), t.size()) < 128) {
    vector<u128> ret(s.size() + t.size() - 1);
    for (int i = 0; i < (int)s.size(); ++i)
      for (int j = 0; j < (int)t.size(); ++j) ret[i + j] += i64(s[i]) * t[j];
    return ret;
  }
  auto d0 = mul<T, mint0>(s, t);
  auto d1 = mul<T, mint1>(s, t);
  auto d2 = mul<T, mint2>(s, t);
  int n = d0.size();
  vector<u128> ret(n);
  for (int i = 0; i < n; i++) {
    i64 n1 = d1[i].get(), n2 = d2[i].get();
    i64 a = d0[i].get();
    i64 b = (n1 + m1 - a) * r01 % m1;
    i64 c = ((n2 + m2 - a) * r02r12 + (m2 - b) * r12) % m2;
    ret[i] = a + b * w1 + u128(c) * w2;
  }
  return ret;
}
}  // namespace ArbitraryNTT
// End include: "../ntt/arbitrary-ntt.hpp"

namespace MultiPrecisionIntegerImpl {
struct TENS {
  static constexpr int offset = 30;
  constexpr TENS() : _tend() {
    _tend[offset] = 1;
    for (int i = 1; i <= offset; i++) {
      _tend[offset + i] = _tend[offset + i - 1] * 10.0;
      _tend[offset - i] = 1.0 / _tend[offset + i];
    }
  }
  long double ten_ld(int n) const {
    assert(-offset <= n and n <= offset);
    return _tend[n + offset];
  }

 private:
  long double _tend[offset * 2 + 1];
};
}  // namespace MultiPrecisionIntegerImpl

// 0 は neg=false, dat={} として扱う
struct MultiPrecisionInteger {
  using M = MultiPrecisionInteger;
  inline constexpr static MultiPrecisionIntegerImpl::TENS tens = {};

  static constexpr int D = 1000000000;
  static constexpr int logD = 9;
  bool neg;
  vector<int> dat;

  MultiPrecisionInteger() : neg(false), dat() {}

  MultiPrecisionInteger(bool n, const vector<int>& d) : neg(n), dat(d) {}

  template <typename I,
            enable_if_t<internal::is_broadly_integral_v<I>>* = nullptr>
  MultiPrecisionInteger(I x) : neg(false) {
    if constexpr (internal::is_broadly_signed_v<I>) {
      if (x < 0) neg = true, x = -x;
    }
    while (x) dat.push_back(x % D), x /= D;
  }

  MultiPrecisionInteger(const string& S) : neg(false) {
    assert(!S.empty());
    if (S.size() == 1u && S[0] == '0') return;
    int l = 0;
    if (S[0] == '-') ++l, neg = true;
    for (int ie = S.size(); l < ie; ie -= logD) {
      int is = max(l, ie - logD);
      long long x = 0;
      for (int i = is; i < ie; i++) x = x * 10 + S[i] - '0';
      dat.push_back(x);
    }
    while(!dat.empty() and dat.back() == 0) dat.pop_back();
  }

  friend M operator+(const M& lhs, const M& rhs) {
    if (lhs.neg == rhs.neg) return {lhs.neg, _add(lhs.dat, rhs.dat)};
    if (_leq(lhs.dat, rhs.dat)) {
      // |l| <= |r|
      auto c = _sub(rhs.dat, lhs.dat);
      bool n = _is_zero(c) ? false : rhs.neg;
      return {n, c};
    }
    auto c = _sub(lhs.dat, rhs.dat);
    bool n = _is_zero(c) ? false : lhs.neg;
    return {n, c};
  }
  friend M operator-(const M& lhs, const M& rhs) { return lhs + (-rhs); }

  friend M operator*(const M& lhs, const M& rhs) {
    auto c = _mul(lhs.dat, rhs.dat);
    bool n = _is_zero(c) ? false : (lhs.neg ^ rhs.neg);
    return {n, c};
  }
  friend pair<M, M> divmod(const M& lhs, const M& rhs) {
    auto dm = _divmod_newton(lhs.dat, rhs.dat);
    bool dn = _is_zero(dm.first) ? false : lhs.neg != rhs.neg;
    bool mn = _is_zero(dm.second) ? false : lhs.neg;
    return {M{dn, dm.first}, M{mn, dm.second}};
  }
  friend M operator/(const M& lhs, const M& rhs) {
    return divmod(lhs, rhs).first;
  }
  friend M operator%(const M& lhs, const M& rhs) {
    return divmod(lhs, rhs).second;
  }

  M& operator+=(const M& rhs) { return (*this) = (*this) + rhs; }
  M& operator-=(const M& rhs) { return (*this) = (*this) - rhs; }
  M& operator*=(const M& rhs) { return (*this) = (*this) * rhs; }
  M& operator/=(const M& rhs) { return (*this) = (*this) / rhs; }
  M& operator%=(const M& rhs) { return (*this) = (*this) % rhs; }

  M operator-() const {
    if (is_zero()) return *this;
    return {!neg, dat};
  }
  M operator+() const { return *this; }
  friend M abs(const M& m) { return {false, m.dat}; }
  bool is_zero() const { return _is_zero(dat); }

  friend bool operator==(const M& lhs, const M& rhs) {
    return lhs.neg == rhs.neg && lhs.dat == rhs.dat;
  }
  friend bool operator!=(const M& lhs, const M& rhs) {
    return lhs.neg != rhs.neg || lhs.dat != rhs.dat;
  }
  friend bool operator<(const M& lhs, const M& rhs) {
    if (lhs == rhs) return false;
    return _neq_lt(lhs, rhs);
  }
  friend bool operator<=(const M& lhs, const M& rhs) {
    if (lhs == rhs) return true;
    return _neq_lt(lhs, rhs);
  }
  friend bool operator>(const M& lhs, const M& rhs) {
    if (lhs == rhs) return false;
    return _neq_lt(rhs, lhs);
  }
  friend bool operator>=(const M& lhs, const M& rhs) {
    if (lhs == rhs) return true;
    return _neq_lt(rhs, lhs);
  }

  // a * 10^b (1 <= |a| < 10) の形で渡す
  // 相対誤差：10^{-16} ~ 10^{-19} 程度 (処理系依存)
  pair<long double, int> dfp() const {
    if (is_zero()) return {0, 0};
    int l = max<int>(0, _size() - 3);
    int b = logD * l;
    string prefix{};
    for (int i = _size() - 1; i >= l; i--) {
      prefix += _itos(dat[i], i != _size() - 1);
    }
    b += prefix.size() - 1;
    long double a = 0;
    for (auto& c : prefix) a = a * 10.0 + (c - '0');
    a *= tens.ten_ld(-((int)prefix.size()) + 1);
    a = clamp<long double>(a, 1.0, nextafterl(10.0, 1.0));
    if (neg) a = -a;
    return {a, b};
  }
  string to_string() const {
    if (is_zero()) return "0";
    string res;
    if (neg) res.push_back('-');
    for (int i = _size() - 1; i >= 0; i--) {
      res += _itos(dat[i], i != _size() - 1);
    }
    return res;
  }
  long double to_ld() const {
    auto [a, b] = dfp();
    if (-tens.offset <= b and b <= tens.offset) {
      return a * tens.ten_ld(b);
    }
    return a * powl(10, b);
  }
  long long to_ll() const {
    long long res = _to_ll(dat);
    return neg ? -res : res;
  }
  __int128_t to_i128() const {
    __int128_t res = _to_i128(dat);
    return neg ? -res : res;
  }

  friend istream& operator>>(istream& is, M& m) {
    string s;
    is >> s;
    m = M{s};
    return is;
  }

  friend ostream& operator<<(ostream& os, const M& m) {
    return os << m.to_string();
  }

  // 内部の関数をテスト
  static void _test_private_function(const M&, const M&);

 private:
  // size
  int _size() const { return dat.size(); }
  // a == b
  static bool _eq(const vector<int>& a, const vector<int>& b) { return a == b; }
  // a < b
  static bool _lt(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i--) {
      if (a[i] != b[i]) return a[i] < b[i];
    }
    return false;
  }
  // a <= b
  static bool _leq(const vector<int>& a, const vector<int>& b) {
    return _eq(a, b) || _lt(a, b);
  }
  // a < b (s.t. a != b)
  static bool _neq_lt(const M& lhs, const M& rhs) {
    assert(lhs != rhs);
    if (lhs.neg != rhs.neg) return lhs.neg;
    bool f = _lt(lhs.dat, rhs.dat);
    if (f) return !lhs.neg;
    return lhs.neg;
  }
  // a == 0
  static bool _is_zero(const vector<int>& a) { return a.empty(); }
  // a == 1
  static bool _is_one(const vector<int>& a) {
    return (int)a.size() == 1 && a[0] == 1;
  }
  // 末尾 0 を削除
  static void _shrink(vector<int>& a) {
    while (a.size() && a.back() == 0) a.pop_back();
  }
  // 末尾 0 を削除
  void _shrink() {
    while (_size() && dat.back() == 0) dat.pop_back();
  }
  // a + b
  static vector<int> _add(const vector<int>& a, const vector<int>& b) {
    vector<int> c(max(a.size(), b.size()) + 1);
    for (int i = 0; i < (int)a.size(); i++) c[i] += a[i];
    for (int i = 0; i < (int)b.size(); i++) c[i] += b[i];
    for (int i = 0; i < (int)c.size() - 1; i++) {
      if (c[i] >= D) c[i] -= D, c[i + 1]++;
    }
    _shrink(c);
    return c;
  }
  // a - b
  static vector<int> _sub(const vector<int>& a, const vector<int>& b) {
    assert(_leq(b, a));
    vector<int> c{a};
    int borrow = 0;
    for (int i = 0; i < (int)a.size(); i++) {
      if (i < (int)b.size()) borrow += b[i];
      c[i] -= borrow;
      borrow = 0;
      if (c[i] < 0) c[i] += D, borrow = 1;
    }
    assert(borrow == 0);
    _shrink(c);
    return c;
  }
  // a * b (fft)
  static vector<int> _mul_fft(const vector<int>& a, const vector<int>& b) {
    if (a.empty() || b.empty()) return {};
    auto m = ArbitraryNTT::multiply_u128(a, b);
    vector<int> c;
    c.reserve(m.size() + 3);
    __uint128_t x = 0;
    for (int i = 0;; i++) {
      if (i >= (int)m.size() && x == 0) break;
      if (i < (int)m.size()) x += m[i];
      c.push_back(x % D);
      x /= D;
    }
    _shrink(c);
    return c;
  }
  // a * b (naive)
  static vector<int> _mul_naive(const vector<int>& a, const vector<int>& b) {
    if (a.empty() || b.empty()) return {};
    vector<long long> prod(a.size() + b.size() - 1 + 1);
    for (int i = 0; i < (int)a.size(); i++) {
      for (int j = 0; j < (int)b.size(); j++) {
        long long p = 1LL * a[i] * b[j];
        prod[i + j] += p;
        if (prod[i + j] >= (4LL * D * D)) {
          prod[i + j] -= 4LL * D * D;
          prod[i + j + 1] += 4LL * D;
        }
      }
    }
    vector<int> c(prod.size() + 1);
    long long x = 0;
    int i = 0;
    for (; i < (int)prod.size(); i++) x += prod[i], c[i] = x % D, x /= D;
    while (x) c[i] = x % D, x /= D, i++;
    _shrink(c);
    return c;
  }
  // a * b
  static vector<int> _mul(const vector<int>& a, const vector<int>& b) {
    if (_is_zero(a) || _is_zero(b)) return {};
    if (_is_one(a)) return b;
    if (_is_one(b)) return a;
    if (min<int>(a.size(), b.size()) <= 128) {
      return a.size() < b.size() ? _mul_naive(b, a) : _mul_naive(a, b);
    }
    return _mul_fft(a, b);
  }
  // 0 <= A < 1e18, 1 <= B < 1e9
  static pair<vector<int>, vector<int>> _divmod_li(const vector<int>& a,
                                                   const vector<int>& b) {
    assert(0 <= (int)a.size() && (int)a.size() <= 2);
    assert((int)b.size() == 1);
    long long va = _to_ll(a);
    int vb = b[0];
    return {_integer_to_vec(va / vb), _integer_to_vec(va % vb)};
  }
  // 0 <= A < 1e18, 1 <= B < 1e18
  static pair<vector<int>, vector<int>> _divmod_ll(const vector<int>& a,
                                                   const vector<int>& b) {
    assert(0 <= (int)a.size() && (int)a.size() <= 2);
    assert(1 <= (int)b.size() && (int)b.size() <= 2);
    long long va = _to_ll(a), vb = _to_ll(b);
    return {_integer_to_vec(va / vb), _integer_to_vec(va % vb)};
  }
  // 1 <= B < 1e9
  static pair<vector<int>, vector<int>> _divmod_1e9(const vector<int>& a,
                                                    const vector<int>& b) {
    assert((int)b.size() == 1);
    if (b[0] == 1) return {a, {}};
    if ((int)a.size() <= 2) return _divmod_li(a, b);
    vector<int> quo(a.size());
    long long d = 0;
    int b0 = b[0];
    for (int i = a.size() - 1; i >= 0; i--) {
      d = d * D + a[i];
      assert(d < 1LL * D * b0);
      int q = d / b0, r = d % b0;
      quo[i] = q, d = r;
    }
    _shrink(quo);
    return {quo, d ? vector<int>{int(d)} : vector<int>{}};
  }
  // 0 <= A, 1 <= B
  static pair<vector<int>, vector<int>> _divmod_naive(const vector<int>& a,
                                                      const vector<int>& b) {
    if (_is_zero(b)) {
      cerr << "Divide by Zero Exception" << endl;
      exit(1);
    }
    assert(1 <= (int)b.size());
    if ((int)b.size() == 1) return _divmod_1e9(a, b);
    if (max<int>(a.size(), b.size()) <= 2) return _divmod_ll(a, b);
    if (_lt(a, b)) return {{}, a};
    // B >= 1e9, A >= B
    int norm = D / (b.back() + 1);
    vector<int> x = _mul(a, {norm});
    vector<int> y = _mul(b, {norm});
    int yb = y.back();
    vector<int> quo(x.size() - y.size() + 1);
    vector<int> rem(x.end() - y.size(), x.end());
    for (int i = quo.size() - 1; i >= 0; i--) {
      if (rem.size() < y.size()) {
        // do nothing
      } else if (rem.size() == y.size()) {
        if (_leq(y, rem)) {
          quo[i] = 1, rem = _sub(rem, y);
        }
      } else {
        assert(y.size() + 1 == rem.size());
        long long rb = 1LL * rem[rem.size() - 1] * D + rem[rem.size() - 2];
        int q = rb / yb;
        vector<int> yq = _mul(y, {q});
        // 真の商は q-2 以上 q+1 以下だが自信が無いので念のため while を回す
        while (_lt(rem, yq)) q--, yq = _sub(yq, y);
        rem = _sub(rem, yq);
        while (_leq(y, rem)) q++, rem = _sub(rem, y);
        quo[i] = q;
      }
      if (i) rem.insert(begin(rem), x[i - 1]);
    }
    _shrink(quo), _shrink(rem);
    auto [q2, r2] = _divmod_1e9(rem, {norm});
    assert(_is_zero(r2));
    return {quo, q2};
  }

  // 0 <= A, 1 <= B
  static pair<vector<int>, vector<int>> _divmod_dc(const vector<int>& a,
                                                   const vector<int>& b);

  // 1 / a を 絶対誤差 B^{-deg} で求める
  static vector<int> _calc_inv(const vector<int>& a, int deg) {
    assert(!a.empty() && D / 2 <= a.back() and a.back() < D);
    int k = deg, c = a.size();
    while (k > 64) k = (k + 1) / 2;
    vector<int> z(c + k + 1);
    z.back() = 1;
    z = _divmod_naive(z, a).first;
    while (k < deg) {
      vector<int> s = _mul(z, z);
      s.insert(begin(s), 0);
      int d = min(c, 2 * k + 1);
      vector<int> t{end(a) - d, end(a)}, u = _mul(s, t);
      u.erase(begin(u), begin(u) + d);
      vector<int> w(k + 1), w2 = _add(z, z);
      copy(begin(w2), end(w2), back_inserter(w));
      z = _sub(w, u);
      z.erase(begin(z));
      k *= 2;
    }
    z.erase(begin(z), begin(z) + k - deg);
    return z;
  }

  static pair<vector<int>, vector<int>> _divmod_newton(const vector<int>& a,
                                                       const vector<int>& b) {
    if (_is_zero(b)) {
      cerr << "Divide by Zero Exception" << endl;
      exit(1);
    }
    if ((int)b.size() <= 64) return _divmod_naive(a, b);
    if ((int)a.size() - (int)b.size() <= 64) return _divmod_naive(a, b);
    int norm = D / (b.back() + 1);
    vector<int> x = _mul(a, {norm});
    vector<int> y = _mul(b, {norm});
    int s = x.size(), t = y.size();
    int deg = s - t + 2;
    vector<int> z = _calc_inv(y, deg);
    vector<int> q = _mul(x, z);
    q.erase(begin(q), begin(q) + t + deg);
    vector<int> yq = _mul(y, {q});
    while (_lt(x, yq)) q = _sub(q, {1}), yq = _sub(yq, y);
    vector<int> r = _sub(x, yq);
    while (_leq(y, r)) q = _add(q, {1}), r = _sub(r, y);
    _shrink(q), _shrink(r);
    auto [q2, r2] = _divmod_1e9(r, {norm});
    assert(_is_zero(r2));
    return {q, q2};
  }

  // int -> string
  // 先頭かどうかに応じて zero padding するかを決める
  static string _itos(int x, bool zero_padding) {
    assert(0 <= x && x < D);
    string res;
    for (int i = 0; i < logD; i++) {
      res.push_back('0' + x % 10), x /= 10;
    }
    if (!zero_padding) {
      while (res.size() && res.back() == '0') res.pop_back();
      assert(!res.empty());
    }
    reverse(begin(res), end(res));
    return res;
  }

  // convert ll to vec
  template <typename I,
            enable_if_t<internal::is_broadly_integral_v<I>>* = nullptr>
  static vector<int> _integer_to_vec(I x) {
    if constexpr (internal::is_broadly_signed_v<I>) {
      assert(x >= 0);
    }
    vector<int> res;
    while (x) res.push_back(x % D), x /= D;
    return res;
  }

  static long long _to_ll(const vector<int>& a) {
    long long res = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) res = res * D + a[i];
    return res;
  }

  static __int128_t _to_i128(const vector<int>& a) {
    __int128_t res = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) res = res * D + a[i];
    return res;
  }

  static void _dump(const vector<int>& a, string s = "") {
    if (!s.empty()) cerr << s << " : ";
    cerr << "{ ";
    for (int i = 0; i < (int)a.size(); i++) cerr << a[i] << ", ";
    cerr << "}" << endl;
  }
};

using bigint = MultiPrecisionInteger;

/**
 * @brief 多倍長整数
 */
// End include: "bigint.hpp"

namespace GCDforBigintImpl {

bigint bigint_pow(bigint a, long long k) {
  if (k == 0) return 1;
  bigint half = bigint_pow(a, k / 2);
  bigint res = half * half;
  return k % 2 ? res * a : res;
}

// a = 2^x 5^y の形で表現する
pair<int, int> shrink(int a) {
  assert(a > 0);
  int x = __builtin_ctz(a);
  a >>= x;
  int y = a == 1        ? 0
          : a == 5      ? 1
          : a == 25     ? 2
          : a == 125    ? 3
          : a == 625    ? 4
          : a == 3125   ? 5
          : a == 15625  ? 6
          : a == 78125  ? 7
          : a == 390625 ? 8
                        : 9;
  return {x, y};
}

pair<int, int> shrink(bigint& a) {
  assert(a.neg == false);
  if (a.dat.empty()) return {0, 0};
  pair<int, int> res{0, 0};
  while (true) {
    int g = gcd(bigint::D, a.dat[0]);
    if (g == 1) break;
    if (g != bigint::D) a *= bigint::D / g;
    a.dat.erase(begin(a.dat));
    auto s = shrink(g);
    res.first += s.first, res.second += s.second;
  }
  return res;
}

template <bool FAST = false>
bigint gcd_d_ary(bigint a, bigint b) {
  a.neg = b.neg = false;
  if constexpr (FAST) {
    if (max<int>(a.dat.size(), b.dat.size()) <= 4) {
      return __int128_t(BinaryGCDImpl::binary_gcd128(a.to_i128(), b.to_i128()));
    }
  }
  if (a.dat.empty()) return b;
  if (b.dat.empty()) return a;
  pair<int, int> s = shrink(a), t = shrink(b);
  if (a < b) swap(a, b);
  while (true) {
    if (b.dat.empty()) break;
    if constexpr (FAST) {
      if ((int)a.dat.size() <= 4) break;
    }
    a = a - b;
    if (!a.dat.empty()) {
      while ((a.dat[0] & 1) == 0) {
        int m = a.dat[0] ? __builtin_ctz(a.dat[0]) : 32;
        m = min(m, bigint::logD);
        int mask = (1 << m) - 1, prod = bigint::D >> m;
        a.dat[0] >>= m;
        for (int i = 1; i < (int)a.dat.size(); i++) {
          a.dat[i - 1] += prod * (a.dat[i] & mask);
          a.dat[i] >>= m;
        }
        if (a.dat.back() == 0) a.dat.pop_back();
      }
    }
    if (a < b) swap(a, b);
  }
  assert(a >= b);
  bigint g;
  if constexpr (FAST) {
    if (b.dat.empty()) {
      g = a;
    } else {
      g = __int128_t(BinaryGCDImpl::binary_gcd128(a.to_i128(), b.to_i128()));
    }
  } else {
    g = a;
  }
  int e2 = min(s.first, t.first);
  int e5 = min(s.second, t.second);
  if (e2) g *= bigint_pow(bigint{2}, e2);
  if (e5) g *= bigint_pow(bigint{5}, e5);
  return g;
}
}  // namespace GCDforBigintImpl

MultiPrecisionInteger gcd(const MultiPrecisionInteger& a,
                          const MultiPrecisionInteger& b) {
  return GCDforBigintImpl::gcd_d_ary<true>(a, b);
}

MultiPrecisionInteger lcm(const MultiPrecisionInteger& a,
                          const MultiPrecisionInteger& b) {
  return a / gcd(a, b) * b;
}
// End include: "bigint-gcd.hpp"
// Begin include: "rational.hpp"

// End include: "rational.hpp"

using BigRational = RationalBase<bigint, bigint>;

double to_double(const BigRational& r) {
  pair<long double, int> a = r.x.dfp();
  pair<long double, int> b = r.y.dfp();
  return a.first / b.first * powl(10.0, a.second - b.second);
}
// End include: "bigint-rational.hpp"
// Begin include: "bigint.hpp"

// End include: "bigint.hpp"
//

/*
using mint = BigRational;
using vm = vector<mint>;
using vvm = vector<vm>;
using fps = FormalPowerSeries_rational<mint>;
Binomial_rational<mint> C;
*/
// End include: "../../math/bigint-all.hpp"
// Begin include: "../../modulo/binomial.hpp"

#include <cassert>
#include <type_traits>
#include <vector>
using namespace std;

// コンストラクタの MAX に 「C(n, r) や fac(n) でクエリを投げる最大の n 」
// を入れると倍速くらいになる
// mod を超えて前計算して 0 割りを踏むバグは対策済み
template <typename T>
struct Binomial {
	vector<T> f, g, h;
	Binomial(int MAX = 0) {
		assert(T::get_mod() != 0 && "Binomial<mint>()");
		f.resize(1, T{1});
		g.resize(1, T{1});
		h.resize(1, T{1});
		if (MAX > 0) extend(MAX + 1);
	}

	void extend(int m = -1) {
		int n = f.size();
		if (m == -1) m = n * 2;
		m = min<int>(m, T::get_mod());
		if (n >= m) return;
		f.resize(m);
		g.resize(m);
		h.resize(m);
		for (int i = n; i < m; i++) f[i] = f[i - 1] * T(i);
		g[m - 1] = f[m - 1].inverse();
		h[m - 1] = g[m - 1] * f[m - 2];
		for (int i = m - 2; i >= n; i--) {
			g[i] = g[i + 1] * T(i + 1);
			h[i] = g[i] * f[i - 1];
		}
	}

	T fac(int i) {
		if (i < 0) return T(0);
		while (i >= (int)f.size()) extend();
		return f[i];
	}

	T finv(int i) {
		if (i < 0) return T(0);
		while (i >= (int)g.size()) extend();
		return g[i];
	}

	T inv(int i) {
		if (i < 0) return -inv(-i);
		while (i >= (int)h.size()) extend();
		return h[i];
	}

	T C(int n, int r) {
		if (n < 0 || n < r || r < 0) return T(0);
		return fac(n) * finv(n - r) * finv(r);
	}

	inline T operator()(int n, int r) { return C(n, r); }

	template <typename I>
	T multinomial(const vector<I>& r) {
		static_assert(is_integral<I>::value == true);
		int n = 0;
		for (auto& x : r) {
			if (x < 0) return T(0);
			n += x;
		}
		T res = fac(n);
		for (auto& x : r) res *= finv(x);
		return res;
	}

	template <typename I>
	T operator()(const vector<I>& r) {
		return multinomial(r);
	}

	T C_naive(int n, int r) {
		if (n < 0 || n < r || r < 0) return T(0);
		T ret = T(1);
		r = min(r, n - r);
		for (int i = 1; i <= r; ++i) ret *= inv(i) * (n--);
		return ret;
	}

	T P(int n, int r) {
		if (n < 0 || n < r || r < 0) return T(0);
		return fac(n) * finv(n - r);
	}

	// [x^r] 1 / (1-x)^n
	T H(int n, int r) {
		if (n < 0 || r < 0) return T(0);
		return r == 0 ? 1 : C(n + r - 1, r);
	}
};
// End include: "../../modulo/binomial.hpp"
// Begin include: "../../modint/montgomery-modint.hpp"

// End include: "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
using F = RationalBase<bigint,bigint>;
Binomial<mint> binom;
constexpr ll E=1e5;

void cal(ll N,vl A){
	rep(pc,1,N){
		V<P<F,ll>> sum_msk;
		rep(msk,1<<N)if(popcnt(msk)==pc){
			F sum(0);
			rep(i,N)if(msk>>i&1){
				sum+=F(1,A[i]);
			}
			sum_msk.eb(sum,msk);
		}
		sort(all(sum_msk));
		rep(i,sum_msk.size()-1){
			auto[sum,msk]=sum_msk[i];
			auto[tum,nsk]=sum_msk[i+1];
			if(tum-sum<=F(1,E)){
				out("Yes");
				out(pc);
				vvl ans(2);
				vl p{msk,nsk};
				rep(b,2)rep(i,N)if(p[b]>>i&1)ans[b].eb(i+1);
				each(a,ans)out(a);
				return;
			}
		}
	}
	out("No");
}
void dal(ll N,vl A){
	const ll K=logl(N)+1;
	ll M=-1;
	rep(i,1,N){
		if(binom(N,i).get()>E*K){
			M=i;
			break;
		}
	}

	assert(M>=1);
	vl cnt(E*K);
	ll ans=-1;
	auto dfs=[&](auto&& self,vl cur)->void{
		if(cur.size()==M){
			lld sum=0;
			each(c,cur)sum+=(lld)1/A[c];
			if(cnt[sum*E]++>=1)ans=sum*E;
			return;
		}
		ll lim=(cur.empty()? 0:cur.back()+1);
		rep(i,lim,N){
			cur.eb(i);
			self(self,cur);
			if(ans>=0)return;
			cur.pop_back();
		}
	}; dfs(dfs,vl());

	out("Yes");
	out(M);
	vvl bns;
	auto efs=[&](auto&& self,vl cur)->void{
		if(cur.size()==M){
			lld sum=0;
			each(c,cur)sum+=(lld)1/A[c];
			ll cns=sum*E;
			if(cns==ans)bns.eb(cur);
			return;
		}
		ll lim=(cur.empty()? 0:cur.back()+1);
		rep(i,lim,N){
			cur.eb(i);
			self(self,cur);
			if(bns.size()>=2)return;
			cur.pop_back();
		}
	}; efs(efs,vl());
	each(b,bns){
		each(e,b)++e;
		out(b);
	}
}

void yamada::solve()
{
	constexpr ll DIV=21;
	inl(N);
	amin(N,DIV);
	vl A(N); in(A);
	{
		vvl pos(E);
		rep(i,N)pos[A[i]-1].eb(i);
		each(p,pos)if(p.size()>=2){
			out("Yes");
			out(1);
			rep(2)out(p[0]+1);
			return;
		}
	}
	if(N<DIV)cal(N,A);
	else dal(N,A);
}