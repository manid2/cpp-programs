/*
 * Example to show vtable in C++
 * =============================
 *
 * Refer
 * -----
 *
 * https://www.hackerearth.com/practice/notes/virtual-function-and-virtual-table-in-c/
 */

#include <iostream>
#include <memory>

using namespace std;

// base class
class Vehicle
{
public:
	virtual void ApplyBreaks() { cout << "Vehicle Breaks" << endl; }
	virtual void ApplyHorns() { cout << "Vehicle Horns" << endl; }
};

// derived class 1
class Truck : public Vehicle
{
public:
	void ApplyBreaks() { cout << "-> Truck Breaks" << endl; }
};

// derived class 2
class Car : public Vehicle
{
public:
	void ApplyHorns() { cout << "-> Car Horns" << endl; }
};

// class to demo each concept
class RuntimeBehaviour
{
public:
	void runtimePolymorphismDemo(void);
};

void RuntimeBehaviour::runtimePolymorphismDemo(void)
{
	shared_ptr<Vehicle> v(new Vehicle());
	v->ApplyBreaks(); //Calls vehicle ApplyBreak
	v->ApplyHorns();  //Calls vehicle ApplyHorn
	cout << endl;

	v = make_shared<Truck>();
	v->ApplyBreaks(); //calls Truck ApplyBreak
	v->ApplyHorns();  //calls Vehicle ApplyHorn
	cout << endl;

	v = make_shared<Car>();
	v->ApplyBreaks(); //calls Truck ApplyBreak
	v->ApplyHorns();  //calls Vehicle ApplyHorn
	cout << endl;

	cout << "sizeof(Vehicle): " << sizeof(Vehicle) << endl;
	cout << "sizeof(Truck)  : " << sizeof(Truck) << endl;
	cout << "sizeof(Car)    : " << sizeof(Car) << endl;
}

int main(int, char **)
{
	RuntimeBehaviour rb;
	rb.runtimePolymorphismDemo();
	return 0;
}
