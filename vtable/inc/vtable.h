/*
 * vtable.h
 *
 *  Created on: 25-Nov-2019
 *      Author: Mani Kumar
 */

#ifndef _LEARNCPPCONCEPTS_VTABLE_INC_H_
#define _LEARNCPPCONCEPTS_VTABLE_INC_H_

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
  // function to call for each concept in cpp related to virtual table
  void runtimePolymorphismDemo(void);
  void virtualDestructorDemo(void);
};

} /* namespace PFF */

#endif /* _LEARNCPPCONCEPTS_VTABLE_INC_H_ */
