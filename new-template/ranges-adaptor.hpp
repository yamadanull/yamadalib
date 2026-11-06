namespace yamada {

namespace yamadaAdaptorImpl {
template <class F = identity>
struct _All : ranges::range_adaptor_closure<_All<F>> {
	F f;
	constexpr _All() requires default_initializable<F> = default;
	constexpr explicit _All(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::all_of(forward<R>(r), [f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
	template <class G>
	auto operator<<(G&& g) const { return _All<decay_t<G>>(forward<G>(g)); }
};

template <class F = identity>
struct _Any : ranges::range_adaptor_closure<_Any<F>> {
	F f;
	constexpr _Any() requires default_initializable<F> = default;
	constexpr explicit _Any(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::any_of(forward<R>(r), [f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
	template <class G>
	auto operator<<(G&& g) const { return _Any<decay_t<G>>(forward<G>(g)); }
};

template <class T> // todo: Comp に対応
struct _BinarySearch : ranges::range_adaptor_closure<_BinarySearch<T>> {
	T x;
	explicit _BinarySearch(T x) : x(x) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const { return ranges::binary_search(forward<R>(r), x); }
};

template <class T>
struct _Count : ranges::range_adaptor_closure<T> {
	T x;
	explicit _Count(T x) : x(x) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const { return ranges::count(forward<R>(r), x); }
};

template <class F = identity>
struct _CountIf : ranges::range_adaptor_closure<_CountIf<F>> {
	F f;
	constexpr _CountIf() requires default_initializable<F> = default;
	constexpr explicit _CountIf(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::count_if(forward<R>(r), [f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
	template <class G>
	auto operator<<(G&& g) const { return _CountIf<decay_t<G>>(forward<G>(g)); }
};

template <class F = identity>
struct _Each : ranges::range_adaptor_closure<_Each<F>> {
	F f;
	constexpr _Each() requires default_initializable<F> = default;
	constexpr explicit _Each(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::for_each(forward<R>(r), [f = f](auto&& t) mutable -> decltype(auto) {
			if constexpr (invocable<decltype(f)&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
	}
	template <class G>
	auto operator<<(G&& g) const { return _Each<decay_t<G>>(forward<G>(g)); }
};

template <class F = identity>
struct _Sum : ranges::range_adaptor_closure<_Sum<F>> {
	F f;
	constexpr _Sum() requires default_initializable<F> = default;
	constexpr explicit _Sum(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		auto v = views::transform(forward<R>(r), [f = f](auto&& t) mutable {
			if constexpr (invocable<F&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
		return ranges::fold_left(v, ranges::range_value_t<decltype(v)>{}, plus<>{});
	}
	template <class G>
	auto operator<<(G&& g) const { return _Sum<decay_t<G>>(forward<G>(g)); }
};

template <class F = identity>
struct _Max : ranges::range_adaptor_closure<_Max<F>> {
	F f;
	constexpr _Max() requires default_initializable<F> = default;
	constexpr explicit _Max(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::max(views::transform(forward<R>(r), [f = f](auto&& t) mutable {
			if constexpr (invocable<F&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		}));
	}
	template <class G>
	auto operator<<(G&& g) const { return _Max<decay_t<G>>(forward<G>(g)); }
};

template <class F = identity>
struct _MaxIndex : ranges::range_adaptor_closure<_MaxIndex<F>> {
	F f;
	constexpr _MaxIndex() requires default_initializable<F> = default;
	constexpr explicit _MaxIndex(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		auto v = views::transform(forward<R>(r), [f = f](auto&& t) mutable {
			if constexpr (invocable<F&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
		return ranges::max_element(v) - v.begin();
	}
	template <class G>
	auto operator<<(G&& g) const { return _MaxIndex<decay_t<G>>(forward<G>(g)); }
};

template <class F = identity>
struct _Min : ranges::range_adaptor_closure<_Min<F>> {
	F f;
	constexpr _Min() requires default_initializable<F> = default;
	constexpr explicit _Min(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		return ranges::min(views::transform(forward<R>(r), [f = f](auto&& t) mutable {
			if constexpr (invocable<F&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		}));
	}
	template <class G>
	auto operator<<(G&& g) const { return _Min<decay_t<G>>(forward<G>(g)); }
};

template <class F = identity>
struct _MinIndex : ranges::range_adaptor_closure<_MinIndex<F>> {
	F f;
	constexpr _MinIndex() requires default_initializable<F> = default;
	constexpr explicit _MinIndex(F f) : f(move(f)) {}
	template <ranges::input_range R>
	auto operator()(R&& r) const {
		auto v = views::transform(forward<R>(r), [f = f](auto&& t) mutable {
			if constexpr (invocable<F&, decltype(t)>) return invoke(f, forward<decltype(t)>(t));
			else return apply(f, forward<decltype(t)>(t));
		});
		return ranges::min_element(v) - v.begin();
	}
	template <class G>
	auto operator<<(G&& g) const { return _MinIndex<decay_t<G>>(forward<G>(g)); }
};

} // namespace yamadaAdaptorImpl

inline constexpr yamadaAdaptorImpl::_All All{};
inline constexpr yamadaAdaptorImpl::_Any Any{};
inline constexpr yamadaAdaptorImpl::_Each Each{};
inline constexpr yamadaAdaptorImpl::_Sum Sum{};
inline constexpr yamadaAdaptorImpl::_Max Max{};
inline constexpr yamadaAdaptorImpl::_Min Min{};
template <class T>
auto BinarySearch(T x) { return yamadaAdaptorImpl::_BinarySearch(x); }
template <class T>
auto Count(T x) { return yamadaAdaptorImpl::_Count(x); }

constexpr auto Copy = ranges::copy;
constexpr auto Fill = ranges::fill;
constexpr auto Sort = ranges::sort;
constexpr auto Rotate = ranges::rotate;
constexpr auto Reverse = ranges::reverse;
constexpr auto rtov = ranges::to<vector>();
constexpr auto rtos = ranges::to<string>();

} // namespace yamada
