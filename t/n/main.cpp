#line 2 "/root/lib/template/template.hpp"
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
#line 1 "/root/lib/template/util.hpp"
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
	for (int i = -M; i <= M; i++) for (int j = 1; j <= M; j++) {
		if ((mint)i / j == a) {
			if (j == 1) cout << i << "\n";
			else cout << i << "/" << j << "\n";
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
		for (int i = -M; i <= M; i++) {
			for (int j = 1; j <= M; j++) if ((mint)i / j == A[pos]) {
				if (j == 1) cout << i << (pos == N - 1 ? "\n" : " ");
				else cout << i << "/" << j << (pos == N - 1 ? "\n" : " ");
				fn = true;
				break;
			}
			if (fn) break;
		}
		if (!fn) cout << "NF" << (pos == N - 1 ? "\n" : " ");
	}
}

} // namespace yamada

#line 58 "/root/lib/template/template.hpp"

// bit operation
#line 1 "/root/lib/template/bitop.hpp"
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
#line 61 "/root/lib/template/template.hpp"

// inout
#line 1 "/root/lib/template/inout.hpp"
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
#line 64 "/root/lib/template/template.hpp"

// macro
#line 1 "/root/lib/template/macro.hpp"
#define each(x, v) for (auto&& x : v)
#define each2(x, y, v) for (auto&& [x, y] : v)
#define each3(x, y, z, v) for (auto&& [x, y, z] : v)
#define all(v) (v).begin(), (v).end()

#define rep1(a) for (long long i = 0; i < (long long)(a); ++i)
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
#line 67 "/root/lib/template/template.hpp"

namespace yamada {
void solve();
}
int main() { yamada::solve(); }
#line 2 "/root/lib/geometry/line.hpp"

#line 2 "/root/lib/geometry/geometry-base.hpp"

#line 9 "/root/lib/geometry/geometry-base.hpp"
using namespace std;

using Real = long double;
constexpr Real EPS = 1e-10;
constexpr Real pi = 3.141592653589793238462643383279L;
bool equals(Real a, Real b) { return fabs(b - a) < EPS; }
int sign(Real a) { return equals(a, 0) ? 0 : a > 0 ? 1 : -1; }

template <typename R>
struct PointBase {
  using P = PointBase;
  R x, y;
  PointBase() : x(0), y(0) {}
  PointBase(R _x, R _y) : x(_x), y(_y) {}
  template <typename T, typename U>
  PointBase(const pair<T, U>& p) : x(p.first), y(p.second) {}

  P operator+(const P& r) const { return {x + r.x, y + r.y}; }
  P operator-(const P& r) const { return {x - r.x, y - r.y}; }
  P operator*(R r) const { return {x * r, y * r}; }
  P operator/(R r) const { return {x / r, y / r}; }

  P& operator+=(const P& r) { return (*this) = (*this) + r; }
  P& operator-=(const P& r) { return (*this) = (*this) - r; }
  P& operator*=(R r) { return (*this) = (*this) * r; }
  P& operator/=(R r) { return (*this) = (*this) / r; }

  bool operator<(const P& r) const { return x != r.x ? x < r.x : y < r.y; }
  bool operator==(const P& r) const { return x == r.x and y == r.y; }
  bool operator!=(const P& r) const { return !((*this) == r); }

  P rotate(R rad) const {
    return {x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)};
  }

  R real() const { return x; }
  R imag() const { return y; }
  friend R real(const P& p) { return p.x; }
  friend R imag(const P& p) { return p.y; }
  friend R dot(const P& l, const P& r) { return l.x * r.x + l.y * r.y; }
  friend R cross(const P& l, const P& r) { return l.x * r.y - l.y * r.x; }
  friend R abs(const P& p) { return sqrt(p.x * p.x + p.y * p.y); }
  friend R norm(const P& p) { return p.x * p.x + p.y * p.y; }
  friend R arg(const P& p) { return atan2(p.y, p.x); }

  friend istream& operator>>(istream& is, P& p) {
    R a, b;
    is >> a >> b;
    p = P{a, b};
    return is;
  }
  friend ostream& operator<<(ostream& os, const P& p) {
    return os << p.x << " " << p.y;
  }
};
using Point = PointBase<Real>;
using Points = vector<Point>;

