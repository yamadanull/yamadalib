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

template <typename T = long long>
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
// Begin include: "debug.hpp"
namespace DebugImpl {

template <typename U, typename = void>
struct is_specialize : false_type {};
template <typename U>
struct is_specialize< U, typename conditional<false, typename U::iterator, void>::type> : true_type {};
template <typename U>
struct is_specialize< U, typename conditional<false, decltype(U::first), void>::type> : true_type {};
template <typename U>
struct is_specialize<U, enable_if_t<is_integral<U>::value, void>> : true_type {};

void dump(const char& t) { cerr << t; }

void dump(const string& t) { cerr << t; }

void dump(const bool& t) { cerr << (t ? "true" : "false"); }

void dump(__int128_t t) {
	if (t == 0) cerr << 0;
	if (t < 0) cerr << '-', t = -t;
	string S;
	while (t) S.push_back('0' + t % 10), t /= 10;
	reverse(begin(S), end(S));
	cerr << S;
}

void dump(__uint128_t t) {
	if (t == 0) cerr << 0;
	string S;
	while (t) S.push_back('0' + t % 10), t /= 10;
	reverse(begin(S), end(S));
	cerr << S;
}

template <typename U, enable_if_t<!is_specialize<U>::value, nullptr_t> = nullptr>
void dump(const U& t) { cerr << t; }

template <typename T>
void dump(const T& t, enable_if_t<is_integral<T>::value>* = nullptr) {
	string res;
	if (t == yamada::inf) res = "inf";
	if constexpr (is_signed<T>::value) {
		if (t == -yamada::inf) res = "-inf";
	}
	if constexpr (sizeof(T) == 8) {
		if (t == yamada::infLL) res = "inf";
		if constexpr (is_signed<T>::value) {
			if (t == -yamada::infLL) res = "-inf";
		}
	}
	if (res.empty()) res = to_string(t);
	cerr << res;
}

template <typename T, typename U>
void dump(const pair<T, U>&);
template <typename T>
void dump(const pair<T*, int>&);

template <typename T>
void dump(const T& t, enable_if_t<!is_void<typename T::iterator>::value>* = nullptr) {
	cerr << "[ ";
	for (auto it = t.begin(); it != t.end();) {
		dump(*it);
		cerr << (++it == t.end() ? "" : ", ");
	}
	cerr << " ]";
}

template <typename T, typename U>
void dump(const pair<T, U>& t) {
	cerr << "( ";
	dump(t.first);
	cerr << ", ";
	dump(t.second);
	cerr << " )";
}

template <typename T>
void dump(const pair<T*, int>& t) {
	cerr << "[ ";
	for (int i = 0; i < t.second; i++) {
		dump(t.first[i]);
		cerr << (i == t.second - 1 ? "" : ", ");
	}
	cerr << " ]";
}

void trace() { cerr << endl; }
template <typename Head, typename... Tail>
void trace(Head&& head, Tail&&... tail) {
	cerr << " ";
	dump(head);
	if (sizeof...(tail) != 0) cerr << ",";
	trace(std::forward<Tail>(tail)...);
}

}  // namespace DebugImpl

#define yamadaDebug

#ifdef yamadaDebug
#define err(...) \
	do { \
		cerr << "## " << #__VA_ARGS__ << " = "; \
		DebugImpl::trace(__VA_ARGS__); \
	} while (0)
#else
#define err(...) (void(0))
#endif

// End include: "debug.hpp"
// Begin include: "macro.hpp"
#define each1(x, v) for (auto&& x : v)
#define each2(x, y, v) for (auto&& [x, y] : v)
#define each3(x, y, z, v) for (auto&& [x, y, z] : v)
#define each4(x, y, z, w, v) for (auto&& [x, y, z, w] : v)
#define overload5(a, b, c, d, e, f, ...) f
#define each(...) overload5(__VA_ARGS__, each4, each3, each2, each1)(__VA_ARGS__)

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

