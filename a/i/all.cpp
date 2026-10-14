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
// Begin include: "../../fps/ntt-friendly-fps.hpp"

// Begin include: "../ntt/ntt.hpp"

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
// End include: "../ntt/ntt.hpp"
// Begin include: "./formal-power-series.hpp"

template <typename mint>
struct FormalPowerSeries : vector<mint> {
	using vector<mint>::vector;
	using FPS = FormalPowerSeries;

	FPS &operator+=(const FPS &r) {
		if (r.size() > this->size()) this->resize(r.size());
		for (int i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];
		return *this;
	}

	FPS &operator+=(const mint &r) {
		if (this->empty()) this->resize(1);
		(*this)[0] += r;
		return *this;
	}

	FPS &operator-=(const FPS &r) {
		if (r.size() > this->size()) this->resize(r.size());
		for (int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];
		return *this;
	}

	FPS &operator-=(const mint &r) {
		if (this->empty()) this->resize(1);
		(*this)[0] -= r;
		return *this;
	}

	FPS &operator*=(const mint &v) {
		for (int k = 0; k < (int)this->size(); k++) (*this)[k] *= v;
		return *this;
	}

	FPS &operator/=(const FPS &r) {
		if (this->size() < r.size()) {
			this->clear();
			return *this;
		}
		int n = this->size() - r.size() + 1;
		if ((int)r.size() <= 64) {
			FPS f(*this), g(r);
			g.shrink();
			mint coeff = g.back().inverse();
			for (auto &x : g) x *= coeff;
			int deg = (int)f.size() - (int)g.size() + 1;
			int gs = g.size();
			FPS quo(deg);
			for (int i = deg - 1; i >= 0; i--) {
				quo[i] = f[i + gs - 1];
				for (int j = 0; j < gs; j++) f[i + j] -= quo[i] * g[j];
			}
			*this = quo * coeff;
			this->resize(n, mint(0));
			return *this;
		}
		return *this = ((*this).rev().pre(n) * r.rev().inv(n)).pre(n).rev();
	}

	FPS &operator/=(const mint &v) {
		for (int k = 0; k < (int)this->size(); k++) (*this)[k] /= v;
		return *this;
	}

	FPS &operator%=(const FPS &r) {
		*this -= *this / r * r;
		shrink();
		return *this;
	}

	FPS operator+(const FPS &r) const { return FPS(*this) += r; }
	FPS operator+(const mint &v) const { return FPS(*this) += v; }
	FPS operator-(const FPS &r) const { return FPS(*this) -= r; }
	FPS operator-(const mint &v) const { return FPS(*this) -= v; }
	FPS operator*(const FPS &r) const { return FPS(*this) *= r; }
	FPS operator*(const mint &v) const { return FPS(*this) *= v; }
	FPS operator/(const FPS &r) const { return FPS(*this) /= r; }
	FPS operator/(const mint &v) const { return FPS(*this) /= v; }
	FPS operator%(const FPS &r) const { return FPS(*this) %= r; }
	FPS operator-() const {
		FPS ret(this->size());
		for (int i = 0; i < (int)this->size(); i++) ret[i] = -(*this)[i];
		return ret;
	}

	void shrink() {
		while (this->size() && this->back() == mint(0)) this->pop_back();
	}

	FPS rev() const {
		FPS ret(*this);
		reverse(begin(ret), end(ret));
		return ret;
	}

	FPS dot(FPS r) const {
		FPS ret(min(this->size(), r.size()));
		for (int i = 0; i < (int)ret.size(); i++) ret[i] = (*this)[i] * r[i];
		return ret;
	}

	// 前 sz 項を取ってくる。sz に足りない項は 0 埋めする
	FPS pre(int sz) const {
		FPS ret(begin(*this), begin(*this) + min((int)this->size(), sz));
		if ((int)ret.size() < sz) ret.resize(sz);
		return ret;
	}

	FPS operator>>(int sz) const {
		if ((int)this->size() <= sz) return {};
		FPS ret(*this);
		ret.erase(ret.begin(), ret.begin() + sz);
		return ret;
	}

	FPS operator<<(int sz) const {
		FPS ret(*this);
		ret.insert(ret.begin(), sz, mint(0));
		return ret;
	}

	FPS diff() const {
		const int n = (int)this->size();
		FPS ret(max(0, n - 1));
		mint one(1), coeff(1);
		for (int i = 1; i < n; i++) {
			ret[i - 1] = (*this)[i] * coeff;
			coeff += one;
		}
		return ret;
	}

