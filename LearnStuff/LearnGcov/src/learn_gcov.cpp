/*
 * learn_gcov.h
 *
 *  Created on: 20-Mar-2018
 *      Author: Mani Kumar
 */

#include "learn_gcov_func.h"

using namespace std;

namespace PFF {

void showChoices() {
	cout << "MENU" << endl;
	cout << "1: Add " << endl;
	cout << "2: Subtract" << endl;
	cout << "3: Multiply " << endl;
	cout << "4: Divide " << endl;
	cout << "5: Exit " << endl;
	cout << "Enter your choice :";
}

float add(float a, float b) {
	return a + b;
}

float subtract(float a, float b) {
	return a - b;
}

float multiply(float a, float b) {
	return a * b;
}

float divide(float a, float b) {
	return a / b;
}

}  // namespace PFF
