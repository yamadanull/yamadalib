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

// utility
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
using vi = vector<int>;
using vl = vector<long long>;
using vd = V<double>;
using vs = V<string>;
using vvi = vector<vector<int>>;
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
using pi = P<int, int>;
using vp = V<pl>;
using vvp = VV<pl>;

constexpr int inf = 1001001001;
constexpr long long infLL = 4004004004004004004LL;

template <typename T, typename U>
inline bool amin(T &x, U y) {
	return (y < x) ? (x = y, true) : false;
}
template <typename T, typename U>
inline bool amax(T &x, U y) {
	return (x < y) ? (x = y, true) : false;
}

template <typename T>
inline T Max(const vector<T> &v) {
	return *max_element(begin(v), end(v));
}
template <typename T>
inline T Min(const vector<T> &v) {
	return *min_element(begin(v), end(v));
}
template <typename T>
inline long long Sum(const vector<T> &v) {
	return accumulate(begin(v), end(v), T(0));
}

template <typename T>
int lb(const vector<T> &v, const T &a) {
	return lower_bound(begin(v), end(v), a) - begin(v);
}
template <typename T>
int ub(const vector<T> &v, const T &a) {
	return upper_bound(begin(v), end(v), a) - begin(v);
}

constexpr long long TEN(int n) {
	long long ret = 1, x = 10;
	for (; n; x *= x, n >>= 1) ret *= (n & 1 ? x : 1);
	return ret;
}

template <typename T, typename U>
pair<T, U> mkp(const T &t, const U &u) {
	return make_pair(t, u);
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
bool nxp(T &v) {
	return next_permutation(begin(v), end(v));
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
vector<U> Digit(T a, const U &x) {
	vector<U> ret;
	while (a > 0) {
		ret.emplace_back(a % x);
		a /= x;
	}
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
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			res[j][i] = v[i][j];
		}
	}
	return res;
}

template <typename T>
vector<T> Rotate(const vector<T> &v, int clockwise = true) {
	using U = typename T::value_type;
	int H = v.size(), W = v[0].size();
	vector res(W, T(H, U{}));
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (clockwise) {
				res[W - 1 - j][i] = v[i][j];
			} else {
				res[j][H - 1 - i] = v[i][j];
			}
		}
	}
	return res;
}

template <typename T, typename F>
T bisect(T ok, T bad, F pred) {
	if (ok == bad) return ok;
	if (!pred(ok)) return ok; 
	while (bad - ok > 1) { T mid = ok + (bad - ok) / 2; (pred(mid) ? ok : bad) = mid; } 
	return bad;
}

template <typename T, typename F>
T bisect_double(T ok, T bad, F pred, int iter = 100) {
	if (ok == bad) return ok;
	if (!pred(ok)) return ok; 
	for (int i = 0; i < iter; i++){
		T mid = ok + (bad - ok) / 2; (pred(mid) ? ok : bad) = mid;
	} 
	return bad;
}

template <typename T>
bool inLR(T L, T x, T R){ return (L <= x && x < R); }

bool YESNO(bool b) { cout << (b ? "YES\n" : "NO\n"); return b; }
bool YesNo(bool b) { cout << (b ? "Yes\n" : "No\n"); return b; }

template <typename mint>
void mout(mint a, int M = 100) {
	if (a == 0) { cout << 0 << "\n"; return; }
	for (int i = 0; i <= M; i++) for (int j = 1; j <= M; j++) {
		mint val = (mint)i / j;
		if (val == a) {
			if (j == 1) cout << i << "\n";
			else cout << i << "/" << j << "\n";
			return;
		}
		else if (val == -a) {
			if (j == 1) cout << -i << "\n";
			else cout << -i << "/" << j << "\n";
			return;
		}
	}
	cout << "NF\n";
}

template <typename mint>
void mout(std::vector<mint> A, int M = 100) {
	int N = A.size();
	for (int pos = 0; pos < N; pos++) {
		if (A[pos] == 0) { cout << 0 << (pos == N - 1 ? "\n" : " "); continue; }

		bool fn = false;
		for (int i = 0; i <= M; i++) {
			for (int j = 1; j <= M; j++) {
				mint val = (mint)i / j;
				if (val == A[pos]) {
					if (j == 1) cout << i << (pos == N - 1 ? "\n" : " ");
					else cout << i << "/" << j << (pos == N - 1 ? "\n" : " ");
					fn = true;
					break;
				}
				else if (val == -A[pos]) {
					if (j == 1) cout << -i << (pos == N - 1 ? "\n" : " ");
					else cout << -i << "/" << j << (pos == N - 1 ? "\n" : " ");
					fn = true;
					break;
				}
			}
			if (fn) break;
		}
		if (!fn) cout << "NF" << (pos == N - 1 ? "\n" : " ");
	}
}

} // namespace yamada

