#include "blockingqueue.h"

BlockingQueue::BlockingQueue():quit(false)
{

}

BlockingQueue::~BlockingQueue()
{

}

void BlockingQueue::put(std::function<void()>&& f)
{
    std::unique_lock<std::mutex> lock(mtx);
    queue.push(std::move(f));
    cond.notify_all();
}

std::function<void()> BlockingQueue::take()
{
    std::unique_lock<std::mutex> lock(mtx);
    while(queue.empty() && !quit)
    {
        cond.wait(lock);
    }
    if(!quit)
    {
        std::function<void()> task(std::move(queue.front()));
        queue.pop();
        return task;
    }else
    {
        return ([](){});
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

