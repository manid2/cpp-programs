#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

namespace
{

const int MAX_COUNT = 5;
const int SLEEP_FOR = 500;

int count = 1; // shared data
std::mutex mu;
std::condition_variable cond;

// predicate template
template <typename T>
class Predict
{
  const T rem; // remainder
public:
  Predict(const T &v) : rem(v) {}
  bool operator()(void) const { return count % 2 == rem; }
};

// predicates for odd and even numbers
Predict<int> po(1);
Predict<int> pe(0);

void PrintOdd()
{
  for (; count < MAX_COUNT;)
  {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, po); //[](){return count % 2 == 1}
    std::cout << "thread_1 (Odd)   - " << count << std::endl;
    count++;
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_FOR));
    //locker.unlock();
    cond.notify_all();
  }
}

void PrintEven()
{
  for (; count < MAX_COUNT;)
  {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, pe);
    std::cout << "thread_2 (Even)  - " << count << std::endl;
    count++;
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_FOR));
    //locker.unlock();
    cond.notify_all();
  }
}

} // namespace

int main(int argc, char **argv)
{
  std::cout << "--- sequence starts ---" << std::endl;
  std::thread t1(PrintOdd);
  std::thread t2(PrintEven);
  t1.join();
  t2.join();
  std::cout << "--- sequence stop ---" << std::endl;
  return 0;
}
