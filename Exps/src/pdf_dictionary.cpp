/*
 * pdf_dictionary.cpp
 *
 *  Created on: 10-May-2018
 *      Author: Mani Kumar
 */

#include <pdf_dictionary.h>

namespace LilPDF {

PDFDictionary::PDFDictionary() {
  init();
  _type = dictionary_type;
}

PDFDictionary::PDFDictionary(const PDFDictionary_t &d) {
  init();
  _type = dictionary_type;
  _uval.dictionary = new PDFDictionary_t(d);
  DEBUG_INF(" _type = %d\n", _type);
}

PDFDictionary::~PDFDictionary() {
  clear();
}

PDFDictionary &PDFDictionary::operator=(const PDFDictionary_t &d) {
  init();
  _type = real_type;
  _uval.dictionary = new PDFDictionary_t(d);
  DEBUG_INF(" _type = %d\n", _type);
  return *this;
}

} /* namespace LilPDF */