// ccw, 点の進行方向
int ccw(const Point& a, const Point& b, const Point& c) {
  Point x = b - a, y = c - a;
  if (cross(x, y) > EPS) return +1;                 // 反時計回り
  if (cross(x, y) < -EPS) return -1;                // 時計回り
  if (min(norm(x), norm(y)) < EPS * EPS) return 0;  // c=a または c=b
  if (dot(x, y) < EPS) return +2;                   // c-a-b の順で一直線
  if (norm(x) < norm(y)) return -2;                 // a-b-c の順で一直線
  return 0;                                         // a-c-b の順で一直線
}
#line 2 "/root/lib/geometry/polygon.hpp"

#line 4 "/root/lib/geometry/polygon.hpp"

using Polygon = vector<Point>;

// 多角形の内部に点があるか？
// OUT : 0, ON : 1, IN : 2
int contains_polygon(const Polygon &Q, const Point &p) {
  bool in = false;
  for (int i = 0; i < (int)Q.size(); i++) {
    Point a = Q[i] - p, b = Q[(i + 1) % Q.size()] - p;
    if (imag(a) > imag(b)) swap(a, b);
    if (sign(imag(a)) <= 0 && 0 < sign(imag(b)) && sign(cross(a, b)) < 0)
      in = !in;
    if (equals(cross(a, b), 0) && sign(dot(a, b)) <= 0) return 1;
  }
  return in ? 2 : 0;
}

// 多角形の面積
Real area(const Polygon &p) {
  Real A = 0;
  for (int i = 0; i < (int)p.size(); ++i) {
    A += cross(p[i], p[(i + 1) % p.size()]);
  }
  return A * 0.5;
}

// 頂点集合から凸包を生成
// boundary : 周上の点も列挙する場合 true
template <bool boundary = false>
Polygon convex_hull(vector<Point> ps) {
  sort(begin(ps), end(ps));
  ps.erase(unique(begin(ps), end(ps)), end(ps));
  int n = ps.size(), k = 0;
  if (n <= 2) return ps;
  vector<Point> ch(2 * n);
  // 反時計周り
  Real th = boundary ? -EPS : +EPS;
  for (int i = 0; i < n; ch[k++] = ps[i++]) {
    while (k >= 2 && cross(ch[k - 1] - ch[k - 2], ps[i] - ch[k - 1]) < th) --k;
  }
  for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = ps[i--]) {
    while (k >= t && cross(ch[k - 1] - ch[k - 2], ps[i] - ch[k - 1]) < th) --k;
  }
  ch.resize(k - 1);
  return ch;
}

// 凸包の内部に点があるか？
// OUT : 0, ON : 1, IN : 2
int contains_convex(const Polygon &C, const Point &p) {
  int N = C.size();
  auto b1 = cross(C[1] - C[0], p - C[0]);
  auto b2 = cross(C[N - 1] - C[0], p - C[0]);
  if (b1 < -EPS or b2 > EPS) return 0;
  int L = 1, R = N - 1;
  while (L + 1 < R) {
    int M = (L + R) / 2;
    (cross(p - C[0], C[M] - C[0]) >= 0 ? R : L) = M;
  }
  auto v = cross(C[L] - p, C[R] - p);
  if (equals(v, 0)) {
    return 1;
  } else if (v > 0) {
    return equals(b1, 0) or equals(b2, 0) ? 1 : 2;
  } else {
    return 0;
  }
}