// End include: "util.hpp"

// bit operation
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

// inout
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

// macro
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
// Begin include: "../../graph/strongly-connected-components.hpp"

// Begin include: "./graph-template.hpp"

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

// Input of Edges
template <typename T>
Edges<T> esgraph([[maybe_unused]] int N, int M, int is_weighted = true,
		bool is_1origin = true) {
	Edges<T> es;
	for (int _ = 0; _ < M; _++) {
		int x, y;
		cin >> x >> y;
		T c;
		if (is_weighted)
			cin >> c;
		else
			c = 1;
		if (is_1origin) x--, y--;
		es.emplace_back(x, y, c);
	}
	return es;
}

// Input of Adjacency Matrix
template <typename T>
vector<vector<T>> adjgraph(int N, int M, T INF, int is_weighted = true,
		bool is_directed = false, bool is_1origin = true) {
	vector<vector<T>> d(N, vector<T>(N, INF));
	for (int _ = 0; _ < M; _++) {
		int x, y;
		cin >> x >> y;
		T c;
		if (is_weighted)
			cin >> c;
		else
			c = 1;
		if (is_1origin) x--, y--;
		d[x][y] = c;
		if (!is_directed) d[y][x] = c;
	}
	return d;
}

/**
 * @brief グラフテンプレート
 * @docs docs/graph/graph-template.md
 */
// End include: "./graph-template.hpp"

// Strongly Connected Components
// DAG of SC graph   ... scc.dag (including multiedges)
// new node of k     ... scc[k]
// inv of scc[k] = i ... scc.belong(i)
template <typename G>
struct StronglyConnectedComponents {
 private:
  const G &g;
  vector<vector<int>> rg;
  vector<int> comp, order;
  vector<char> used;
  vector<vector<int>> blng;

 public:
  vector<vector<int>> dag;
  StronglyConnectedComponents(G &_g) : g(_g), used(g.size(), 0) { build(); }

  int operator[](int k) { return comp[k]; }

  vector<int> &belong(int i) { return blng[i]; }

 private:
  void dfs(int idx) {
    if (used[idx]) return;
    used[idx] = true;
    for (auto to : g[idx]) dfs(int(to));
    order.push_back(idx);
  }

  void rdfs(int idx, int cnt) {
    if (comp[idx] != -1) return;
    comp[idx] = cnt;
    for (int to : rg[idx]) rdfs(to, cnt);
  }

  void build() {
    for (int i = 0; i < (int)g.size(); i++) dfs(i);
    reverse(begin(order), end(order));
    used.clear();
    used.shrink_to_fit();

    comp.resize(g.size(), -1);

    rg.resize(g.size());
    for (int i = 0; i < (int)g.size(); i++) {
      for (auto e : g[i]) {
        rg[(int)e].emplace_back(i);
      }
    }
    int ptr = 0;
    for (int i : order)
      if (comp[i] == -1) rdfs(i, ptr), ptr++;
    rg.clear();
    rg.shrink_to_fit();
    order.clear();
    order.shrink_to_fit();

    dag.resize(ptr);
    blng.resize(ptr);
    for (int i = 0; i < (int)g.size(); i++) {
      blng[comp[i]].push_back(i);
      for (auto &to : g[i]) {
        int x = comp[i], y = comp[to];
        if (x == y) continue;
        dag[x].push_back(y);
      }
    }
  }
};
// End include: "../../graph/strongly-connected-components.hpp"
// Begin include: "../../graph/graph-template.hpp"

// End include: "../../graph/graph-template.hpp"
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

