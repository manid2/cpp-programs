/*
 * runtimebehaviour.cpp
 *
 *  Created on: 22-Aug-2018
 *      Author: mani
 */

#include "runtimebehaviour.h"

namespace PFF {

RuntimeBehaviour::RuntimeBehaviour() {
  // TODO Auto-generated constructor stub

}

RuntimeBehaviour::~RuntimeBehaviour() {
  // TODO Auto-generated destructor stub
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