	FPS integral() const {
		const int n = (int)this->size();
		FPS ret(n + 1);
		ret[0] = mint(0);
		if (n > 0) ret[1] = mint(1);
		auto mod = mint::get_mod();
		for (int i = 2; i <= n; i++) ret[i] = (-ret[mod % i]) * (mod / i);
		for (int i = 0; i < n; i++) ret[i + 1] *= (*this)[i];
		return ret;
	}

	mint eval(mint x) const {
		mint r = 0, w = 1;
		for (auto &v : *this) r += w * v, w *= x;
		return r;
	}

	FPS log(int deg = -1) const {
		assert(!(*this).empty() && (*this)[0] == mint(1));
		if (deg == -1) deg = (int)this->size();
		return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
	}

	FPS pow(int64_t k, int deg = -1) const {
		const int n = (int)this->size();
		if (deg == -1) deg = n;
		if (k == 0) {
			FPS ret(deg);
			if (deg) ret[0] = 1;
			return ret;
		}
		for (int i = 0; i < n; i++) {
			if ((*this)[i] != mint(0)) {
				mint rev = mint(1) / (*this)[i];
				FPS ret = (((*this * rev) >> i).log(deg) * k).exp(deg);
				ret *= (*this)[i].pow(k);
				ret = (ret << (i * k)).pre(deg);
				if ((int)ret.size() < deg) ret.resize(deg, mint(0));
				return ret;
			}
			if (__int128_t(i + 1) * k >= deg) return FPS(deg, mint(0));
		}
		return FPS(deg, mint(0));
	}

	static void *ntt_ptr;
	static void set_fft();
	FPS &operator*=(const FPS &r);
	void ntt();
	void intt();
	void ntt_doubling();
	static int ntt_pr();
	FPS inv(int deg = -1) const;
	FPS exp(int deg = -1) const;
};
template <typename mint>
void *FormalPowerSeries<mint>::ntt_ptr = nullptr;

/**
 * @brief 多項式/形式的冪級数ライブラリ
 * @docs docs/fps/formal-power-series.md
 */
// End include: "./formal-power-series.hpp"

template <typename mint>
void FormalPowerSeries<mint>::set_fft() {
  if (!ntt_ptr) ntt_ptr = new NTT<mint>;
}

template <typename mint>
FormalPowerSeries<mint>& FormalPowerSeries<mint>::operator*=(
    const FormalPowerSeries<mint>& r) {
  if (this->empty() || r.empty()) {
    this->clear();
    return *this;
  }
  set_fft();
  auto ret = static_cast<NTT<mint>*>(ntt_ptr)->multiply(*this, r);
  return *this = FormalPowerSeries<mint>(ret.begin(), ret.end());
}

template <typename mint>
void FormalPowerSeries<mint>::ntt() {
  set_fft();
  static_cast<NTT<mint>*>(ntt_ptr)->ntt(*this);
}

template <typename mint>
void FormalPowerSeries<mint>::intt() {
  set_fft();
  static_cast<NTT<mint>*>(ntt_ptr)->intt(*this);
}

template <typename mint>
void FormalPowerSeries<mint>::ntt_doubling() {
  set_fft();
  static_cast<NTT<mint>*>(ntt_ptr)->ntt_doubling(*this);
}

template <typename mint>
int FormalPowerSeries<mint>::ntt_pr() {
  set_fft();
  return static_cast<NTT<mint>*>(ntt_ptr)->pr;
}

template <typename mint>
FormalPowerSeries<mint> FormalPowerSeries<mint>::inv(int deg) const {
  assert((*this)[0] != mint(0));
  if (deg == -1) deg = (int)this->size();
  FormalPowerSeries<mint> res(deg);
  res[0] = {mint(1) / (*this)[0]};
  for (int d = 1; d < deg; d <<= 1) {
    FormalPowerSeries<mint> f(2 * d), g(2 * d);
    for (int j = 0; j < min((int)this->size(), 2 * d); j++) f[j] = (*this)[j];
    for (int j = 0; j < d; j++) g[j] = res[j];
    f.ntt();
    g.ntt();
    for (int j = 0; j < 2 * d; j++) f[j] *= g[j];
    f.intt();
    for (int j = 0; j < d; j++) f[j] = mint(0);
    f.ntt();
    for (int j = 0; j < 2 * d; j++) f[j] *= g[j];
    f.intt();
    for (int j = d; j < min(2 * d, deg); j++) res[j] = -f[j];
  }
  return res.pre(deg);
}

