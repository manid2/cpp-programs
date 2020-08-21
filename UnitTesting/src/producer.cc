// gtest and gmock example, producer definitions
#include "producer.hh"

namespace gtest_gmock_ns {

std::string Producer::getNameVirt(const std::string &url)
{
    return std::string("sample string");
}

} // namespace gtest_gmock_ns
