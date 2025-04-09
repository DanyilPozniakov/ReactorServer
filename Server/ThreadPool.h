//
// Created by pozni on 3/16/2025.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <thread>
#include <functional>

class ThreadPool
{
public:
    ThreadPool();
    virtual ~ThreadPool();

    void Init();

    void RunThreads();
    void Shutdown();

    void ProcessTask(std::function<void()> task);

private:
    std::vector<std::thread> m_workers;
};


#endif //THREADPOOL_H
