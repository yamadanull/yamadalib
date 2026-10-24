/**
 * date    : 2026-10-25 02:54:19
 * author  : yamadanull
 * library : https://github.com/yamadanull/yamadalib/
 */

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
T bisect(F f) { // 判定回数は上限を決め打ちした場合の高々２倍程度 // f(0) && !f(inf) が必要
	T ok = 0, ng = 1;
	while (f(ng)) ng *= 2;
	while (ng - ok > 1) { T mid = ok + (ng - ok) / 2; (f(mid) ? ok : ng) = mid; } 
	return ng;
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
	ranges::reverse(S);
	return os << S;
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
	cerr << "[ ";
	for (const auto& x : a) {
		cerr << (exchange(f, 1) ? ", " : "");
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
// ===== BEGIN INCLUDE: ../../fps/ntt-friendly-fps.hpp =====

// ===== BEGIN INCLUDE: ../ntt/ntt.hpp =====

#include <vector>

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

	void fft4(std::vector<mint> &a, int k) {
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
					mint t0 = a[j0], t1 = a[j0 + v] * xx, t2 = a[j2] * ww, t3 = a[j2 + v] * wx;
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

	void ifft4(std::vector<mint> &a, int k) {
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

	void ntt(std::vector<mint> &a) {
		if ((int)a.size() <= 1) return;
		fft4(a, __builtin_ctz(a.size()));
	}

	void intt(std::vector<mint> &a) {
		if ((int)a.size() <= 1) return;
		ifft4(a, __builtin_ctz(a.size()));
		mint iv = mint(a.size()).inverse();
		for (auto &x : a) x *= iv;
	}

	std::vector<mint> multiply(const std::vector<mint> &a, const std::vector<mint> &b) {
		int l = a.size() + b.size() - 1;
		if (std::min<int>(a.size(), b.size()) <= 40) {
			std::vector<mint> s(l);
			for (int i = 0; i < (int)a.size(); ++i)
				for (int j = 0; j < (int)b.size(); ++j) s[i + j] += a[i] * b[j];
			return s;
		}
		int k = 2, M = 4;
		while (M < l) M <<= 1, ++k;
		setwy(k);
		std::vector<mint> s(M);
		for (int i = 0; i < (int)a.size(); ++i) s[i] = a[i];
		fft4(s, k);
		if (a.size() == b.size() && a == b) {
			for (int i = 0; i < M; ++i) s[i] *= s[i];
		} else {
			std::vector<mint> t(M);
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

	void ntt_doubling(std::vector<mint> &a) {
		int M = (int)a.size();
		auto b = a;
		intt(b);
		mint r = mint(1), zeta = mint(pr).pow((mint::get_mod() - 1) / (M << 1));
		for (int i = 0; i < M; i++) b[i] *= r, r *= zeta;
		ntt(b);
		std::copy(begin(b), end(b), back_inserter(a));
	}
};
// ===== END INCLUDE: ../ntt/ntt.hpp =====
// ===== BEGIN INCLUDE: ./formal-power-series.hpp =====

template <typename mint>
struct FormalPowerSeries : std::vector<mint> {
	using std::vector<mint>::vector;
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
		FPS ret(std::min(this->size(), r.size()));
		for (int i = 0; i < (int)ret.size(); i++) ret[i] = (*this)[i] * r[i];
		return ret;
	}

	// 前 sz 項を取ってくる。sz に足りない項は 0 埋めする
	FPS pre(int sz) const {
		FPS ret(begin(*this), begin(*this) + std::min((int)this->size(), sz));
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
// ===== END INCLUDE: ./formal-power-series.hpp =====

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
		for (int j = 0; j < std::min((int)this->size(), 2 * d); j++) f[j] = (*this)[j];
		for (int j = 0; j < d; j++) g[j] = res[j];
		f.ntt();
		g.ntt();
		for (int j = 0; j < 2 * d; j++) f[j] *= g[j];
		f.intt();
		for (int j = 0; j < d; j++) f[j] = mint(0);
		f.ntt();
		for (int j = 0; j < 2 * d; j++) f[j] *= g[j];
		f.intt();
		for (int j = d; j < std::min(2 * d, deg); j++) res[j] = -f[j];
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
		fps x(begin(*this), begin(*this) + std::min<int>(this->size(), m));
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
		for (int i = m; i < std::min<int>(this->size(), 2 * m); ++i) x[i] += (*this)[i];
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
// ===== END INCLUDE: ../../fps/ntt-friendly-fps.hpp =====
// ===== BEGIN INCLUDE: ../../modint/montgomery-modint.hpp =====

#include <cstdint>
#include <iostream>
#include <ostream>

template <std::uint32_t mod>
struct LazyMontgomeryModInt {
	using mint = LazyMontgomeryModInt;
	using i32 = std::int32_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

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

	friend std::ostream &operator<<(std::ostream &os, const mint &b) {
		return os << b.get();
	}

	friend std::istream &operator>>(std::istream &is, mint &b) {
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
// ===== END INCLUDE: ../../modint/montgomery-modint.hpp =====

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
void yamada::solve()
{
	struct gps{
		fps nume;
		ll cnt; // deno: (1+x)^cnt
	};
	const fps BS{1,1};
	auto stdize=[&](this auto stdize,gps &F,gps &G)->void{
		if(F.cnt<G.cnt)stdize(G,F);
		ll t=F.cnt-G.cnt;
		G.nume*=BS.pow(t,t+1);
		G.cnt+=t;
	};
	auto add=[&](gps F,gps G)->gps{ stdize(F,G); return{F.nume+G.nume,F.cnt}; };
	auto mul=[&](gps F,gps G)->gps{ return{F.nume*G.nume,F.cnt+G.cnt}; };

	auto[Fl,F,Fr]=[&]()->array<vc<gps>,3>{
		IN(N,BIND(A,B)=(PR(LL,LL)*N).uz());
		vp cmp;
		each(i,a,A|Enumerate)cmp.eb(a,i);
		each(i,b,B|Enumerate)cmp.eb(b,i);
		Sort(cmp);

		vc<gps>Fl(N*2),F(N*2),Fr(N*2);
		each(i,a,A|Enumerate){
			ll ci=lb<pl>(cmp,{a,i});
			Fl[ci]={BS,0};
			F[ci]={fps{a},0};
			Fr[ci]={fps{2},0};
		}
		each(i,b,B|Enumerate){
			ll ci=lb<pl>(cmp,{b,i});
			Fl[ci]={fps{0,2},1};
			F[ci]={fps{b},1};
			Fr[ci]={fps{1},0};
		}
		return{Fl,F,Fr};
	}();
	/* each(f,Fl)err(f.nume,f.cnt); */
	/* each(f,F)err(f.nume,f.cnt); */
	/* each(f,Fr)err(f.nume,f.cnt); */
	ll N=len(F)/2;

	/* err(N); */
	gps ans=[&](this auto dfs,ll L,ll R)->array<gps,3>{
		if(R-L==1)return {Fl[L],F[L],Fr[L]};
		ll M=(L+R)/2;
		auto[fl0,f0,fr0]=dfs(L,M);
		auto[fl1,f1,fr1]=dfs(M,R);
		auto f=add(mul(fl0,f1),mul(f0,fr1));
		auto fl=mul(fl0,fl1);
		auto fr=mul(fr0,fr1);
		/* err(L,R,f.nume,f.cnt); */
		/* err(L,R,fl.nume,fl.cnt); */
		/* err(L,R,fr.nume,fr.cnt); */
		return{fl,f,fr};
	}(0,N*2)[1];
	/* err(ans.nume,ans.cnt); */
	/* err(BS.pow(0)); */

	ans.nume*=BS.pow(ans.cnt,N).inv();
	each(a,ans.nume.pre(N))out(a);
}
