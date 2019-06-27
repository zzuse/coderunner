#ifndef STACK_H
#define STACK_H
#include <deque>

template< typename T>
class Stack{
	public:
		T& top()
		{
			return stack.front();
		}
		void push(const T &pushValue)
		{
			stack.push_front(pushValue);
		}
		void pop();
//		{
//			stack.pop_front();
//		}
		bool isEmpty() const
		{
			return stack.empty();
		}
		size_t size() const
		{
			return stack.size();
		}
	private:
		std::deque<T> stack;
};

template< typename T>
inline void Stack<T>::pop()
{
	stack.pop_front();
}

#endif