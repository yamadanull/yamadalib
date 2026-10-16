/**
 * date    : 2026-10-15 22:41:39
 * author  : yamadanull
 * library : https://github.com/yamadanull/yamadalib/
 */

// ===== BEGIN INCLUDE: ../../monoid/minidx.hpp =====

#include <utility>
#include <limits>

namespace MONOID {

template <typename E, E INF = std::numeric_limits<E>::max(), bool tie_is_left = true>
struct MinIdx {
	using value_type = std::pair<E, int>;
	static constexpr bool is_small(const value_type& x, const value_type& y) {
		if (x.first < y.first) return true;
		if (x.first > y.first) return false;
		return !tie_is_left xor x.second < y.second;
	}
	static constexpr value_type O(const value_type& x, const value_type& y) {
		return is_small(x, y) ? x : y;
	}
	static constexpr value_type I() { return {INF, -1}; }
	static constexpr bool COMMUTATIVE = true;
};

} // namespace monoid
// ===== END INCLUDE: ../../monoid/minidx.hpp =====
// ===== BEGIN INCLUDE: ../../segment-tree/segment-tree.hpp =====
#include <algorithm>
#include <cassert>
#include <vector>

template <typename Monoid>
struct SegmentTree {
	using X = typename Monoid::value_type;
	std::vector<X> dat;
	int N, LOG, size;

	SegmentTree() {}
	SegmentTree(int N) { build(N); }
	template <typename F>
	SegmentTree(int N, F init) { build(N, init); }
	template <std::ranges::input_range R>
	SegmentTree(const R& v) { build(v); }

	void build(int m) {
		build(m, [](int i) -> X { return Monoid::I(); });
	}
	template <std::ranges::input_range R>
	void build(const R& v) {
		build(v.size(), [&](int i) -> X { return v[i]; });
	}
	template <typename F>
	void build(int m, F init) {
		N = m, LOG = 1;
		while ((1 << LOG) < N) ++LOG;
		size = 1 << LOG;
		dat.assign(size << 1, Monoid::I());
		for (int i = 0; i < N; i++) dat[size + i] = init(i);
		for (int i = size - 1; i >= 1; i--) update(i);
	}

	X get(int i) const { return dat[size + i]; }
	std::vector<X> get() const { return {dat.begin() + size, dat.begin() + size + N}; }

	void update(int i) { dat[i] = Monoid::O(dat[2 * i], dat[2 * i + 1]); }
	void set(int i, const X x) {
		assert(i < N);
		dat[i += size] = x;
		while (i >>= 1) update(i);
	}

	void multiply(int i, const X x) {
		assert(i < N);
		i += size;
		dat[i] = Monoid::O(dat[i], x);
		while (i >>= 1) update(i);
	}

	X prod(int L, int R) const {
		assert(0 <= L && L <= R && R <= N);
		X vl = Monoid::I(), vr = Monoid::I();
		L += size, R += size;
		while (L < R) {
			if (L & 1) vl = Monoid::O(vl, dat[L++]);
			if (R & 1) vr = Monoid::O(dat[--R], vr);
			L >>= 1, R >>= 1;
		}
		return Monoid::O(vl, vr);
	}

	std::vector<int> prod_ids(int L, int R) const {
		assert(0 <= L && L <= R && R <= N);
		std::vector<int> I, J;
		L += size, R += size;
		while (L < R) {
			if (L & 1) I.emplace_back(L++);
			if (R & 1) J.emplace_back(--R);
			L >>= 1, R >>= 1;
		}
		std::ranges::reverse(J);
		I.resize(I.size() + J.size());
		for (int j = 0; j < (int)J.size(); j++) I[(int)I.size() - (int)J.size() + j] = J[j];
		return I;
	}

	X prod() const { return dat[1]; }
	template <typename... Args>
	X operator()(Args... args) { return prod(args...); }
	template <typename... Args>
	X operator[](Args... args) { return get(args...); }

