/*
 * cgraphic.h
 *
 *  Created on: 29-Jan-2018
 *      Author: Mani Kumar
 */

#ifndef COMPOSITE_CGRAPHIC_H_
#define COMPOSITE_CGRAPHIC_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

namespace mani_dp {

// Composite Interface
class IGraphic {
public:
   virtual ~IGraphic(){}

   virtual void draw() const = 0;

   virtual void remove(IGraphic *g){}
   virtual void add(IGraphic *g){}
   virtual void getChild(int){}
};

// Leaf #1
class Line: public IGraphic {
public:
   void draw() const;
};

// Leaf #2
class Rectangle: public IGraphic {
public:
   void draw() const;
};

// Leaf #3
class Text: public IGraphic {
public:
   void draw() const;
};

// Composite
class Picture: public IGraphic {
public:
   void draw() const;
   void add(IGraphic *aGraphic);

private:
   std::vector<IGraphic*> gList;
};

static int execute() {
   Line line;
   Rectangle rect;
   Text text;

   Picture pic;
   pic.add(&line);
   pic.add(&rect);
   pic.add(&text);
   pic.add(&rect);
   pic.draw();

   return 0;
}

} // end of namespace mani_dp

#endif /* COMPOSITE_CGRAPHIC_H_ */
