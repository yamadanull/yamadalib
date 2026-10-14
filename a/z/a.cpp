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
	inline T operator()(int l, int r) { return query(l, r); }
};

long long floor(long long a, long long b) {
	assert(b != 0);
	if (b < 0) a = -a, b = -b;
	return a / b - (a % b < 0);
}
long long under(long long a, long long b) {
	assert(b != 0);
	if (b < 0) a = -a, b = -b;
	return a / b - (a % b <= 0);
}
long long ceil(long long a, long long b) {
	assert(b != 0);
	if (b < 0) a = -a, b = -b;
	return a / b + (a % b > 0);
}
long long over(long long a, long long b) {
	assert(b != 0);
	if (b < 0) a = -a, b = -b;
	return a / b + (a % b >= 0);
}
long long modulo(long long a, long long b) {
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
// Begin include: "../../segment-tree/segment-tree.hpp"

template <typename S>
struct SegmentTree {
	std::vector<S> dat;
	int N, LOG, M;

	SegmentTree() {}
	SegmentTree(int N) { build(N); }
	template <typename I>
	SegmentTree(int N, I init) { build(N, init); }
	template <typename T>
	SegmentTree(const std::vector<T>& v) { build(v); }

	void build(int _N) {
		build(_N, [](int i) -> S { return S(); });
	}
	template <typename T>
	void build(const std::vector<T>& v) {
		build(v.size(), [&](int i) -> S { return S(v[i]); });
	}
	template <typename I>
	void build(int _N, I init) {
		N = _N, LOG = 1;
		while ((1 << LOG) < N) ++LOG;
		M = 1 << LOG;
		dat.assign(M << 1, S());
		for (int i = 0; i < N; i++) dat[M + i] = init(i);
		for (int i = M - 1; i >= 1; i--) update(i);
	}

	S get(int i) { return dat[M + i]; }
	std::vector<S> get() { return {dat.begin() + M, dat.begin() + M + N}; }
	S &operator[](int i) { return get(i); }

	void set(int i, const S& x) {
		assert(i < N);
		dat[i += M] = x;
		while (i >>= 1) update(i);
	}

	void multiply(int i, const S& x) {
		assert(i < N);
		i += M;
		dat[i] += x;
		while (i >>= 1) update(i);
	}

	S prod(int L, int R) {
		assert(0 <= L && L <= R && R <= N);
		S xl, xr;
		L += M, R += M;
		while (L < R) {
			if (L & 1) xl = xl + dat[L++];
			if (R & 1) xr = dat[--R] + xr;
			L >>= 1, R >>= 1;
		}
		return xl + xr;
	}
	S prod() { return dat[1]; }

	std::vector<int> prod_idxs(int L, int R) { // これはうれしいかも
		assert(0 <= L && L <= R && R <= N);
		std::vector<int> ans, bns;
		L += M, R += M;
		while (L < R) {
			if (L & 1) ans.emplace_back(L++);
			if (R & 1) bns.emplace_back(--R);
			L >>= 1, R >>= 1;
		}
		std::reverse(all(bns));
		for (auto& b : bns) ans.emplace_back(b);
		return ans;
	}

	template <class G>
	int max_right(G check, int L) {
		assert(0 <= L && L <= N && check(S()));
		if (L == N) return N;
		L += M;
		S sm;
		do {
			while (L % 2 == 0) L >>= 1;
			if (!check(sm + dat[L])) {
				while (L < M) {
					L = 2 * L;
					if (check(sm + dat[L])) {
						sm += dat[L++];
					}
				}
				return L - M;
			}
			sm += dat[L++];
		} while ((L & -L) != L);
		return N;
	}

	template <class G>
	int min_left(G check, int R) {
		assert(0 <= R && R <= N && check(S()));
		if (R == 0) return 0;
		R += M;
		S sm;
		do {
			--R;
			while (R > 1 && (R % 2)) R >>= 1;
			if (!check(dat[R] + sm)) {
				while (R < M) {
					R = 2 * R + 1;
					if (check(dat[R] + sm)) {
						sm = dat[R--] + sm;
					}
				}
				return R + 1 - M;
			}
			sm = dat[R] + sm;
		} while ((R & -R) != R);
		return 0;
	}

	// prod_{l<=i<r} A[i xor x]
	S xor_prod(int l, int r, int xor_val) { // これいる？
		static_assert(S::COMMUTATIVE);
		S ans;
		for (int k = 0; k <= LOG; ++k) {
			if (l >= r) break;
			if (l & 1) ans += (dat[(M >> k) + ((l++) ^ xor_val)]);
			if (r & 1) ans += (dat[(M >> k) + ((--r) ^ xor_val)]);
			l /= 2, r /= 2, xor_val /= 2;
		}
		return ans;
	}

	private:
	void update(int i) { dat[i] = dat[i * 2] + dat[i * 2 + 1]; }
};
// End include: "../../segment-tree/segment-tree.hpp"
// Begin include: "../../segment-tree/lazy-segment-tree-utility.hpp"

// Begin include: "../monoid/basic.hpp"

namespace Monoid {

template <typename Derived, typename T>
struct Common {
	constexpr Derived operator+(const Derived &b) const { Derived r = static_cast<const Derived&>(*this); return r += b; }
	constexpr Derived operator-(const Derived &b) const { Derived r = static_cast<const Derived&>(*this); return r -= b; }
	constexpr Derived operator-() const { return Derived() - static_cast<const Derived&>(*this); }
	constexpr operator T() const { return static_cast<const Derived&>(*this).a; }
	constexpr bool operator==(const Derived &b) const { return static_cast<const Derived&>(*this).a == b.a; }
	constexpr bool operator!=(const Derived &b) const { return static_cast<const Derived&>(*this).a != b.a; }
};

template <typename T>
struct Plus : Common<Plus<T>, T> {
	static constexpr bool COMMUTATIVE = 1;
	using value_type = T;
	T a;
	constexpr Plus &operator+=(const Plus &b) {
		a += T(b);
		return *this;
	}
	constexpr Plus &operator-=(const Plus &b) {
		a -= T(b);
		return *this;
	}
	constexpr Plus() : a() {}
	constexpr Plus(T _a) : a(_a) {}
};

template <typename T, T MINF>
struct Max : Common<Max<T, MINF>, T> {
	static constexpr bool COMMUTATIVE = 1;
	using value_type = T;
	T a;
	constexpr Max &operator+=(const Max &b) {
		a = std::max(a, T(b));
		return *this;
	}
	constexpr Max() : a(MINF) {}
	constexpr Max(T _a) : a(_a) {}
};

template <typename T, T INF>
struct Min : Common<Min<T, INF>, T> {
	static constexpr bool COMMUTATIVE = 1;
	using value_type = T;
	T a;
	constexpr Min &operator+=(const Min &b) {
		a = std::min(a, T(b));
		return *this;
	}
	constexpr Min() : a(INF) {}
	constexpr Min(T _a) : a(_a) {}
};

template <typename T, T UNUSED_VALUE>
struct Update : Common<Update<T, UNUSED_VALUE>, T> {
	static constexpr bool COMMUTATIVE = 0;
	using value_type = T;
	T a;
	constexpr Update &operator+=(const Update &b) {
		if (T(b) != UNUSED_VALUE) a = T(b);
		return *this;
	}
	constexpr Update() : a(UNUSED_VALUE) {}
	constexpr Update(T _a) : a(_a) {}
	constexpr Update operator+(const Update &b) const { return Update(*this) += b; }
};

template <typename MonoidBase>
struct CntMonoid { // コンテスト中にこれを直接扱うのは、頭が爆発するので非推奨
	static constexpr bool COMMUTATIVE = MonoidBase::COMMUTATIVE;
	using value_type = typename std::pair<int, MonoidBase>;
	using T = value_type;
	using T_Base = typename MonoidBase::value_type;
	T a;
	constexpr CntMonoid &operator+=(const CntMonoid &b) {
		a.first += T(b).first;
		a.second += T(b).second;
		return *this;
	}
	constexpr CntMonoid() : a(0, MonoidBase()) {}
	constexpr CntMonoid(T _a) : a(_a) {}
	constexpr CntMonoid(T_Base _a) : a(1, _a) {}
	constexpr CntMonoid operator+(const CntMonoid &b) const { return CntMonoid(*this) += b; }
	constexpr operator T() const { return a; }
	constexpr operator T_Base() const { return T_Base(a.second); }
	constexpr bool operator==(const CntMonoid &b) const { return CntMonoid(*this).a == b.a; }
	constexpr bool operator!=(const CntMonoid &b) const { return CntMonoid(*this).a != b.a; }
};

} // namespace Monoid

namespace ActedMonoid {

using namespace Monoid;

template <typename Derived, typename Base>
struct CRTP : Base {
	using Base::Base;
	constexpr Derived& operator+=(const Derived& b) { Base::operator+=(b); return static_cast<Derived&>(*this); };
	constexpr Derived operator+(const Derived& b) const { Derived r = static_cast<const Derived&>(*this); return r += b; }
	constexpr Derived operator^(const Derived& b) const { Derived r = static_cast<const Derived&>(*this); return r ^= b; }
	constexpr bool operator==(const Derived &b) const { return static_cast<const Derived&>(*this).a == b.a; }
	constexpr bool operator!=(const Derived &b) const { return static_cast<const Derived&>(*this).a != b.a; }
};

template <typename T, T MINF>
struct Add_Max : CRTP<Add_Max<T, MINF>, Max<T, MINF>> {
	using Base = CRTP<Add_Max<T, MINF>, Max<T, MINF>>;
	using Base::Base;
	using ActingMonoid = Plus<T>;
	constexpr Add_Max<T, MINF> &operator^=(const ActingMonoid &b) {
		this->a += T(b);
		return *this;
	}
};

template <typename T, T INF>
struct Add_Min : CRTP<Add_Min<T, INF>, Min<T, INF>> {
	using Base = CRTP<Add_Min<T, INF>, Min<T, INF>>;
	using Base::Base;
	using ActingMonoid = Plus<T>;
	constexpr Add_Min<T, INF> &operator^=(const ActingMonoid &b) {
		this->a += T(b);
		return *this;
	}
};

template <typename T>
struct Add_Sum : CRTP<Add_Sum<T>, CntMonoid<Plus<T>>> {
	using Base = CRTP<Add_Sum<T>, CntMonoid<Plus<T>>>;
	using Base::Base;
	using ActingMonoid = Plus<T>;
	constexpr Add_Sum<T> &operator^=(const ActingMonoid &b) {
		(this->a).second += T(b) * (this->a).first;
		return *this;
	}
};

template <typename T, T MINF>
struct Update_Max : CRTP<Update_Max<T, MINF>, Max<T, MINF>> {
	using Base = CRTP<Update_Max<T, MINF>, Max<T, MINF>>;
	using Base::Base;
	using ActingMonoid = Update<T, MINF>;
	constexpr Update_Max<T, MINF> &operator^=(const ActingMonoid &b) {
		if (T(b) != MINF) this->a = T(b);
		return *this;
	}
};

template <typename T, T INF>
struct Update_Min : CRTP<Update_Min<T, INF>, Min<T, INF>> {
	using Base = CRTP<Update_Min<T, INF>, Min<T, INF>>;
	using Base::Base;
	using ActingMonoid = Update<T, INF>;
	constexpr Update_Min<T, INF> &operator^=(const ActingMonoid &b) {
		if (T(b) != INF) this->a = T(b);
		return *this;
	}
};

template <typename T, T UNUSED_VALUE>
struct Update_Sum : CRTP<Update_Sum<T, UNUSED_VALUE>, CntMonoid<Plus<T>>> {
	using Base = CRTP<Update_Sum<T, UNUSED_VALUE>, CntMonoid<Plus<T>>>;
	using Base::Base;
	using ActingMonoid = Update<T, UNUSED_VALUE>;
	constexpr Update_Sum<T, UNUSED_VALUE> &operator^=(const ActingMonoid &b) {
		if (T(b) != UNUSED_VALUE) (this->a).second = T(b) * (this->a).first;
		return *this;
	}
};

} // namespace ActedMonoid
// End include: "../monoid/basic.hpp"
// Begin include: "lazy-segment-tree.hpp"

template <typename AM>
struct LazySegmentTree {
	using S = AM;
	using F = typename AM::ActingMonoid;
	int N, LOG, M;
	std::vector<S> dat; // このライブラリはlaz反映済式
	std::vector<F> laz;

	LazySegmentTree() {}
	LazySegmentTree(int N) { build(N); }
	template <typename I>
	LazySegmentTree(int N, I init) { build(N, init); }
	template <typename U>
	LazySegmentTree(const std::vector<U>& v) { build(v); }

	void set(int p, S x) {
		assert(0 <= p && p < N);
		p += M;
		for (int i = LOG; i >= 1; i--) push(p >> i);
		dat[p] = x;
		for (int i = 1; i <= LOG; i++) update(p >> i);
	}
	void multiply(int p, const S& x) {
		assert(0 <= p && p < N);
		p += M;
		for (int i = LOG; i >= 1; i--) push(p >> i);
		dat[p] += x;
		for (int i = 1; i <= LOG; i++) update(p >> i);
	}

	S get(int p) {
		assert(0 <= p && p < N);
		p += M;
		for (int i = LOG; i >= 1; i--) push(p >> i);
		return dat[p];
	}
	std::vector<S> get() {
		for (int k = 1; k < M; k++) push(k);
		return {dat.begin() + M, dat.begin() + M + N};
	}
	S operator[](const int &k) { return get(k); }

	S prod(int l, int r) {
		assert(0 <= l && l <= r && r <= N);
		if (l == r) return S();
		l += M, r += M;
		for (int i = LOG; i >= 1; i--) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push((r - 1) >> i);
		}
		S xl, xr;
		while (l < r) {
			if (l & 1) xl = xl + dat[l++];
			if (r & 1) xr = dat[--r] + xr;
			l >>= 1, r >>= 1;
		}
		return xl + xr;
	}
	S prod() { return dat[1]; }
	inline S operator()(int l, int r) { return prod(l, r); }

	void apply(int l, int r, F f) {
		assert(0 <= l && l <= r && r <= N);
		if (l == r) return;
		l += M, r += M;
		for (int i = LOG; i >= 1; i--) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push((r - 1) >> i);
		}
		int l2 = l, r2 = r;
		while (l < r) {
			if (l & 1) apply_at(l++, f);
			if (r & 1) apply_at(--r, f);
			l >>= 1, r >>= 1;
		}
		l = l2, r = r2;
		for (int i = 1; i <= LOG; i++) {
			if (((l >> i) << i) != l) update(l >> i);
			if (((r >> i) << i) != r) update((r - 1) >> i);
		}
	}

	template <typename G>
	int max_right(int l, const G check) {
		assert(0 <= l && l <= N);
		assert(check(S()));
		if (l == N) return N;
		l += M;
		for (int i = LOG; i >= 1; i--) push(l >> i);
		S sm;
		do {
			while (l % 2 == 0) l >>= 1;
			if (!check(sm + dat[l])) {
				while (l < M) {
					push(l);
					l = (2 * l);
					if (check(sm + dat[l])) sm += dat[l++];
				}
				return l - M;
			}
			sm += dat[l++];
		} while ((l & -l) != l);
		return N;
	}

	template <typename G>
	int min_left(int r, const G check) {
		assert(0 <= r && r <= N);
		assert(check(S()));
		if (r == 0) return 0;
		r += M;
		for (int i = LOG; i >= 1; i--) push((r - 1) >> i);
		S sm;
		do {
			r--;
			while (r > 1 && (r % 2)) r >>= 1;
			if (!check(dat[r] + sm)) {
				while (r < M) {
					push(r);
					r = (2 * r + 1);
					if (check(dat[r] + sm)) sm = dat[r--] + sm;
				}
				return r + 1 - M;
			}
			sm = dat[r] + sm;
		} while ((r & -r) != r);
		return 0;
	}

	private:
	void update(int k) { dat[k] = dat[k * 2] + dat[k * 2 + 1]; }
	void apply_at(int k, F f) {
		dat[k] ^= f;
		if (k < M) laz[k] += f;
	}
	void push(int k) {
		if (laz[k] == F()) return;
		apply_at(2 * k, laz[k]), apply_at(2 * k + 1, laz[k]);
		laz[k] = F();
	}

	void build(int _N) { build(_N, [](int i) -> S { return S(); }); }
	template <typename U>
	void build(const std::vector<U>& v) { build(v.size(), [&](int i) -> S { return S(v[i]); }); }
	template <typename I>
	void build(int _N, I init) {
		N = _N, LOG = 1;
		while ((1 << LOG) < N) ++LOG;
		M = 1 << LOG;
		dat.assign(M << 1, S());
		laz.assign(M, F());
		for (int i = 0; i < N; i++) dat[M + i] = init(i);
		for (int i = M - 1; i >= 1; i--) update(i);
	}
};
// End include: "lazy-segment-tree.hpp"

