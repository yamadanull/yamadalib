/**
 * date   : 2026-10-12 17:24:04
 * author : yamadanull
 */

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#line 1 "src/structure/segtree/rollback/rollback_lazysegtree.hpp"



#include <array>
#include <cstddef>
#include <functional>
#include <limits>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>
#line 1 "src/structure/types/monoid/monoid_act.hpp"


#line 1 "src/structure/types/monoid/monoid.hpp"



#line 5 "src/structure/types/monoid/monoid.hpp"

template<auto op_func, auto e_func>
struct Monoid{
    using S = std::decay_t<decltype(e_func())>;
    constexpr S op(S a, S b)const{
        return op_func(a,b);
    }
    constexpr S e()const{
        return e_func();
    }
};


#line 4 "src/structure/types/monoid/monoid_act.hpp"

template<auto op_func, auto e_func, auto mapping_func, auto composition_func, auto id_func>
struct Monoid_Act: Monoid<op_func,e_func>{
    using S = std::decay_t<decltype(e_func())>;
    using T = std::decay_t<decltype(id_func())>;
    constexpr S mapping(T f, S x)const{
        return mapping_func(f, x);
    }
    constexpr T composition(T f, T g)const{
        return composition_func(f, g);
    }
    constexpr T id()const{
        return id_func();
    }
};


#line 14 "src/structure/segtree/rollback/rollback_lazysegtree.hpp"

template<auto Monoid_act, int MAX_SIZE, int MAX_UPDATE>
struct RollbackLazySegtree{
    static_assert(MAX_SIZE > 0);
    static_assert(MAX_UPDATE >= 0);

    using S = typename std::remove_cvref_t<decltype(Monoid_act)>::S;
    using T = typename std::remove_cvref_t<decltype(Monoid_act)>::T;
    using Snapshot = int;

    static constexpr int sz = []{
        int res = 1;
        while(res < MAX_SIZE){
            res <<= 1;
        }
        return res;
    }();

    static constexpr int height = []{
        int res = 1;
        int h = 0;
        while(res < MAX_SIZE){
            res <<= 1;
            h++;
        }
        return h;
    }();

private:
    static constexpr std::size_t changes_per_update =
        static_cast<std::size_t>(8 * height) + 4;

    static_assert(
        static_cast<std::size_t>(MAX_UPDATE) <=
        std::numeric_limits<std::size_t>::max() / changes_per_update
    );

    static constexpr std::size_t history_capacity =
        static_cast<std::size_t>(MAX_UPDATE) * changes_per_update;

    struct DataHistory{
        int index;
        S value;
    };

    struct LazyHistory{
        int index;
        T value;
    };

    struct Operation{
        int data_size;
        int lazy_size;
    };

    int _n = 0;
    int operation_count = 0;
    int data_history_size = 0;
    int lazy_history_size = 0;

    std::array<S, 2 * sz> data;
    std::array<T, sz> lazy;
    std::array<std::optional<DataHistory>, history_capacity> data_history;
    std::array<std::optional<LazyHistory>, history_capacity> lazy_history;
    std::array<Operation, MAX_UPDATE> operation_history;

