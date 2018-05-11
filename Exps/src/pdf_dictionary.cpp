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
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
}

PDFDictionary::~PDFDictionary() {
  clear();
}

PDFDictionary &PDFDictionary::operator=(const PDFDictionary_t &d) {
  init();
  _type = real_type;
  _uval.dictionary = new PDFDictionary_t(d);
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
  return *this;
}

PDFString PDFDictionary::toString() const {
  PDFSStream ss;
  PDFDictionary_t &dict = *_uval.dictionary;

  for (auto&& item : dict) {
    ss << item.first << " " << item.second;
  }

  ss << cv_format("dict\n");
  return ss.str();
}

PDFObject* PDFDictionary::fromString(const PDFString& str) const {
  //PDFObject* p = new PDFObject();
  return NULL;  //p;
}

size_t PDFDictionary::serialize(PDFOStream &ps) {
//  ps.seekp(getStartOffset());

  if (getIndirectFlag() && getReferencedFlag()) {
    ps << getObjNum() << " " << getGenNum() << " " << " R";
  } else if (getIndirectFlag() && !getReferencedFlag()) {
    ps << getObjNum() << " " << getGenNum() << " obj" << PDF_NEW_LINE;
    ps << PDF_DICT_BGN;

    ps << this->toString();

    ps << PDF_DICT_END << PDF_NEW_LINE;
    ps << "endobj" << PDF_NEW_LINE;
  }

  setEndOffset(ps.tellp());
  return getSize();
}

} /* namespace LilPDF */
