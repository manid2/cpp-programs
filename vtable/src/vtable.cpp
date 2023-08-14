/*
 * vtable.cpp
 *
 *  Created on: 25-Nov-2019
 *      Author: Mani Kumar
 */

#include "vtable.h"

namespace PFF {

RuntimeBehaviour::RuntimeBehaviour() {
}

RuntimeBehaviour::~RuntimeBehaviour() {
}

void RuntimeBehaviour::runtimePolymorphismDemo(void) {
  std::shared_ptr<Vehicle> v(new Vehicle());
  v->ApplyBreaks();  //Calls vehicle ApplyBreak
  v->ApplyHorns();  //Calls vehicle ApplyHorn
  std::cout << endl;

  v = std::make_shared<Truck>();
  v->ApplyBreaks();  //calls Truck ApplyBreak
  v->ApplyHorns();  //calls Vehicle ApplyHorn
  std::cout << endl;

  v = std::make_shared<Car>();
  v->ApplyBreaks();  //calls Truck ApplyBreak
  v->ApplyHorns();  //calls Vehicle ApplyHorn
  std::cout << endl;

  std::cout << "sizeof(Vehicle): " << sizeof(Vehicle) << endl;
  std::cout << "sizeof(Truck)  : " << sizeof(Truck) << endl;
  std::cout << "sizeof(Car)    : " << sizeof(Car) << endl;
}

} /* namespace PFF */