#define all(v) (v).begin(), (v).end()
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

#define ini(...) \
	int __VA_ARGS__; \
	in(__VA_ARGS__)
#define inl(...) \
	long long __VA_ARGS__; \
	in(__VA_ARGS__)
#define ins(...) \
	string __VA_ARGS__; \
	in(__VA_ARGS__)
#define in2(s, t) \
	for (int i = 0; i < (int)s.size(); i++) { \
		in(s[i], t[i]); \
	}
#define in3(s, t, u) \
	for (int i = 0; i < (int)s.size(); i++) { \
		in(s[i], t[i], u[i]); \
	}
#define in4(s, t, u, v) \
	for (int i = 0; i < (int)s.size(); i++) { \
		in(s[i], t[i], u[i], v[i]); \
	}
#define die(...) \
	do { \
		yamada::out(__VA_ARGS__);\
		return; \
	} while (0)
// End include: "macro.hpp"

namespace yamada {
void solve();
}
int main() { yamada::solve(); }
// End include: "../../template/template.hpp"
// Begin include: "../../graph/namori.hpp"

#include <vector>

// Begin include: "../data-structure/union-find.hpp"

struct UnionFind {
	vector<int> data, nxt;
	UnionFind(int N) : data(N, -1), nxt(N) {
		for (int i = 0; i < N; i++) nxt[i] = i;
	}

	int find(int k) { return data[k] < 0 ? k : data[k] = find(data[k]); }

	int unite(int x, int y) {
		if ((x = find(x)) == (y = find(y))) return false;
		if (data[x] > data[y]) swap(x, y);
		data[x] += data[y];
		data[y] = x;
		swap(nxt[x], nxt[y]);
		return true;
	}

	// f(x, y) : x に y をマージ
	template <typename F>
	int unite(int x, int y, const F &f) {
		if ((x = find(x)) == (y = find(y))) return false;
		if (data[x] > data[y]) swap(x, y);
		data[x] += data[y];
		data[y] = x;
		f(x, y);
		swap(nxt[x], nxt[y]);
		return true;
	}

	// g(x, y) : y に x をマージ
	template <typename F, typename G>
	int unite(int x, int y, const F &f, const G &g) {
		if ((x = find(x)) == (y = find(y))) return false;
		if (data[x] > data[y]) {
			g(x, y);
			swap(x, y);
		}
		else f(x, y);
		data[x] += data[y];
		data[y] = x;
		return true;
	}

	int size(int k) { return -data[find(k)]; }

	int same(int x, int y) { return find(x) == find(y); }

	vector<int> enumerate(int i) {
		vector<int> res{i};
		for (int j = nxt[i]; j != i; j = nxt[j]) res.push_back(j);
		return res;
	}

	vector<vector<int> > groups() {
		vector<vector<int> > ret;
		for (int i = 0; i < (int)data.size(); ++i) if (i == find(i)) {
			ret.emplace_back(enumerate(i));
		}
		return ret;
	}
};
// End include: "../data-structure/union-find.hpp"
// Begin include: "../tree/heavy-light-decomposition.hpp"

// Begin include: "../graph/graph-template.hpp"

template <typename T>
struct edge {
	int src, to;
	T cost;

	edge(int _to, T _cost) : src(-1), to(_to), cost(_cost) {}
	edge(int _src, int _to, T _cost) : src(_src), to(_to), cost(_cost) {}

	edge &operator=(const int &x) {
		to = x;
		return *this;
	}

	operator int() const { return to; }
};
template <typename T>
using Edges = vector<edge<T>>;
template <typename T>
using WeightedGraph = vector<Edges<T>>;
using UnweightedGraph = vector<vector<int>>;

