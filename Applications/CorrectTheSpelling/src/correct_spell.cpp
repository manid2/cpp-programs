/*
 * correct_spell.cpp
 *
 *  Created on: 20-Mar-2018
 *      Author: Mani Kumar
 */

// Code to print permutate string is borrowed from 
// https://stackoverflow.com/questions/1995328/are-there-any-better-methods-to-do-permutation-of-string

#include "correct_spell.h"

using namespace std;

namespace PFF {

bool CorrectTheSpelling::initiliazeAspell(void) {

	// check if the current permutation is a valid English word.
	spell_config = new_aspell_config();
	aspell_config_replace(spell_config, "lang", "en_GB");
	aspell_config_replace(spell_config, "ignore-case", "true");

	possible_err = new_aspell_speller(spell_config);

	if (aspell_error_number(possible_err) != 0)
		puts(aspell_error_message(possible_err));
	else
		spell_checker = to_aspell_speller(possible_err);

	std::cout << "initialized aspell!" << std::endl;
	return true;
}

bool CorrectTheSpelling::executeAspell(const char *word, int size) {
	bool isCorrectWord = false;

	int correct = aspell_speller_check(spell_checker, word, size);
	switch (correct) {
	case 1: /* the word is in the dictionary, hence print it */
		//std::cout << " " << word << endl;
		isCorrectWord = true;
		break;
	case -1: /* some error! */
	case 0: /* the word is not in the dictionary! */
	default: /* do nothing! */
		;
	}

	return isCorrectWord;
}

bool CorrectTheSpelling::finalizeAspell(void) {
	delete_aspell_config(spell_config);
	delete_aspell_speller(spell_checker);
	std::cout << "finalized aspell!" << std::endl;
	return true;
}

} // namespace PFF
