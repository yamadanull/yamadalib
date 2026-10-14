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
	T get_val(int i) { return S[i + 1] - S[i]; }
};

template <typename T>
T Floor(T a, T b) { return a / b - (a % b && (a ^ b) < 0); }
template <typename T>
T Ceil(T a, T b) { return a / b + (a % b && (a ^ b) >= 0); }

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
// Begin include: "../../segment-tree/segment-tree-beats.hpp"

struct AngelBeats {
  using i64 = long long;
  static constexpr i64 INF = numeric_limits<i64>::max() / 2.1;

  struct alignas(32) Node {
    i64 sum = 0, g1 = 0, l1 = 0;
    i64 g2 = -INF, gc = 1, l2 = INF, lc = 1, add = 0;
  };

  vector<Node> v;
  i64 n, log;

  AngelBeats() {}
  AngelBeats(int _n) : AngelBeats(vector<i64>(_n)) {}
  AngelBeats(const vector<i64>& vc) {
    n = 1, log = 0;
    while (n < (int)vc.size()) n <<= 1, log++;
    v.resize(2 * n);
    for (i64 i = 0; i < (int)vc.size(); ++i) {
      v[i + n].sum = v[i + n].g1 = v[i + n].l1 = vc[i];
    }
    for (i64 i = n - 1; i; --i) update(i);
  }

  void range_chmin(int l, int r, i64 x) { inner_apply<1>(l, r, x); }
  void range_chmax(int l, int r, i64 x) { inner_apply<2>(l, r, x); }
  void range_add(int l, int r, i64 x) { inner_apply<3>(l, r, x); }
  void range_update(int l, int r, i64 x) { inner_apply<4>(l, r, x); }
  i64 range_min(int l, int r) { return inner_fold<1>(l, r); }
  i64 range_max(int l, int r) { return inner_fold<2>(l, r); }
  i64 range_sum(int l, int r) { return inner_fold<3>(l, r); }

 private:
  void update(int k) {
    Node& p = v[k];
    Node& l = v[k * 2 + 0];
    Node& r = v[k * 2 + 1];

    p.sum = l.sum + r.sum;

    if (l.g1 == r.g1) {
      p.g1 = l.g1;
      p.g2 = max(l.g2, r.g2);
      p.gc = l.gc + r.gc;
    } else {
      bool f = l.g1 > r.g1;
      p.g1 = f ? l.g1 : r.g1;
      p.gc = f ? l.gc : r.gc;
      p.g2 = max(f ? r.g1 : l.g1, f ? l.g2 : r.g2);
    }

    if (l.l1 == r.l1) {
      p.l1 = l.l1;
      p.l2 = min(l.l2, r.l2);
      p.lc = l.lc + r.lc;
    } else {
      bool f = l.l1 < r.l1;
      p.l1 = f ? l.l1 : r.l1;
      p.lc = f ? l.lc : r.lc;
      p.l2 = min(f ? r.l1 : l.l1, f ? l.l2 : r.l2);
    }
  }

  void push_add(int k, i64 x) {
    Node& p = v[k];
    p.sum += x << (log + __builtin_clz(k) - 31);
    p.g1 += x;
    p.l1 += x;
    if (p.g2 != -INF) p.g2 += x;
    if (p.l2 != INF) p.l2 += x;
    p.add += x;
  }
  void push_min(int k, i64 x) {
    Node& p = v[k];
    p.sum += (x - p.g1) * p.gc;
    if (p.l1 == p.g1) p.l1 = x;
    if (p.l2 == p.g1) p.l2 = x;
    p.g1 = x;
  }
  void push_max(int k, i64 x) {
    Node& p = v[k];
    p.sum += (x - p.l1) * p.lc;
    if (p.g1 == p.l1) p.g1 = x;
    if (p.g2 == p.l1) p.g2 = x;
    p.l1 = x;
  }
  void push(int k) {
    Node& p = v[k];
    if (p.add != 0) {
      push_add(k * 2 + 0, p.add);
      push_add(k * 2 + 1, p.add);
      p.add = 0;
    }
    if (p.g1 < v[k * 2 + 0].g1) push_min(k * 2 + 0, p.g1);
    if (p.l1 > v[k * 2 + 0].l1) push_max(k * 2 + 0, p.l1);

    if (p.g1 < v[k * 2 + 1].g1) push_min(k * 2 + 1, p.g1);
    if (p.l1 > v[k * 2 + 1].l1) push_max(k * 2 + 1, p.l1);
  }

