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

using namespace placeholders;
constexpr auto Ofs(const int K = 1) { return views::transform(bind(plus(), _1, K)); }
} // namespace yamada
