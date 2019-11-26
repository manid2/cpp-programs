/*
 * test_carbuilder.cpp
 *
 *  Created on: 26-Nov-2019
 *      Author: Mani Kumar
 */

#include "test_precomp.h"
#include "carbuilder.h"

using namespace mani_dp;

namespace {

// Test fixture class
class CarBuilderTest : public ::testing::Test {
 protected:
  void SetUp() override {
    this->car = NULL;
  }

  // void TearDown() override {}

  Car *car;
  Director director;
};

TEST_F(CarBuilderTest, JeepBuilder_Body) {
  JeepBuilder jeepBuilder;
  director.setBuilder(&jeepBuilder);
  car = director.getCar();
  EXPECT_EQ(car->body->shape, "SUV");
}

TEST_F(CarBuilderTest, JeepBuilder_Engine) {
  JeepBuilder jeepBuilder;
  director.setBuilder(&jeepBuilder);
  car = director.getCar();
  EXPECT_EQ(car->engine->horsepower, 400);
}

} /* namespace */
