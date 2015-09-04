#include "blockingqueue.h"

BlockingQueue::BlockingQueue():quit(false)
{

}

BlockingQueue::~BlockingQueue()
{

}

void BlockingQueue::put(Task&& t)
{
    std::unique_lock<std::mutex> lock(mtx);
    queue.push(std::move(t));

    cond.notify_all();
}

Task BlockingQueue::take()
{
    std::unique_lock<std::mutex> lock(mtx);
    while(queue.empty() && !quit)
    {
        cond.wait(lock);
    }
    if(!quit)
    {
        Task t(std::move(queue.front()));
        queue.pop();
        return t;
    }else
    {
        return Task("quit");
    }
}

int BlockingQueue::size()
{
    std::unique_lock<std::mutex> lock(mtx);
    return queue.size();
}

//signal to wake up all blocking take thread
void BlockingQueue::wakeupAndQuit()
{
    quit = true;
    cond.notify_all();
}

