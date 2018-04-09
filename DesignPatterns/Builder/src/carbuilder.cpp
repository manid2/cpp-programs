/*
 * carm_builder.cpp
 *
 *  Created on: 23-Jan-2018
 *      Author: Mani Kumar
 */

#include "carbuilder.h"

namespace mani_dp {

void Car::specifications() {
   std::cout << "body:" << body->shape << std::endl;
   std::cout << "engine horsepower:" << engine->horsepower << std::endl;
   std::cout << "tire size:" << wheels[0]->size << "'" << std::endl;
}

void Director::setBuilder(Builder *newBuilder) {
   m_builder = newBuilder;
}

Car* Director::getCar() const {
   Car* car = new Car();

   car->body = m_builder->getBody();

   car->engine = m_builder->getEngine();

   car->wheels[0] = m_builder->getWheel();
   car->wheels[1] = m_builder->getWheel();
   car->wheels[2] = m_builder->getWheel();
   car->wheels[3] = m_builder->getWheel();

   return car;
}



} // end of namespace mani_dp
