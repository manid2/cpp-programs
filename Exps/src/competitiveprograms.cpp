/*
 * competitiveprograms.cpp
 *
 *  Created on: 31-Jul-2018
 *      Author: mani
 */

#include <competitiveprograms.h>

namespace PFF {

CompetitivePrograms::CompetitivePrograms() {
  // TODO Auto-generated constructor stub

}

CompetitivePrograms::~CompetitivePrograms() {
  // TODO Auto-generated destructor stub
}

void CompetitivePrograms::pipe2commaSeparatedValues(void) {

  string li, na, no;
  while (cin >> li) {
    size_t pi = li.find_first_of("|");
    if (string::npos != pi) {
      na = li.substr(0, pi);
      no = li.substr(pi + 1);
      if (na.empty() || no.empty()) {
        cout << "\n";
        continue;
      }
      cout << na << "," << no << "\n";
    } else
      cout << "\n";
  }
}

} /* namespace PFF */
