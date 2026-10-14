#pragma once
// 要練習

template <class T> struct V : vector<T>{
	using vT = vector<T>;
	using cvT = const vector<T>;
	using cT = const T;
	using vT::vT; //親クラスのコンストラクタの隠蔽を回避
	using vT::begin, vT::end, vT::insert, vT::erase;
	auto it(int i) { return begin() + i; }
	auto it(int i) const { return begin() + i; }
	V(cvT& b) : vT(b) {}
	V(vT&& b) : vT(move(b)) {}
	V(int n, cT& x) : vT(n, x) {}// ┬ 型推論のためラッパー
	V(long long n, cT& x) : vT(n, x) {}
	template <class S> V(const V<S>& b) : vT(b.begin(), b.end()) {}
	template <class S> V(const vector<S>& b) : vT(b.begin(), b.end()) {}
	V(int n, T s, T d) { iota(n, s, d); }
	V(int n, function<T(int)> g) : vT(n) { for (int i = 0; i < n; ++i) (*this)[i] = g(i); }
	V &operator+=(cvT &b) { assert(size() == b.size()); for (int i = 0; i < size(); ++i) (*this)[i] += b[i]; return *this; }
	V &operator-=(cvT &b) { assert(size() == b.size()); for (int i = 0; i < size(); ++i) (*this)[i] -= b[i]; return *this; }
	V &operator*=(cvT &b) { assert(size() == b.size()); for (int i = 0; i < size(); ++i) (*this)[i] *= b[i]; return *this; }
	V &operator/=(cvT &b) { assert(size() == b.size()); for (int i = 0; i < size(); ++i) (*this)[i] /= b[i]; return *this; }
	V &operator%=(cvT &b) { assert(size() == b.size()); for (int i = 0; i < size(); ++i) (*this)[i] %= b[i]; return *this; }
	V &operator+=(const V<T> &b) { return *this += (cvT&)b; }
	V &operator-=(const V<T> &b) { return *this -= (cvT&)b; }
	V &operator*=(const V<T> &b) { return *this *= (cvT&)b; }
	V &operator/=(const V<T> &b) { return *this /= (cvT&)b; }
	V &operator%=(const V<T> &b) { return *this %= (cvT&)b; }
	V operator+(cvT &b) { return V(*this) += b; }
	V operator-(cvT &b) { return V(*this) -= b; }
	V operator*(cvT &b) { return V(*this) *= b; }
	V operator/(cvT &b) { return V(*this) /= b; }
	V operator%(cvT &b) { return V(*this) %= b; }
	V operator+(const V<T> &b) { return V(*this) += b; }
	V operator-(const V<T> &b) { return V(*this) -= b; }
	V operator*(const V<T> &b) { return V(*this) *= b; }
	V operator/(const V<T> &b) { return V(*this) /= b; }
	V operator%(const V<T> &b) { return V(*this) %= b; }
	template <class S> V &operator+=(S x) { for (T &e: *this) e += x;  return *this; }
	template <class S> V &operator-=(S x) { for (T &e: *this) e -= x;  return *this; }
	template <class S> V &operator*=(S x) { for (T &e: *this) e *= x;  return *this; }
	template <class S> V &operator/=(S x) { for (T &e: *this) e /= x;  return *this; }
	template <class S> V &operator%=(S x) { for (T &e: *this) e %= x;  return *this; }
	template <class S> V operator+(S x) const { return V(*this) += x; }
	template <class S> V operator-(S x) const { return V(*this) -= x; }
	template <class S> V operator*(S x) const { return V(*this) *= x; }
	template <class S> V operator/(S x) const { return V(*this) /= x; }
	template <class S> V operator%(S x) const { return V(*this) %= x; }
	V &operator--(int) { return *this -= 1; }
	V &operator++(int) { return *this += 1; }
	V operator-() const { return V(*this) *= -1; }
	template <class S> friend V operator-(S x, const V &a) { return -a+=x; }
	T& at(int i) { assert(i >= 0); if (n() <= i)vT::resize(i + 1); return vT::operator[](i); }
	V slice(int l, int r, int d = 1) const {
		V ret;
		for (int i = l; d > 0 && i <= r || d < 0 && r <= i; i += d) ret.emplace_back((*this)[i]);
		return ret;
	}
	int size() const { return (int)vT::size(); }
	V &emplace_back(cT& x, int n = 1) { for (int i = 0; i < n; ++i) { vT::emplace_back(x); } return *this; }
	V &pop_back(int n = 1) { for (int i = 0; i < n; ++i) { vT::pop_back(); } return *this; }
	V &push_front(cT& x, int n = 1) { this->insert(0, x, n); return *this; }
	V &pop_front(int n = 1) { erase(0, n-1); return *this; }
	T pull_back() { T x = move(vT::back()); vT::pop_back(); return x; }
	T pull_front() { T x = move(vT::front()); erase(0); return x; }
	V &insert(int i, cT& x, int n = 1) { insert(it(i), n, x); return *this; }
	V &insert(int i, cvT& b) { insert(it(i), b.begin(), b.end()); return *this; }
	V &erase(int i) { erase(it(i)); return *this; }
	V &erase(int l, int r) { erase(it(l), it(r + 1)); return *this; }
	V &erase(const V<int> &idxs) {
		for (int I = 0; I < idxs.n(); int++I) {
			int l = idxs[I] + 1, r = (I < idxs.n() - 1) ? idxs[I + 1] : this->n();
			copy(it(l), it(r), it(l-I-1));//[l, r)を前にI + 1個ずらす
		}
		vT::resize(this->n() - idxs.n());
		return *this;
	}
	V &eraseall(cT& x) { return eraseall(0, size() - 1, x); }
	V &eraseall(int l, int r, cT& x) { erase(remove(it(l), it(r + 1), x), it(r + 1)); return *this; }
	template <class Pr> V &eraseif(Pr pr) { return eraseif(0, size() - 1, pr); }
	template <class Pr> V &eraseif(int l, int r, Pr pr) { erase(remove_if(it(l), it(r + 1), pr), it(r + 1)); return *this; }
	V &concat(cvT &b, int n = 1) {
		cvT B = (&b == this) ? *this : vT{};
		for (int i = 0; i < n; ++i) this->insert(size(),(&b == this)?B:b);
		return *this;
	}
	V repeat(int n) { return V{}.concat(*this, n); }
	V &reverse(int l = 0, int r=-1) { r+=r < 0?size():0; std::reverse(it(l), it(r + 1)); return *this; }
	V &rotate(int m) { return rotate(0, size() - 1, m); }
	V &rotate(int l, int r, int m) { std::rotate(it(l), it(m), it(r + 1)); return *this; }
	V &sort(int l = 0, int r=-1) { r+=r < 0?size():0; std::sort(it(l), it(r + 1)); return *this; }
	V &rsort(int l = 0, int r=-1) { return sort(l, r).reverse(l, r); }
	template <class Pr> V &sort(Pr pr) { return sort(0, size() - 1, pr); }
	template <class Pr> V &sort(int l, int r, Pr pr) { std::sort(it(l), it(r + 1), pr); return *this; }
	template <int key> V &sortbykey(int l = 0, int r=-1) {
		r+=r < 0?size():0;
		sort(l, r,[](cT &x, cT &y) {return get<key>(x)<get<key>(y);});
		return *this;
	}
	V &uniq() { erase(unique(begin(), end()), end()); return *this; }
	V &sortq() { return sort().uniq(); }
	V &fill(cT& x) { return fill(0, size() - 1, x); }
	V &fill(int l, int r, cT& x) { std::fill(it(l), it(r + 1), x); return *this; }
	V &copy(int i, cvT &b, int n = 1) {//A[i]スタートでbをn回分コピー
		for (int t = 0; t < n; ++t) for (int j = 0; j<(int)b.size(); ++j) {
			if (i>=size()) return *this;
			if (i>=0) (*this)[i]=b[j];
			i++;
		}
		return *this;
	}
	template <class S = int> V &iota(int n, T s = 0, S d = 1) {
		vT::resize(n);
		if (n == 0) return *this;
		(*this)[0]=s;
		for (int i = 1; i < n; ++i) (*this)[i]=(*this)[i-1] + d;
		return *this;
	}
	int count(cT& x) const { return count(0, size() - 1, x); }
	int count(int l, int r, cT& x) const { return int(std::count(it(l), it(r + 1), x)); }
	template <class Pr> int countif(Pr pr) const { return countif(0, size() - 1, pr); }
	template <class Pr> int countif(int l, int r, Pr pr) const { return int(count_if(it(l), it(r + 1), pr)); }
	int find(cT& x) const { return find(0, size() - 1, x); }
	int find(int l, int r, cT& x) const { return int(std::find(it(l), it(r + 1), x) - begin()); }
	int rfind(cT& x) const { return rfind(0, size() - 1, x); }
	int rfind(int l, int r, cT& x) const {
		for (int i = r; i>=l; --i) if ((*this)[i]==x) return i;
		return l-1;
	}
	template <class Pr> int findif(Pr pr) const { return findif(0, size() - 1, pr); }
	template <class Pr> int findif(int l, int r, Pr pr) const { return int(find_if(it(l), it(r + 1), pr) - begin()); }
	V<int> findall(cT& x) const { return findall(0, size() - 1, x); }
	V<int> findall(int l, int r, cT& x) const { return findallif(l, r,[&](cT& y) {return y == x;}); }
	template <class Pr> V<int> findallif(Pr pr) const { return findallif(0, size() - 1, pr); }
	template <class Pr> V<int> findallif(int l, int r, Pr pr) const {
		V<int> ret;
		for (int i = l; i<=r; ++i) if (pr((*this)[i])) ret.emplace_back(i);
		return ret;
	}
	int  flooridx(cT& x) const { return int(upper_bound(begin(), end(), x) - begin() - 1); }
	int   ceilidx(cT& x) const { return int(lower_bound(begin(), end(), x) - begin()); }
	int  leftnmof(cT& x) const { return flooridx(x) + 1; }
	int rightnmof(cT& x) const { return size() - ceilidx(x); }
	bool contains(cT& x) const { int i = flooridx(x); return i>=0 && (*this)[i]==x; }
	template <class Pr> int  flooridx(cT& x, Pr pr) const { return int(upper_bound(begin(), end(), x, pr) - begin() - 1); }
	template <class Pr> int   ceilidx(cT& x, Pr pr) const { return int(lower_bound(begin(), end(), x, pr) - begin()); }
	template <class Pr> int  leftnmof(cT& x, Pr pr) const { return flooridx(x, pr) + 1; }
	template <class Pr> int rightnmof(cT& x, Pr pr) const { return size() - ceilidx(x, pr); }
	template <class Pr> bool contains(cT& x, Pr pr) const { int i = flooridx(x, pr); return i>=0 && (*this)[i]==x; }

	template <class S> using VV    = V<V<S>>;      template <class S> using sVV    = vector<vector<S>>;
	template <class S> using VVV   = V<VV<S>>;     template <class S> using sVVV   = vector<sVV<S>>;
	template <class S> using VVVV  = V<VVV<S>>;    template <class S> using sVVVV  = vector<sVVV<S>>;
	template <class S> using VVVVV = V<VVVV<S>>;   template <class S> using sVVVVV = vector<sVVVV<S>>;
	auto tostd() const { return tov(*this); }
	template <class S> static vector<S> tov(const V<S>&v) { return v; }
	template <class S> static sVV<S>    tov(const VV<S>    &v) { sVV<S>    ret; for (auto&& e : v) ret.emplace_back(e);         return ret; }
	template <class S> static sVVV<S>   tov(const VVV<S>   &v) { sVVV<S>   ret; for (auto&& e : v) ret.emplace_back(e.tostd()); return ret; }
	template <class S> static sVVVV<S>  tov(const VVVV<S>  &v) { sVVVV<S>  ret; for (auto&& e : v) ret.emplace_back(e.tostd()); return ret; }
	template <class S> static sVVVVV<S> tov(const VVVVV<S> &v) { sVVVVV<S> ret; for (auto&& e : v) ret.emplace_back(e.tostd()); return ret; }
};
/*
   vll a={9, 8, 7},b={1, 2, 3};
   vpll p={{5, 3},{7, 8},{0, 2},};
   - -------- 操作系 --------
   a+=x a-=x a*=x a/=x a%=x a + x a-x a*x a/x a%x -a x-a a++ a--  //∀i a[i]にxを演算
   a+=b a-=b a*=b a/=b a%=b a + b a-b a*b a/b a%b  //要素毎演算(同サイズ時)
   a.at(i)=x;         //a[i]=x, 未確保ならresize
   a.push_front(x, n); //n個先頭追加 省略時1
   a.emplace_back(x, n);  //n個末尾追加 省略時1
   a.pop_front(n);    //n個先頭削除 省略時1
   a.pop_back(n);     //n個末尾削除 省略時1
   ll x = a.pull_front(); //pop_front()と同時に値取得
   ll x = a.pull_back();  //pop_back()と同時に値取得
   a.insert(i, x, n); //a[i]にn個x挿入  n省略時1
   a.insert(i, b);   //a[i]にvll b挿入
   a.erase(i);      //a[i]削除
   a.erase(l, r);    //区間[l, r]削除
   a.erase(idxs.sortq()); //a[i0],a[i1],…を削除 idxsはソート&ユニーク必要
   a.eraseall(x);     //xを全て削除
   a.eraseall(l, r, x); //区間[l, r]のxを全て削除
   a.eraseif(pr);     //条件prを満たす要素を全て削除
   a.eraseif(l, r, pr); //区間[l, r]の 条件prを満たす要素を全て削除
   a.concat(b);     //aにbを結合 b = a可
   a.concat(b, n);   //aにbをn回結合 b = a可
   a.reverse(l, r);  //[l, r]を反転       l, r省略可
   a.rotate(m);     //a[m]を先頭にするrotate
   a.rotate(l, r, m); //a[m]を先頭にするrotate 範囲[l, r]
   a.sort(l, r);     //[l, r]をソート     l, r省略可
   a.rsort(l, r);    //[l, r]を逆順ソート l, r省略可
   p.sort(l, r,[&](pll x, pll y) {return x.second<y.second;});//比較関数指定sort l, r省略可
   a.uniq();      //連続同値を1つにする
   a.sortq();     //ソートしてユニーク
   a.fill(l, r, x); //[l, r]にx代入        l, r省略可
   a.copy(i, b);    //bを   コピー、a[i:i + b.size()]へ   i負可、はみ出す分無視
   a.copy(i, b, n); //bをn回コピー、a[i, i + b.size()*n]へ i負可、はみ出す分無視
   a.iota(n, s, d); //aを等差数列にする 長さn, 初項s, 公差d
   vll a(n, s, d);  //コンストラクタ版iota
   vll b = a.slice(st, en, d); //a[st:en:d]   d省略時1
   vll b = a.repeat(n);   //aをn回繰り返す
   - -------- 検索系 --------
   auto pr=[&](auto &x) { return x>0; };  //検索条件
   ll m = a.count(x);     //xの個数
   ll m = a.count(l, r, x); //xの個数in[l, r]
   ll m = a.countif(pr);     //条件満たす個数
   ll m = a.countif(l, r, pr); //条件満たす個数in[l, r]
   ll i = a.find(x);         //xの最左位置i         ない時N(配列長)
   ll i = a.find(l, r, x);     //xの最左位置i in[l, r] ない時r + 1
   ll i = a.findif(pr);      //条件満たす最左位置i         ない時N(配列長)
   ll i = a.findif(l, r, pr);  //条件満たす最左位置i in[l, r] ない時r + 1
   vll is = a.findall(x);        //xの位置i列挙
   vll is = a.findall(l, r, x);    //xの位置i列挙in[l, r]
   vll is = a.findallif(pr);     //条件満たす位置i列挙
   vll is = a.findallif(l, r, pr); //条件満たす位置i列挙in[l, r]
   - -------- 昇順sort済み配列用 --------
   ll i = a.flooridx(x);   //x以下の最近傍位置i ない時-1
   ll i = a.ceilidx(x);    //x以上の最近傍位置i ない時N(配列長)
   ll m = a.leftnmof(x);   //x以下の個数
   ll m = = a.rightnmof(x);  //x以上の個数
   bool b = a.contains(x); //xを含む
   - -------- 比較関数prでsort済みの配列用 --------
   auto pr=[&](auto &x, auto &y) { return x>y; }; //降順ソート時
   ll i = a.flooridx(x, pr);   //x以左の最近傍位置i ない時-1
   ll i = a.ceilidx(x, pr);    //x以右の最近傍位置i ない時N(配列長)
   ll m = a.leftnmof(x, pr);   //x以左の個数
   ll m = a.rightnmof(x, pr);  //x以右の個数
   bool b = a.contains(x, pr); //xを含む

   a.concat(b, n).pop_back().rsort().uniq();  //連続適用できる
   auto aa = a.tostd(); //N次元VをN次元vectorに変換(N≦5)
 */


template <class T> struct wrapv: V<T>{
	using int = long long;
	T def = T();
	T defIF = T();
	wrapv(const V<T> &b):V<T>(b) {}
	wrapv(V<T> &&b):V<T>(move(b)) {}
	wrapv(const std::vector<T> &b):V<T>(b) {}
	wrapv(std::vector<T> &&b):V<T>(move(b)) {}
	T &operator[](int i) {
		return (i<0 || this->size()<=i) ? (defIF = def) : V<T>::operator[](i);
	}
	void setdef(const T& x) { def = x; }
};
/*
   wrapv v = vll(N, 0, 1); //vllなどでコンストラクトしてから代入する
   v.setdef(INF); //範囲外での値セット
 */

