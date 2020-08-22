// gtest and gmock example, consumer declarations
#ifndef _CONSUMER_H_
#define _CONSUMER_H_

#include "producer.hh"
#include <algorithm>

namespace gtest_gmock_ns {

class Consumer {
public:
    Consumer(Producer *p) : producer(p) {}
    int countLevelOfDomain(const std::string &url) const;

private:
    Producer *producer;
};

extern int execute(int argc, char **argv);

} // namespace gtest_gmock_ns

#endif /*CONSUMER_H*/