// Input of (Unweighted) Graph
UnweightedGraph graph(int N, int M = -1, bool is_directed = false,
		bool is_1origin = true) {
	UnweightedGraph g(N);
	if (M == -1) M = N - 1;
	for (int _ = 0; _ < M; _++) {
		int x, y;
		cin >> x >> y;
		if (is_1origin) x--, y--;
		g[x].push_back(y);
		if (!is_directed) g[y].push_back(x);
	}
	return g;
}

// Input of Weighted Graph
template <typename T>
WeightedGraph<T> wgraph(int N, int M = -1, bool is_directed = false,
		bool is_1origin = true) {
	WeightedGraph<T> g(N);
	if (M == -1) M = N - 1;
	for (int _ = 0; _ < M; _++) {
		int x, y;
		cin >> x >> y;
		T c;
		cin >> c;
		if (is_1origin) x--, y--;
		g[x].emplace_back(x, y, c);
		if (!is_directed) g[y].emplace_back(y, x, c);
	}
	return g;
}
// End include: "../graph/graph-template.hpp"

template <typename G>
struct HeavyLightDecomposition {
private:
	void dfs_sz(int cur) {
		size[cur] = 1;
		for (auto& dst : g[cur]) {
			if (dst == par[cur]) {
				if (g[cur].size() >= 2 && int(dst) == int(g[cur][0]))
					swap(g[cur][0], g[cur][1]);
				else continue;
			}
			depth[dst] = depth[cur] + 1;
			par[dst] = cur;
			dfs_sz(dst);
			size[cur] += size[dst];
			if (size[dst] > size[g[cur][0]]) {
				swap(dst, g[cur][0]);
			}
		}
	}

	void dfs_hld(int cur) {
		down[cur] = id++;
		for (auto dst : g[cur]) {
			if (dst == par[cur]) continue;
			nxt[dst] = (int(dst) == int(g[cur][0]) ? nxt[cur] : int(dst));
			dfs_hld(dst);
		}
		up[cur] = id;
	}

	// [u, v) 半開区間を閉区間に分解
	vector<pair<int, int>> ascend(int u, int v) const {
		vector<pair<int, int>> res;
		while (nxt[u] != nxt[v]) {
			res.emplace_back(down[u], down[nxt[u]]);
			u = par[nxt[u]];
		}
		if (u != v) res.emplace_back(down[u], down[v] + 1);
		return res;
	}

	vector<pair<int, int>> ascend_origin(int u, int v) const {
		vector<pair<int, int>> res;
		while (nxt[u] != nxt[v]) {
			res.emplace_back(u, nxt[u]);
			u = par[nxt[u]];
		}
		if (u != v) res.emplace_back(u, g[v][0]);
		return res;
	}

	// (u, v] 半開区間を閉区間に分解
	vector<pair<int, int>> descend(int u, int v) const {
		if (u == v) return {};
		if (nxt[u] == nxt[v]) return {{down[u] + 1, down[v]}};
		auto res = descend(u, par[nxt[v]]);
		res.emplace_back(down[nxt[v]], down[v]);
		return res;
	}

	vector<pair<int, int>> descend_origin(int u, int v) const {
		if (u == v) return {};
		if (nxt[u] == nxt[v]) return {{g[u][0], v}};
		auto res = descend_origin(u, par[nxt[v]]);
		res.emplace_back(nxt[v], v);
		return res;
	}

public:
	G& g;
	int root, id;
	vector<int> size, depth, down, up, nxt, par;
	HeavyLightDecomposition(G& _g, int _root = 0)
		: g(_g),
		root(_root),
		id(0),
		size(g.size(), 0),
		depth(g.size(), 0),
		down(g.size(), -1),
		up(g.size(), -1),
		nxt(g.size(), root),
		par(g.size(), root) {
		dfs_sz(root);
		dfs_hld(root);
	}

	pair<int, int> idx(int i) const { return make_pair(down[i], up[i]); }