  void subtree_chmin(int k, i64 x) {
    if (v[k].g1 <= x) return;
    if (v[k].g2 < x) {
      push_min(k, x);
      return;
    }
    push(k);
    subtree_chmin(k * 2 + 0, x);
    subtree_chmin(k * 2 + 1, x);
    update(k);
  }

  void subtree_chmax(int k, i64 x) {
    if (x <= v[k].l1) return;
    if (x < v[k].l2) {
      push_max(k, x);
      return;
    }
    push(k);
    subtree_chmax(k * 2 + 0, x);
    subtree_chmax(k * 2 + 1, x);
    update(k);
  }

  template <int cmd>
  inline void _apply(int k, i64 x) {
    if constexpr (cmd == 1) subtree_chmin(k, x);
    if constexpr (cmd == 2) subtree_chmax(k, x);
    if constexpr (cmd == 3) push_add(k, x);
    if constexpr (cmd == 4) subtree_chmin(k, x), subtree_chmax(k, x);
  }

  template <int cmd>
  void inner_apply(int l, int r, i64 x) {
    if (l == r) return;
    l += n, r += n;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }
    {
      int l2 = l, r2 = r;
      while (l < r) {
        if (l & 1) _apply<cmd>(l++, x);
        if (r & 1) _apply<cmd>(--r, x);
        l >>= 1;
        r >>= 1;
      }
      l = l2;
      r = r2;
    }
    for (int i = 1; i <= log; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }

  template <int cmd>
  inline i64 e() {
    if constexpr (cmd == 1) return INF;
    if constexpr (cmd == 2) return -INF;
    return 0;
  }

  template <int cmd>
  inline void op(i64& a, const Node& b) {
    if constexpr (cmd == 1) a = min(a, b.l1);
    if constexpr (cmd == 2) a = max(a, b.g1);
    if constexpr (cmd == 3) a += b.sum;
  }

  template <int cmd>
  i64 inner_fold(int l, int r) {
    if (l == r) return e<cmd>();
    l += n, r += n;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }
    i64 lx = e<cmd>(), rx = e<cmd>();
    while (l < r) {
      if (l & 1) op<cmd>(lx, v[l++]);
      if (r & 1) op<cmd>(rx, v[--r]);
      l >>= 1;
      r >>= 1;
    }
    if constexpr (cmd == 1) lx = min(lx, rx);
    if constexpr (cmd == 2) lx = max(lx, rx);
    if constexpr (cmd == 3) lx += rx;
    return lx;
  }
};

/**
 * @brief Range Chmin Chmax Add Update Range Min Max Sum Segment Tree Beats!
 * @docs docs/segment-tree/segment-tree-beats.md
 */
// End include: "../../segment-tree/segment-tree-beats.hpp"
// Begin include: "../../segment-tree/lazy-segment-tree-utility.hpp"

template <typename T, typename E, T (*f)(T, T), T (*g)(T, E), E (*h)(E, E), T (*ti)(), E (*ei)()>
struct LazySegmentTreeBase {
	int n, log, s;
	vector<T> val;
	vector<E> laz;

	explicit LazySegmentTreeBase() {}
	explicit LazySegmentTreeBase(const vector<T>& vc) { init(vc); }

	void init(const vector<T>& vc) {
		n = 1, log = 0, s = vc.size();
		while (n < s) n <<= 1, log++;
		val.resize(2 * n, ti());
		laz.resize(n, ei());
		for (int i = 0; i < s; ++i) val[i + n] = vc[i];
		for (int i = n - 1; i; --i) _update(i);
	}

