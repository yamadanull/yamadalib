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
////////////////////////////////////////////////////////////
template <bool FLUSH = false>
struct _out {
	template <class T>
	void operator=(const T& x) const {
		cout << x << "\n";
		if constexpr (FLUSH) cout.flush();
	}
	template <class... T>
	void operator()(const T&... x) const {
		bool f{};
		(..., (cout << (exchange(f, 1) ? " " : "") << x));
		cout << '\n';
		if constexpr (FLUSH) cout.flush();
	}
};
struct _YESNO {
	bool operator= (const bool& b) const { cout << (b ? "YES\n" : "NO\n"); return b; }
	bool operator()(const bool& b) const { cout << (b ? "YES\n" : "NO\n"); return b; }
};
struct _YesNo {
	bool operator= (const bool& b) const { cout << (b ? "Yes\n" : "No\n"); return b; }
	bool operator()(const bool& b) const { cout << (b ? "Yes\n" : "No\n"); return b; }
};
struct _yesno {
	bool operator= (const bool& b) const { cout << (b ? "yes\n" : "no\n"); return b; }
	bool operator()(const bool& b) const { cout << (b ? "yes\n" : "no\n"); return b; }
};
inline constexpr _out<false> out{};
inline constexpr _out<true> fout{};
inline constexpr _YESNO YESNO{};
inline constexpr _YesNo YesNo{};
inline constexpr _yesno yesno{};
////////////////////////////////////////////////////////////

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

#define yamadaDebug

#ifdef yamadaDebug
#define err(...) \
	do { \
		std::cerr << "## " << #__VA_ARGS__ << " = "; \
		yamada::DebugImpl::trace(__VA_ARGS__); \
	} while (0)
#else
#define err(...) (void(0))
#endif
