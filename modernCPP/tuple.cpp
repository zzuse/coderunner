#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <tuple>
#include <string>
#include <type_traits>  // std::remove_reference_t
#include <utility>      // std::forward
#include <stddef.h>     // size_t
#include <stdio.h>

using namespace std;

template <typename T, typename... Args>
inline unique_ptr<T>
make_unique(Args&&... args)
{
	return unique_ptr<T>(new T(forward<Args>(args)...));
}

// forward<Args>(args)... 可以理解为forward<int>(arg1),forward<int>(arg2),...
// 所以可以特化为
template<>
inline unique_ptr<vector<int>>
make_unique(int&& arg1, int&& arg2)
{
	return unique_ptr<vector<int>>(
		new vector<int>(
		forward<int>(arg1),
		forward<int>(arg2)));
}

template <typename F>
auto compose(F f)
{
	return [f](auto&&... x) {
		return f(
			forward<decltype(x)>(x)...);
	};
}

template <
	template <typename, typename>
	class OutContainer = vector,
	typename F, class R
>
auto fmap(F&& f, R&& inputs)
{
	typedef decay_t<decltype (f(*inputs.begin()))> result_type;
	OutContainer<result_type, allocator<result_type>> result;
	for (auto&& item:inputs) {
		result.push_back(f(item));
	}
	return result;
}

template <typename F, typename...Args>
auto compose(F f, Args... other)
{
	return [f, other...](auto&&...x) {
		return f(compose(other...)(forward<decltype(x)>(x)...));
	};
}

auto square_list = [](auto&& container) {
	return fmap(
		[](int x){ return x * x; }, container
	);
};

auto sum_list = [](auto&& container) {
	return accumulate(
		container.begin(), container.end(), 0
	);
};

auto squared_sum = compose(sum_list, square_list);

		template <class A, A... Ints>
		struct integer_sequence {};

		template <size_t... Ints>
		using index_sequence =
			integer_sequence<size_t, Ints...>;

		template <size_t N, size_t... Ints>
		struct index_sequence_helper {
			typedef
				typename index_sequence_helper<N - 1, N - 1, Ints...>::type type;
		};

		template <size_t... Ints>
		struct index_sequence_helper<0, Ints...> {
			typedef index_sequence<Ints...> type;
		};

		template <size_t N>
		using make_index_sequence =
			typename index_sequence_helper<N>::type;		

int main(int argc, char *argv[]) {
	vector v{1,2,3,4,5};
	cout << squared_sum(v) << endl;
}