    void initialize(int n){
        if(n < 0 || MAX_SIZE < n)[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: range violation (constructor)."
            );
        }
        _n = n;
        data.fill(Monoid_act.e());
        lazy.fill(Monoid_act.id());
    }

    void build(){
        for(int k = sz - 1; k > 0; k--){
            data[k] = Monoid_act.op(data[2 * k], data[2 * k + 1]);
        }
    }

    void write_data(int k, const S& value){
        if(
            static_cast<std::size_t>(data_history_size) >= history_capacity
        )[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: history capacity exceeded (update)."
            );
        }
        data_history[data_history_size].emplace(DataHistory{k, data[k]});
        data[k] = value;
        data_history_size++;
    }

    void write_lazy(int k, const T& value){
        if(
            static_cast<std::size_t>(lazy_history_size) >= history_capacity
        )[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: history capacity exceeded (update)."
            );
        }
        lazy_history[lazy_history_size].emplace(LazyHistory{k, lazy[k]});
        lazy[k] = value;
        lazy_history_size++;
    }

    void restore(Operation snapshot){
        while(snapshot.data_size < data_history_size){
            --data_history_size;
            const auto& entry = *data_history[data_history_size];
            data[entry.index] = entry.value;
            data_history[data_history_size].reset();
        }
        while(snapshot.lazy_size < lazy_history_size){
            --lazy_history_size;
            const auto& entry = *lazy_history[lazy_history_size];
            lazy[entry.index] = entry.value;
            lazy_history[lazy_history_size].reset();
        }
    }

    void update(int k){
        S value = Monoid_act.op(data[2 * k], data[2 * k + 1]);
        write_data(k, value);
    }

    void all_apply(int k, const T& f){
        S value = Monoid_act.mapping(f, data[k]);
        if(k < sz){
            T action = Monoid_act.composition(f, lazy[k]);
            write_data(k, value);
            write_lazy(k, action);
        }else{
            write_data(k, value);
        }
    }

    void push(int k){
        T action = lazy[k];

        if (action == Monoid_act.id()) return;

        all_apply(2 * k, action);
        all_apply(2 * k + 1, action);
        write_lazy(k, Monoid_act.id());
    }

    void set_impl(int k, int l, int r, int p, const S& x){
        if(r - l == 1){
            write_data(k, x);
            return;
        }
        push(k);
        int mid = l + (r - l) / 2;
        if(p < mid){
            set_impl(2 * k, l, mid, p, x);
        }else{
            set_impl(2 * k + 1, mid, r, p, x);
        }
        update(k);
    }

    void apply_impl(
        int k,
        int l,
        int r,
        int ql,
        int qr,
        const T& f
    ){
        if(ql <= l && r <= qr){
            all_apply(k, f);
            return;
        }
        push(k);
        int mid = l + (r - l) / 2;
        if(ql < mid){
            apply_impl(2 * k, l, mid, ql, qr, f);
        }
        if(mid < qr){
            apply_impl(2 * k + 1, mid, r, ql, qr, f);
        }
        update(k);
    }

    S prod_impl(
        int k,
        int l,
        int r,
        int ql,
        int qr,
        const T& carry
    ) const{
        if(r <= ql || qr <= l){
            return Monoid_act.e();
        }
        if(ql <= l && r <= qr){
            return Monoid_act.mapping(carry, data[k]);
        }
        T next = k < sz
            ? Monoid_act.composition(carry, lazy[k])
            : carry;
        int mid = l + (r - l) / 2;
        return Monoid_act.op(
            prod_impl(2 * k, l, mid, ql, qr, next),
            prod_impl(2 * k + 1, mid, r, ql, qr, next)
        );
    }

    template<class F, class... Args>
    int max_right_impl(
        int k,
        int l,
        int r,
        int ql,
        const T& carry,
        S& sm,
        F& f,
        Args&... args
    ) const{
        if(r <= ql || _n <= l){
            return -1;
        }
        if(ql <= l && r <= _n){
            S value = Monoid_act.mapping(carry, data[k]);
            S next_value = Monoid_act.op(sm, value);
            if(std::invoke(f, next_value, args...)){
                sm = next_value;
                return -1;
            }
            if(r - l == 1){
                return l;
            }
        }
        T next = k < sz
            ? Monoid_act.composition(carry, lazy[k])
            : carry;
        int mid = l + (r - l) / 2;
        int res = max_right_impl(
            2 * k, l, mid, ql, next, sm, f, args...
        );
        if(res != -1){
            return res;
        }
        return max_right_impl(
            2 * k + 1, mid, r, ql, next, sm, f, args...
        );
    }

    template<class F, class... Args>
    int min_left_impl(
        int k,
        int l,
        int r,
        int qr,
        const T& carry,
        S& sm,
        F& f,
        Args&... args
    ) const{
        if(qr <= l || _n <= l){
            return -1;
        }
        if(r <= qr && r <= _n){
            S value = Monoid_act.mapping(carry, data[k]);
            S next_value = Monoid_act.op(value, sm);
            if(std::invoke(f, next_value, args...)){
                sm = next_value;
                return -1;
            }
            if(r - l == 1){
                return r;
            }
        }
        T next = k < sz
            ? Monoid_act.composition(carry, lazy[k])
            : carry;
        int mid = l + (r - l) / 2;
        int res = min_left_impl(
            2 * k + 1, mid, r, qr, next, sm, f, args...
        );
        if(res != -1){
            return res;
        }
        return min_left_impl(
            2 * k, l, mid, qr, next, sm, f, args...
        );
    }

    template<class F>
    void perform_update(F&& update_function){
        if(operation_count == MAX_UPDATE)[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: capacity violation (update)."
            );
        }
        Operation snapshot{data_history_size, lazy_history_size};
        try{
            std::forward<F>(update_function)();
        }catch(...){
            restore(snapshot);
            throw;
        }
        operation_history[operation_count++] = snapshot;
    }

