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
// Begin include: "../../monoid/make-monoid.hpp"

template <typename T, T (*op)(T, T), T (*ti)(), bool COMMUTATIVE = 0>
struct MyMono {
	using value_type = T;
	T a;
	constexpr MyMono &operator+=(const MyMono &b) { a = op(a, b); return *this; }
	constexpr MyMono operator+(const MyMono &b) const { return op(a, b); }
	constexpr bool operator==(const MyMono &b) const { return (*this).a == b.a; }
	constexpr bool operator!=(const MyMono &b) const { return (*this).a != b.a; }
	constexpr MyMono() : a(ti()) {}
	constexpr MyMono(T _a) : a(_a) {}
	constexpr operator T() const { return a; }
};

// h(f, g)(x) : g(f(x))
template <typename T, typename E, T (*f)(T, T), T (*g)(T, E), E (*h)(E, E),
          T (*ti)(), E (*ei)(), bool S_COMMUTATIVE = 0, bool F_COMMUTATIVE = 0>
struct MyAM : MyMono<T, f, ti, S_COMMUTATIVE> {
	using Base = MyMono<T, f, ti, S_COMMUTATIVE>;
	using Base::Base;
	using ActingMonoid = MyMono<E, h, ei, F_COMMUTATIVE>;
	constexpr MyAM &operator+=(const MyAM &b) { (*this).a = f(MyAM(*this), b); return *this; }
	constexpr MyAM operator+(const MyAM &b) const { return f(MyAM(*this), b); }
	constexpr MyAM &operator^=(const ActingMonoid &b) { (*this).a = g((*this).a, b); return *this; }
	constexpr MyAM operator^(const ActingMonoid &b) const { return g(MyAM(*this), b); }
	constexpr bool operator==(const MyAM &b) const { return (*this).a == b.a; }
	constexpr bool operator!=(const MyAM &b) const { return (*this).a != b.a; }
};
// End include: "../../monoid/make-monoid.hpp"
using namespace yamada;

// [左端通る、右端通る、全部通る、全部通らない、答え
using T=tuple<ll,ll,ll,ll,ll>;
T ti(){return{-infLL,-infLL,-infLL,-infLL,-infLL};};
T F(T x,T y){
	if(y==ti())return x;
	if(x==ti())return y;
	auto[lans,rans,aans,nans,ans]=x;
	auto[lbns,rbns,abns,nbns,bns]=y;

	ll lcns=lans+nbns;
	amin(lcns,aans+lbns);

	ll rcns=nans+rbns;
	amin(rcns,rans+abns);

	ll acns=aans+abns;
	ll ncns=nans+nbns;
	ll cns=infLL;
	amin(cns,ans+nbns);
	amin(cns,nans+bns);
	amin(cns,rans+lbns);
	amin(cns,lcns);
	amin(cns,rcns);
	amin(cns,acns);
	amin(cns,ncns);
	return{lcns,rcns,acns,ncns,cns};
}

T getT(ll a){
	if(a==0)return{1,1,1,0,0};
	return{0,0,0,a,0};
}

void yamada::solve()
{
	inl(N,Q);
	vl A(N); in(A);
	V<T> init;
	each(a,A)init.eb(getT(a));

	SegmentTree<MyMono<T,F,ti>> seg(init);

	while(Q--){
		inl(i,a); --i;
		seg.set(i,getT(a));
		ll ans=get<4>(seg.prod().a);
		out(ans);
	}
}