	void update(int l, int r, const E& x) {
		if (l == r) return;
		l += n, r += n;
		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l) _push(l >> i);
			if (((r >> i) << i) != r) _push((r - 1) >> i);
		}
		{
			int l2 = l, r2 = r;
			while (l < r) {
				if (l & 1) _apply(l++, x);
				if (r & 1) _apply(--r, x);
				l >>= 1;
				r >>= 1;
			}
			l = l2;
			r = r2;
		}
		for (int i = 1; i <= log; i++) {
			if (((l >> i) << i) != l) _update(l >> i);
			if (((r >> i) << i) != r) _update((r - 1) >> i);
		}
	}

	T query(int l, int r) {
		if (l == r) return ti();
		l += n, r += n;
		T L = ti(), R = ti();
		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l) _push(l >> i);
			if (((r >> i) << i) != r) _push((r - 1) >> i);
		}
		while (l < r) {
			if (l & 1) L = f(L, val[l++]);
			if (r & 1) R = f(val[--r], R);
			l >>= 1;
			r >>= 1;
		}
		return f(L, R);
	}

	T query() { return val[1]; }

	void set_val(int k, const T& x) {
		k += n;
		for (int i = log; i >= 1; i--) {
			if (((k >> i) << i) != k || (((k + 1) >> i) << i) != (k + 1))
				_push(k >> i);
		}
		val[k] = x;
		for (int i = 1; i <= log; i++) {
			if (((k >> i) << i) != k || (((k + 1) >> i) << i) != (k + 1))
				_update(k >> i);
		}
	}

	void update_val(int k, const E& x) {
		k += n;
		for (int i = log; i >= 1; i--) {
			if (((k >> i) << i) != k || (((k + 1) >> i) << i) != (k + 1))
				_push(k >> i);
		}
		val[k] = g(val[k], x);
		for (int i = 1; i <= log; i++) {
			if (((k >> i) << i) != k || (((k + 1) >> i) << i) != (k + 1))
				_update(k >> i);
		}
	}

	T get_val(int k) {
		k += n;
		for (int i = log; i >= 1; i--) {
			if (((k >> i) << i) != k || (((k + 1) >> i) << i) != (k + 1))
				_push(k >> i);
		}
		return val[k];
	}

	template <class G>
	int max_right(int l, G check) {
		assert(0 <= l && l <= s);
		assert(check(ti()));
		if (l == n) return n;
		l += n;
		for (int i = log; i >= 1; i--) _push(l >> i);
		T sm = ti();
		do {
			while (l % 2 == 0) l >>= 1;
			if (!check(f(sm, val[l]))) {
				while (l < n) {
					_push(l);
					l = (2 * l);
					if (check(f(sm, val[l]))) {
						sm = f(sm, val[l]);
						l++;
					}
				}
				return l - n;
			}
			sm = f(sm, val[l]);
			l++;
		} while ((l & -l) != l);
		return s;
	}

	template <class G>
	int min_left(int r, G check) {
		assert(0 <= r && r <= s);
		assert(check(ti()));
		if (r == 0) return 0;
		r += n;
		for (int i = log; i >= 1; i--) _push((r - 1) >> i);
		T sm = ti();
		do {
			r--;
			while (r > 1 && (r % 2)) r >>= 1;
			if (!check(f(val[r], sm))) {
				while (r < n) {
					_push(r);
					r = (2 * r + 1);
					if (check(f(val[r], sm))) {
						sm = f(val[r], sm);
						r--;
					}
				}
				return r + 1 - n;
			}
			sm = f(val[r], sm);
		} while ((r & -r) != r);
		return 0;
	}

	private:
	void _push(int i) {
		if (laz[i] != ei()) {
			val[2 * i + 0] = g(val[2 * i + 0], laz[i]);
			val[2 * i + 1] = g(val[2 * i + 1], laz[i]);
			if (2 * i < n) {
				compose(laz[2 * i + 0], laz[i]);
				compose(laz[2 * i + 1], laz[i]);
			}
			laz[i] = ei();
		}
	}
	inline void _update(int i) { val[i] = f(val[2 * i + 0], val[2 * i + 1]); }
	inline void _apply(int i, const E& x) {
		if (x != ei()) {
			val[i] = g(val[i], x);
			if (i < n) compose(laz[i], x);
		}
	}
	inline void compose(E& a, const E& b) { a = a == ei() ? b : h(a, b); }
};

