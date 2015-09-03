#include "threadpool.h"
#include <algorithm>
#include <iostream>

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
        Task t(std::move(queue.take()));
        std::cout<<t.get_name()<<std::endl;
    }
    std::cout<<"brk\n";
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

void ThreadPool::submit(Task&& x)
{
    queue.put(std::move(x));
}

