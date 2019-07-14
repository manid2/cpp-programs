/*
 * test_CorrectSpell.cpp
 *
 *  Created on: 13-Jul-2019
 *      Author: Mani Kumar
 */

#include "test_precomp.h"
#include "CorrectSpell.h"
#include <vector>

using namespace std;
using namespace PFF;

namespace {

// Test data
const vector<string> CorrectWords = { "hello", "world", "word" }; // same output words
const vector<string> ToBeCorrectWords = { "olleh", "dworl", "dwor" }; // to be corrected words
const vector<string> WrongWords = { "anam", "mana", "paru" }; // no output words
const vector<string> LargeWords = { "Number12345", "012345678910",
    "ABCDEFGHIJKLMNOPG" }; // large words are invalid inputs

/*
 * Functional tests - to verify the working of the application for correct
 * inputs.
 */
TEST(CorrectTheSpelling, Functional) {
  // same output words
  for (auto s : CorrectWords) {
    CorrectTheSpelling cts(s);
    cts.checkSpelling();
    string c = cts.getCorrectedWord();
    EXPECT_EQ(s, c);
  }
  // to be corrected words
  for (size_t i = 0; i < ToBeCorrectWords.size(); ++i) {
    string s = ToBeCorrectWords.at(i);
    CorrectTheSpelling cts(s);
    cts.checkSpelling();
    string c = cts.getCorrectedWord();
    EXPECT_EQ(c, CorrectWords.at(i));
  }
  // no output words
  for (auto s : WrongWords) {
    CorrectTheSpelling cts(s);
    cts.checkSpelling();
    string c = cts.getCorrectedWord();
    EXPECT_TRUE(c.empty());
  }
  // TODO verify c'tors
  // TODO verify APIs
}

/*
 * Error handling tests - to verify the error handling of the application for
 * error inputs.
 */
TEST(CorrectTheSpelling, ErrorHandling) {

}

/*
 * Input combination tests - to verify the behavior and correctness of the
 * application for all possible inputs.
 */
TEST(CorrectTheSpelling, Combinations) {

}

/*
 * Boundary tests - to verify the edge cases and limits of the applications.
 */
TEST(CorrectTheSpelling, Boundaries) {

}

/*
 * Performance tests - to verify time and space requirements of the
 * application code.
 */
TEST(CorrectTheSpelling, Performance) {

}

}  // namespace
