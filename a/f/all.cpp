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
// Begin include: "../../graph/graph-template.hpp"

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
// End include: "../../graph/graph-template.hpp"
// Begin include: "../../tree/pruefer-code.hpp"

// Begin include: "../misc/rng.hpp"

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
// End include: "../misc/rng.hpp"

// input: [c \in [0, n)] * (n-2), n>=3
vector<vector<int>> pruefer_code(const vector<int>& code) {
  int n = code.size() + 2;
  assert(n > 2);
  vector<vector<int>> g(n);
  vector<int> deg(n, 1);
  int e = 0;
  for (auto& x : code) deg[x]++;
  set<int> ps;
  for (int j = 0; j < n; j++) {
    if (deg[j] == 1) ps.insert(j);
  }
  for (auto& i : code) {
    if (ps.empty()) break;
    int j = *begin(ps);
    ps.erase(j);
    g[i].push_back(j);
    g[j].push_back(i);
    if (deg[i] == 1) ps.erase(i);
    deg[i]--, deg[j]--;
    if (deg[i] == 1) ps.insert(i);
    e++;
  }
  int u = -1, v = -1;
  for (int i = 0; i < n; i++) {
    if (deg[i] == 1) (u == -1 ? u : v) = i;
  }
  assert(u != -1 and v != -1);
  g[u].push_back(v);
  g[v].push_back(u);
  e++;
  assert(e == n - 1);
  return g;
}

vector<vector<int>> random_tree(int n) {
  if (n <= 2) {
    vector<vector<int>> g(n);
    if (n == 2) {
      g[0].push_back(1);
      g[1].push_back(0);
    }
    return g;
  }
  vector<int> pruefer(n - 2);
  for (auto& x : pruefer) x = randint(0, n);
  return pruefer_code(pruefer);
}

/**
 * @brief Pruefer Code
 */
// End include: "../../tree/pruefer-code.hpp"
using namespace yamada;

std::vector<int> TreeToPruferSequence(const VV<int> &tree) {
	ll N=tree.size();
	if (N <= 2) return std::vector<int>{};

	std::priority_queue<int, std::vector<int>, std::greater<int>> que;
	std::vector<int> deg(N);
	for (size_t v = 0; v < N; ++v) {
		deg[v] = tree[v].size();
		if (deg[v] == 1) que.push(v);
	}

	std::vector<int> seq; seq.reserve(N - 2);
	while (seq.size() + 2 < N) {
		const int leaf = que.top(); que.pop();
		for (int u : tree[leaf]) {
			if (deg[u] != 0) {
				seq.push_back(u);
				--deg[u];
				if (deg[u] == 1) que.push(u);
				break;
			}
		}
		--deg[leaf];
	}

	return seq;
}

void cal_alice(ll N){
	auto g=graph(N);
	auto A=TreeToPruferSequence(g);
	each(a,A)++a;
	fout(A);
}

void cal_bob(ll N){
	vc<int> A(N-2); in(A); each(a,A)a--;
	auto g=pruefer_code(A);
	rep(u,N)each(v,g[u])if(u<v)out(u+1,v+1);
}

void yamada::solve()
{
	ins(S);
	inl(N);
	fout(N-2);
	if(S[0]=='A')cal_alice(N);
	else cal_bob(N);
}