namespace SegmentTreeUtil {

template <typename T>
struct Pair {
	T first, second;
	Pair() = default;
	Pair(const T& f, const T& s) : first(f), second(s) {}
	operator T() const { return first; }
	friend ostream& operator<<(ostream& os, const Pair<T>& p) {
		os << T(p.first);
		return os;
	}
};

template <typename T>
T Mx(T a, T b) { return max(a, b); }
template <typename T>
T Mn(T a, T b) { return min(a, b); }
template <typename T>
T Update(T, T b) { return b; }
template <typename T>
T Add(T a, T b) { return a + b; }
template <typename T>
Pair<T> Psum(Pair<T> a, Pair<T> b) { return Pair<T>(a.first + b.first, a.second + b.second); }
template <typename T>
Pair<T> Padd(Pair<T> a, T b) { return Pair<T>(a.first + a.second * b, a.second); }
template <typename T>
Pair<T> PUpdate(Pair<T> a, T b) { return Pair<T>(a.second * b, a.second); }
template <typename T>
Pair<T> Pid() { return Pair<T>(T{}, T{}); }
template <typename T>
T Zero() { return T{}; }
template <typename T, T val>
T Const() { return val; }

template <typename T, T MINF>
struct AddMax_LazySegmentTree : LazySegmentTreeBase<T, T, Mx<T>, Add<T>, Add<T>, Const<T, MINF>, Zero<T>> {
	using base = LazySegmentTreeBase<T, T, Mx<T>, Add<T>, Add<T>, Const<T, MINF>, Zero<T>>;
	AddMax_LazySegmentTree(const vector<T>& v) : base(v) {}
};

template <typename T, T INF>
struct AddMin_LazySegmentTree : LazySegmentTreeBase<T, T, Mn<T>, Add<T>, Add<T>, Const<T, INF>, Zero<T>> {
	using base = LazySegmentTreeBase<T, T, Mn<T>, Add<T>, Add<T>, Const<T, INF>, Zero<T>>;
	AddMin_LazySegmentTree(const vector<T>& v) : base(v) {}
};

template <typename T>
struct AddSum_LazySegmentTree : LazySegmentTreeBase<Pair<T>, T, Psum<T>, Padd<T>, Add<T>, Pid<T>, Zero<T>> {
	using base = LazySegmentTreeBase<Pair<T>, T, Psum<T>, Padd<T>, Add<T>, Pid<T>, Zero<T>>;
	AddSum_LazySegmentTree(const vector<T>& v) {
		vector<Pair<T>> w(v.size());
		for (int i = 0; i < (int)v.size(); i++) w[i] = Pair<T>(v[i], 1);
		base::init(w);
	}
};

template <typename T, T MINF>
struct UpdateMax_LazySegmentTree : LazySegmentTreeBase<T, T, Mx<T>, Update<T>, Update<T>, Const<T, MINF>, Const<T, MINF>> {
	using base = LazySegmentTreeBase<T, T, Mx<T>, Update<T>, Update<T>, Const<T, MINF>, Const<T, MINF>>;
	UpdateMax_LazySegmentTree(const vector<T>& v) : base(v) {}
};

template <typename T, T INF>
struct UpdateMin_LazySegmentTree : LazySegmentTreeBase<T, T, Mn<T>, Update<T>, Update<T>, Const<T, INF>, Const<T, INF>> {
	using base = LazySegmentTreeBase<T, T, Mn<T>, Update<T>, Update<T>, Const<T, INF>, Const<T, INF>>;
	UpdateMin_LazySegmentTree(const vector<T>& v) : base(v) {}
};

template <typename T, T UNUSED_VALUE>
struct UpdateSum_LazySegmentTree : LazySegmentTreeBase<Pair<T>, T, Psum<T>, PUpdate<T>, Update<T>, Pid<T>, Const<T, UNUSED_VALUE>> {
	using base = LazySegmentTreeBase<Pair<T>, T, Psum<T>, PUpdate<T>, Update<T>, Pid<T>, Const<T, UNUSED_VALUE>>;
	UpdateSum_LazySegmentTree(const vector<T>& v) {
		vector<Pair<T>> w(v.size());
		for (int i = 0; i < (int)v.size(); i++) w[i] = Pair<T>(v[i], 1);
		base::init(w);
	}
};

}  // namespace SegmentTreeUtil
using SegmentTreeUtil::AddMax_LazySegmentTree;
using SegmentTreeUtil::AddMin_LazySegmentTree;
using SegmentTreeUtil::AddSum_LazySegmentTree;
using SegmentTreeUtil::UpdateMax_LazySegmentTree;
using SegmentTreeUtil::UpdateMin_LazySegmentTree;
using SegmentTreeUtil::UpdateSum_LazySegmentTree;

/**
 * @brief 使用頻度の高い遅延セグメント木
 * @docs docs/segment-tree/lazy-segment-tree-utility.md
 */
// End include: "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	inl(N,M);
	vl A(N); in(A);
	vl L(N);
	{
		AngelBeats seg(N);
		seg.range_update(0,N,N);
		while(M--){
			inl(l,r); --l;
			seg.range_chmin(l,r,l);
		}
		rep(i,N)L[i]=seg.range_sum(i,i+1);
	}

	UpdateMax_LazySegmentTree<ll,-infLL> seg(vl(N,0));
	rep(i,N){
		ll ans=seg.query(0,L[i]);
		amax(ans,0);
		ans+=A[i];
		seg.update_val(i,ans);
	}
	out(seg.query());
}