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
// error test data
const vector<string> EmptyWords = { "", "", "" };
const vector<char const*> NullPtrs = { 0, 0, 0 };
const vector<string> LargeWords = { "Number12345", "012345678910",
    "ABCDEFGHIJKLMNOPG" };
// boundary values test data
const vector<string> OneChar = { "a", "b", "c" };
// NOTE: These max (10) chars are provided to be correct for use in
// boundary test cases. If random incorrect words are used then the test
// breaks due to lack of expected output to verify the boundary condition.
const vector<string> MaxChar = { "Everything", "Basketball", "Literature" };

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
  // verify CorrectTheSpelling::checkSpelling(char const *str) variant
  for (auto s : CorrectWords) {
    CorrectTheSpelling cts;
    cts.checkSpelling(s.c_str());
    string c = cts.getCorrectedWord();
    EXPECT_EQ(s, c);
  }
}

/*
 * Error handling tests - to verify the error handling of the application for
 * error inputs.
 */
TEST(CorrectTheSpelling, ErrorHandling) {
  // empty string
  for (auto s : EmptyWords) {
    CorrectTheSpelling cts(s);
    EXPECT_FALSE(cts.checkSpelling());
  }
  // null ptr
  for (auto s : NullPtrs) {
    CorrectTheSpelling cts;
    EXPECT_FALSE(cts.checkSpelling(s));
  }
  // large string
  for (auto s : LargeWords) {
    CorrectTheSpelling cts;
    EXPECT_FALSE(cts.checkSpelling(s));
  }
}

/*
 * Input combination tests - to verify the behavior and correctness of the
 * application for all possible inputs.
 */
TEST(CorrectTheSpelling, Combinations) {
/* NOTE: since only one string is input to this code hence no input
   combination tests are written. Input combo tests are written when
   there are multiple inputs given to the code. */
}

/*
 * Boundary tests - to verify the edge cases and limits of the applications.
 */
TEST(CorrectTheSpelling, Boundaries) {
  // single char strings
  for (auto s : OneChar) {
    CorrectTheSpelling cts(s);
    EXPECT_TRUE(cts.checkSpelling());
  }
  // max char strings
  for (auto s : MaxChar) {
    CorrectTheSpelling cts(s);
    EXPECT_TRUE(cts.checkSpelling());
  }
}

/*
 * Performance tests - to verify time and space requirements of the
 * application code.
 */
TEST(CorrectTheSpelling, Performance) {
/* Intentionally leaving this tests blank to give an opportunity
   to write your own tests for this case. */
}

}  // namespace
