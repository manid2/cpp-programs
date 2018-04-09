/*
 * cburgerbuilder.h
 *
 *  Created on: 23-Jan-2018
 *      Author: Mani Kumar
 */

#ifndef BUILDER_INC_CBURGERBUILDER_H_
#define BUILDER_INC_CBURGERBUILDER_H_


namespace mani_dp {

// Forward declarations
class Burger;
class BurgerBuilder;

class Burger {
public:
   Burger(int size);
   void showFlavors() const;

public:
   int  m_size;
   bool m_cheese;
   bool m_peperoni;
   bool m_lettuce;
   bool m_tomato;
};

class BurgerBuilder {
public:
   BurgerBuilder(int size);
   virtual ~BurgerBuilder(){};

   BurgerBuilder& AddCheese();
   BurgerBuilder& AddPepperoni();
   BurgerBuilder& AddLettuce();
   BurgerBuilder& AddTomato();
   Burger* build() const;
private:
   Burger* m_burger;
};

static void execute()
{
   Burger *burger = BurgerBuilder(12).AddCheese().AddLettuce().AddTomato().build();
   burger->showFlavors();
}

} // end of namespace mani_dp

#endif /* BUILDER_INC_CBURGERBUILDER_H_ */