	template <typename F>
	int max_right(int L, F check) const {
		assert(0 <= L && L <= N && check(Monoid::I()));
		if (L == N) return N;
		L += size;
		X sm = Monoid::I();
		do {
			while (L % 2 == 0) L >>= 1;
			if (!check(Monoid::O(sm, dat[L]))) {
				while (L < size) {
					L = 2 * L;
					if (check(Monoid::O(sm, dat[L]))) {
						sm = Monoid::O(sm, dat[L++]);
					}
				}
				return L - size;
			}
			sm = Monoid::O(sm, dat[L++]);
		} while ((L & -L) != L);
		return N;
	}

	template <typename F>
	int min_left(int R, F check) const {
		assert(0 <= R && R <= N && check(Monoid::I()));
		if (R == 0) return 0;
		R += size;
		X sm = Monoid::I();
		do {
			--R;
			while (R > 1 && (R % 2)) R >>= 1;
			if (!check(Monoid::O(dat[R], sm))) {
				while (R < size) {
					R = 2 * R + 1;
					if (check(Monoid::O(dat[R], sm))) {
						sm = Monoid::O(dat[R--], sm);
					}
				}
				return R + 1 - size;
			}
			sm = Monoid::O(dat[R], sm);
		} while ((R & -R) != R);
		return 0;
	}

	// prod_{l<=i<r} A[i xor x]
	X xor_prod(int l, int r, int xor_val) const {
		static_assert(Monoid::COMMUTATIVE);
		X x = Monoid::I();
		for (int k = 0; k < LOG + 1; ++k) {
			if (l >= r) break;
			if (l & 1) {
				x = Monoid::O(x, dat[(size >> k) + ((l++) ^ xor_val)]);
			}
			if (r & 1) {
				x = Monoid::O(x, dat[(size >> k) + ((--r) ^ xor_val)]);
			}
			l /= 2, r /= 2, xor_val /= 2;
		}
		return x;
	}
};
// ===== END INCLUDE: ../../segment-tree/segment-tree.hpp =====
// ===== BEGIN INCLUDE: ../../template/template.hpp =====

#include <bits/stdc++.h>
using namespace std;

// ===== BEGIN INCLUDE: util.hpp =====
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
using vvc = vector<vector<T>>;
template <typename T>
using vvvc = vector<vector<vector<T>>>;
template <typename T>
using vvvvc = vector<vector<vector<vector<T>>>>;
using vint = vector<int>;
using vl = vector<long long>;
using vd = vector<double>;
using vs = vector<string>;
using vvl = vector<vector<long long>>;
using vvvl = vector<vector<vector<long long>>>;
using vvvvl = vector<vector<vector<vector<long long>>>>;
template <typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxpq = priority_queue<T, vector<T>, less<T>>;

using pint = pair<int, int>;
using pl = pair<ll, ll>;
using vp = vc<pl>;
using vvp = vvc<pl>;

template <typename T>
int len(const T &t) { return t.size(); }

constexpr int inf = 1001001001;
constexpr long long infLL = 4004004004004004004LL;

template <typename T, typename U>
inline bool amin(T &x, U y) { return (y < x) ? (x = y, true) : false; }
template <typename T, typename U>
inline bool amax(T &x, U y) { return (x < y) ? (x = y, true) : false; }

template <typename T, typename U>
pair<T, U> mkp(const T &t, const U &u) { return make_pair(t, u); }
template <typename... Args>
tuple<Args...> mkt(const Args&... args) { return make_tuple(args...); }

template <ranges::input_range R>
ranges::range_value_t<R> Sum(const R &v) { return ranges::fold_left(v, ranges::range_value_t<R>(0), plus()); }

template <typename T>
int lb(const vector<T> &v, const T &a) { return ranges::lower_bound(v, a) - v.begin(); }
template <typename T>
int ub(const vector<T> &v, const T &a) { return ranges::upper_bound(v, a) - v.begin(); }

constexpr long long TEN(int n) {
	long long ret = 1, x = 10;
	for (; n; x *= x, n >>= 1) ret *= (n & 1 ? x : 1);
	return ret;
}