// 凸包が与えられるので最遠点対を返す
// 返り値：頂点番号のペア
pair<int, int> convex_polygon_diameter(const Polygon &p) {
  int N = (int)p.size();
  int is = 0, js = 0;
  for (int i = 1; i < N; i++) {
    if (imag(p[i]) > imag(p[is])) is = i;
    if (imag(p[i]) < imag(p[js])) js = i;
  }
  Real maxdis = norm(p[is] - p[js]);

  int maxi, maxj, i, j;
  i = maxi = is;
  j = maxj = js;
  do {
    if (cross(p[(i + 1) % N] - p[i], p[(j + 1) % N] - p[j]) >= 0) {
      j = (j + 1) % N;
    } else {
      i = (i + 1) % N;
    }
    if (norm(p[i] - p[j]) > maxdis) {
      maxdis = norm(p[i] - p[j]);
      maxi = i;
      maxj = j;
    }
  } while (i != is || j != js);
  return minmax(maxi, maxj);
}
#line 5 "/root/lib/geometry/line.hpp"

struct Line {
  Point a, b;

  Line() = default;
  Line(const Point &_a, const Point &_b) : a(_a), b(_b) {}
  // Ax+By=C
  Line(const Real &A, const Real &B, const Real &C) {
    if (equals(A, 0)) {
      assert(!equals(B, 0));
      a = Point(0, C / B);
      b = Point(1, C / B);
    } else if (equals(B, 0)) {
      a = Point(C / A, 0);
      b = Point(C / A, 1);
    } else if (equals(C, 0)) {
      a = Point(0, C / B);
      b = Point(1, (C - A) / B);
    } else {
      a = Point(0, C / B);
      b = Point(C / A, 0);
    }
  }
  friend ostream &operator<<(ostream &os, const Line &l) {
    return os << l.a << " to " << l.b;
  }
  friend istream &operator>>(istream &is, Line &l) { return is >> l.a >> l.b; }
};
using Lines = vector<Line>;

bool is_parallel(const Line &a, const Line &b) {
  return equals(cross(a.b - a.a, b.b - b.a), 0);
}
bool is_orthogonal(const Line &a, const Line &b) {
  return equals(dot(a.a - a.b, b.a - b.b), 0);
}
Point cross_point_ll(const Line &l, const Line &m) {
  Real A = cross(l.b - l.a, m.b - m.a);
  Real B = cross(l.b - l.a, l.b - m.a);
  if (equals(abs(A), 0) && equals(abs(B), 0)) return m.a;
  return m.a + (m.b - m.a) * B / A;
}
bool is_intersect_ll(const Line &l, const Line &m) {
  Real A = cross(l.b - l.a, m.b - m.a);
  Real B = cross(l.b - l.a, l.b - m.a);
  if (equals(abs(A), 0) && equals(abs(B), 0)) return true;
  return !is_parallel(l, m);
}

// 直線に頂点から垂線を下ろした時の交点
Point projection(const Line &l, const Point &p) {
  Real t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + (l.a - l.b) * t;
}

// 凸包を直線で切った時の片方 (直線 a->b の進行方向左側) を返す
Polygon convex_polygon_cut(const Polygon &U, const Line &l) {
  Polygon ret;
  for (int i = 0; i < (int)U.size(); i++) {
    const Point &now = U[i];
    const Point &nxt = U[(i + 1) % U.size()];
    auto cf = cross(l.a - now, l.b - now);
    auto cs = cross(l.a - nxt, l.b - nxt);
    if (sign(cf) >= 0) {
      ret.emplace_back(now);
    }
    if (sign(cf) * sign(cs) < 0) {
      ret.emplace_back(cross_point_ll(Line(now, nxt), l));
    }
  }
  return ret;
}
#line 3 "a.cpp"

void yamada::solve()
{
	inl(N,M);
	Polygon S(N),T(M); in(S,T);

	Points inter;
	rep(i,N)rep(j,M){
		Line l(S[i],S[(i+1)%N]);
		Line m(T[j],T[(j+1)%M]);
		if(cross(l.b-l.a,m.a-l.a)*cross(l.b-l.a,m.b-l.a)>=0)continue;
		if(cross(m.b-m.a,l.a-m.a)*cross(m.b-m.a,l.b-m.a)>=0)continue;

		Point M=cross_point_ll(l,m);
		inter.eb(M);
	}

	each(p,S){
		if(contains_convex(T,p))inter.eb(p);
	}
	each(p,T){
		if(contains_convex(S,p))inter.eb(p);
	}

	Polygon ans=convex_hull(inter);
	out(area(ans));
}