public:
    RollbackLazySegtree(const RollbackLazySegtree&) = delete;
    RollbackLazySegtree& operator=(const RollbackLazySegtree&) = delete;
    RollbackLazySegtree(RollbackLazySegtree&&) = delete;
    RollbackLazySegtree& operator=(RollbackLazySegtree&&) = delete;

    explicit RollbackLazySegtree(int n = MAX_SIZE){
        initialize(n);
        build();
    }

    explicit RollbackLazySegtree(const std::vector<S>& v){
        if(v.size() > static_cast<std::size_t>(MAX_SIZE))[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: range violation (constructor)."
            );
        }
        initialize(static_cast<int>(v.size()));
        for(int k = 0; k < _n; k++){
            data[k + sz] = v[static_cast<std::size_t>(k)];
        }
        build();
    }

    template<std::size_t N>
    explicit RollbackLazySegtree(const std::array<S, N>& v){
        if(N > static_cast<std::size_t>(MAX_SIZE))[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: range violation (constructor)."
            );
        }
        initialize(static_cast<int>(N));
        for(int k = 0; k < _n; k++){
            data[k + sz] = v[static_cast<std::size_t>(k)];
        }
        build();
    }

    int size() const{
        return _n;
    }

    int history_size() const{
        return operation_count;
    }

    bool can_undo() const{
        return operation_count != 0;
    }

    void set(int k, const S& x){
        if(k < 0 || _n <= k)[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: range violation (set)."
            );
        }
        perform_update([&]{
            set_impl(1, 0, sz, k, x);
        });
    }

    void apply(int k, const T& f){
        if(k < 0 || _n <= k)[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: range violation (apply)."
            );
        }
        perform_update([&]{
            apply_impl(1, 0, sz, k, k + 1, f);
        });
    }

    void apply(int l, int r, const T& f){
        if(l < 0 || r < l || _n < r)[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: range violation (apply)."
            );
        }
        perform_update([&]{
            if(l != r){
                apply_impl(1, 0, sz, l, r, f);
            }
        });
    }

    S get(int k) const{
        if(k < 0 || _n <= k)[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: range violation (get)."
            );
        }
        return prod_impl(1, 0, sz, k, k + 1, Monoid_act.id());
    }

    S prod(int l, int r) const{
        if(l < 0 || r < l || _n < r)[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: range violation (prod)."
            );
        }
        return prod_impl(1, 0, sz, l, r, Monoid_act.id());
    }

    S all_prod() const{
        return data[1];
    }

    int max_right(int l, auto f, auto&&... args) const{
        if(l < 0 || _n < l)[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: range violation (max_right)."
            );
        }
        if(!std::invoke(f, Monoid_act.e(), args...))[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: f(e) must be true (max_right)."
            );
        }
        if(l == _n){
            return _n;
        }
        S sm = Monoid_act.e();
        int res = max_right_impl(
            1, 0, sz, l, Monoid_act.id(), sm, f, args...
        );
        return res == -1 ? _n : res;
    }

    int min_left(int r, auto f, auto&&... args) const{
        if(r < 0 || _n < r)[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: range violation (min_left)."
            );
        }
        if(!std::invoke(f, Monoid_act.e(), args...))[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: f(e) must be true (min_left)."
            );
        }
        if(r == 0){
            return 0;
        }
        S sm = Monoid_act.e();
        int res = min_left_impl(
            1, 0, sz, r, Monoid_act.id(), sm, f, args...
        );
        return res == -1 ? 0 : res;
    }

    Snapshot snapshot() const{
        return operation_count;
    }

    void undo(){
        if(!can_undo())[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: undo history is empty (undo)."
            );
        }
        --operation_count;
        restore(operation_history[operation_count]);
    }

    void rollback(Snapshot snapshot){
        if(snapshot < 0 || operation_count < snapshot)[[unlikely]]{
            throw std::runtime_error(
                "library assertion fault: range violation (rollback)."
            );
        }
        while(snapshot < operation_count){
            undo();
        }
    }
};