	template <typename F>
	void path_query(int u, int v, bool vertex, const F& f) {
		int l = lca(u, v);
		for (auto&& [a, b] : ascend(u, l)) {
			int s = a + 1, t = b;
			s > t ? f(t, s) : f(s, t);
		}
		if (vertex) f(down[l], down[l] + 1);
		for (auto&& [a, b] : descend(l, v)) {
			int s = a, t = b + 1;
			s > t ? f(t, s) : f(s, t);
		}
	}

	template <typename F>
	void path_noncommutative_query(int u, int v, bool vertex, const F& f) {
		int l = lca(u, v);
		for (auto&& [a, b] : ascend(u, l)) f(a + 1, b);
		if (vertex) f(down[l], down[l] + 1);
		for (auto&& [a, b] : descend(l, v)) f(a, b + 1);
	}

	// 閉区間 -> 閉区間たち
	vector<pair<int, int>> path_query_origin(int u, int v, bool vertex = 1) {
		int l = lca(u, v);
		auto ans = ascend_origin(u, l);
		if (vertex) ans.emplace_back(l, l);
		for (auto&& [a, b] : descend_origin(l, v)) ans.emplace_back(a, b);
		return ans;
	}

	template <typename F>
	void subtree_query(int u, bool vertex, const F& f) {
		f(down[u] + int(!vertex), up[u]);
	}

	int lca(int a, int b) {
		while (nxt[a] != nxt[b]) {
			if (down[a] < down[b]) swap(a, b);
			a = par[nxt[a]];
		}
		return depth[a] < depth[b] ? a : b;
	}

	int dist(int a, int b) { return depth[a] + depth[b] - depth[lca(a, b)] * 2; }
};

/**
 * @brief Heavy Light Decomposition(重軽分解)
 * @docs docs/tree/heavy-light-decomposition.md
 */
// End include: "../tree/heavy-light-decomposition.hpp"
// Begin include: "graph-template.hpp"

// End include: "graph-template.hpp"

using namespace std;

template <typename T>
struct Namori {
	using G = WeightedGraph<T>;

	int n;
	G g;

	// 部分グラフ
	vector<G> aux;

	// ループ部分の(頂点,辺の重み)
	// loop[i].se は loop[i] と loop[i+1] の間の辺
	vector<pair<int, T>> loop;

	// 頂点の対応関係
	vector<pair<int, int>> mp;

	// HL分解
	vector<HeavyLightDecomposition<G>> hld;

	Namori(int _n = 0) : _uf(_n) { init(_n); }

	void init(int _n) {
		n = _n;
		g.resize(n);
		_uf.data.resize(n);
		fill(begin(_uf.data), end(_uf.data), -1);
		_is_loop.resize(n, false);
		mp.resize(n, make_pair(-1, -1));
	}

	void add_edge(int u, int v, T w = 1) {
		assert(_built == false);
		if (_uf.same(u, v)) {
			_root = u, _adj = v, _w = w;
		} else {
			_uf.unite(u, v);
			g[u].emplace_back(u, v, w);
			g[v].emplace_back(v, u, w);
		}
		if (++_es == n) build();
	}

	void build() {
		if (_built) return;

		_buf.resize(n, -1);
		dfs1(_root, -1);

		for (int c = _adj; c >= 0; c = _buf[c]) {
			loop.emplace_back(c, -1);
			_is_loop[c] = true;
			for (auto& e : g[c]) {
				if (e == _buf[c]) loop.back().second = e.cost;
			}
		}
		assert(loop.back().first == _root);
		loop.back().second = _w;

		_h.resize(n);
		for (auto& [i, _] : loop) dfs2(i, -1);

		fill(begin(_buf), end(_buf), 0);
		for (auto& [i, _] : loop) dfs3(i);

		_uf.data.clear();
		_buf.clear();
		_is_loop.clear();

		aux.resize(loop.size());
		for (int i = 0; i < (int)loop.size(); i++) {
			int k = loop[i].first, j = 0;
			dfs4(k, i, j);
			aux[i].resize(j);

			dfs5(k);
			hld.emplace_back(aux[i]);
		}

		_h.clear();
		_built = true;
	}

