/*
 * consumer.h
 *
 *  Created on: 05-May-2019
 *      Author: manid2
 */

#ifndef LEARNCPP_LEARNGTESTANDGMOCK_INC_CONSUMER_H_
#define LEARNCPP_LEARNGTESTANDGMOCK_INC_CONSUMER_H_

#include <string>
#include <algorithm>

#include "producer.h"

namespace PFF {

class Consumer {
 public:
  Consumer(Producer *p)
      : producer(p) {
  }
  int countLevelOfDomain(const std::string & url) const;

 private:
  Producer *producer;
};

extern int execute(int argc, char **argv);

}  // namespace PFF

#endif /*CONSUMER_H*/
