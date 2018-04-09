/*
 * cburgerbuilder.cpp
 *
 *  Created on: 23-Jan-2018
 *      Author: Mani Kumar
 */


#include <iostream>
#include "cburgerbuilder.h"

namespace mani_dp {

Burger::Burger(int size) :
      m_size(size), m_cheese(false), m_peperoni(false), m_lettuce(false), m_tomato(false) {
}

void Burger::showFlavors() const {
   std::cout << m_size;
   if(m_cheese)
      std::cout << "-cheese";
   if(m_peperoni)
      std::cout << "-peperoni";
   if(m_lettuce)
      std::cout << "-lettuce";
   if(m_tomato)
      std::cout << "-tomato";
   std::cout << std::endl;
}

BurgerBuilder::BurgerBuilder(int size) {
   m_burger = new Burger(size);
}

BurgerBuilder& BurgerBuilder::AddCheese() {
   m_burger->m_cheese = true;
   return *this;
}

BurgerBuilder& BurgerBuilder::AddPepperoni() {
   m_burger->m_peperoni = true;
   return *this;
}

BurgerBuilder& BurgerBuilder::AddLettuce() {
   m_burger->m_lettuce = true;
   return *this;
}

BurgerBuilder& BurgerBuilder::AddTomato() {
   m_burger->m_tomato = true;
   return *this;
}

Burger* BurgerBuilder::build() const {
   return m_burger;
}

} // end of namespace mani_dp
