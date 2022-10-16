#ifndef CHANNEL_BUFFERED_CHANNEL_H
#define CHANNEL_BUFFERED_CHANNEL_H
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <iostream>
template<class T>
class BufferedChannel
{
private:
    bool isOpen;
    std::condition_variable cv;
    std::mutex m;
    std::queue<T> q;
    int size;
public:
    BufferedChannel(int s)
    {
        size = s;
        isOpen = true;
    }
    void send(T value)
    {
        std::unique_lock<std::mutex> lock(m);
        if(!isOpen)
        {
            throw std::runtime_error("Channel is closed");
        }
        cv.wait(lock, [&] {return q.size() != size; });
        q.push(value);
        std::cout << "Value " << value << " was added" << std::endl;
        lock.unlock();
        cv.notify_one();
    }
    std::pair<T,bool> recv()
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock,[&] {return !q.empty(); });
        T value = q.front();
        q.pop();
        std::cout << "Value " << value << " was deleted" << std::endl;
        lock.unlock();
        cv.notify_one();
        return std::pair<T,bool>(value,isOpen);
    }
    void close()
    {
        std::lock_guard<std::mutex> lkg(m);
        isOpen = false;
        std::cout << "Channel was closed" << std::endl;
        cv.notify_one();
    }
};
#endif
