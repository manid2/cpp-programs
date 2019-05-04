/*
 * producer.h
 *
 *  Created on: 05-May-2019
 *      Author: manid2
 */

#ifndef LEARNCPP_LEARNGTESTANDGMOCK_INC_PRODUCER_H_
#define LEARNCPP_LEARNGTESTANDGMOCK_INC_PRODUCER_H_

#include <string>

namespace PFF {

class Producer {
public:
	virtual ~Producer(){}
	virtual std::string getDomainFromUrl(const std::string & url) const = 0;

	virtual std::string getNameVirt(const std::string & url);
};

} // namespace PFF

#endif /* LEARNCPP_LEARNGTESTANDGMOCK_INC_PRODUCER_H_ */
