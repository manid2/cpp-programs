#ifndef _INC_PRODUCER_H_
#define _INC_PRODUCER_H_

#include <iostream>
#include <string>

namespace PFF {

class Producer {
 public:
  // ctor
  Producer();
  // dtor
  virtual ~Producer();

  // virtual function
  virtual std::string getNameVirt(const std::string& name);

  // non-virtual function
  // virtual std::string getNameNonVirt(const std::string& name);
};

}  // namespace PFF

#endif  // _INC_PRODUCER_H_