template <typename T>
vector<T> mkrui(const vector<T> &v, const bool rev = false) {
	vector<T> ret(v.size() + 1);
	if (rev) {
		for (int i = (int)v.size() - 1; i >= 0; i--) ret[i] = v[i] + ret[i + 1];
	} else {
		for (int i = 0; i < (int)v.size(); i++) ret[i + 1] = ret[i] + v[i];
	}
	return ret;
};

template <typename T>
vector<T> mkuni(const vector<T> &v) {
	vector<T> ret(v);
	ranges::sort(ret);
	ret.erase(ranges::unique(ret).begin(), ret.end());
	return ret;
}

template <typename F>
vector<int> mkord(int N, const F &f) {
	vector<int> ord = views::iota(0, N) | ranges::to<vector>();
	ranges::sort(ord, f);
	return ord;
}

template <typename T>
vector<int> mkinv(const vector<T> &v) {
	vector<int> inv(ranges::max(v) + 1, -1);
	for (int i = 0; i < (int)v.size(); i++) inv[v[i]] = i;
	return inv;
}

vector<int> mkiota(int N) { return views::iota(0, N) | ranges::to<vector>(); }

vector<int> p_mrg(const vector<int> &f, const vector<int> &g) { // g o f
	return f | views::transform([&](auto a) { return g[a]; }) | ranges::to<vector>();
}

template <typename T> // f: old_idx -> new_idx
vector<T> p_shf(const vector<T>& A, const vector<int>& f, const bool inv = false) {
	int n = A.size();
	vector<T> ret(n);
	if (!inv) for (int i = 0; i < n; i++) ret[f[i]] = A[i];
	else for (int i = 0; i < n; i++) ret[i] = A[f[i]];
	return ret;
}

template <typename T>
T mkrev(const T &v) { return v | views::reverse | ranges::to<vector>(); }

template <typename C>
bool nxp(C &v) { return ranges::next_permutation(v).found; }
template <typename F>
void nxp(int N, F f) {
	auto a = views::iota(0, N) | ranges::to<vector>();
	do { f(a); } while (nxp(a));
}

// i 要素目 : [0, A[i])
template <typename F>
void Product(const vector<int> &A, const F& f) {
	vector<int> cur;
	[&](this auto dfs, int i) -> void {
		if (i == (int)A.size()) { f(cur); return; }
		for (int j = 0; j < A[i]; j++) cur.emplace_back(j), dfs(i + 1), cur.pop_back();
	}(0);
}
// i 要素目 : [0, M)
template <typename F>
void Product(const int N, const int M, const F& f) { vector<int> A(N, M); Product(A, f); }