	pair<int, int> idx(int i) const { return mp[i]; }

	int root(int i) const { return loop[mp[i].first].first; }

	private:
	// 初期化用の状態変数
	UnionFind _uf;
	vector<int> _buf;
	vector<bool> _is_loop;
	int _root = -1, _adj = -1, _es = 0;
	bool _built = false;
	T _w = 0;
	G _h;

	// parをメモする
	void dfs1(int c, int p) {
		for (auto& d : g[c]) {
			if (d != p) {
				_buf[d] = c;
				dfs1(d, c);
			}
		}
	}

	// _h で有向木を作る
	void dfs2(int c, int p) {
		for (auto& d : g[c]) {
			if (d == p or _is_loop[d]) continue;
			_h[c].emplace_back(c, d, d.cost);
			dfs2(d, c);
		}
	}

	// HLD用に順番替え
	void dfs3(int c) {
		_buf[c] = 1;
		for (auto& d : _h[c]) {
			dfs3(d);
			_buf[c] += _buf[d];
			if (_buf[d] > _buf[_h[c][0]]) {
				swap(_h[c][0], d);
			}
		}
	}

	// 順番をつける
	void dfs4(int c, int i, int& j) {
		mp[c] = make_pair(i, j++);
		for (auto& d : _h[c]) {
			dfs4(d, i, j);
		}
	}

	// 部分グラフを作る
	void dfs5(int c) {
		for (auto& d : _h[c]) {
			dfs5(d);
			auto [i, j] = mp[c];
			auto [_, k] = mp[d];
			aux[i][j].emplace_back(j, k, d.cost);
			// 逆辺も入れたいときはここをオンにする(動くか不明)
			// aux[i][k].emplace_back(k, j, d.cost);
		}
	}
};

/**
 * @brief Functional Graph(なもりグラフ)の分解
 * @docs docs/graph/functional-graph.md
 */
// End include: "../../graph/namori.hpp"
// Begin include: "../../graph/undirected-namori.hpp"

// Gは連結グラフである必要がある
// 有向なもりを返す
template <typename Graph>
Graph UndirectedNamori(Graph G) {
	int N = G.size();
	int M = 0;
	Graph g(N);

	queue<int> q;
	vector<int> cnt(N);
	for (int i = 0; i < N; i++) {
		cnt[i] = G[i].size();
		if (G[i].size() == 1) q.push(i);
	}

	vector<bool> decom(N);
	while(!q.empty()) {
		int pos = q.front(); q.pop();
		for (auto& e : G[pos]) if (!decom[e]) {
			g[pos].emplace_back(e); ++M;
			if (--cnt[e] == 1) q.push(e);
		}
		decom[pos] = true;
	}

	auto dfs = [&](auto&& self, int pos, int par)->void{
		if (M == N) return;
		for (auto& e: G[pos]) if (e != par && !decom[e]) {
			g[pos].emplace_back(e); ++M;
			if (M == N) return;
			self(self, e, pos);
			if (M == N) return;
		}
	};

	for (int i = 0; i < N; i++) if (!decom[i]) {
		dfs(dfs, i, -1);
		break;
	}
	return g;
}
// End include: "../../graph/undirected-namori.hpp"
// Begin include: "../../graph/graph-template.hpp"

// End include: "../../graph/graph-template.hpp"
using namespace yamada;

