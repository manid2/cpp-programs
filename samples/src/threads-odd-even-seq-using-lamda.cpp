#include <iostream> // std::cout
#include <thread>   // std::thread
#include <mutex>    // std::mutex
#include <condition_variable>

using namespace std;

namespace
{

std::mutex mu;
std::condition_variable cond;

int count = 1;

void PrintOdd(int num)
{
  for (int i = 0; i < num; i++)
  {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, []() { return (count % 2 == 1); });
    cout << "Thread_A: " << count << endl;
    count++;
    locker.unlock();
    cond.notify_all();
  }
}

void PrintEven(int num)
{
  for (int i = 0; i < num; i++)
  {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, []() { return (count % 2 == 0); });
    cout << "Thread_B: " << count << endl;
    count++;
    locker.unlock();
    cond.notify_all();
  }
}

} /* namespace */

int main(int argc, char **argv)
{
  std::cout << "--- sequence starts ---" << std::endl;
  std::thread t1(PrintOdd, 3);
  std::thread t2(PrintEven, 3);
  t1.join();
  t2.join();
  std::cout << "--- sequence stop ---" << std::endl;
  return 0;
}