template <typename T, typename U>
vector<U> Digit(T a, const U &x, int siz = -1) {
	vector<U> ret;
	while (a > 0) {
		ret.emplace_back(a % x);
		a /= x;
	}
	if (siz >= 0) ret.resize(siz);
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
vector<T> Transpose(const vector<T> &A) {
	if (A.empty()) return {};
	return views::iota(0, (int)A[0].size()) | views::transform([&](auto j) {
		return A | views::transform([&](auto&& a) { return a[j]; }) | ranges::to<T>();
	}) | ranges::to<vector<T>>();
}

template <typename T>
vector<T> RotateGrid(const vector<T> &A) {
	if (A.empty()) return {};
	return views::iota(0, (int)A[0].size()) | views::transform([&](auto j) {
		return A | views::transform([&](auto&& a) { return a[j]; }) | ranges::to<T>();
	}) | views::reverse | ranges::to<vector<T>>();
}

template <typename T, typename F>
T bisect(T ok, T ng, F f) { // ok < ng でも ok > ng でも可能 // f(ok) && !f(ng) が必要
	while (abs(ok - ng) > 1) { T mid = (ok + ng) / 2; (f(mid) ? ok : ng) = mid; } 
	return ok;
}

template <typename T, typename F>
T bisect(F f) { // 思考停止用 // 判定回数は上限を決め打ちした場合の高々２倍程度
	T ok = 0, ng = 1;
	while (f(ng)) ng *= 2;
	while (ng - ok > 1) { T mid = ok + (ng - ok) / 2; (f(mid) ? ok : ng) = mid; } 
	return ok;
}

template <typename T, typename F>
T bisect_double(T ok, T ng, F f, int iter = 100) {
	if (ok == ng) return ok;
	while (iter--) { T mid = (ok + ng) / 2; (f(mid) ? ok : ng) = mid; } 
	return ng;
}

template <typename T0, typename T1, typename T2>
bool inLR(T0 L, T1 x, T2 R){ return L <= x && x < R; }
bool YESNO(bool b) { cout << (b ? "YES\n" : "NO\n"); return b; }
bool YesNo(bool b) { cout << (b ? "Yes\n" : "No\n"); return b; }
bool yesno(bool b) { cout << (b ? "yes\n" : "no\n"); return b; }

long long Isqrt(long long n) {
	if (n <= 0) return 0;
	long long x = sqrt(n);
	while ((x + 1) * (x + 1) <= n) x++;
	while (x * x > n) x--;
	return x;
}

template <typename T>
struct CumulativeSum {
	vector<T> S;
	CumulativeSum(vector<T> &A) : S(A.size() + 1) {
		for (int i = 0; i < (int)A.size(); i++) S[i + 1] = S[i] + A[i];
	}
	T query(int l, int r) { return (l <= r ? S[r] - S[l] : T(0)); }
	T query() { return S.back(); }
	inline T operator()(int l, int r) { return query(l, r); }
	inline T operator()() { return query(); }
};

// 速度よりオーバーフロー対策優先
template <typename T>
T floor(T a, T b) { assert(b); if (b < 0) a = -a, b = -b; return a / b - (a % b < 0); }
template <typename T>
T under(T a, T b) { assert(b); if (b < 0) a = -a, b = -b; return a / b - (a % b <= 0); }
template <typename T>
T ceil (T a, T b) { assert(b); if (b < 0) a = -a, b = -b; return a / b + (a % b > 0); }
template <typename T>
T over (T a, T b) { assert(b); if (b < 0) a = -a, b = -b; return a / b + (a % b >= 0); }
template <typename T>
T modulo(T a, T b) { assert(b > 0); T c = a % b; return c < 0 ? c + b : c; }

template <typename T>
pair<T, T> divmod(T a, T b) {
	assert(b > 0);
	T q = a / b, r = a % b;
	if (r < 0) --q, r += b;
	return {q, r};
}

template <typename mint, int iter = 1000>
string tof(const mint &a) {
	for (int deno = 1; deno <= iter; deno++) {
		mint inv = ((mint)deno).inverse();
		for (int nume = 0; nume <= iter; nume++) {
			mint val = inv * nume;
			if (val == a) {
				if (deno == 1) return to_string(nume);
				return to_string(nume) + "/" + to_string(deno);
			}
			else if (-val == a) {
				if (deno == 1) return to_string(-nume);
				return to_string(-nume) + "/" + to_string(deno);
			}
		}
	}
	return "!NF"; // Not Found
}

template <typename mint>
constexpr auto Tof = views::transform(tof<mint, 1000>);

} // namespace yamada
// ===== END INCLUDE: util.hpp =====
// ===== BEGIN INCLUDE: bitop.hpp =====
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