template <typename T, T MINF>
using AddMax_LazySegmentTree = LazySegmentTree<ActedMonoid::Add_Max<T, MINF>>;
template <typename T, T INF>
using AddMin_LazySegmentTree = LazySegmentTree<ActedMonoid::Add_Min<T, INF>>;
template <typename T>
using AddSum_LazySegmentTree = LazySegmentTree<ActedMonoid::Add_Sum<T>>;
template <typename T, T MINF>
using UpdateMax_LazySegmentTree = LazySegmentTree<ActedMonoid::Update_Max<T, MINF>>;
template <typename T, T INF>
using UpdateMin_LazySegmentTree = LazySegmentTree<ActedMonoid::Update_Min<T, INF>>;
template <typename T, T UNUSED_VALUE>
using UpdateSum_LazySegmentTree = LazySegmentTree<ActedMonoid::Update_Sum<T, UNUSED_VALUE>>;

// End include: "../../segment-tree/lazy-segment-tree-utility.hpp"
// Begin include: "../../string/suffix-array.hpp"

// Begin include: "../data-structure/sparse-table.hpp"

#include <cassert>
#include <limits>
#include <vector>
using namespace std;

template <typename T>
struct SparseTableMin {
	inline static constexpr T INF = numeric_limits<T>::max() / 2;
	int N;
	vector<vector<T> > table;
	T f(T a, T b) { return min(a, b); }
	SparseTableMin() {}
	SparseTableMin(const vector<T> &v) : N(v.size()) {
		int b = 1;
		while ((1 << b) <= N) ++b;
		table.push_back(v);
		for (int i = 1; i < b; i++) {
			table.push_back(vector<T>(N, INF));
			for (int j = 0; j + (1 << i) <= N; j++) {
				table[i][j] = f(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	// [l, r)
	T query(int l, int r) {
		assert(0 <= l and l <= r and r <= N);
		if (l == r) return INF;
		int b = 31 - __builtin_clz(r - l);
		return f(table[b][l], table[b][r - (1 << b)]);
	}
};

template <typename T>
struct SparseTableMax {
	inline static constexpr T MINF = numeric_limits<T>::min() / 2;
	int N;
	vector<vector<T> > table;
	T f(T a, T b) { return max(a, b); }
	SparseTableMax() {}
	SparseTableMax(const vector<T> &v) : N(v.size()) {
		int b = 1;
		while ((1 << b) <= N) ++b;
		table.push_back(v);
		for (int i = 1; i < b; i++) {
			table.push_back(vector<T>(N, MINF));
			for (int j = 0; j + (1 << i) <= N; j++) {
				table[i][j] = f(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	// [l, r)
	T query(int l, int r) {
		assert(0 <= l and l <= r and r <= N);
		if (l == r) return MINF;
		int b = 31 - __builtin_clz(r - l);
		return f(table[b][l], table[b][r - (1 << b)]);
	}
};

template <typename T>
using SparseTable = SparseTableMin<T>;
// End include: "../data-structure/sparse-table.hpp"

// remind: SA including empty string
// verify https://judge.yosupo.jp/submission/240
struct SuffixArray {
	int _size;
	vector<int> sa;
	string &s;
	SuffixArray(string &s) : _size(s.size()), s(s) {
		s.push_back(0);
		sa.resize(s.size());
		iota(begin(sa), end(sa), 0);
		sort(begin(sa), end(sa), [&](int a, int b) { return s[a] == s[b] ? a > b : s[a] < s[b]; });
		vector<int> classes(s.size());
		vector<int> c(s.begin(), s.end());
		vector<int> cnt(s.size());

		for (int len = 1; len < (int)s.size(); len <<= 1) {
			for (int i = 0; i < (int)s.size(); i++) {
				if (i > 0 && c[sa[i - 1]] == c[sa[i]] &&
				    sa[i - 1] + len < (int)s.size() &&
				    c[sa[i - 1] + len / 2] == c[sa[i] + len / 2]) {
					classes[sa[i]] = classes[sa[i - 1]];
				}
				else classes[sa[i]] = i;
			}
			iota(begin(cnt), end(cnt), 0);
			copy(begin(sa), end(sa), begin(c));
			for (int i = 0; i < (int)s.size(); i++) {
				int s1 = c[i] - len;
				if (s1 >= 0) sa[cnt[classes[s1]]++] = s1;
			}
			classes.swap(c);
		}
		s.pop_back();
	}

	void output() {
		cout << "SA\tidx\tstr" << endl;
		for (int i = 0; i < size(); i++) {
			cout << i << ": \t" << sa[i] << " \t";
			if (sa[i] != _size)
				cout << s.substr(sa[i], _size - sa[i]) << endl;
			else
				cout << "$" << endl;
		}
		cout << endl;
	}

	int size() const { return _size + 1; }
	int operator[](int k) const { return sa[k]; }
};

struct LCPArray {
	const SuffixArray &SA;
	vector<int> LCP, rank;
	LCPArray(const SuffixArray &sa) : SA(sa) {
		LCP.resize(SA.size());
		rank.resize(SA.size());
		for (int i = 0; i < SA.size(); i++) {
			rank[SA[i]] = i;
		}
		LCP[0] = 0;

		for (int i = 0, h = 0; i < SA.size() - 1; i++) {
			int j = SA[rank[i] - 1];
			h ? h-- : h;
			while ((i > j ? i : j) + h < SA.size() - 1 &&
					SA.s[i + h] == SA.s[j + h] && ++h)
				;
			LCP[rank[i] - 1] = h;
		}
	}

	void output() {
		cout << "SA\tidx\tLCP\tstr" << endl;
		for (int i = 0; i < SA.size(); i++) {
			cout << i << "\t" << SA[i] << " \t" << LCP[i] << "\t";
			if (SA[i] == SA.size() - 1)
				cout << "$";
			else
				cout << SA.s.substr(SA[i], SA.size() - 1 - SA[i]);
			cout << endl;
		}
	}
};

// verify
// https://onlinejudge.u-aizu.ac.jp/status/users/NyaanNyaan/submissions/1/ALDS1_14_D/judge/3874273/C++14
// https://atcoder.jp/contests/abc135/submissions/7574225
// https://judge.yosupo.jp/submission/241
// https://atcoder.jp/contests/abc141/submissions/7577295
struct StringSearch {
	string &s;
	const SuffixArray &sa;
	const LCPArray &lcp;
	SparseTable<int> sparse;
	StringSearch(LCPArray &lcp)
		: s(lcp.SA.s), sa(lcp.SA), lcp(lcp), sparse(lcp.LCP) {}

	pair<int, int> comp(const string &t, int len, int si, int ti = 0) {
		int sn = (int)s.size(), tn = (int)t.size();
		si += len, ti += len;
		while (si < sn && ti < tn) {
			if (s[si] != t[ti]) return make_pair(s[si] < t[ti], ti);
			si++, ti++;
		}
		return make_pair((si >= sn && ti < tn), ti);
	}

	pair<int, int> find_range(int left, int med, int right, int len) {
		{
			int ng = left - 1, ok = med;
			while (ng + 1 < ok) {
				int cur = (ng + ok) / 2;
				if (sparse.query(cur, med) >= len)
					ok = cur;
				else
					ng = cur;
			}
			left = ok;
		}
		{
			int ok = med, ng = right + 1;
			while (ok + 1 < ng) {
				int cur = (ng + ok) / 2;
				if (sparse.query(med, cur) >= len)
					ok = cur;
				else
					ng = cur;
			}
			right = ok;
		}
		return make_pair(left, right);
	}

	public:
	// Longest Common Prefix between S[i , N) and S[j , N)
	int ArbitaryLCP(int i, int j) {
		if (i == j) return (int)(s.size()) - i;
		return sparse.query(min(lcp.rank[i], lcp.rank[j]),
				max(lcp.rank[i], lcp.rank[j]));
	}

	// String Search  O(|T| + log |S|)
	// return : [l, r], l and r are indices of Suffix Array
	// if T doesn't exist, return (-1, -1)
	pair<int, int> find(string &t) {
		int left = 1, right = sa.size() - 1, med = left;
		int leftlen = 0, rightlen = 0, tlen = t.size();
		pair<int, int> ret;
		while (left + 1 < right) {
			med = (left + right) / 2;
			int corres_len = max(min(leftlen, sparse.query(left, med)),
					min(rightlen, sparse.query(med, right)));
			if (corres_len < max(leftlen, rightlen)) {
				if (leftlen < rightlen)
					left = med, leftlen = corres_len;
				else
					right = med, rightlen = corres_len;
				continue;
			}
			ret = comp(t, corres_len, sa[med]);
			if (ret.second == tlen) return find_range(left, med, right, tlen);
			if (ret.first == 0)
				right = med, rightlen = ret.second;
			else
				left = med, leftlen = ret.second;
		}
		if (sa.size() <= 3) {
			if (comp(t, 0, sa[left]).second == tlen)
				return find_range(left, left, right, tlen);
			if (comp(t, 0, sa[right]).second == tlen)
				return find_range(left, right, right, tlen);
			return make_pair(-1, -1);
		}
		med = left + right - med;
		ret = comp(t, min(leftlen, rightlen), sa[med]);
		if (ret.second == tlen) return find_range(left, med, right, tlen);
		return make_pair(-1, -1);
	}
};

// first: Suffix Array
// second: LCPArray
pair<vector<pair<int, int>>, vector<int>> Strings (vector<string> &S) {
	int N = S.size();
	string all;
	vector<int> st(N);
	for (int i = 0; i < N; i++) {
		st[i] = all.size();
		all += S[i] + "$";
	}
	SuffixArray sa_all(all);
	vector<int> lcp = LCPArray(sa_all).LCP;
	lcp.erase(lcp.begin(), lcp.begin() + N + 1);
	vector<pair<int, int>> sa(sa_all.size() - N - 1);

	for (int si = 0; si < (int)sa.size(); si++){
		int pos = sa_all[si + N + 1];
		int i = upper_bound(st.begin(), st.end(), pos) - st.begin() - 1;
		int j = pos - st[i];
		sa[si] = make_pair(i, j);
		lcp[si] = min(lcp[si], (int)S[i].size() - j);
	}

	return make_pair(sa, lcp);
}

// End include: "../../string/suffix-array.hpp"
using namespace yamada;
constexpr int K=26;

V<int> getF(string &S){
	int N=S.size();
	string T="naist"; each(c,T)c-='a';
	int M=T.size();

	vv(int,npos,M,N,inf);
	rep(i,N)rep(k,M)if(S[i]==T[k]){
		npos[k][i]=i;
	}
	rep(k,M)repr(i,N-1)if(npos[k][i]==inf){
		npos[k][i]=npos[k][i+1];
	}

	V<int> ans(N,inf);
	rep(i,N){
		int L=i;
		rep(k,M){
			L=npos[k][L];
			if(L==inf)break;
		}
		if(L<inf)ans[i]=L-i+1;
	}
	return ans;
}


void yamada::solve()
{
	ins(S);
	each(c,S)c-='a';
	int N=S.size();
	auto F=getF(S);

	SuffixArray sa(S);
	return;

	auto lcp=LCPArray(sa).LCP;
	V<int> len(sa.size());
	rep(i,len.size()){
		len[i]=N-sa[i];
	}

	int M = lcp.size();
	AddMin_LazySegmentTree<int,inf> seg(lcp);
	ll ans=0;

	V<tuple<int,int,int>> q; // [L,R,dep]
	q.reserve(1<<20);
	q.eb(0,M,0);
	// Suffix Array 内の番号 [L, R) 内のLCPがdep
	while(!q.empty()){
		auto[L,R,dep]=q.back(); q.pop_back();
		if(R-L==1)continue;
		for (int l = L, r = L; l < R; l = r){
			r = seg.max_right(l,[&](int mn){ return mn > dep; }) + 1;
			int ndep = (l + 1 == r? len[l] : seg.prod(l, r - 1).a);
			if (ndep > dep){
				if(inLR<int>(0LL,sa[l],N)){
					int border=F[sa[l]];
					if(border<=ndep){
						int bns=ndep-max<int>(dep,border-1);
						ans+=bns;
					}
				}
				q.eb(l,r,ndep);
			}
		}
	}
	out(ans);
}
