#include <functional>
#include <iostream>
#include <type_traits>
#include <utility>


using namespace std;


template <class Fun>
class y_combinator_result {
	Fun fun_;
public:
	template <class T>
	explicit y_combinator_result (T&& fun):fun_(std::forward<T>(fun))
	{}
	
	template <class... Args>
	decltype(auto)
	operator()(Args&&... args)
	{
		return fun_(std::ref(*this),
		std::forward<Args>(args)...);
	}
};

template <class Fun>
decltype(auto)
y_combinator(Fun&& fun)
{
	return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

int main()
{
	auto almost_fact = [](auto f, int n) -> int {
		if (n == 0)
			return 1;
		else {
			return n*f(n-1);
		}
	};
	auto fact = y_combinator(almost_fact);
	std::cout << fact(3) << std::endl;
}