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
// Begin include: "../../data-structure-2d/fenwick-tree-on-wavelet-matrix.hpp"
#include <immintrin.h>
//

struct bit_vector {
	using u32 = uint32_t;
	using i64 = int64_t;
	using u64 = uint64_t;

	static constexpr u32 w = 64;
	vector<u64> block;
	vector<u32> count;
	u32 n, zeros;

	inline u32 get(u32 i) const { return u32(block[i / w] >> (i % w)) & 1u; }
	inline void set(u32 i) { block[i / w] |= 1LL << (i % w); }

	bit_vector() {}
	bit_vector(int _n) { init(_n); }
	__attribute__((optimize("O3,unroll-loops"))) void init(int _n) {
		n = zeros = _n;
		block.resize(n / w + 1, 0);
		count.resize(block.size(), 0);
	}

	__attribute__((target("popcnt"))) void build() {
		for (u32 i = 1; i < block.size(); ++i)
			count[i] = count[i - 1] + _mm_popcnt_u64(block[i - 1]);
		zeros = rank0(n);
	}

	inline u32 rank0(u32 i) const { return i - rank1(i); }

	__attribute__((target("bmi2,popcnt"))) inline u32 rank1(u32 i) const {
		return count[i / w] + _mm_popcnt_u64(_bzhi_u64(block[i / w], i % w));
	}
};

template <typename S, typename T>
struct WaveletMatrix {
	using u32 = uint32_t;
	using i64 = int64_t;
	using u64 = uint64_t;

	struct BIT {
		u32 N;
		vector<T> data;

		BIT() = default;
		BIT(int size) { init(size); }

		void init(int size) {
			N = size;
			data.assign(N + 1, 0);
		}

		__attribute__((target("bmi"))) void add(u32 k, T x) {
			for (++k; k <= N; k += _blsi_u32(k)) data[k] += x;
		}

		__attribute__((target("bmi"))) T sum(u32 k) const {
			T ret = T();
			for (; k; k = _blsr_u32(k)) ret += data[k];
			return ret;
		}

		__attribute__((target("bmi"))) T sum(int l, int r) const {
			T ret = T();
			while (l != r) {
				if (l < r) {
					ret += data[r];
					r = _blsr_u32(r);
				} else {
					ret -= data[l];
					l = _blsr_u32(l);
				}
			}
			return ret;
		}
	};

	using P = pair<S, S>;
	int n, lg;
	vector<bit_vector> bv;
	vector<BIT> bit;
	vector<P> ps;
	vector<S> ys;

	WaveletMatrix() {}

	void add_point(S x, S y) {
		ps.emplace_back(x, y);
		ys.emplace_back(y);
	}

	void imos_add_point(S L, S D, S R, S U) {
		add_point(L, D);
		add_point(R, D);
		add_point(L, U);
		add_point(R, U);
	}

	__attribute__((optimize("O3"))) void build() {
		sort(begin(ps), end(ps));
		ps.erase(unique(begin(ps), end(ps)), end(ps));
		n = ps.size();
		sort(begin(ys), end(ys));
		ys.erase(unique(begin(ys), end(ys)), end(ys));
		vector<u32> cur(n), nxt(n);
		for (int i = 0; i < n; ++i) cur[i] = yid(ps[i].second);
		lg = __lg(max(n, 1)) + 1;
		bv.assign(lg, n);
		bit.assign(lg, n);
		for (int h = lg - 1; h >= 0; --h) {
			for (int i = 0; i < n; ++i)
				if ((cur[i] >> h) & 1) bv[h].set(i);
			bv[h].build();
			array<decltype(begin(nxt)), 2> it{begin(nxt), begin(nxt) + bv[h].zeros};
			for (int i = 0; i < n; ++i) *it[bv[h].get(i)]++ = cur[i];
			swap(cur, nxt);
		}
	}

	int xid(S x) const {
		return lower_bound(
				begin(ps), end(ps), make_pair(x, S()),
				[](const P& a, const P& b) { return a.first < b.first; }) -
			begin(ps);
	}

	int yid(S y) const { return lower_bound(begin(ys), end(ys), y) - begin(ys); }

	void add(S x, S y, T val) {
		int i = lower_bound(begin(ps), end(ps), P{x, y}) - begin(ps);
		for (int h = lg - 1; h >= 0; --h) {
			int i0 = bv[h].rank0(i);
			if (bv[h].get(i))
				i += bv[h].zeros - i0;
			else
				i = i0;
			bit[h].add(i, val);
		}
	}

	void imos_add(S L, S D, S R, S U, T val) {
		add(L, D, val);
		add(R, D, -val);
		add(L, U, -val);
		add(R, U, val);
	}

	T sum(int l, int r, u32 upper) const { // DO NOT USE!!!!!!!!!!!!!
		T res = 0;
		for (int h = lg; h--;) {
			int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
			if ((upper >> h) & 1) {
				res += bit[h].sum(l0, r0);
				l += bv[h].zeros - l0;
				r += bv[h].zeros - r0;
			} else {
				l = l0, r = r0;
			}
		}
		return res;
	}

	// [(l, 0), (r, res)) の sum が X 未満
	S sum_lower_bound(int l, int r, T X) const {
		l = xid(l);
		r = xid(r);
		S res = 0;
		for (int h = lg; h--;) {
			int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
			T sum_l0r0 = bit[h].sum(l0, r0);
			if (sum_l0r0 < X) {
				X -= sum_l0r0;
				res |= S(1) << h;
				l += bv[h].zeros - l0;
				r += bv[h].zeros - r0;
			}
			else l = l0, r = r0;
		}
		return res < (S)ys.size() ? ys[res] : ys.back() + 1;
	}

