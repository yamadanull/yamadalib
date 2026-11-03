namespace yamada {

template <class F>
struct AllClosure : ranges::range_adaptor_closure<AllClosure<F>> {
	F f;
	explicit AllClosure(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::all_of(forward<R>(r), [f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
};
struct All_t {
	template <class F>
	auto operator<<(F&& f) const { return AllClosure<decay_t<F>>(forward<F>(f)); }
};
inline constexpr All_t All{};
////////////////////////////////////////////////////////////
template <class F>
struct AnyClosure : ranges::range_adaptor_closure<AnyClosure<F>> {
	F f;
	explicit AnyClosure(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::any_of(forward<R>(r), [f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
};
struct Any_t {
	template <class F>
	auto operator<<(F&& f) const { return AnyClosure<decay_t<F>>(forward<F>(f)); }
};
inline constexpr Any_t Any{};
///////////////////////////////////////////////////////////
template <class F>
struct EachClosure : ranges::range_adaptor_closure<EachClosure<F>> {
	F f;
	explicit EachClosure(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::for_each(forward<R>(r), [f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
};
struct Each_t {
	template <class F>
	auto operator<<(F&& f) const { return EachClosure<decay_t<F>>(forward<F>(f)); }
};
inline constexpr Each_t Each{};

} // namespace yamada
#define EACH(a, A) A | yamada::Each << [&](auto a)
