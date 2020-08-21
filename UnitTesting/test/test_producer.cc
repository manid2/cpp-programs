// gtest and gmock example, produce tests by mocking
#include "test_precomp.hh"
#include "producer.hh"
#include "consumer.hh"

using namespace gtest_gmock_ns;

namespace {

class ProducerMock : public Producer {
public:
    MOCK_CONST_METHOD1(getDomainFromUrl, std::string(const std::string &url));
};

TEST(Consumer, CalculateDomainLevel)
{
    const std::string url = "http://www.fantasticdomain.com/site/index.html";
    std::string domain = "fantasticdomain.com";
    ProducerMock mock;
    Consumer consumer(&mock);
    EXPECT_CALL(mock, getDomainFromUrl(url))
        .WillOnce(::testing::Return(domain));
    int domainLevel = consumer.countLevelOfDomain(url);
    EXPECT_EQ(domainLevel, 2);
}

} // namespace