template <typename mint>
FormalPowerSeries<mint> FormalPowerSeries<mint>::exp(int deg) const {
  using fps = FormalPowerSeries<mint>;
  assert((*this).size() == 0 || (*this)[0] == mint(0));
  if (deg == -1) deg = this->size();

  fps inv;
  inv.reserve(deg + 1);
  inv.push_back(mint(0));
  inv.push_back(mint(1));

  auto inplace_integral = [&](fps& F) -> void {
    const int n = (int)F.size();
    auto mod = mint::get_mod();
    while ((int)inv.size() <= n) {
      int i = inv.size();
      inv.push_back((-inv[mod % i]) * (mod / i));
    }
    F.insert(begin(F), mint(0));
    for (int i = 1; i <= n; i++) F[i] *= inv[i];
  };

  auto inplace_diff = [](fps& F) -> void {
    if (F.empty()) return;
    F.erase(begin(F));
    mint coeff = mint(1), one = mint(1);
    for (int i = 0; i < (int)F.size(); i++) {
      F[i] *= coeff;
      coeff += one;
    }
  };

  fps b{1, 1 < (int)this->size() ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};
  for (int m = 2; m < deg; m *= 2) {
    auto y = b;
    y.resize(2 * m);
    y.ntt();
    z1 = z2;
    fps z(m);
    for (int i = 0; i < m; ++i) z[i] = y[i] * z1[i];
    z.intt();
    fill(begin(z), begin(z) + m / 2, mint(0));
    z.ntt();
    for (int i = 0; i < m; ++i) z[i] *= -z1[i];
    z.intt();
    c.insert(end(c), begin(z) + m / 2, end(z));
    z2 = c;
    z2.resize(2 * m);
    z2.ntt();
    fps x(begin(*this), begin(*this) + min<int>(this->size(), m));
    x.resize(m);
    inplace_diff(x);
    x.push_back(mint(0));
    x.ntt();
    for (int i = 0; i < m; ++i) x[i] *= y[i];
    x.intt();
    x -= b.diff();
    x.resize(2 * m);
    for (int i = 0; i < m - 1; ++i) x[m + i] = x[i], x[i] = mint(0);
    x.ntt();
    for (int i = 0; i < 2 * m; ++i) x[i] *= z2[i];
    x.intt();
    x.pop_back();
    inplace_integral(x);
    for (int i = m; i < min<int>(this->size(), 2 * m); ++i) x[i] += (*this)[i];
    fill(begin(x), begin(x) + m, mint(0));
    x.ntt();
    for (int i = 0; i < 2 * m; ++i) x[i] *= y[i];
    x.intt();
    b.insert(end(b), begin(x) + m, end(x));
  }
  return fps{begin(b), begin(b) + deg};
}

/**
 * @brief NTT mod用FPSライブラリ
 * @docs docs/fps/ntt-friendly-fps.md
 */
// End include: "../../fps/ntt-friendly-fps.hpp"
/* #include "../../ntt/multivariate-circular-convolution.hpp" */
// Begin include: "../../fps/multivariate-fps.hpp"

#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

// Begin include: "../modulo/binomial.hpp"

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
// End include: "../modulo/binomial.hpp"
// Begin include: "../ntt/multivariate-multiplication.hpp"

// 長さが等しい列同士の畳み込みしかしない
template <typename fps>
fps multivariate_multiplication(const fps& f, const fps& g,
                                const vector<int>& base) {
  assert(f.size() == g.size());
  int n = f.size(), s = base.size(), W = 1;
  if (s == 0) return fps{f[0] * g[0]};
  while (W < 2 * n) W *= 2;

  vector<int> chi(n);
  for (int i = 0; i < n; i++) {
    int x = i;
    for (int j = 0; j < s - 1; j++) chi[i] += (x /= base[j]);
    chi[i] %= s;
  }

  vector<fps> F(s, fps(W)), G(s, fps(W));
  for (int i = 0; i < n; i++) F[chi[i]][i] = f[i], G[chi[i]][i] = g[i];

  for (auto& x : F) x.ntt();
  for (auto& x : G) x.ntt();
  fps a(s);
  for (int k = 0; k < W; k++) {
    fill(begin(a), end(a), typename fps::value_type());
    for (int i = 0; i < s; i++)
      for (int j = 0; j < s; j++) {
        a[i + j - (i + j >= s ? s : 0)] += F[i][k] * G[j][k];
      }
    for (int i = 0; i < s; i++) F[i][k] = a[i];
  }
  for (auto& x : F) x.intt();
  fps h(n);
  for (int i = 0; i < n; i++) h[i] = F[chi[i]][i];
  return h;
}

/**
 * @brief Multivariate Multiplication
 * @docs docs/ntt/multivariate-multiplication.md
 */
