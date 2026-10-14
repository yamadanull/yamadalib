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
	if (!pred(ok)) return ok; 
	while (bad - ok > 1) { T mid = ok + (bad - ok) / 2; (pred(mid) ? ok : bad) = mid; } 
	return bad;
}

template <typename T, typename F>
T bisect_double(T ok, T bad, F pred, int iter = 100) {
	if (ok == bad) return ok;
	if (!pred(ok)) return ok; 
	while (iter--) { T mid = ok + (bad - ok) / 2; (pred(mid) ? ok : bad) = mid; } 
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
		bool found = false;
		for (int i = 0; i <= M; i++) {
			for (int j = 1; j <= M; j++) {
				mint val = (mint)i / j;
				if (val == A[pos]) {
					if (j == 1) cout << i << (pos == N - 1 ? "\n" : " ");
					else cout << i << "/" << j << (pos == N - 1 ? "\n" : " ");
					found = true;
					break;
				}
				else if (val == -A[pos]) {
					if (j == 1) cout << -i << (pos == N - 1 ? "\n" : " ");
					else cout << -i << "/" << j << (pos == N - 1 ? "\n" : " ");
					found = true;
					break;
				}
			}
			if (found) break;
		}
		if (!found) cout << "NF" << (pos == N - 1 ? "\n" : " ");
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
	T get_val(int i) { return S[i + 1] - S[i]; }
};

template <typename T>
T extgcd(T a, T b, T &x, T &y) {
	T d = a;
	if(b != 0) {
		d = extgcd(b, a % b, y, x);
		y -= (a / b) * x;
	}
	else x = 1, y = 0;
	return d;
}

// floor(sqrt(x))
long long isqrt (long long x) {
	long long y = sqrt(x);
	while (y * y > x) y--;
	while ((y + 1) * (y + 1) <= x) y++;
	return y;
}

template <typename T>
T Floor(T a, T b) { return a / b - (a % b && (a ^ b) < 0); }
template <typename T>
T Ceil(T a, T b) { return a / b + (a % b && (a ^ b) >= 0); }

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
// Begin include: "../../shortest-path/bfs-restore.hpp"

vector<pair<int, int>> bfs_restore(vector<vector<int>>& g, int st = 0) {
	vector<pair<int, int>> d(g.size(), make_pair(-1, -1));
	d[st] = make_pair(0, -1);
	queue<int> Q;
	Q.push(st);
	while (!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		int cd = d[cur].first;
		for (auto&& dst : g[cur]) {
			if (d[dst].first == -1) {
				d[dst].first = cd + 1;
				d[dst].second = cur;
				Q.push(dst);
			}
		}
	}
	return d;
}
// End include: "../../shortest-path/bfs-restore.hpp"
// Begin include: "../../tree/tree-query.hpp"
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
// End include: "../graph/graph-template.hpp"

template <typename G>
struct Tree {
private:
	G& g;
	int root;
	vector<array<int, 24>> bl;
	vector<int> dp;
	vector<int> sz;
	void build() {
		bl.resize(g.size());
		dp.resize(g.size());
		sz.resize(g.size());
		for (auto& v : bl) fill(begin(v), end(v), -1);
		dfs(root, -1, 0);
	}

	void dfs(int c, int p, int _dp) {
		dp[c] = _dp;
		sz[c] = 1;
		for (int i = p, x = 0; i != -1;) {
			bl[c][x] = i;
			i = bl[i][x], x++;
		}
		for (auto& d : g[c]) {
			if (d == p) continue;
			dfs(d, c, _dp + 1);
			sz[c] += sz[d];
		}
	}

public:
	Tree(G& _g, int _r = 0) : g(_g), root(_r) { build(); }

	int depth(int u) const { return dp[u]; }
	int size(int u) const {return sz[u]; }
	int par(int u) const { return u == root ? -1 : bl[u][0]; }

	int kth_ancestor(int u, int k) const {
		if (dp[u] < k) return -1;
		while (k) {
			int t = __builtin_ctz(k);
			u = bl[u][t], k ^= 1 << t;
		}
		return u;
	}

	int nxt(int s, int t) const {
		if (dp[s] >= dp[t]) return par(s);
		int u = kth_ancestor(t, dp[t] - dp[s] - 1);
		return bl[u][0] == s ? u : bl[s][0];
	}

	vector<int> path(int s, int t) const {
		vector<int> pre, suf;
		while (dp[s] > dp[t]) {
			pre.push_back(s);
			s = bl[s][0];
		}
		while (dp[s] < dp[t]) {
			suf.push_back(t);
			t = bl[t][0];
		}
		while (s != t) {
			pre.push_back(s);
			suf.push_back(t);
			s = bl[s][0];
			t = bl[t][0];
		}
		pre.push_back(s);
		reverse(begin(suf), end(suf));
		copy(begin(suf), end(suf), back_inserter(pre));
		return pre;
	}

