#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "noncopyable.h"
#include "blockingqueue.h"

#include <vector>
#include <thread>
#include <queue>
#include <future>
#include <algorithm>
#include <iostream>
class ThreadPool : public NonCopyable
{
public:
    ThreadPool(int size);
    ~ThreadPool();
    void start();
    void stop();
    template<class F, class... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    void run();
    std::vector<std::thread> pool;
    int size;
    BlockingQueue queue;
    bool running;
};

ThreadPool::ThreadPool(int num):pool(num),size(num),running(false){}

ThreadPool::~ThreadPool()
{
    if(running)
        stop();
}

void ThreadPool::run()
{
    while(running)
    {
        std::function<void()>task(std::move(queue.take()));
        task();
    }
    //std::cout<<"brk\n";
}

void ThreadPool::start()
{
    running = true;
    for(int i = 0;i < size;i++)
    {
       pool[i] = std::thread(&ThreadPool::run,this);
    }
}

void ThreadPool::stop()
{
    running = false;
    queue.wakeupAndQuit();
    for_each(pool.begin(),pool.end(),std::bind(std::thread::join,std::placeholders::_1));

}

template<class F, class... Args>
auto ThreadPool::submit(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

    std::future<return_type> res = task->get_future();
    queue.put([task](){(*task)();});

    return res;
}

#endif // THREADPOOL_H
