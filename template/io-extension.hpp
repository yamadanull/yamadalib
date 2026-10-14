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
