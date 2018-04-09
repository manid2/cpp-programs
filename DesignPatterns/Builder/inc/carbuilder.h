/*
 * carbuilder.h
 *
 *  Created on: 23-Jan-2018
 *      Author: Mani Kumar
 */

#ifndef BUILDER_INC_CARBUILDER_H_
#define BUILDER_INC_CARBUILDER_H_

#include <iostream>
#include <string>

namespace mani_dp {

/* Car parts */
class Wheel {
public:
   int size;
};

class Engine {
public:
   int horsepower;
};

class Body {
public:
   std::string shape;
};

/* Final product -- a car */
class Car {
public:
   Wheel* wheels[4];
   Engine* engine;
   Body* body;

   void specifications();
};

/* Builder is responsible for constructing the smaller parts */
class Builder {
public:
   virtual ~Builder() {};
   virtual Wheel* getWheel() = 0;
   virtual Engine* getEngine() = 0;
   virtual Body* getBody() = 0;
};

/* Director is responsible for the whole process */
class Director {
private:
   Builder* m_builder;

public:
   void setBuilder(Builder* newBuilder);
   Car* getCar() const;
};

/* Concrete Builder for Jeep SUV cars */
class JeepBuilder : public Builder
{
    public:
        Wheel* getWheel()
        {
            Wheel* wheel = new Wheel();
            wheel->size = 22;
            return wheel;
        }

        Engine* getEngine()
        {
            Engine* engine = new Engine();
            engine->horsepower = 400;
            return engine;
        }

        Body* getBody()
        {
            Body* body = new Body();
            body->shape = "SUV";
            return body;
        }
};

/* Concrete builder for Nissan family cars */
class NissanBuilder : public Builder
{
    public:
        Wheel* getWheel()
        {
            Wheel* wheel = new Wheel();
            wheel->size = 16;
            return wheel;
        }

        Engine* getEngine()
        {
            Engine* engine = new Engine();
            engine->horsepower = 85;
            return engine;
        }

        Body* getBody()
        {
            Body* body = new Body();
            body->shape = "hatchback";
            return body;
        }
};

static void execute()
{
   // Car builder
      Car* car;  // Final product

      /* A director who controls the process */
      Director director;

      /* Concrete builders */
      JeepBuilder jeepBuilder;
      NissanBuilder nissanBuilder;

      /* Build a Jeep */
      std::cout << "Jeep" << std::endl;
      director.setBuilder(&jeepBuilder);  // using JeepBuilder instance
      car = director.getCar();
      car->specifications();

      std::cout << std::endl;

      /* Build a Nissan */
      std::cout << "Nissan" << std::endl;
      director.setBuilder(&nissanBuilder);  // using NissanBuilder instance
      car = director.getCar();
      car->specifications();
}

}  // end of namespace mani_dp

#endif /* BUILDER_INC_CARBUILDER_H_ */
