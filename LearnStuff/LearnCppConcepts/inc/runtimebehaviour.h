/*
 * runtimebehaviour.h
 *
 *  Created on: 22-Aug-2018
 *      Author: mani
 */

#ifndef LEARNSTUFF_LEARNCPPCONCEPTS_INC_RUNTIMEBEHAVIOUR_H_
#define LEARNSTUFF_LEARNCPPCONCEPTS_INC_RUNTIMEBEHAVIOUR_H_

#include <iostream>
#include <memory>

using namespace std;

namespace PFF {

// below code taken from
// https://www.hackerearth.com/practice/notes/virtual-function-and-virtual-table-in-c/
// base class
class Vehicle {
 public:
  virtual void ApplyBreaks() {
    cout << "Vehicle Breaks" << endl;
  }
  virtual void ApplyHorns() {
    cout << "Vehicle Horns" << endl;
  }
};

// derived class 1
class Truck : public Vehicle {
 public:
  void ApplyBreaks() {
    cout << "-> Truck Breaks" << endl;
  }
};

// derived class 2
class Car : public Vehicle {
 public:
  void ApplyHorns() {
    cout << "-> Car Horns" << endl;
  }
};

// class to demo each concept
class RuntimeBehaviour {
 public:
  RuntimeBehaviour();
  virtual ~RuntimeBehaviour();

 public:
  // functions to call for each concept in cpp related to virtual table
  void runtimePolymorphismDemo(void);
};

static int execute(int argc, char **argv) {
  RuntimeBehaviour rb;
  rb.runtimePolymorphismDemo();
  return 0;
}

} /* namespace PFF */

#endif /* LEARNSTUFF_LEARNCPPCONCEPTS_INC_RUNTIMEBEHAVIOUR_H_ */
