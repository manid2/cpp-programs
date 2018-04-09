/*
 * corganization.h
 *
 *  Created on: 29-Jan-2018
 *      Author: Mani Kumar
 */

#ifndef COMPOSITE_CORGANIZATION_H_
#define COMPOSITE_CORGANIZATION_H_

#include <iostream>
#include <string>
#include <vector>

namespace mani_dp {

class Employee {
public:
   virtual ~Employee() { };
   Employee(const std::string& name, float salary) :
         name_(name), salary_(salary) {
   }
   virtual std::string GetName() {
      return name_;
   }
   virtual float GetSalary() {
      return salary_;
   }

protected:
   float salary_;
   std::string name_;
};

class Developer : public Employee {
public:
    Developer(const std::string& name, float salary) : Employee(name, salary) {}
};

class Designer : public Employee {
public:
    Designer(const std::string& name, float salary) : Employee(name, salary) {}
};

/*
 * Contains the organization information.
 */
class COrganization {
public:
   virtual ~COrganization() { };

   void AddEmployee(const Employee& employee) {
      employees_.push_back(employee);
   }

   float GetNetSalaries() {
      float net_salary = 0;
      for(auto&& employee : employees_) {
         net_salary += employee.GetSalary();
      }
      return net_salary;
   }

private:
   std::vector<Employee> employees_;
};

static int execute()
{
    Developer john("John Doe", 12000);
    Designer jane("M J", 15001);

    COrganization org;
    org.AddEmployee(john);
    org.AddEmployee(jane);

    std::cout << "Net salaries: " << org.GetNetSalaries() << std::endl;
    return 0;
}

} /* namespace mani_dp */

#endif /* COMPOSITE_CORGANIZATION_H_ */
