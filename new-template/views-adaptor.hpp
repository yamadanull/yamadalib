namespace yamada {

template <int K>
constexpr auto Adjacent = views::adjacent<K>;
///////////////////////////////////////////////////////////
constexpr auto Chunk = views::chunk;
///////////////////////////////////////////////////////////
constexpr auto Drop = views::drop;
///////////////////////////////////////////////////////////
struct DropWhile_t{
	template<class F>
	auto operator<<(F&& f) const {
		return views::drop_while([f = forward<F>(f)](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
};
inline constexpr DropWhile_t DropWhile{};
///////////////////////////////////////////////////////////
struct Filter_t{
	template<class F>
	auto operator<<(F&& f) const {
		return views::filter([f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
};
inline constexpr Filter_t Filter{};
///////////////////////////////////////////////////////////
struct Map_t {
	template<class F>
	auto operator<<(F&& f) const {
		return views::transform([f = forward<F>(f)](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
};
inline constexpr Map_t Map{};

} // namespace yamada
#define MAP(a, A) A | yamada::Map << [&](auto a)
