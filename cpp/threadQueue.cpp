#include <iostream>
#include <unistd.h>
#include <thread>
#include <queue>

template <class Object> 
class ThreadQueue {
private:   
    std::queue <Object> que;
    int size;
    pthread_mutex_t mutex;   
public:   
    ThreadQueue();   
    ~ThreadQueue();   
public:   
    bool IsEmpty() const;   
    void push(const Object &obj);   
    Object& pop();
    int Count() const;
    Object& Front(); 
    Object& Back();     
    void Clear();
};
int main(int argc, char *argv[]) {
    int val_count=10;
//    queue_t<int> my_queue;
    ThreadQueue<int> my_queue;
    std::thread thr_push([&](int count){
        while(count--) {
            int val = count * 2;
            std::cout << "push value " << val << std::endl;
            my_queue.push(val);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }, val_count);
    sleep(10);
    std::thread thr_pop([&](int count){
        while (count--) {
            int val = my_queue.pop();
            std::cout << "pop value" << val << std::endl;
        }
    }, val_count);
    thr_push.join();
    thr_pop.join();
    return 0;
}

template <class Object> 
ThreadQueue<Object>::ThreadQueue()
{   
    pthread_mutex_init(&mutex, NULL);
    size = 0;
}

template <class Object> 
ThreadQueue<Object>::~ThreadQueue()   
{   
    pthread_mutex_destroy(&mutex);  
}

template <class Object> 
bool ThreadQueue<Object>::IsEmpty() const  
{   
    if(size == 0)   
        return true;   
    else  
        return false;
}

template <class Object> 
void ThreadQueue<Object>::push(const Object &obj)   
{
    pthread_mutex_lock(&mutex);
    que.push(obj);
    size = que.size();
    pthread_mutex_unlock(&mutex);
}

template <class Object>
Object& ThreadQueue<Object>::pop()   
{   
    pthread_mutex_lock(&mutex);   
    Object& top = que.front();
    que.pop();
    size = que.size();
    pthread_mutex_unlock(&mutex);
    return top;
}

template <class Object> 
int ThreadQueue<Object>::Count() const  
{   
    return(size);
}

template <class Object>
Object& ThreadQueue<Object>::Front()  
{   
    pthread_mutex_lock(&mutex);   
    Object &obj = que.front();
    pthread_mutex_unlock(&mutex);   
    return obj;   
}

template <class Object>
Object& ThreadQueue<Object>::Back()  
{   
    pthread_mutex_lock(&mutex);   
    Object &obj = que.back();
    pthread_mutex_unlock(&mutex);   
    return obj;   
}

template <class Object>
void ThreadQueue<Object>::Clear()   
{   
    pthread_mutex_lock(&mutex);   
    while (!que.empty())
    {
        que.pop();
    }
    size = 0;
    pthread_mutex_unlock(&mutex);   
}