// choose n numbers from [l, r) without overlapping
vector<i64> randset(i64 l, i64 r, i64 n) {
  assert(l <= r && n <= r - l);
  unordered_set<i64> s;
  for (i64 i = n; i; --i) {
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
  int n = v.size();
  for (int i = 1; i < n; i++) swap(v[i], v[randint(0, i + 1)]);
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
// Begin include: "../../geometry/integer-geometry.hpp"
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

struct Point {
	using T = __int128_t;
	T x, y;
	Point() : x(0), y(0) {}
	Point(T x_, T y_) : x(x_), y(y_) {}

	Point &operator+=(const Point &p) {
		this->x += p.x;
		this->y += p.y;
		return *this;
	}

	Point &operator-=(const Point &p) {
		this->x -= p.x;
		this->y -= p.y;
		return *this;
	}

	Point &operator*=(const long long &r) {
		this->x *= r;
		this->y *= r;
		return *this;
	}

	int pos() const {
		if (y < 0) return -1;
		if (y == 0 && 0 <= x) return 0;
		return 1;
	}

	long double slope() {
		if (x == 0) {
			if (y > 0) return std::numeric_limits<long double>::max();
			else return std::numeric_limits<long double>::min();
		}
		return (long double)y / x;
	}

	void shrink() {
		T g = binary_gcd(x, y);
		x /= g;
		y /= g;
	}

	Point operator+(const Point &p) const { return Point(*this) += p; }
	Point operator-(const Point &p) const { return Point(*this) -= p; }
	Point operator*(long long &r) const { return Point(*this) *= r; }
	Point operator-() const { return Point(-this->x, -this->y); }
	bool operator==(const Point &p) const { return x == p.x && y == p.y; }
	bool operator!=(const Point &p) const { return x != p.x || y != p.y; }
	bool operator<(const Point &p) const { return x == p.x ? y < p.y : x < p.x; }

	friend istream &operator>>(istream &is, Point &p) {
		long long x, y;
		is >> x >> y;
		p.x = x, p.y = y;
		return is;
	}

	friend ostream &operator<<(ostream &os, const Point &p) {
		os << (long long)(p.x) << " " << (long long)(p.y);
		return os;
	}
};
using Points = vector<Point>;

Point::T dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
Point::T cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }

// sort by argument (-Pi ~ Pi)
void ArgumentSort(Points &v) {
	sort(begin(v), end(v), [](Point a, Point b) {
		if (a.pos() != b.pos()) return a.pos() < b.pos();
		return cross(a, b) > 0;
	});
}

// 1 ... counterclockwise / 0 straight / -1 clockwise
int ccw(const Point &a, const Point &b, const Point &c) {
	Point::T t = cross(b - a, c - a);
	return t < 0 ? -1 : t == 0 ? 0 : 1;
}

// v must have sorted by x-coordinate
Points LowerHull(const Points &ps) {
	int N = (int)ps.size();
	for (int i = 0; i < N - 1; i++) assert(ps[i].x <= ps[i + 1].x);
	if (N <= 2) return ps;
	Points convex(N);
	int k = 0;
	for (int i = 0; i < N; convex[k++] = ps[i++]) {
		while (k >= 2 && ccw(convex[k - 2], convex[k - 1], ps[i]) <= 0) --k;
	}
	convex.resize(k);
	return convex;
}

Points UpperHull(const Points &ps) {
	int N = (int)ps.size();
	for (int i = 0; i < N - 1; i++) assert(ps[i].x <= ps[i + 1].x);
	if (N <= 2) return ps;
	Points convex(N);
	int k = 0;
	for (int i = 0; i < N; convex[k++] = ps[i++]) {
		while (k >= 2 && ccw(convex[k - 2], convex[k - 1], ps[i]) >= 0) --k;
	}
	convex.resize(k);
	return convex;
}

Points ConvexHull(Points ps) {
	sort(begin(ps), end(ps));
	ps.erase(unique(begin(ps), end(ps)), end(ps));
	int N = ps.size();
	if (N <= 2) return ps;
	Points convex(2 * N);
	int k = 0;
	for (int i = 0; i < N; convex[k++] = ps[i++]) {
		while (k >= 2 && ccw(convex[k - 2], convex[k - 1], ps[i]) <= 0) --k;
	}
	for (int i = N - 2, t = k + 1; i >= 0; convex[k++] = ps[i--]) {
		while (k >= t && ccw(convex[k - 2], convex[k - 1], ps[i]) <= 0) --k;
	}
	convex.resize(k - 1);
	return convex;
}
// End include: "../../geometry/integer-geometry.hpp"
using namespace yamada;

const Point Start(0,5000);
int N,M,K;
Points ps;
VV<double> Ps;
vi ans,cns,d_idxs,s_idxs;
vvi to_d,to_s;
int bns;
UnweightedGraph g;
double score;
VV<double> dist;

// Begin include: "score.hpp"
using namespace yamada;

VV<double> dag_dp(){ // ゴミiが処理機jに行く確率
	StronglyConnectedComponents scc(g);
	assert(scc.dag.size()==N+M);
	vv(double,dp,N,N+M,0); // ゴミiがトポロジカル番号jを通る確率
	rep(i,N){
		dp[i][scc[bns]]=1;
		rep(j,N+M)if(dp[i][j]>0){
			int pos=scc.belong(j)[0];
			if(!g[pos].empty()){
				int u=scc[g[pos][0]];
				int v=scc[g[pos][1]];
				int k=cns[pos-N];
				dp[i][u]+=dp[i][j]*Ps[k][i];
				dp[i][v]+=dp[i][j]*(1-Ps[k][i]);
			}
		}
	}
	vv(double,ret,N,N);
	rep(i,N)rep(j,N)ret[i][j]=dp[i][scc[j]];
	return ret;
}

void ans_adj(){
	auto data=dag_dp();
	V<double>dp(1<<N);
	rep(S,(1<<N)-1){
		int j=popcnt(S); // 処理機jに行かせるゴミを決める
		rep(i,N)if(!(S>>i&1)){
			int T=S|(1<<i);
			amax(dp[T],dp[S]+data[i][j]);
		}
	}

	for(int j=N-1,pos=(1<<N)-1; j>=0; j--){
		assert(popcnt(pos)==j+1);
		rep(i,N)if(pos>>i&1){
			int npos=pos^(1<<i);
			if(dp[npos]+data[i][j]==dp[pos]){
				ans[j]=i;
				pos=npos;
				break;
			}
		}
	}
}

double cal_score(){
	auto data=dag_dp();
	double ret=0;
	rep(j,N)ret+=data[ans[j]][j];
	return ret;
}
// End include: "score.hpp"

int near_d(int pos){
	double x=rnd(-10,0);
	int rank=pow(1.1,x)*N;
	return to_d[pos][rank];
}

int near_s(int pos){
	double x=rnd(-10,0);
	int rank=pow(1.1,x)*M;
	return to_s[pos][rank];
}

bool inter_check(int a,int b,int c,int d){
	if(a==c||a==d||b==c||b==d)return true;
	Point p1=ps[a],p2=ps[b],q1=ps[c],q2=ps[d];
	if(cross(p2-p1,q1-p1)*cross(p2-p1,q2-p1)>0)return true;
	if(cross(q2-q1,p1-q1)*cross(q2-q1,p2-q1)>0)return true;
	return false;
}

bool add_e(){
	int pos=-1,b=-1;
	rep(i,N,N+M)if(!g[i].empty()){
		rep(j,2){
			if(inLR(0,g[i][j],N)){ pos=i; b=j; break; }
		}
		if(pos>=0)break;
	}
	if(pos<0)return false;
	rep(3){
		int i=randint(N,N+M);
		if(g[i].empty())continue;
		int j=randint(0,2);
		if(inLR(0,g[i][j],N)){ pos=i; b=j; break; }
	}

	int TIMELIMIT=0.03*CLOCKS_PER_SEC;
	int ti=clock();
	while(clock()-ti<TIMELIMIT){
		int to=near_s(pos);
		if(!g[to].empty())continue;
		if(pos==to)continue;
		int pto=g[pos][b];
		g[pos][b]=to;
		g[to].eb(near_d(to));
		g[to].eb(near_d(to));
		if(StronglyConnectedComponents(g).dag.size()<N+M){
			g[pos][b]=pto; g[to].clear(); continue;
		}

		bool fn=true;
		rep(i,N+M){
			each(e,g[i]){
				if(!inter_check(i,e,pos,to)){ fn=false; break; }
				if(!inter_check(i,e,to,g[to][0])){ fn=false; break; }
				if(!inter_check(i,e,to,g[to][1])){ fn=false; break; }
			}
			if(!fn)break;
		}
		if(!fn){ g[pos][b]=pto; g[to].clear(); continue; }
		cns[to-N]=randint(0,K);
		return true;
	}
	return false;
}

void increace_d(){
	UnweightedGraph G(N+M);
	rep(i,N+M)each(e,g[i])g[e].eb(i);
	int pos=-1;
	{
		int TIMELIMIT=0.03*CLOCKS_PER_SEC;
		int ti=clock();
		while(clock()-ti<TIMELIMIT){
			int npos=randint(0,N);
			if(G[npos].empty()){
				pos=npos;
				break;
			}
		}
	}
	if(pos<0)return;
	int TIMELIMIT=0.03*CLOCKS_PER_SEC;
	int ti=clock();
	while(clock()-ti<TIMELIMIT){
		int npos=randint(0,N);
		if(G[npos].size()>=2){
			each(v,G[npos]){
				bool fn=true;
				rep(i,N+M)each(e,g[i]){
					if(!inter_check(i,e,v,npos)){ fn=false; break; }
				}
				if(fn){
					int b=(g[v][0]==npos? 0:1);
					g[v][b]=pos;
					return;
				}
			}
		}
	}
}

void yamada::solve()
{
	const int ti=clock();
	in(N,M,K);
	ps.resize(N+M); in(ps);
	Ps.resize(K,V<double>(N)); in(Ps);

	d_idxs.resize(N); rep(i,N)d_idxs[i]=i;
	s_idxs.resize(M); rep(i,M)s_idxs[i]=i;
	sort(all(d_idxs),[&](int a,int b){return ps[a]<ps[b];});
	sort(all(s_idxs),[&](int a,int b){return ps[a+N]<ps[b+N];});

	dist.resize(N+M,V<double>(N+M));
	rep(i,N+M)rep(j,N+M){
		Point v=ps[i]-ps[j];
		dist[i][j]=sqrt(v.x*v.x+v.y*v.y);
	}

	to_d.resize(N+M,vi(N)); each(td,to_d)rep(i,N)td[i]=i;
	to_s.resize(N+M,vi(M)); each(ts,to_s)rep(i,M)ts[i]=i+N;
	rep(i,N+M){
		sort(all(to_d[i]),[&](int a,int b){return dist[i][a]<dist[i][b];});
		sort(all(to_s[i]),[&](int a,int b){return dist[i][a]<dist[i][b];});
	}

	ans.resize(N); rep(i,N)ans[i]=i;
	bns=s_idxs[0]+N;
	g.resize(N+M);
	cns.resize(M,-1);
	cns[bns-N]=randint(0,K);
	g[bns].eb(d_idxs[0]);
	g[bns].eb(d_idxs[1]);

	{ // add 分別機
		int TIMELIMIT=0.50*CLOCKS_PER_SEC;
		while(clock()-ti<TIMELIMIT)add_e();
	}

	{ // 有効な処理機を増やす
		int TIMELIMIT=1.00*CLOCKS_PER_SEC;
		while(clock()-ti<TIMELIMIT)add_e();
	}

	ans_adj();
	{ // 使用分別機を劇的に調整
		int TIMELIMIT=1.50*CLOCKS_PER_SEC;
		score=cal_score();
		while(clock()-ti<TIMELIMIT){
			vi pcns=cns;
			each(c,cns)if(c>=0)c=randint(0,K);
			ans_adj();
			double nscore=cal_score();
			if(nscore<score)cns=pcns;
			else score=nscore;
		}
	}

	{ // 使用分別機を使うか調整
		int TIMELIMIT=1.90*CLOCKS_PER_SEC;
		int cnt=0;
		score=cal_score();
		while(clock()-ti<TIMELIMIT){
			int pos=randint(N,N+M);
			if(g[pos].empty())continue;
			if(randint(0,2)){
				int ocns=cns[pos-N];
				cns[pos-N]=randint(0,K);
				double nscore=cal_score();
				if(nscore<score)cns[pos-N]=ocns;
				else{
					score=nscore;
					if(++cnt%10==0)ans_adj();
				}
			}
			else{
				swap(g[pos][0],g[pos][1]);
				double nscore=cal_score();
				if(nscore<score)swap(g[pos][0],g[pos][1]);
				else{
					score=nscore;
					if(++cnt%10==0)ans_adj();
				}
			}
		}
	}

	out(ans);
	out(bns);
	rep(i,N,N+M){
		if(cns[i-N]<0)out(-1);
		else out(cns[i-N],g[i]);
	}
}