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
#define ZIN(...) for (auto&& [__VA_ARGS__] : std::views::zip(__VA_ARGS__)) yamada::in(__VA_ARGS__)
