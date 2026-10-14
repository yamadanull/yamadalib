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
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;
using lld = long double;

template <typename T>
using vc = vector<T>;
template <typename T>
using VV = vector<vector<T>>;
template <typename T>
using VVV = vector<vector<vector<T>>>;
template <typename T>
using VVVV = vector<vector<vector<vector<T>>>>;
using vl = vector<long long>;
using vd = vector<double>;
using vs = vector<string>;
using vb = vector<bool>;
using vvl = vector<vector<long long>>;
using vvvl = vector<vector<vector<long long>>>;
using vvvvl = vector<vector<vector<vector<long long>>>>;
template <typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxpq = priority_queue<T, vector<T>, less<T>>;

template <typename T, typename U>
struct pr : pair<T, U> {
	template <typename... Args>
	pr(Args... args) : pair<T, U>(args...) {}

	using pair<T, U>::first;
	using pair<T, U>::second;

	pr &operator+=(const pr &r) {
		first += r.first;
		second += r.second;
		return *this;
	}
	pr &operator-=(const pr &r) {
		first -= r.first;
		second -= r.second;
		return *this;
	}
	pr &operator*=(const pr &r) {
		first *= r.first;
		second *= r.second;
		return *this;
	}
	template <typename S>
	pr &operator*=(const S &r) {
		first *= r, second *= r;
		return *this;
	}
	pr operator+(const pr &r) const { return pr(*this) += r; }
	pr operator-(const pr &r) const { return pr(*this) -= r; }
	pr operator*(const pr &r) const { return pr(*this) *= r; }
	template <typename S>
	pr operator*(const S &r) const {
		return pr(*this) *= r;
	}
	pr operator-() const { return pr{-first, -second}; }
};

using pl = pr<ll, ll>;
using vp = vc<pl>;
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
vector<int> mkord(int n, F f) {
	vector<int> ord(n);
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
	iota(ret.begin(), ret.end(), 0);
	return ret;
}

// g o f
vector<int> p_mrg(vector<int> f, const vector<int> &g) {
	for (int i = 0; i < (int)f.size(); i++) f[i]=g[f[i]];
	return f;
}

// f: old_idx -> new_idx
template <typename T>
vector<T> p_shf(const vector<int>& f, const vector<T>& A, const bool inv = false) {
	int n = A.size();
	vector<T> ret(n);
	if (!inv) for (int i = 0; i < n; i++) ret[f[i]] = A[i];
	else for (int i = 0; i < n; i++) ret[i] = A[f[i]];
	return ret;
}

template <typename T>
T mkrev(const T &v) {
	T w{v};
	reverse(begin(w), end(w));
	return w;
}

template <typename T>
bool nxp(T &v) { return std::next_permutation(begin(v), end(v)); }
template <typename F>
void nxp(int n, F f) {
	vector<int> a(n);
	iota(begin(a), end(a), 0);
	do { f(a); } while (nxp(a));
}

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
bool yesno(bool b) { std::cout << (b ? "yes\n" : "no\n"); return b; }

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
	T query() { return S.back(); }
	inline T operator()(int l, int r) { return query(l, r); }
	inline T operator()() { return query(); }
};

long long Floor(long long a, long long b) {
	assert(b != 0);
	if (b < 0) a = -a, b = -b;
	return a / b - (a % b < 0);
}
long long Under(long long a, long long b) {
	assert(b != 0);
	if (b < 0) a = -a, b = -b;
	return a / b - (a % b <= 0);
}
long long Ceil(long long a, long long b) {
	assert(b != 0);
	if (b < 0) a = -a, b = -b;
	return a / b + (a % b > 0);
}
long long Over(long long a, long long b) {
	assert(b != 0);
	if (b < 0) a = -a, b = -b;
	return a / b + (a % b >= 0);
}
long long Modulo(long long a, long long b) {
	assert(b > 0);
	long long c = a % b;
	return c < 0 ? c + b : c;
}

} // namespace yamada