string tog(int msk, int N) {
	return views::iota(0, N) | views::transform([&](auto i) {
		return msk >> i & 1 ? '#' : '.';
	}) | ranges::to<string>();
}
}  // namespace yamada
// ===== END INCLUDE: bitop.hpp =====
// ===== BEGIN INCLUDE: io.hpp =====
namespace yamada {

istream& operator>>(istream& is, __int128_t& x) {
	string S; is >> S;
	x = 0;
	bool f{};
	for (auto &c : S) {
		if (c == '-') { f = 1; continue; }
		x *= 10;
		x += c - '0';
	}
	if (f) x = -x;
	return is;
}
istream& operator>>(istream& is, __uint128_t& x) {
	string S; is >> S;
	x = 0;
	for (auto &c : S) {
		x *= 10;
		x += c - '0';
	}
	return is;
}
ostream& operator<<(ostream& os, __int128_t x) {
	if (x == 0) return os << 0;
	if (x < 0) os << '-', x = -x;
	string S;
	while (x) S.push_back('0' + x % 10), x /= 10;
	ranges::reverse(S);
	return os << S;
}
ostream& operator<<(ostream& os, __uint128_t x) {
	if (x == 0) return os << 0;
	string S;
	while (x) S.push_back('0' + x % 10), x /= 10;
	ranges::reverse(S); return os << S;
}

template <class T> // tuple / pair / array
concept TupleLike = requires { tuple_size<remove_cvref_t<T>>::value; };
template <class R> // vector / set / ranges::view など（set は入力不可）
concept ListLike = ranges::input_range<R> && !convertible_to<R, string_view> && !TupleLike<R>;

template <TupleLike T> ostream& operator<<(ostream&, const T&);
template <TupleLike T> istream& operator>>(istream&, T&&);
template <ListLike  R> ostream& operator<<(ostream&, const R&);
template <ListLike  R> istream& operator>>(istream&, R&&);

template <TupleLike T>
istream& operator>>(istream& is, T&& t) {
	apply([&](auto&... x) { (..., (is >> x)); }, t);
	return is;
}
template <ListLike R>
istream& operator>>(istream& is, R&& a) {
	for (auto&& x : a) is >> x;
	return is;
}
template <TupleLike T>
ostream& operator<<(ostream& os, const T& t) {
	bool f{};
	apply([&](const auto&... x) { (..., (os << (exchange(f, 1) ? " " : "") << x)); }, t);
	return os;
}
template <ListLike R>
ostream& operator<<(ostream& os, const R& a) {
	bool f{};
	for (const auto& x : a) os << (exchange(f, 1) ? " " : "") << x;
	return os;
}

template <class... T>
void in(T&&... x) { (cin >> ... >> x); }
template <class... T>
void out (const T&... x) { bool f{}; (..., (cout << (exchange(f, 1) ? " " : "") << x)); cout << '\n'; }
template <class... T> // "Flush after OUT"
void fout(const T&... x) { bool f{}; (..., (cout << (exchange(f, 1) ? " " : "") << x)); cout << endl; }
template <class... T> // "WithOUT ln"
void wout(const T&... x) { bool f{}; (..., (cout << (exchange(f, 1) ? " " : "") << x)); }

struct IoSetupYamada {
	IoSetupYamada() {
		cin.tie(nullptr);
		ios::sync_with_stdio(false);
		cout << fixed << setprecision(15);
		cerr << fixed << setprecision(7);
	}
} iosetupyamada;

namespace DebugImpl {

void dump(const char&   t) { cerr << t; }
void dump(const string& t) { cerr << t; }
void dump(const bool&   t) { cerr << (t ? "true" : "false"); }
void dump(__int128_t    t) { cerr << t; }
void dump(__uint128_t   t) { cerr << t; }

template <integral T>
void dump(const T& t) {
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

template <typename T>
requires (!ListLike<T> && !TupleLike<T> && !integral<T>)
void dump(const T& t) { cerr << t; }

template <ListLike  R> void dump(const R&);
template <TupleLike T> void dump(const T&);

template <ListLike R>
void dump(const R& a) {
	bool f{};
	for (const auto& x : a) {
		cerr << (exchange(f, 1) ? ", " : "[ ");
		dump(x);
	}
	cerr << " ]";
}

template <TupleLike T>
void dump(const T& t) {
	bool f{};
	apply([&](const auto&... x) {
		(..., (cerr << (exchange(f, 1) ? ", " : "( "), dump(x)));
	}, t);
	cerr << " )";
}

template <class... T>
void trace(const T&... x) {
	bool f{};
	(..., (cerr << (exchange(f, 1) ? ", " : " "), dump(x)));
	cerr << endl;
}

}  // namespace DebugImpl
}  // namespace yamada


#ifdef yamadaDebug
#define err(...) \
	do { \
		std::cerr << "## " << #__VA_ARGS__ << " = "; \
		yamada::DebugImpl::trace(__VA_ARGS__); \
	} while (0)
#else
#define err(...) (void(0))
#endif
// ===== END INCLUDE: io.hpp =====
// ===== BEGIN INCLUDE: io-extension.hpp =====
namespace yamada {
namespace ioImpl {

struct EVAL_TAG {};
template <class T> T read() { T x{}; cin >> x; return x; }
template <class F>
struct GEN {
	F f;
	auto operator()(long long i = 0) const { return f(i); }
	auto operator=(EVAL_TAG) const { return (*this)(); }

