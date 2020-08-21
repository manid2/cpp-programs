// gtest and gmock example, producer declarations
#ifndef _PRODUCER_H_
#define _PRODUCER_H_

#include <string>

namespace gtest_gmock_ns {

class Producer {
public:
    virtual ~Producer() {}
    virtual std::string getDomainFromUrl(const std::string &url) const = 0;

    virtual std::string getNameVirt(const std::string &url);
};

} // namespace gtest_gmock_ns

#endif /* _PRODUCER_H_ */
