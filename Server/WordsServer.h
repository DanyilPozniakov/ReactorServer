//
// Created by pozni on 3/2/2025.
//

#ifndef WORDSSERVER_H
#define WORDSSERVER_H

#include <thread>
#include <vector>

#include "TaskManager.h"

class WordsServer
{
public:
    WordsServer();
    virtual ~WordsServer();

    void Init();
    void Run();
    void Shutdown();

    [[nodiscard]] TaskManager* GetTaskManager() const;

    TaskManager* m_taskManager;



private:
    std::thread m_socketThread;
};



#endif //WORDSSERVER_H