// End include: "util.hpp"
// Begin include: "bitop.hpp"
namespace yamada {
__attribute__((target("popcnt"))) inline int popcnt(const u64 &a) {
	return __builtin_popcountll(a);
}
inline int lsb(const u64 &a) { return a ? __builtin_ctzll(a) : 64; }
inline int msb(const u64 &a) { return a ? 63 - __builtin_clzll(a) : -1; }
template <typename T>
inline int gbit(const T &a, int i) { return (a >> i) & 1; }
template <typename T>
inline void sbit(T &a, int i, bool b) { if (gbit(a, i) != b) a ^= T(1) << i; }
constexpr long long PW(int n) { return 1LL << n; }
constexpr long long MSK(int n) { return (1LL << n) - 1; }
}  // namespace yamada
// End include: "bitop.hpp"
// Begin include: "inout.hpp"
namespace yamada {

template <typename T, size_t K> ostream &operator<<(ostream &os, const array<T, K> &v);
template <typename T, size_t K> istream &operator>>(istream &is, array<T, K> &v);
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v);
template <typename T> istream &operator>>(istream &is, vector<T> &v);
template <typename T, typename U> ostream &operator<<(ostream &os, const pair<T, U> &p);
template <typename T, typename U> istream &operator>>(istream &is, pair<T, U> &p);

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

template <typename T, size_t K>
ostream &operator<<(ostream &os, const array<T, K> &v) {
	for (int i = 0; i < K; i++) os << (i ? " " : "") << v[i];
	return os;
}