// End include: "../ntt/multivariate-multiplication.hpp"
// Begin include: "formal-power-series.hpp"

// End include: "formal-power-series.hpp"

// FFT mod でないと使えない
// f.size() != (base の総積) でも動くが, 二項演算は長さが等しい列同士しかダメ
// 添え字アクセスは operator() を使う
template <typename mint>
struct MultivariateFormalPowerSeries {
  using mfps = MultivariateFormalPowerSeries<mint>;
  using fps = FormalPowerSeries<mint>;

  fps f;
  vector<int> base;

  MultivariateFormalPowerSeries() = default;
  MultivariateFormalPowerSeries(const vector<int>& _base) : base(_base) {
    int n = 1;
    for (auto& x : base) n *= x;
    f.resize(n);
  }
  MultivariateFormalPowerSeries(const fps& _f, const vector<int>& _base)
      : f(_f), base(_base) {}

  friend ostream& operator<<(ostream& os, const mfps& rhs) {
    os << "[ ";
    for (int i = 0; i < (int)rhs.f.size(); i++) {
      os << rhs.f[i] << (i + 1 == (int)rhs.f.size() ? "" : ", ");
    }
    return os << " ]";
  }

  long long _id(int) { return 0; }
  template <typename Head, typename... Tail>
  long long _id(int i, Head&& head, Tail&&... tail) {
    assert(i < (int)base.size() && (int)head < base[i]);
    return head + _id(i + 1, std::forward<Tail>(tail)...) * base[i];
  }
  template <typename... Args>
  long long id(Args&&... args) {
    return _id(0, std::forward<Args>(args)...);
  }
  template <typename... Args>
  mint& operator()(Args&&... args) {
    return f[id(std::forward<Args>(args)...)];
  }

  mfps& operator+=(const mfps& rhs) {
    assert(base == rhs.base && f.size() == rhs.f.size());
    for (int i = 0; i < (int)f.size(); i++) f[i] += rhs.f[i];
    return *this;
  }
  mfps& operator-=(const mfps& rhs) {
    assert(base == rhs.base && f.size() == rhs.f.size());
    for (int i = 0; i < (int)f.size(); i++) f[i] -= rhs.f[i];
    return *this;
  }
  mfps& operator*=(const mfps& rhs) {
    assert(base == rhs.base && f.size() == rhs.f.size());
    f = multivariate_multiplication(f, rhs.f, base);
    return *this;
  }
  mfps& operator/=(const mfps& rhs) {
    assert(base == rhs.base);
    assert(f.size() == rhs.f.size());
    return (*this) *= rhs.inv();
  }

  mfps& operator+=(const mint& rhs) {
    assert(!f.empty());
    f[0] += rhs;
    return *this;
  }
  mfps& operator-=(const mint& rhs) {
    assert(!f.empty());
    f[0] -= rhs;
    return *this;
  }
  mfps& operator*=(const mint& rhs) {
    for (auto& x : f) x *= rhs;
    return *this;
  }
  mfps& operator/=(const mint& rhs) {
    for (auto& x : f) x /= rhs;
    return *this;
  }

  mfps operator+(const mfps& rhs) const { return mfps{*this} += rhs; }
  mfps operator-(const mfps& rhs) const { return mfps{*this} -= rhs; }
  mfps operator*(const mfps& rhs) const { return mfps{*this} *= rhs; }
  mfps operator/(const mfps& rhs) const { return mfps{*this} /= rhs; }

  mfps operator+(const mint& rhs) const { return mfps{*this} += rhs; }
  mfps operator-(const mint& rhs) const { return mfps{*this} -= rhs; }
  mfps operator*(const mint& rhs) const { return mfps{*this} *= rhs; }
  mfps operator/(const mint& rhs) const { return mfps{*this} /= rhs; }

  mfps operator+() const { return mfps{*this}; }
  mfps operator-() const { return mfps{-f, base}; }

  friend bool operator==(const mfps& lhs, const mfps& rhs) {
    return lhs.f == rhs.f && lhs.base == rhs.base;
  }
  friend bool operator!=(const mfps& lhs, const mfps& rhs) {
    return lhs.f != rhs.f || lhs.base != rhs.base;
  }

  mfps diff() const {
    mfps g{*this};
    for (int i = 0; i < (int)g.f.size(); i++) g.f[i] *= i;
    return g;
  }
  mfps integral() const {
    static Binomial<mint> binom;
    mfps g{*this};
    for (int i = 1; i < (int)g.f.size(); i++) g.f[i] *= binom.inv(i);
    return g;
  }

