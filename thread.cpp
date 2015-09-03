#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "noncopyable.h"
#include "blockingqueue.h"
#include "task.h"
#include "threadpool.h"
#include <unistd.h>

using namespace std;


int main()
{
    ThreadPool pool(8);
    pool.start();
    pool.submit(Task("hello"));

    for(int i = 0;i< 6;i++)
    {
        pool.submit(Task("app"));
    }

    sleep(1);
    //pool.submit(Task("app"));
    pool.stop();
    sleep(2);

    return 0;
}
