#pragma once

class FDrawCommand;

class ENGINE_API FCommandQueue
{
public:
    void Enqueue(FDrawCommand* InDrawCommand);
    void ExecuteAll();

private:
    std::queue<FDrawCommand*> CommandQueue;
    std::mutex QueueMutex;
};