  mfps inv() const {
    assert(f[0] != 0);
    if (base.empty()) return mfps{fps{f[0].inverse()}, base};
    int n = f.size(), s = base.size(), W = 1;
    while (W < 2 * n) W *= 2;

    vector<int> chi(W);
    for (int i = 0; i < W; i++) {
      int x = i;
      for (int j = 0; j < s - 1; j++) chi[i] += (x /= base[j]);
      chi[i] %= s;
    }
    auto hadamard_prod = [&s](vector<fps>& F, vector<fps>& G, vector<fps>& H) {
      fps a(s);
      for (int k = 0; k < (int)F[0].size(); k++) {
        fill(begin(a), end(a), typename fps::value_type());
        for (int i = 0; i < s; i++)
          for (int j = 0; j < s; j++) {
            a[i + j - (i + j >= s ? s : 0)] += F[i][k] * G[j][k];
          }
        for (int i = 0; i < s; i++) H[i][k] = a[i];
      }
    };
    fps g(W);
    g[0] = f[0].inverse();
    for (int d = 1; d < n; d *= 2) {
      vector<fps> F(s, fps(2 * d)), G(s, fps(2 * d)), H(s, fps(2 * d));
      for (int j = 0; j < min((int)f.size(), 2 * d); j++) F[chi[j]][j] = f[j];
      for (int j = 0; j < d; j++) G[chi[j]][j] = g[j];
      for (auto& x : F) x.ntt();
      for (auto& x : G) x.ntt();
      hadamard_prod(F, G, H);
      for (auto& x : H) x.intt();
      for (auto& x : F) fill(begin(x), end(x), typename fps::value_type());
      for (int j = d; j < 2 * d; j++) F[chi[j]][j] = H[chi[j]][j];
      for (auto& x : F) x.ntt();
      hadamard_prod(F, G, H);
      for (auto& x : H) x.intt();
      for (int j = d; j < 2 * d; j++) g[j] = -H[chi[j]][j];
    }
    mfps res{*this};
    res.f = fps{begin(g), begin(g) + n};
    return res;
  }
  mfps log() const {
    assert(!f.empty() && f[0] == 1);
    return ((*this).diff() / *this).integral();
  }
  mfps exp() const {
    assert(!f.empty() && f[0] == mint{0});
    int n = f.size();
    mfps g{fps{1}, base};
    for (int d = 1; d < n; d *= 2) {
      int s = min(n, d * 2);
      g.f.resize(s, mint{0});
      g *= mfps{fps{begin(f), begin(f) + s}, base} - g.log() + 1;
    }
    return g;
  }
  mfps pow(long long e) const {
    assert(!f.empty());
    if (f[0] != 0) {
      mint f0inv = f[0].inverse(), coe = f[0].pow(e);
      return (((*this) * f0inv).log() * e).exp() * coe;
    }
    int n = f.size();
    long long base_sum = 0;
    for (auto& b : base) base_sum += b - 1;
    if (e > base_sum) return mfps{fps(n), base};
    mfps res{fps(n), base}, a{*this};
    res.f[0] = 1;
    for (; e; a *= a, e >>= 1) {
      if (e & 1) res *= a;
    }
    return res;
  }
};

/**
 * @brief 多変数形式的冪級数ライブラリ
 */
// End include: "../../fps/multivariate-fps.hpp"
// Begin include: "../../modint/montgomery-modint.hpp"

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
// End include: "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps=MultivariateFormalPowerSeries<mint>;
void yamada::solve()
{
	ini(Z,Y,X);
	vv(string,A,X,Y);
	vv(string,B,X,Y);
	in(A,B);
	each(b2,B)each(b1,b2)reverse(all(b1));
	each(b2,B)reverse(all(b2));
	reverse(all(B));
	char C='W',D='B';

	vvv(ll,cnt,X,Y,Z);
	rep(2){
		swap(C,D);
		fps f({X*2,Y*2,Z*2});
		fps g({X*2,Y*2,Z*2});
		rep(i,X)rep(j,Y)rep(k,Z)if(A[i][j][k]==C)f(i,j,k)=1;
		rep(i,X)rep(j,Y)rep(k,Z)if(B[i][j][k]==D)g(i,j,k)=1;
		auto h=f*g;
		rep(i,X*2)rep(j,Y*2)rep(k,Z*2)cnt[i%X][j%Y][k%Z]+=h(i,j,k).get();
	}

	ll ans=infLL;
	rep(i,X)rep(j,Y)rep(k,Z)amin(ans,cnt[i][j][k]);
	out(ans);
}