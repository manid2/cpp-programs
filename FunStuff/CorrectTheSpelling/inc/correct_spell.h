/*
 * correct_spell.h
 *
 *  Created on: 20-Mar-2018
 *      Author: Mani Kumar
 */

#ifndef CORRECTTHESPELLING_INC_CORRECT_SPELL_H_
#define CORRECTTHESPELLING_INC_CORRECT_SPELL_H_

// C headers
#include <stdio.h>
#include <string.h>
#include <aspell.h>  // for spell check

// C++ headers
#include <iostream>
#include <string>
#include <algorithm>  // std::next_permutation

namespace PFF {

class CorrectTheSpelling {
public:
	CorrectTheSpelling(void){};
	virtual ~CorrectTheSpelling(){};

	bool initiliazeAspell(void);
	bool executeAspell(const char *word, int size);
	bool finalizeAspell(void);

private:
	AspellConfig * spell_config = NULL;
	AspellCanHaveError * possible_err = NULL;
	AspellSpeller * spell_checker = NULL;
};


static int execute(int argc, char **argv) {
	char str_default[] = "ABC";
	char *str = argc == 2 ? argv[1] : str_default;

	CorrectTheSpelling cts;
	cts.initiliazeAspell();

	std::string s(str);
	// sort string into ascending order,
	// so we get all the permutations using std::next_permutation
	std::sort(s.begin(), s.end());
	do {
		//std::cout << " " << s << endl;
		if (cts.executeAspell(s.c_str(), s.size()))
			std::cout << "-> correct word: " << s << std::endl;
	} while (std::next_permutation(s.begin(), s.end()));

	cts.finalizeAspell();
	return 0;
}

} // namespace PFF

#endif /* CORRECTTHESPELLING_INC_CORRECT_SPELL_H_ */
