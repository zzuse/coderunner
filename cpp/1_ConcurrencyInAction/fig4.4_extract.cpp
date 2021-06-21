#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

template<typename T>
class threadsafe_queue
{
private:
	std::mutex mut;
	std::queue<T> data_queue;
	std::condition_variable data_cond;

public:
	void push(T new_value)
	{
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(new_value);
		data_cond.notify_one();
	}
	
	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk,[this]{return !data_queue.empty();});
		value = data_queue.front();
		data_queue.pop();
	}
};


bool more_data_to_prepare()
{
	return false;
}

struct data_chunk
{};

data_chunk prepare_data()
{
	return data_chunk();
}

void process(data_chunk&)
{}

bool is_last_chunk(data_chunk&)
{
	return true;
}

threadsafe_queue<data_chunk> data_queue;

void data_preparation_thread()
{
	while (more_data_to_prepare()) {
		data_chunk const data=prepare_data();
		data_queue.push(data);
	}
}

void data_processing_thread()
{
	while (true) {
		data_chunk data;
		data_queue.wait_and_pop(data);
		process(data);
		if(is_last_chunk(data))
			break;
	}
}

using namespace std;
int main(int argc, char *argv[]) {
	std::thread t1(data_preparation_thread);
	std::thread t2(data_processing_thread);
	
	t1.join();
	t2.join();
}