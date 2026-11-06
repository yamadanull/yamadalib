namespace yamada {

namespace yamadaAdaptorImpl {

struct _DropWhile{
	template<class F>
	auto operator<<(F&& f) const {
		return views::drop_while([f = forward<F>(f)](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
};
struct _Filter{
	template<class F>
	auto operator<<(F&& f) const {
		return views::filter([f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
};
struct _TakeWhile{
	template<class F>
	auto operator<<(F&& f) const {
		return views::take_while([f = forward<F>(f)](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
};
struct _Map {
	template<class F>
	auto operator<<(F&& f) const {
		return views::transform([f = forward<F>(f)](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
};

} // namespace adaptorImpl

inline constexpr yamadaAdaptorImpl::_DropWhile DropWhile{};
inline constexpr yamadaAdaptorImpl::_Filter Filter{};
inline constexpr yamadaAdaptorImpl::_TakeWhile TakeWhile{};
inline constexpr yamadaAdaptorImpl::_Map Map{};

template <int K>
constexpr auto Adjacent = views::adjacent<K>;
constexpr auto Chunk = views::chunk;
constexpr auto Drop = views::drop;
constexpr auto Enumerate = views::enumerate;
constexpr auto Iota = views::iota;
constexpr auto Join = views::join;
constexpr auto Slide = views::slide;
constexpr auto Stride = views::stride;
constexpr auto Take = views::take;

} // namespace yamada