using namespace std;

using U32 = uint32_t;
using U64 = uint64_t;

static constexpr int BITS = 30;
static constexpr U32 VALUE_MASK = (U32(1) << BITS) - 1;

// 問題の制約に合わせて設定
static constexpr int MAX_N = 100000;
static constexpr int MAX_UPDATE = 1000;


// ============================================================
// RollbackLazySegtree 用の作用付きモノイド
// ============================================================


static int clamp_index(U32 value, int n) {
    if (value < 1) return 1;
    if (value > static_cast<U32>(n)) return n;
    return static_cast<int>(value);
}

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

template <typename T, typename U>
struct pr : pair<T, U> {
	template <typename... Args>
	pr(Args... args) : pair<T, U>(args...) {}

	using pair<T, U>::first;
	using pair<T, U>::second;

	pr &operator+=(const pr &r) { first += r.first; second += r.second; return *this; }
	pr &operator-=(const pr &r) { first -= r.first; second -= r.second; return *this; }
	pr &operator*=(const pr &r) { first *= r.first; second *= r.second; return *this; }
	template <typename S>
	pr &operator*=(const S &r) { first *= r, second *= r; return *this; }
	pr operator+(const pr &r) const { return pr(*this) += r; }
	pr operator-(const pr &r) const { return pr(*this) -= r; }
	pr operator*(const pr &r) const { return pr(*this) *= r; }
	template <typename S>
	pr operator*(const S &r) const { return pr(*this) *= r; }
	pr operator-() const { return pr{-first, -second}; }
};

using pint = pr<int, int>;
using pl = pr<ll, ll>;
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

template <typename T>
inline long long Sum(const vector<T> &v) { return accumulate(v.begin(), v.end(), T(0)); }

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
	auto dfs = [&](this auto dfs, int i) -> void {
		if (i == (int)A.size()) { f(cur); return; }
		for (int j = 0; j < A[i]; j++) cur.emplace_back(j), dfs(i + 1), cur.pop_back();
	}; dfs(0);
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
T Floor(T a, T b) { assert(b != 0); if (b < 0) a = -a, b = -b; return a / b - (a % b < 0); }
template <typename T>
T Under(T a, T b) { assert(b != 0); if (b < 0) a = -a, b = -b; return a / b - (a % b <= 0); }
template <typename T>
T Ceil (T a, T b) { assert(b != 0); if (b < 0) a = -a, b = -b; return a / b + (a % b > 0); }
template <typename T>
T Over (T a, T b) { assert(b != 0); if (b < 0) a = -a, b = -b; return a / b + (a % b >= 0); }
template <typename T>
T Modulo(T a, T b) { assert(b > 0); T c = a % b; return c < 0 ? c + b : c; }

template <typename T>
pair<T, T> DivMod(T a, T b) {
	assert(b > 0);
	T q = a / b, r = a % b;
	if (r < 0) --q, r += b;
	return {q, r};
}

