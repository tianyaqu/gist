#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <vector>
#include "noncopyable.h"
#include "blockingqueue.h"
#include "task.h"
#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

BlockingQueue q;
mutex mx;
void thread_task(std::string name)
{
    //mx.lock();
    //lock_guard<mutex> lck(mx);
    //cout<<"thread "<<id<<" over"<<endl;

    //Task x(id);

        q.put(Task(name));
}

void thread_take()
{
    Task x(std::move(q.take()));
    //cout<<x.get_id()<<endl;
}

void func_1()
{
    while(1)
    {
        std::cout<<"y "<<q.size()<<" \n";
        Task t = q.take();
        //Task t(std::move(queue.take()));
        std::cout<<t.get_id()<<" "<<t.get_name()<<std::endl;
        //t.execute();
    }
}

void ff(int& x)
{
    x = x*2;
}

int main()
{
#if 0
    vector<thread> threads(10);
    //thread t(thread_task);
    for(int i= 0 ;i< 10;i++)
    {
        if(i < 3)
        {
            //string n = string('0' + i);
            string name = "app#";
            name.append(1,char('0'+i));

            threads[i] = thread(thread_task,name);
        }
        else
            threads[i] = thread(func_1);
    }


    //for(auto& th: threads) th.join();
    for_each(threads.begin(),threads.end(),bind(thread::join,placeholders::_1));

    int x[]= {19,34,88,90};
    vector<int> v(x,x+4);

    int d = 0;
    for_each(v.begin(),v.end(),bind(ff,placeholders::_1));
    //for(auto ch : v) cout<<ch<<" ";
#endif
#if 0
    std::vector<std::thread> pool(6);
    for(int i = 0;i < 6;i++)
    {
        pool[i] = thread(thread_take);
    }

    for_each(pool.begin(),pool.end(),bind(thread::join,placeholders::_1));
#endif
    //for_each(v.begin(),v.end(),[&d](int x){cout<<x<<"";});
    //A x = A(9);
    //cout<<x.put();
    //

#if 1
    ThreadPool pool(8);
    pool.start();
    pool.submit(Task("hello"));
    //cout<<pool.queue.size()<<" ";

    for(int i = 0;i< 6;i++)
    {
        pool.submit(Task("app"));
    }
    //pool.submit(Task("world"));
    //pool.submit(Task("worldx"));
    //pool.submit(Task("worldy"));
    //cout<<pool.queue.size()<<" ";

    //pool.start();
    sleep(1);
    //pool.submit(Task("app"));
    pool.stop();
    sleep(2);

    //pool.submit(Task("hello"));
    //pool.submit(Task("world"));


#endif
    //cout<<d;
    return 0;
}
