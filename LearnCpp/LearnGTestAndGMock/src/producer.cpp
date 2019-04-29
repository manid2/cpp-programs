#include "producer.h"

using namespace std;

namespace PFF {

// ctor
Producer::Producer() { cout << "Producer(), enter" << endl; }

// dtor
Producer::~Producer() { cout << "~Producer(), enter" << endl; }

// virtual function
std::string Producer::getNameVirt(const std::string& name) {
  string val("in src code");
  //cout << "\tProducer::getNameVirt(), val=[" << val << "]" << endl;
  return val + "_args=" + name;
}

}  // namespace PFF