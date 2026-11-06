namespace yamada {

namespace yamadaAdaptorImpl {
template <class F = identity>
struct views_All : ranges::range_adaptor_closure<views_All<F>> {
	F f;
	constexpr views_All() requires default_initializable<F> = default;
	constexpr explicit views_All(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::all_of(forward<R>(r), [f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
	template <class G>
	auto operator<<(G&& g) const { return views_All<decay_t<G>>(forward<G>(g)); }
};

template <class F = identity>
struct views_Any : ranges::range_adaptor_closure<views_Any<F>> {
	F f;
	constexpr views_Any() requires default_initializable<F> = default;
	constexpr explicit views_Any(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::any_of(forward<R>(r), [f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
	template <class G>
	auto operator<<(G&& g) const { return views_Any<decay_t<G>>(forward<G>(g)); }
};

template <class F = identity>
struct views_CountIf : ranges::range_adaptor_closure<views_CountIf<F>> {
	F f;
	constexpr views_CountIf() requires default_initializable<F> = default;
	constexpr explicit views_CountIf(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::count_if(forward<R>(r), [f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
	template <class G>
	auto operator<<(G&& g) const { return views_CountIf<decay_t<G>>(forward<G>(g)); }
};

template <class F = identity>
struct views_Each : ranges::range_adaptor_closure<views_Each<F>> {
	F f;
	constexpr views_Each() requires default_initializable<F> = default;
	constexpr explicit views_Each(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::for_each(forward<R>(r), [f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
	template <class G>
	auto operator<<(G&& g) const { return views_Each<decay_t<G>>(forward<G>(g)); }
};

template <class F = identity>
struct views_Sum : ranges::range_adaptor_closure<views_Sum<F>> {
	F f;
	constexpr views_Sum() requires default_initializable<F> = default;
	constexpr explicit views_Sum(F f) : f(move(f)) {}

	template <ranges::input_range R>
	auto operator()(R&& r) const {
		auto v = views::transform(forward<R>(r), [f = f](auto&& t) mutable {
			if constexpr (invocable<F&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
		return ranges::fold_left(v, ranges::range_value_t<decltype(v)>{}, plus<>{});
	}
	template <class G>
	auto operator<<(G&& g) const { return views_Sum<decay_t<G>>(forward<G>(g)); }
};

// todo: Comp, Proj に対応
template <class T>
struct _BinarySearch : ranges::range_adaptor_closure<_BinarySearch<T>> {
	T x;
	explicit _BinarySearch(T x) : x(x) {}
	template <ranges::viewable_range R>
	auto operator()(R&& r) const {
		return ranges::binary_search(forward<R>(r), x);
	}
};

/* struct _add : ranges::range_adaptor_closure<_add> { */
/*	 int n; */
/*	 explicit _add(int n) : n(n) {} */
/*	 template <ranges::viewable_range R> */
/*	 auto operator()(R&& r) const { */
/*		 return forward<R>(r) | views::transform([n = n](auto x) { return x + n; }); */
/*	 } */
/* }; */
/* auto add(int n) { */
/*	 return _add(n); */
/* } */
} // namespace yamadaAdaptorImpl

inline constexpr yamadaAdaptorImpl::views_All All{};
inline constexpr yamadaAdaptorImpl::views_Any Any{};
inline constexpr yamadaAdaptorImpl::views_Each Each{};
inline constexpr yamadaAdaptorImpl::views_Sum Sum{};
template <class T>
auto BinarySearch(T x) { return yamadaAdaptorImpl::_BinarySearch(x); }

constexpr auto rtov = ranges::to<vector>();
constexpr auto rtos = ranges::to<string>();

} // namespace yamada
