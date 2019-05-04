/*
 * test_producer.cpp
 *
 *  Created on: 01-Mar-2018
 *      Author: mani
 */

#include "test_precomp.h"
#include "producer.h"
#include "consumer.h"

using namespace PFF;

namespace {

class ProducerMock : public Producer {
 public:
  MOCK_CONST_METHOD1(getDomainFromUrl, std::string(const std::string & url) );
};

TEST(Consumer, CalculateDomainLevel) {
  const std::string url = "http://www.fantasticdomain.com/site/index.html";
  std::string domain = "fantasticdomain.com";
  ProducerMock mock;
  Consumer consumer(&mock);
  EXPECT_CALL(mock, getDomainFromUrl(url)).WillOnce(::testing::Return(domain));
  int domainLevel = consumer.countLevelOfDomain(url);
  EXPECT_EQ(domainLevel, 2);
}

}  // namespace
