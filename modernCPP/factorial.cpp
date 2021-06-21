#include <iostream>

using namespace std;

template <int n>
struct factorial {
	static_assert( n >= 0, "Arg must be non-negative");
	static const int value = n * factorial<n - 1>::value;
};

template <>
struct factorial<0> {
	  static const int value = 1;
};

template <bool cond,
          typename Then,
          typename Else>
struct If;

template <typename Then,
          typename Else>
struct If<true, Then, Else>
{  typedef Then type;};

template <typename Then,
          typename Else>
struct If<false, Then, Else>
{  typedef Else type;};

template <bool condition,
          typename Body>
struct WhileLoop;

//递归分支
template <typename Body>
struct WhileLoop<true, Body> {
	  typedef typename WhileLoop<
	    Body::cond_value,
	    typename Body::next_type>::type
	    type;
	};
//退出循环分支
template <typename Body>
struct WhileLoop<false, Body> {
	  typedef typename Body::res_type type;
	};

template <typename Body>
struct While {  typedef typename WhileLoop<
    Body::cond_value, Body>::type
    type;
};

template <class T, T v>
struct integral_constantA {
	 static const T value = v;
	 typedef T value_type;
	 typedef integral_constantA type;
};

template <int result, int n>
struct SumLoop {
	  static const bool cond_value =    n != 0;
	  static const int res_value =    result;
	  typedef integral_constantA<    int, res_value>    res_type;
	  typedef SumLoop<result + n, n - 1>    next_type;
	};

template <int n>
struct Sum {
	  typedef SumLoop<0, n> type;
	};

int main(int argc, char *argv[]) {
	printf("%d\n", factorial<10>::value);
	printf("%d\n", While<Sum<10>::type>::type::value);
}