#include "consumer.h"

using namespace std;

namespace PFF {

Consumer::Consumer() {
  m_producer = std::make_shared<Producer>();
}

Consumer::Consumer(Producer *p) {
  this->m_producer.reset(p);
}

void Consumer::fCallNameVirt() {
  std::cout << m_producer->getNameVirt("Consumer::fCallNameVirt()")
            << std::endl;
}

int execute(int argc, char **argv) {
  Consumer client;
  client.fCallNameVirt();
  return 0;
}

}
