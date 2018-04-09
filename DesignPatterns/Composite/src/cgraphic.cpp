/*
 * cgraphic.cpp
 *
 *  Created on: 29-Jan-2018
 *      Author: Mani Kumar
 */

#include "cgraphic.h"

using namespace std;

namespace mani_dp {

void Line::draw() const {
   cout << "Line draw()\n";
}

void Rectangle::draw() const {
   cout << "Rectangle draw() \n";
}

void Text::draw() const {
   cout << "Text draw() \n";
}

void Picture::add(IGraphic *aGraphic) {
   gList.push_back(aGraphic);
}

void Picture::draw() const {
   cout << "Drawing a picture!\n";
   // for each element in gList, call the draw member function
   for_each(gList.begin(), gList.end(), mem_fun(&IGraphic::draw));
}

}  // namespace mani_dp
