// gtest and gmock example, consumer definitions
#include "consumer.hh"

namespace gtest_gmock_ns {

int Consumer::countLevelOfDomain(const std::string &url) const
{
    std::string domain = producer->getDomainFromUrl(url);
    return std::count(domain.begin(), domain.end(), '.') + 1;
}

int execute(int argc, char **argv) { return 0; }

} // namespace gtest_gmock_ns
