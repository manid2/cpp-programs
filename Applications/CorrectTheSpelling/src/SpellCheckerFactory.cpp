/*
 * SpellCheckerFactory.cpp
 *
 *  Created on: 14-Jul-2019
 *      Author: manid2
 */

#include <SpellCheckerFactory.h>

using namespace std;

namespace PFF {

SpellCheckerFactory::SpellCheckerFactory() {
  // TODO Auto-generated constructor stub

}

SpellCheckerFactory::~SpellCheckerFactory() {
  // TODO Auto-generated destructor stub
}

std::shared_ptr<ISpellChecker> SpellCheckerFactory::getSpellChecker(void) const {
  // NOTE: can be extended to construct different types of spell checkers.
  return make_shared<AspellChecker>();
}

} /* namespace PFF */
