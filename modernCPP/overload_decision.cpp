#include <stdio.h>
#include <type_traits>
using namespace std;

struct Test {
	typedef int foo;
};

template <typename T>
void f(typename T::foo)
{
	puts("1");
}

template <typename T>
void f(T)
{
	puts("2");
}

template <typename T>
struct has_reserve {
	struct good {char dummy;};
	struct bad {char dummy[2];};
	template <class U, void (U::*)(size_t)>
	struct SFINAE {};
	template <class U>
	static good reserve(SFINAE<U, &U::reserve>*);
	template <class U>
	static bad reserve(...);
	static const bool value = sizeof(reserve<T>(nullptr))==sizeof(good);
};

template <typename C, typename T>
enable_if_t<has_reserve<C>::value, void>
append(C& container, T* ptr, size_t size)
{  
	container.reserve( container.size() + size);  
	for (size_t i = 0; i < size; ++i) 
	{
		container.push_back(ptr[i]);
	}
}

template <typename C, typename T>
enable_if_t<!has_reserve<C>::value, void>
append(C& container, T* ptr, size_t size)
{  for (size_t i = 0; i < size; ++i) 
	{
			container.push_back(ptr[i]);
	}
}

template <typename C, typename T>
auto append(C& container, T* ptr, size_t size)
-> decltype(declval<C&>().reserve(1U), void())
{
	container.reserve(container.size() + size);
		for (size_t i = 0; i < size; ++i) {
			container.push_back(ptr[i]);
		}
}

template <typename C, typename T>
void _append(C& container, T* ptr, size_t size, true_type)
{
	container.reserve(container.size()+size);
	for (size_t i = 0; i< size; ++i){
	container.push_back(ptr[i]);
	}
}

template <typename C, typename T>
void _append(C& container, T* ptr, size_t size, false_type)
{
	for (size_t i = 0; i< size; ++i){
		container.push_back(ptr[i]);
	}
}

template <typename C, typename T>
void append(C& container, T* ptr, size_t size)
{
	_appennd(container, ptr, size, integral_constant<bool, has_reserve<C>::value>{});
}

template <typename C, typename T>
void append(C& container , T& ptr, size_t size)
{
	_append(container, ptr, size, has_reserve<C>{});
}

// no reserve() will fail
// template <typename C, typename T>
// void append(C& container, T* ptr, size_t size)
// {
//   if (has_reserve<C>::value) {
//   	container.reserve(container.size()+size);
//   }
//   for (size_t i = 0; i < size; ++i ) {
//     container.push_back(ptr[i]);
//   }
// }

int main(int argc, char *argv[]) {
	f<Test>(10);
	f<int>(10);
}
