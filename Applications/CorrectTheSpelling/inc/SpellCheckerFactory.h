/*
 * SpellCheckerFactory.h
 *
 *  Created on: 14-Jul-2019
 *      Author: manid2
 */

#ifndef APPLICATIONS_CORRECTTHESPELLING_INC_SPELLCHECKERFACTORY_H_
#define APPLICATIONS_CORRECTTHESPELLING_INC_SPELLCHECKERFACTORY_H_

#include <memory>
#include <ISpellChecker.h>
#include <AspellChecker.h>

namespace PFF {

/**
 * Factory design pattern to return a spell checker object
 */
class SpellCheckerFactory {
public:
  SpellCheckerFactory();
  virtual ~SpellCheckerFactory();

  // NOTE: options to create the spell checker are omitted for simplicity
  std::shared_ptr<ISpellChecker> getSpellChecker(void) const;
};

} /* namespace PFF */

#endif /* APPLICATIONS_CORRECTTHESPELLING_INC_SPELLCHECKERFACTORY_H_ */