	template<class A>
	auto to(auto n) const {
		auto g = [p = *this, n](long long) {
			long long size;
			if constexpr (requires { n(); }) size = n();
			else size = n;
			A a;
			if constexpr (requires { a.reserve(size); }) a.reserve(size);
			for (long long i = 0; i < size; ++i) a.insert(a.end(), p(i));
			return a;
		};
		return GEN<decltype(g)>{g};
	}
	template<template<class...> class A>
	auto to(auto n) const {
		return to<decltype(ranges::to<A>(declval<vector<decltype((*this)())>>() | views::as_rvalue))>(n);
	}
	auto operator* (auto n) const { return to<vector>(n); }
	auto operator[](auto n) const { return to<vector>(n); }
	template<size_t N>
	auto array() const {
		return ioImpl::GEN{[p = *this](long long) {
			std::array<decltype(p()), N> a;
			if constexpr (N > 0) for (size_t i = 0; i < N; ++i) a[i] = p(i);
			return a;
		}};
	}
	auto operator-(auto d) const {
		return ioImpl::GEN{[p = *this, d](long long i) { return p(i) - d; }};
	}
	auto operator+(auto d) const {
		return ioImpl::GEN{[p = *this, d](long long i) { return p(i) + d; }};
	}
	auto operator--() const { // 前置デクリメントで使う (例: --LL --INT) (後置だと CE)
		return ioImpl::GEN{[p = *this](long long i) { return p(i) - 1; }};
	}
	auto operator++() const {
		return ioImpl::GEN{[p = *this](long long i) { return p(i) + 1; }};
	}
	auto uz() { // UnZip
		return ioImpl::GEN{[p = *this](long long i) {
			auto v = p(i);
			using T = ranges::range_value_t<decltype(v)>;
			return [&]<size_t... I>(index_sequence<I...>) {
				tuple<vector<tuple_element_t<I, T>>...> ans;
				((get<I>(ans).reserve(v.size())), ...);
				for (auto &x : v) ((get<I>(ans).push_back(get<I>(x))), ...);
				return ans;
			}(make_index_sequence<tuple_size_v<T>>{});
		}};
	}
};

template <class T>
const auto RD = GEN{[](long long) { return read<T>(); }};
[[maybe_unused]] const auto IDX = GEN{[](long long i) { return i; }};
[[maybe_unused]] const auto INT = RD<int>;
[[maybe_unused]] const auto LL  = RD<long long>;
[[maybe_unused]] const auto CHR = RD<char>;
[[maybe_unused]] const auto STR = RD<string>;
[[maybe_unused]] const auto DBL = RD<double>;
[[maybe_unused]] const auto LLD = RD<long double>;
auto CON(auto x) { return GEN{[x = move(x)](long long) { return x; }}; } // CONstant
auto PR(auto p, auto q) { return GEN{[=](ll i) { return pair{p(i), q(i)}; }}; } // PaiR
auto TP(auto... p) { return GEN{[=](long long i) { return tuple{p(i)...}; }}; } // TuPle

} // namespace ioImpl

using ioImpl::RD;
using ioImpl::IDX;
using ioImpl::INT;
using ioImpl::LL;
using ioImpl::CHR;
using ioImpl::STR;
using ioImpl::DBL;
using ioImpl::LLD;
using ioImpl::CON;
using ioImpl::PR;
using ioImpl::TP;

}  // namespace yamada

#define FN(i,...) yamada::ioImpl::GEN{[&](long long i) { return (__VA_ARGS__); }} // これ衝突怖い
#define IN(...) __VA_OPT__(IOIMPL_E3(IOIMPL_EACH(__VA_ARGS__))) // これ衝突怖い
#define BIND(...) ([__VA_ARGS__])

#define IOIMPL_E0(...) __VA_ARGS__
#define IOIMPL_E1(...) IOIMPL_E0(IOIMPL_E0(IOIMPL_E0(__VA_ARGS__)))
#define IOIMPL_E2(...) IOIMPL_E1(IOIMPL_E1(IOIMPL_E1(__VA_ARGS__)))
#define IOIMPL_E3(...) IOIMPL_E2(IOIMPL_E2(IOIMPL_E2(__VA_ARGS__)))
#define IOIMPL_LP ()
#define IOIMPL_NEXT() IOIMPL_EACH
#define IOIMPL_EACH(e,...) IOIMPL_ITEM(e) __VA_OPT__(IOIMPL_NEXT IOIMPL_LP (__VA_ARGS__))
#define IOIMPL_ITEM(e) auto IOIMPL_NORMALIZE(e) = [] { \
	if constexpr (std::string_view{#e}.contains('=')) return yamada::ioImpl::EVAL_TAG{}; \
	else return yamada::ioImpl::LL(); \
}();

#define IOIMPL_PROBE(...) ~, 1,
#define IOIMPL_CHECK_N(_0, _1, ...) _1
#define IOIMPL_CHECK(...) IOIMPL_CHECK_N(__VA_ARGS__, 0)
#define IOIMPL_IS_PAREN(x) IOIMPL_CHECK(IOIMPL_PROBE x)

#define IOIMPL_UNPAREN(...) __VA_ARGS__
#define IOIMPL_STRIP_0(x) x
#define IOIMPL_STRIP_1(x) IOIMPL_UNPAREN x
#define IOIMPL_STRIP_IMPL(b,x) IOIMPL_STRIP_##b(x)
#define IOIMPL_STRIP(b,x) IOIMPL_STRIP_IMPL(b,x)
#define IOIMPL_NORMALIZE(x) IOIMPL_STRIP(IOIMPL_IS_PAREN(x),x)
// ===== END INCLUDE: io-extension.hpp =====
// ===== BEGIN INCLUDE: ranges.hpp =====
namespace yamada {
constexpr auto All = ranges::all_of; // of なし (Python に合わせている）
constexpr auto Any = ranges::any_of; // 同上
constexpr auto BinarySearch = ranges::binary_search;
constexpr auto Contains = ranges::contains;
constexpr auto Copy = ranges::copy;
constexpr auto Count = ranges::count;
constexpr auto CountIf = ranges::count_if;
constexpr auto Fill = ranges::fill;
constexpr auto Find = ranges::find;
constexpr auto FindIf = ranges::find_if;
constexpr auto FoldLeft = ranges::fold_left;
constexpr auto FoldRight = ranges::fold_right;
constexpr auto IsSorted = ranges::is_sorted;
constexpr auto IsSortedUntil = ranges::is_sorted_until;
constexpr auto LowerBound = ranges::lower_bound;
constexpr auto Max = ranges::max;
constexpr auto MaxElement = ranges::max_element;
constexpr auto Min = ranges::min;
constexpr auto MinElement = ranges::min_element;
constexpr auto MinMax = ranges::minmax;
constexpr auto MinMaxElement = ranges::minmax_element;
constexpr auto Reverse = ranges::reverse;
constexpr auto Rotate = ranges::rotate;
constexpr auto Sort = ranges::sort;
constexpr auto UpperBound = ranges::upper_bound;

template <int K>
constexpr auto Adjacent = views::adjacent<K>;
constexpr auto Chunk = views::chunk;
constexpr auto Drop = views::drop;
constexpr auto DropWhile = views::drop_while;
constexpr auto Enumerate = views::enumerate;
constexpr auto Filter = views::filter;
constexpr auto Join = views::join;
constexpr auto Slide = views::slide;
constexpr auto Stride = views::stride;
constexpr auto Take = views::take;
constexpr auto TakeWhile = views::take_while;
constexpr auto Zip = views::zip;

constexpr auto Rev = views::reverse; // ranges の方と混同しない
constexpr auto Transform = views::transform; // ranges の方は多分使わない
constexpr auto Iota = views::iota; // ranges の方は多分使わない

constexpr auto rtov = ranges::to<vector>();
constexpr auto rtos = ranges::to<string>();

using namespace placeholders;
constexpr auto Ofs(const int K = 1) { return views::transform(bind(plus(), _1, K)); }
} // namespace yamada
// ===== END INCLUDE: ranges.hpp =====
// ===== BEGIN INCLUDE: macro.hpp =====
#define FORE1(x, v) for (auto&& x : v)
#define FORE2(x, y, v) for (auto&& [x, y] : v)
#define FORE3(x, y, z, v) for (auto&& [x, y, z] : v)
#define FORE4(x, y, z, u, v) for (auto&& [x, y, z, u] : v)
#define FORE5(x, y, z, t, u, v) for (auto&& [x, y, z, t, u] : v)
#define FORE6(x, y, z, s, t, u, v) for (auto&& [x, y, z, s, t, u] : v)
#define OVERLOAD7(a, b, c, d, e, f, g, h, ...) h
#define each(...) OVERLOAD7(__VA_ARGS__, FORE6, FORE5, FORE4, FORE3, FORE2, FORE1)(__VA_ARGS__)

#define FOR1(a) for (long long _ = 0; _ < (long long)(a); ++_)
#define FOR2(i, a) for (long long i = 0; i < (long long)(a); ++i)
#define FOR3(i, a, b) for (long long i = a; i < (long long)(b); ++i)
#define FOR4(i, a, b, c) for (long long i = a; i < (long long)(b); i += c)
#define OVERLOAD4(a, b, c, d, e, ...) e
#define rep(...) OVERLOAD4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)

#define FOR_R1(a) for (long long i = (long long)(a)-1; i >= 0LL; --i)
#define FOR_R2(i, a) for (long long i = (long long)(a)-1; i >= 0LL; --i)
#define FOR_R3(i, a, b) for (long long i = (long long)(b)-1; i >= (long long)(a); --i)
#define OVERLOAD3(a, b, c, d, ...) d
#define repr(...) OVERLOAD3(__VA_ARGS__, FOR_R3, FOR_R2, FOR_R1)(__VA_ARGS__)

#define eb emplace_back
#define pb push_back
#define fi first
#define se second

#define VV(type, name, h, ...) \
	vector<vector<type>> name(h, vector<type>(__VA_ARGS__))
#define VVV(type, name, h, w, ...) \
	vector<vector<vector<type>>> name( \
			h, vector<vector<type>>(w, vector<type>(__VA_ARGS__)))
#define VVVV(type, name, a, b, c, ...) \
	vector<vector<vector<vector<type>>>> name( \
			a, vector<vector<vector<type>>>( \
				b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))

#define DIE(...) do { yamada::out(__VA_ARGS__); return; } while (0)
// ===== END INCLUDE: macro.hpp =====

namespace yamada {
void solve();
}
int main() { yamada::solve(); }
// ===== END INCLUDE: ../../template/template.hpp =====
 
void yamada::solve()
{
	IN(N,A=PR(LL,IDX)*N);
	SegmentTree<MONOID::MinIdx<ll>> seg(A);
	out(seg().se+1);
}