	int lca(int u, int v) {
		if (dp[u] != dp[v]) {
			if (dp[u] > dp[v]) swap(u, v);
			v = kth_ancestor(v, dp[v] - dp[u]);
		}
		if (u == v) return u;
		for (int i = __lg(dp[u]); i >= 0; --i) {
			if (dp[u] < (1 << i)) continue;
			if (bl[u][i] != bl[v][i]) u = bl[u][i], v = bl[v][i];
		}
		return bl[u][0];
	}

	// u - v 間のパス上の頂点のうち u から距離 i の頂点
	// (dist(u, v) < i のとき -1)
	int jump(int u, int v, int i) {
		int lc = lca(u, v);
		int d1 = dp[u] - dp[lc];
		if (i <= d1) return kth_ancestor(u, i);
		int d = d1 + dp[v] - dp[lc];
		if (i <= d) return kth_ancestor(v, d - i);
		return -1;
	}

	int len(int u, int v) { return depth(u) + depth(v) - depth(lca(u, v)) * 2; }
};

/**
 * @brief 木に対する一般的なクエリ
 * @docs docs/tree/tree-query.md
 */
// End include: "../../tree/tree-query.hpp"
// Begin include: "../../graph/two-edge-connected-components.hpp"

// Begin include: "./graph-template.hpp"

// End include: "./graph-template.hpp"
// Begin include: "./lowlink.hpp"

#include <vector>
using namespace std;

// Begin include: "./graph-template.hpp"

// End include: "./graph-template.hpp"

// bridge ... 橋 (辺 (u, v) が u < v となるように格納)
// articulation point ... 関節点
template <typename G>
struct LowLink {
	const G &g;
	int N;
	vector<int> ord, low, articulation;
	vector<pair<int, int> > bridge;

	LowLink(const G &_g) : g(_g), N(g.size()), ord(N, -1), low(N, -1) {
		for (int i = 0, k = 0; i < N; i++) {
			if (ord[i] == -1) {
				k = dfs(i, k, -1);
			}
		}
	}

	int dfs(int idx, int k, int par) {
		low[idx] = (ord[idx] = k++);
		int cnt = 0;
		bool arti = false, second = false;
		for (auto &to : g[idx]) {
			if (ord[to] == -1) {
				cnt++;
				k = dfs(to, k, idx);
				low[idx] = min(low[idx], low[to]);
				arti |= (par != -1) && (low[to] >= ord[idx]);
				if (ord[idx] < low[to]) {
					bridge.emplace_back(minmax(idx, (int)to));
				}
			}
			else if (to != par || second) {
				low[idx] = min(low[idx], ord[to]);
			}
			else second = true;
		}
		arti |= par == -1 && cnt > 1;
		if (arti) articulation.push_back(idx);
		return k;
	}
};
// End include: "./lowlink.hpp"

template <typename G>
struct TwoEdgeConnectedComponents {
  const G &g;
  LowLink<G> low;
  vector<int> comp;
  int k;
  vector<vector<int>> groups, tree;
  TwoEdgeConnectedComponents(const G &g_)
      : g(g_), low(g_), comp(g_.size(), -1), k(0) {
    for (int i = 0; i < (int)g.size(); i++) {
      if (comp[i] == -1) dfs(i, -1);
    }
    groups.resize(k);
    tree.resize(k);
    for (int i = 0; i < (int)g.size(); i++) {
      groups[comp[i]].push_back(i);
    }
    for (auto &e : low.bridge) {
      int u = comp[e.first], v = comp[e.second];
      tree[u].push_back(v);
    }
  };

  int operator[](const int &k) const { return comp[k]; }

  void dfs(int i, int p) {
    if (p >= 0 && low.ord[p] >= low.low[i])
      comp[i] = comp[p];
    else
      comp[i] = k++;
    for (auto &d : g[i]) {
      if (comp[d] == -1) dfs(d, i);
    }
  }
};
// End include: "../../graph/two-edge-connected-components.hpp"
// Begin include: "../../graph/graph-template.hpp"

// End include: "../../graph/graph-template.hpp"

void yamada::solve()
{
	inl(N,M);
	auto g=graph(N,M);
	TwoEdgeConnectedComponents tecd(g);

	auto tree=tecd.tree;
	auto grs=tecd.groups;

	vl belong(N);
	rep(i,grs.size())each(v,grs[i])belong[v]=i;
	Tree t(tree);
	auto path=t.path(belong[0],belong[1]);
	if(path.size()!=tree.size())die("No");
	assert(0);
	out("Yes");

	auto d0=bfs_restore(g,0);
	auto d1=bfs_restore(g,1);

	vl ans(N),bns(N);
	rep(i,N)ans[i]=d0[i].se;
	rep(i,N)bns[i]=d1[i].se;
	out(bns[0]+1);
	out(ans[1]+1);
	rep(i,2,N)out(ans[i]+1,bns[i]+1);
}