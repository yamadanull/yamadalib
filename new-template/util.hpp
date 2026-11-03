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

template <integral T, typename F>
T bisearch(T ok, T ng, F f) { // ok < ng でも ok > ng でも可能 // f(ok) && !f(ng) が必要
	while (abs(ok - ng) > 1) { T mid = (ok + ng) / 2; (f(mid) ? ok : ng) = mid; } 
	return ok;
}
template <integral T, typename F> // 判定回数は上限を決め打ちした場合の高々２倍程度
T bisearch(T l, F f) { // !f(l) && f(inf) が必要 (0000...1111...)
	T r = l + 1;
	while (!f(r)) r += r - l;
	return bisearch(r, l, f);
}
template <integral T, typename F> 
T bisearch(F f) { return bisearch(T(0), f); }

template <floating_point T, typename F>
T bisearch(T ok, T ng, F f, int iter = 100) {
	while (iter--) { T mid = (ok + ng) / 2; (f(mid) ? ok : ng) = mid; } 
	return ng;
}
template <floating_point T, typename F>
T bisearch(T l, F f, int iter = 100) {
	T r = l + 1;
	while (!f(r)) r += r - l;
	return bisearch(r, l, f, iter);
}
template <floating_point T, typename F>
T bisearch(F f, int iter = 100) { return bisearch(T(0), f, iter); }

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