ll cal_cyc(vl A,ll K){
	ll N=A.size();
	vl C(N);
	rep(i,N-1)C[i+1]=A[i]-C[i];
	if(N%2){
		ll d=A.back()-(C.front()+C.back());
		if(d%2)return infLL;
		rep(i,0,N,2)C[i]+=d/2;
		rep(i,1,N,2)C[i]-=d/2;
		ll ans=0;
		rep(u,N){
			if(C[u]<0)return infLL;
			if(0<C[u] && C[u]<K)return infLL;
			ans+=Ceil(C[u],K*2);
		}
		return ans;
	}
	if(C.front()+C.back()!=A.back())return infLL;

	ll ansbase=0;
	each(c,C)ansbase+=Ceil(c,K*2);

	vl C0,C1;
	rep(i,N)(i%2? C1:C0).eb(C[i]);
	auto c0=C0; each(c,c0)c=Modulo(c-1,K*2)+1;
	auto c1=C1; each(c,c1)c=Modulo(c-1,K*2)+1;
	sort(all(C0)); sort(all(C1));
	sort(all(c0)); sort(all(c1));

	auto get=[&](ll X)->ll{ // 辺０の寄与がX
		auto exs=[&](vl& A,ll l,ll r)->bool{ return lb(A,l)<lb(A,r); };
		if(exs(C0,-infLL,-X))return infLL;
		if(exs(C0,-X+1,-X+K))return infLL;
		if(exs(C1,-infLL,X))return infLL;
		if(exs(C1,X+1,X+K))return infLL;
		ll xquo=Floor(X,K*2);
		ll xrem=Modulo(X,K*2);
		ll ans=ansbase;
		{
			ll m=ub(c0,K*2-xrem);
			ans+=m*xquo;
			ans+=(N/2-m)*(xquo+1);
		}
		{
			ll m=ub(c1,xrem);
			ans-=m*(xquo+1);
			ans-=(N/2-m)*xquo;
		}
		return ans;
	};

	ll ans=infLL;
	each(c,C0)amin(ans,get(-c));
	each(c,C1)amin(ans,get(c));
	// 全部K以上にするための辺０寄与の範囲
	ll xL=-infLL,xR=infLL;
	each(c,C0)amax(xL,-c);
	each(c,C1)amin(xR,c);
	auto to_inLR=[&](ll c)->ll{
		c=Modulo(c,K*2);
		c+=xL/(K*2)*(K*2);
		while(c>=xL)c-=K*2;
		while(c<xL)c+=K*2;
		return c;
	};

	each(c,c0)amin(ans,get(to_inLR(-c)));
	each(c,c1)amin(ans,get(to_inLR(c)));
	return ans;
}

pr<ll,ll> cal_tree(WeightedGraph<ll> g,vl A,ll K){
	ll N=g.size();
	auto cnt=A; // u,p(u) に施す回数
	auto dfs=[&](auto&& self,ll u)->ll{
		each(v,g[u])cnt[u]-=self(self,v);
		return cnt[u];
	};
	dfs(dfs,0);
	if(Min(cnt)<0)return {infLL,infLL};
	rep(u,1,N)if(0<cnt[u] && cnt[u]<K)return {infLL,infLL};
	ll ans=0;
	rep(u,1,N)ans+=Ceil(cnt[u],K*2);
	return {ans,cnt[0]};
}

void yamada::solve()
{
	inl(N,K);
	vl A(N); in(A);
	auto g=UndirectedNamori(graph(N,N));
	Namori<ll> nam(N);
	rep(u,N)each(v,g[u])nam.add_edge(u,v);

	ll M=nam.aux.size();
	vvl B(M); rep(gi,M)B[gi].resize(nam.aux[gi].size());
	rep(u,N){
		auto[i,j]=nam.idx(u);
		B[i][j]=A[u];
	}
	ll ans=0;
	vl Acyc;
	rep(gi,M){
		auto& t=nam.aux[gi];
		ll n=t.size();
		auto[bns,a]=cal_tree(t,B[gi],K);
		if(bns==infLL)die(-1);
		ans+=bns;
		Acyc.eb(a);
	}
	ll bns=cal_cyc(Acyc,K);
	if(bns==infLL)die(-1);
	out(ans+bns);
}