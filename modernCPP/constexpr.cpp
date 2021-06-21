#include <array>
#include <iostream>
#include <memory>
#include <string_view>

using namespace std;

constexpr int sqr(int n)
{
    return n * n;
}

constexpr int factorial(int n)
{
    if (n < 0) { 
        throw std::invalid_argument( "Arg must be non-negative"); 
    }
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

// Type trait to detect whether an
// output function already exists
template <typename T>
struct has_output_function {
    template <class U>
    static auto output(U* ptr)
        -> decltype(
            std::declval<std::ostream&>()
                << *ptr,
            std::true_type());
    template <class U>
    static std::false_type
    output(...);
    static constexpr bool value =
        decltype(
            output<T>(nullptr))::value;
};

template <typename T>
inline constexpr bool
    has_output_function_v =
        has_output_function<T>::value;

// Output function for std::pair
template <typename T, typename U>
std::ostream& operator<<(
    std::ostream& os,
    const std::pair<T, U>& pr);


    // Element output function for
    // containers that define a key_type
    // and have its value type as
    // std::pair
    template <typename T, typename Cont>
    auto output_element(
        std::ostream& os,
        const T& element, const Cont&,
        const std::true_type)
        -> decltype(
            std::declval<
                typename Cont::key_type>(),
            os);
    // Element output function for other
    // containers
    template <typename T, typename Cont>
    auto output_element(
        std::ostream& os,
        const T& element, const Cont&,
        ...) -> decltype(os);

    // Main output function, enabled
    // only if no output function
    // already exists
    template <
        typename T,
        typename = std::enable_if_t<
            !has_output_function_v<T>>>
    auto operator<<(std::ostream& os,
                                    const T& container)
        -> decltype(container.begin(),
                                container.end(), os);


    template <typename T, typename Cont>
    auto output_element(
        std::ostream& os,
        const T& element, const Cont&,
        const std::true_type)
        -> decltype(
            std::declval<
                typename Cont::key_type>(),
            os)
    {
        os << element.first << " => "
            << element.second;
        return os;
    }

    template <typename T, typename Cont>
    auto output_element(
        std::ostream& os,
        const T& element, const Cont&,
        ...) -> decltype(os)
    {
        os << element;
        return os;
    }

// compile error
//        using element_type =
//            decay_t<decltype(
//                *container.begin())>;
//        constexpr bool is_char_v =
//            is_same_v<element_type, char>;
//        if constexpr (!is_char_v) {
//            os << "{ ";
//        }
//        
//        template <typename T, typename U>
//        std::ostream& operator<<(
//            std::ostream& os,
//            const std::pair<T, U>& pr)
//        {
//            os << '(' << pr.first << ", "
//                 << pr.second << ')';
//            return os;
//        }
        
int main()
{
    std::array<int, sqr(3)> a;
    int b[sqr(3)];
    const int n = sqr(3);
    int c[n];
    constexpr int d = 42;
    // compile error
    // constexpr const int &e = d;

    constexpr string_view sv{ "hi" };
    constexpr pair pr{ sv[0], sv[1] };
    constexpr array an{ pr.first, pr.second };
    constexpr int nn1 = an[0];
    constexpr int nn2 = an[1];
    cout << nn1 << ' ' << nn2 << endl;
    
    constexpr int m = factorial(10);  
    printf("%d\n", m);
}