string rds() { string S; cin >> S; return S; }
int rdi() { int x; cin >> x; return x; }
char rdc() { char c; cin >> c; return c; }
long long rdl() { long long x; cin >> x; return x; }

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
	return "!NF";
}

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
istream &operator>>(istream &is, __int128_t &x) {
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
istream &operator>>(istream &is, __uint128_t &x) {
	string S; is >> S;
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
	ranges::reverse(S);
	return os << S;
}
ostream &operator<<(ostream &os, __uint128_t x) {
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
ostream& operator<<(ostream& os, const T& t) {
	bool f{};
	apply([&](const auto&... x) {
		(..., (os << (exchange(f, 1) ? " " : "") << x));
	}, t);
	return os;
}
template <TupleLike T>
istream& operator>>(istream& is, T&& t) {
	apply([&](auto&... x) { (..., (is >> x)); }, t);
	return is;
}
template <ListLike R>
ostream& operator<<(ostream& os, const R& a) {
	bool f{};
	for (const auto& x : a) os << (exchange(f, 1) ? " " : "") << x;
	return os;
}
template <ListLike R>
istream& operator>>(istream& is, R&& a) {
	for (auto&& x : a) is >> x;
	return is;
}

template <class... T>
void IN(T&&... x) { (cin >> ... >> x); }
template <class... T>
void OUT (const T&... x) { bool f{}; (..., (cout << (exchange(f, 1) ? " " : "") << x)); cout << '\n'; }
template <class... T> // "Flush after OUT"
void FOUT(const T&... x) { bool f{}; (..., (cout << (exchange(f, 1) ? " " : "") << x)); cout << endl; }
template <class... T> // "WithOUT ln"
void WOUT(const T&... x) { bool f{}; (..., (cout << (exchange(f, 1) ? " " : "") << x)); }

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
#define ERR(...) \
	do { \
		std::cerr << "## " << #__VA_ARGS__ << " = "; \
		yamada::DebugImpl::trace(__VA_ARGS__); \
	} while (0)
#else
#define ERR(...) (void(0))
#endif
// ===== END INCLUDE: io.hpp =====
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

namespace rg = ranges;
namespace vw = views;
using namespace placeholders;
} // namespace yamada
// ===== END INCLUDE: ranges.hpp =====
// ===== BEGIN INCLUDE: macro.hpp =====
#define FOR_E1(x, v) for (auto&& x : v)
#define FOR_E2(x, y, v) for (auto&& [x, y] : v)
#define FOR_E3(x, y, z, v) for (auto&& [x, y, z] : v)
#define FOR_E4(x, y, z, w, v) for (auto&& [x, y, z, w] : v)
#define OVERLOAD5(a, b, c, d, e, f, ...) f
#define FOR_E(...) OVERLOAD5(__VA_ARGS__, FOR_E4, FOR_E3, FOR_E2, FOR_E1)(__VA_ARGS__)

#define FOR1(a) for (long long _ = 0; _ < (long long)(a); ++_)
#define FOR2(i, a) for (long long i = 0; i < (long long)(a); ++i)
#define FOR3(i, a, b) for (long long i = a; i < (long long)(b); ++i)
#define FOR4(i, a, b, c) for (long long i = a; i < (long long)(b); i += c)
#define OVERLOAD4(a, b, c, d, e, ...) e
#define FOR(...) OVERLOAD4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)

#define FOR_R1(a) for (long long i = (long long)(a)-1; i >= 0LL; --i)
#define FOR_R2(i, a) for (long long i = (long long)(a)-1; i >= 0LL; --i)
#define FOR_R3(i, a, b) for (long long i = (long long)(b)-1; i >= (long long)(a); --i)
#define OVERLOAD3(a, b, c, d, ...) d
#define FOR_R(...) OVERLOAD3(__VA_ARGS__, FOR_R3, FOR_R2, FOR_R1)(__VA_ARGS__)

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

#define CHAR(...) char __VA_ARGS__; IN(__VA_ARGS__)
#define INT(...) int __VA_ARGS__; IN(__VA_ARGS__)
#define LL(...) long long __VA_ARGS__; IN(__VA_ARGS__)
#define STR(...) std::string __VA_ARGS__; IN(__VA_ARGS__)
#define ZIN(...) for (auto&& [__VA_ARGS__] : std::views::zip(__VA_ARGS__)) IN(__VA_ARGS__)
#define DIE(...) do { yamada::OUT(__VA_ARGS__); return; } while (0)
// ===== END INCLUDE: macro.hpp =====

namespace yamada {
void solve();
}
int main() { yamada::solve(); }
// ===== END INCLUDE: ../../template/template.hpp =====
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
// ===== BEGIN INCLUDE: ../../segment-tree/segment-tree-divide-and-conquer.hpp =====
// F: query info
template <typename F>
struct SegmentTreeDandC {
	int Q, width;
	vector<vector<F>> seg;

	SegmentTreeDandC(int _Q) : Q(_Q) {
		width = 1;
		while (width < Q) width *= 2;
		seg.resize(width * 2);
	}

	void apply(int l, int r, F q) {
		l += width;
		r += width;
		while (l < r) {
			if (l & 1) seg[l++].emplace_back(q);
			if (r & 1) seg[--r].emplace_back(q);
			l >>= 1, r >>= 1;
		}
	}

	vector<F> operator[](int k) { return seg[k]; }

	template <typename T0, typename T1, typename T2, typename T3>
	void run(T0 marge, T1 get_time, T2 rollback, T3 query) {
		auto dfs = [&](auto&& dfs, int l, int r, int u)->void{
			if (l >= Q) return;
			int time = get_time();
			for (auto& f : seg[u]) marge(f);
			if (r - l == 1) query(u - width);
			else {
				dfs(dfs, l, (l + r) / 2, u * 2 + 0);
				dfs(dfs, (l + r) / 2, r, u * 2 + 1);
			}
			rollback(time);
		};
		dfs(dfs, 0, width, 1);
	}
};

// template to use "run"
/*
	using F = ;
	SegmentTreeDandC<F> seg(Q);

	// (calc query range, declarate info, exc...)

	auto marge = [&](F q)->void{
	};
	auto get_time = [&]()->int{
	};
	auto rollback = [&](int time)->void{
	};
	auto query = [&](int qi)->void{
	};
	seg.run(marge, get_time, rollback, query);
*/
// ===== END INCLUDE: ../../segment-tree/segment-tree-divide-and-conquer.hpp =====
using mint = LazyMontgomeryModInt<998244353>;

using namespace yamada;
ll op(ll a,ll b) { return a+b; }
ll e() { return 0; }
ll mapping(int b,ll a) {
	if(b==-1)return a;
    return b;
}
int composition(int f,int g) {
	if(f==-1)return g;
	return f;
}
int id() { return -1; }
constexpr Monoid_Act< op, e, mapping, composition, id > AM{};

const int N_MAX=200'000;
const int M_MAX=180'000;
void yamada::solve()
{
	LL(N,M);
	using F = pl;
	SegmentTreeDandC<F> dac(N);

	// (calc query range, declarate info, exc...)
	FOR(M){
		LL(a,b,c,d); --a; --b;
		dac.apply(a,c,{b,d});
	}

	using Segtree= RollbackLazySegtree<AM,N_MAX,M_MAX>;
	auto seg=make_unique<Segtree>(Iota(1LL,N+1)|rtov);
	mint ans=0;

	auto marge = [&](F q)->void{
		auto[l,r]=q;
		seg->apply(l,r,0);
	};
	auto get_time = [&]()->int{
		return seg->snapshot();
	};
	auto rollback = [&](int time)->void{
		seg->rollback(time);
	};
	auto query = [&](int qi)->void{
		ans+=seg->prod(0,N)*(qi+1);
	};
	dac.run(marge, get_time, rollback, query);
	OUT(ans);
}

