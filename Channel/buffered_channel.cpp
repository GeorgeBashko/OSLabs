#include "buffered_channel.h"
BufferedChannel<int>bc(5);
void threadTest1();
void threadTest2();
int main() {
    std::thread thread1(threadTest1);
    std::thread thread2(threadTest2);
    thread1.join();
    thread2.join();
    return 0;
}
void threadTest1()
{
    bc.send(1);
    bc.send(2);
    bc.send(3);
    std::this_thread::sleep_for(std::chrono::seconds(7));
    bc.send(4);
    bc.send(5);
    bc.recv();
    bc.recv();
    bc.recv();
    bc.recv();
}
void threadTest2()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    bc.recv();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    bc.recv();
    bc.send(6);
    bc.send(7);
    bc.send(8);
    bc.close();
    bc.send(9);
}
