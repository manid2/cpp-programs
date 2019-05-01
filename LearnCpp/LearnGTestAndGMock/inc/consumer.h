/*
 * consumer.h
 *
 *  Created on: 02-May-2019
 *      Author: manid2
 */

#ifndef LEARNCPP_LEARNGTESTANDGMOCK_INC_CONSUMER_H_
#define LEARNCPP_LEARNGTESTANDGMOCK_INC_CONSUMER_H_

#include "producer.h"
#include <memory>

namespace PFF {

class Consumer {
 public:
  Consumer();
  Consumer(Producer *p);
  void fCallNameVirt(void);

 private:
  std::shared_ptr<Producer> m_producer;
};

// entry func into producer class
extern int execute(int argc, char **argv);

}  // namespace PFF

#endif /* LEARNCPP_LEARNGTESTANDGMOCK_INC_CONSUMER_H_ */