	// [(l, 0), (r, res)) の sum が X 以下
	S sum_upper_bound(int l, int r, T X) const { return sum_lower_bound(l, r, X + 1); }

	T sum(S L, S D, S R, S U) const {
		int l = xid(L), r = xid(R);
		return sum(l, r, yid(U)) - sum(l, r, yid(D));
	}

	T imos(S x, S y) const {
		return sum(0, 0, x + 1, y + 1);
	}
};
// End include: "../../data-structure-2d/fenwick-tree-on-wavelet-matrix.hpp"
// Begin include: "../../tree/cartesian-tree.hpp"
/*
   辞書順で高さを unique して、木にしている。
   極大長方形アルゴリズムで線形時間構築。
 */
template <typename T, bool ROOT_IS_MIN = 1>
struct CartesianTree {
	int N;
	vector<T>& A;
	vector<pair<int, int>> range;
	vector<int> lch, rch, par;
	int root;

	CartesianTree(vector<T>& A) : N(A.size()), A(A) {
		range.assign(N, {-1, -1});
		lch.assign(N, -1);
		rch.assign(N, -1);
		par.assign(N, -1);
		if (N == 1) {
			range[0] = {0, 1};
			root = 0;
			return;
		}
		auto is_smaller = [&](int i, int j) -> bool {
			if (ROOT_IS_MIN) return (A[i] < A[j]) || (A[i] == A[j] && i < j);
			return (A[i] > A[j]) || (A[i] == A[j] && i < j);
		};
		vector<int> st;
		for (int i = 0; i < N; i++) {
			while (!st.empty() && is_smaller(i, st.back())) {
				lch[i] = st.back();
				st.pop_back();
			}
			range[i].first = (st.empty() ? 0 : st.back() + 1);
			st.emplace_back(i);
		}
		st.clear();
		for (int i = N - 1; i >= 0; i--) {
			while (!st.empty() && is_smaller(i, st.back())) {
				rch[i] = st.back();
				st.pop_back();
			}
			range[i].second = (st.empty() ? N : st.back());
			st.emplace_back(i);
		}
		for (int i = 0; i < N; i++) if (lch[i] != -1) par[lch[i]] = i;
		for (int i = 0; i < N; i++) if (rch[i] != -1) par[rch[i]] = i;
		for (int i = 0; i < N; i++) if (par[i] == -1) root = i;
	}

	// (l, r, h)
	tuple<int, int, T> maximum_rectangle(int i) {
		auto [l, r] = range[i];
		return {l, r, A[i]};
	}

	// (l, r, h)
	T max_rectangle_area() {
		assert(ROOT_IS_MIN);
		T ans = 0;
		for (int i = 0; i < N; i++) {
			auto [l, r, h] = maximum_rectangle(i);
			ans = max(ans, (r - l) * h);
		}
		return ans;
	}

	long long count_subrectangle(bool baseline) {
		assert(ROOT_IS_MIN);
		long long ans = 0;
		for (int i = 0; i < N; i++) {
			auto [l, r, h] = maximum_rectangle(i);
			long long x = (baseline ? h : h * (h + 1) / 2);
			ans += x * (i - l + 1) * (r - i);
		}
		return ans;
	}
};
// End include: "../../tree/cartesian-tree.hpp"
using namespace yamada;

template<typename T>
vl rec_add_pnt_get(vc<array<int,5>> &LDRUA,vp &lr){
	WaveletMatrix<int,T> wm;
	for(auto&[L,D,R,U,A]:LDRUA){
		/* out("l,r,L,R:",L,R,D,U); */
		wm.imos_add_point(L,D,R,U);
	}
	wm.build();
	for(auto&[L,D,R,U,A]:LDRUA){
		wm.imos_add(L,D,R,U,A);
	}

	int Q=lr.size();
	vl ans(Q);
	rep(qi,Q){
		auto[l,r]=lr[qi];
		ans[qi]+=wm.imos(l,r);
	}
	return ans;
}

void yamada::solve()
{
	ini(N,Q);
	vc<int> A(N); in(A); each(a,A)--a;
	vp lr(Q);
	rep(i,Q)in(lr[i].fi);
	rep(i,Q)in(lr[i].se);
	each2(l,r,lr)--l;

	CartesianTree<int,false> ct(A);
	vl ans(Q);
	vc<array<int,5>> LDRUA(N);
	{ // l
		for(int i=0; i<N; i++){
			auto[L,R]=ct.range[i];
			LDRUA[i]={L,i+1,i+1,N+1,-1};
		}
		auto bns=rec_add_pnt_get<int>(LDRUA,lr);
		out("bns:",bns);
		rep(qi,Q)ans[qi]+=bns[qi]*lr[qi].fi;
	}
	{ // r
		for(int i=0; i<N; i++){
			auto[L,R]=ct.range[i];
			LDRUA[i]={0,i+1,i+1,R+1,1};
		}
		auto bns=rec_add_pnt_get<int>(LDRUA,lr);
		out("bns:",bns);
		rep(qi,Q)ans[qi]+=bns[qi]*lr[qi].se;
	}
	{ // 1
		for(int i=0; i<N; i++){
			auto[L,R]=ct.range[i];
			LDRUA[i]={0,i+1,L,N+1,-L};
		}
		auto bns=rec_add_pnt_get<ll>(LDRUA,lr);
		out("bns:",bns);
		rep(qi,Q)ans[qi]+=bns[qi];
	}
	{ // 1
		for(int i=0; i<N; i++){
			auto[L,R]=ct.range[i];
			LDRUA[i]={0,R+1,i+1,N+1,R};
		}
		auto bns=rec_add_pnt_get<ll>(LDRUA,lr);
		out("bns:",bns);
		rep(qi,Q)ans[qi]+=bns[qi];
	}

	out(ans);
}