template <typename T, size_t K>
istream &operator>>(istream &is, array<T, K> &v) {
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
template <char sep = ' ', typename T, class... U>
void out(const T &t, const U &...u) {
	cout << t;
	if constexpr (sizeof...(u)) {
		cout << sep;
		out<sep>(u...);
	}
	else out();
}

void fout() { cout << endl; }
template <char sep = ' ', typename T, class... U>
void fout(const T &t, const U &...u) {
	cout << t;
	if constexpr (sizeof...(u)) {
		cout << sep;
		fout<sep>(u...);
	}
	else fout();
}

void wout() {}
template <char sep = ' ', typename T, class... U>
void wout(const T &t, const U &...u) {
	cout << t;
	if constexpr (sizeof...(u)) {
		cout << sep;
		wout<sep>(u...);
	}
	else wout();
}

template <size_t iter = 1000, typename mint>
std::string toFraction(const mint &a) {
	for (int deno = 1; deno <= iter; deno++) {
		mint inv = ((mint)deno).inverse();
		for (int nume = 0; nume <= iter; nume++) {
			mint val = inv * nume;
			if (val == a) {
				if (deno == 1) return std::to_string(nume);
				return std::to_string(nume) + "/" + std::to_string(deno);
			}
			else if (-val == a) {
				if (deno == 1) return std::to_string(-nume);
				return std::to_string(-nume) + "/" + std::to_string(deno);
			}
		}
	}
	return "NF";
}

void mout() { cout << endl; }
template <size_t iter = 1000, char sep = ' ', typename mint, class... U>
void mout(const mint &a, const U &...u) {
	std::cout << toFraction<iter, mint>(a);
	if constexpr (sizeof...(u)) {
		cout << sep;
		mout<iter, sep>(u...);
	}
	else mout();
}

template <size_t iter = 1000, typename mint>
void mout(std::vector<mint> &A) {
	for (int i = 0; i < (int)A.size(); i++) {
		std::cout << toFraction(A[i], iter) << (i == (int)A.size() - 1 ? "\n" : " ");
	}
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
#define each4(x, y, z, w, v) for (auto&& [x, y, z, w] : v)
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
// Begin include: "../../misc/all.hpp"

// Begin include: "fastio.hpp"

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>
#include <utility>

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

#define ENABLE_HAS_FUNCTION(var)                                              \
  template <class, class = void>                                              \
  struct has_##var : false_type {};                                           \
  template <class T>                                                          \
  struct has_##var<T, void_t<decltype(&T::var)>>                              \
      : bool_constant<is_member_function_pointer<decltype(&T::var)>::value> { \
  };                                                                          \
  template <class T>                                                          \
  inline constexpr bool has_##var##_v = has_##var<T>::value;

}  // namespace internal
// End include: "../internal/internal-type-traits.hpp"

namespace fastio {
static constexpr int SZ = 1 << 17;
static constexpr int offset = 64;
char inbuf[SZ], outbuf[SZ];
int in_left = 0, in_right = 0, out_right = 0;

struct Pre {
  char num[40000];
  constexpr Pre() : num() {
    for (int i = 0; i < 10000; i++) {
      int n = i;
      for (int j = 3; j >= 0; j--) {
        num[i * 4 + j] = n % 10 + '0';
        n /= 10;
      }
    }
  }
} constexpr pre;

void load() {
  int len = in_right - in_left;
  memmove(inbuf, inbuf + in_left, len);
  in_right = len + fread(inbuf + len, 1, SZ - len, stdin);
  in_left = 0;
}
void flush() {
  fwrite(outbuf, 1, out_right, stdout);
  out_right = 0;
}
void skip_space() {
  if (in_left + offset > in_right) load();
  while (inbuf[in_left] <= ' ') in_left++;
}

void single_read(char& c) {
  if (in_left + offset > in_right) load();
  skip_space();
  c = inbuf[in_left++];
}
void single_read(string& S) {
  skip_space();
  while (true) {
    if (in_left == in_right) load();
    int i = in_left;
    for (; i != in_right; i++) {
      if (inbuf[i] <= ' ') break;
    }
    copy(inbuf + in_left, inbuf + i, back_inserter(S));
    in_left = i;
    if (i != in_right) break;
  }
}
template <typename T,
          enable_if_t<internal::is_broadly_integral_v<T>>* = nullptr>
void single_read(T& x) {
  if (in_left + offset > in_right) load();
  skip_space();
  char c = inbuf[in_left++];
  [[maybe_unused]] bool minus = false;
  if constexpr (internal::is_broadly_signed_v<T>) {
    if (c == '-') minus = true, c = inbuf[in_left++];
  }
  x = 0;
  while (c >= '0') {
    x = x * 10 + (c & 15);
    c = inbuf[in_left++];
  }
  if constexpr (internal::is_broadly_signed_v<T>) {
    if (minus) x = -x;
  }
}
void rd() {}
template <typename Head, typename... Tail>
void rd(Head& head, Tail&... tail) {
  single_read(head);
  rd(tail...);
}

void single_write(const char& c) {
  if (out_right > SZ - offset) flush();
  outbuf[out_right++] = c;
}
void single_write(const bool& b) {
  if (out_right > SZ - offset) flush();
  outbuf[out_right++] = b ? '1' : '0';
}
void single_write(const string& S) {
  flush(), fwrite(S.data(), 1, S.size(), stdout);
}
void single_write(const char* p) { flush(), fwrite(p, 1, strlen(p), stdout); }
template <typename T,
          enable_if_t<internal::is_broadly_integral_v<T>>* = nullptr>
void single_write(const T& _x) {
  if (out_right > SZ - offset) flush();
  if (_x == 0) {
    outbuf[out_right++] = '0';
    return;
  }
  T x = _x;
  if constexpr (internal::is_broadly_signed_v<T>) {
    if (x < 0) outbuf[out_right++] = '-', x = -x;
  }
  constexpr int buffer_size = sizeof(T) * 10 / 4;
  char buf[buffer_size];
  int i = buffer_size;
  while (x >= 10000) {
    i -= 4;
    memcpy(buf + i, pre.num + (x % 10000) * 4, 4);
    x /= 10000;
  }
  if (x < 100) {
    if (x < 10) {
      outbuf[out_right] = '0' + x;
      ++out_right;
    } else {
      uint32_t q = (uint32_t(x) * 205) >> 11;
      uint32_t r = uint32_t(x) - q * 10;
      outbuf[out_right] = '0' + q;
      outbuf[out_right + 1] = '0' + r;
      out_right += 2;
    }
  } else {
    if (x < 1000) {
      memcpy(outbuf + out_right, pre.num + (x << 2) + 1, 3);
      out_right += 3;
    } else {
      memcpy(outbuf + out_right, pre.num + (x << 2), 4);
      out_right += 4;
    }
  }
  memcpy(outbuf + out_right, buf + i, buffer_size - i);
  out_right += buffer_size - i;
}
void wt() {}
template <typename Head, typename... Tail>
void wt(const Head& head, const Tail&... tail) {
  single_write(head);
  wt(std::forward<const Tail>(tail)...);
}
template <typename... Args>
void wtn(const Args&... x) {
  wt(std::forward<const Args>(x)...);
  wt('\n');
}

struct Dummy {
  Dummy() { atexit(flush); }
} dummy;

}  // namespace fastio
using fastio::rd;
using fastio::skip_space;
using fastio::wt;
using fastio::wtn;
// End include: "fastio.hpp"
// Begin include: "rng.hpp"

// Begin include: "../internal/internal-seed.hpp"

#include <chrono>
using namespace std;

namespace internal {
unsigned long long non_deterministic_seed() {
  unsigned long long m =
      chrono::duration_cast<chrono::nanoseconds>(
          chrono::high_resolution_clock::now().time_since_epoch())
          .count();
  m ^= 9845834732710364265uLL;
  m ^= m << 24, m ^= m >> 31, m ^= m << 35;
  return m;
}
unsigned long long deterministic_seed() { return 88172645463325252UL; }

// 64 bit の seed 値を生成 (手元では seed 固定)
// 連続で呼び出すと同じ値が何度も返ってくるので注意
// #define RANDOMIZED_SEED するとシードがランダムになる
unsigned long long seed() {
#if defined(NyaanLocal) && !defined(RANDOMIZED_SEED)
  return deterministic_seed();
#else
  return non_deterministic_seed();
#endif
}

}  // namespace internal
// End include: "../internal/internal-seed.hpp"

namespace my_rand {
using i64 = long long;
using u64 = unsigned long long;

// [0, 2^64 - 1)
u64 rng() {
	static u64 _x = internal::seed();
	return _x ^= _x << 7, _x ^= _x >> 9;
}

// [l, r]
i64 rng(i64 l, i64 r) {
	assert(l <= r);
	return l + rng() % u64(r - l + 1);
}

// [l, r)
i64 randint(i64 l, i64 r) {
	assert(l < r);
	return l + rng() % u64(r - l);
}

// choose N numbers from [l, r) without overlapping
vector<i64> randset(i64 l, i64 r, i64 N) {
	assert(l <= r && N <= r - l);
	unordered_set<i64> s;
	for (i64 i = N; i; --i) {
		i64 m = randint(l, r + 1 - i);
		if (s.find(m) != s.end()) m = r - i;
		s.insert(m);
	}
	vector<i64> ret;
	for (auto& x : s) ret.push_back(x);
	sort(begin(ret), end(ret));
	return ret;
}

// [0.0, 1.0)
double rnd() { return rng() * 5.42101086242752217004e-20; }
// [l, r)
double rnd(double l, double r) {
	assert(l < r);
	return l + rnd() * (r - l);
}

template <typename T>
void randshf(vector<T>& v) {
	int N = v.size();
	for (int i = 1; i < N; i++) swap(v[i], v[randint(0, i + 1)]);
}

}  // namespace my_rand

using my_rand::randint;
using my_rand::randset;
using my_rand::randshf;
using my_rand::rnd;
using my_rand::rng;
// End include: "rng.hpp"
// Begin include: "timer.hpp"

#include <chrono>
using namespace std;

struct Timer {
  chrono::high_resolution_clock::time_point st;

  Timer() { reset(); }
  void reset() { st = chrono::high_resolution_clock::now(); }

  long long elapsed() {
    auto ed = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(ed - st).count();
  }
  long long operator()() { return elapsed(); }
};
// End include: "timer.hpp"
// End include: "../../misc/all.hpp"
using namespace yamada;

constexpr int MAX=500;
constexpr int DIV=20;
constexpr int CNT=(MAX+DIV-1)/DIV;
int S[MAX][CNT];
ll H[CNT][1<<DIV];
ll SSSsiz;
ll SSS[MAX*(MAX-1)*(MAX-2)/6+MAX];

ll genh(string s){
	ll ans=0;
	ll M=s.size();
	rep(j0,0,M,DIV){
		ll a=0;
		rep(j,j0,min(j0+DIV,M))if(s[j]=='1')a|=1LL<<(j-j0);
		ans+=H[j0/DIV][a];
	}
	return ans;
}

void yamada::solve()
{
	rep(bi,CNT){
		ll H2[DIV];
		each(h,H2)h=randint(0,1LL<<50);
		rep(msk,1,1<<DIV){
			ll t=lsb(msk);
			int nsk=msk^1<<t;
			H[bi][msk]=H[bi][nsk]+H2[t];
		}
	}

	ini(N,M,Q);
	rep(i,N){
		ins(s);
		SSS[SSSsiz++]=genh(s);
		rep(j,M)if(s[j]=='1'){
			int bi=j/DIV;
			int bj=j-bi*DIV;
			S[i][bi]|=1<<bj;
		}
	}

	rep(i,N)rep(j,i+1,N){
		ll h=0;
		rep(bi,CNT)h+=H[bi][S[i][bi]&S[j][bi]];
		rep(k,j+1,N){
			ll h2=h;
			rep(bi,CNT){
				h2+=H[bi][S[k][bi]&(S[i][bi]^S[j][bi])];
			}
			SSS[SSSsiz++]=h2;
		}
	}

	sort(SSS,SSS+SSSsiz);
	while(Q--){
		ins(t);
		ll h=genh(t);
		ll SSSi=lower_bound(SSS,SSS+SSSsiz,h)-SSS;
		YesNo(SSSi<SSSsiz && SSS[SSSi]==h);
	}
}