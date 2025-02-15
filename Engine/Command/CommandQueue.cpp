#include "Precompiled.h"
#include "CommandQueue.h"
#include "DrawCommand.h"

void FCommandQueue::Enqueue(FDrawCommand* InDrawCommand)
{
    std::lock_guard<std::mutex> Lock(QueueMutex);
    CommandQueue.push(InDrawCommand);
}

void FCommandQueue::ExecuteAll()
{
    std::lock_guard<std::mutex> Lock(QueueMutex);

    while (!CommandQueue.empty())
    {
        // 커맨드 실행
        CommandQueue.front()->Execute();

        // 메모리 해제
        delete CommandQueue.front();
        CommandQueue.pop();
    }
}
