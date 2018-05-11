/*
 * pdf_dictionary.h
 *
 *  Created on: 10-May-2018
 *      Author: Mani Kumar
 */

#ifndef EXPS_INC_PDF_DICTIONARY_H_
#define EXPS_INC_PDF_DICTIONARY_H_

#include <pdf_object.h>

#include <set>
#include <map>

namespace LilPDF {

// Encapsulates PDF dictionary object.
//
// A dictionary is written as a sequence of key-item pairs enclosed in
// double angle brackets (<< … >>). Example
// <<
//    /Type /Example
//    /Subtype /DictionaryExample
//    /Version 0.01
//    /IntegerItem 12
//    /StringItem (a string)
//    /Subdictionary << /Item1 (A) /Item2 true >>
// >>
class PDFDictionary : public PDFObject {
 public:
  // ctor
  PDFDictionary();
  explicit PDFDictionary(const PDFDictionary_t &d);
  // dtor
  virtual ~PDFDictionary();
  // overloaded operator
  PDFDictionary &operator=(const PDFDictionary_t &d);

  //! Converts the PDF object to its string representation.
  virtual PDFString toString(void) const override;
  //! Constructs a PDF object from string. NOTE: [Partially implemented]
  virtual PDFObject* fromString(const PDFString& str) const override;
  //! writes the object to ostream
  virtual size_t serialize(PDFOStream &ps) override;

#if 0 // these are for parsing
  bool hasKey(const PDFString& key) const {
    return _uval.dictionary->find(key) != _uval.dictionary->end();
  }
  const PDFObject& getItem(const PDFString& key) const {
    return *(_uval.dictionary->at(key));
  }
  std::set<PDFString> getKeys() const {
    std::set<PDFString> keys;
    for (auto&& i : *(_uval.dictionary))
      keys.insert(i.first);
    return keys;
  }
  const PDFDictionary_t& getItems() const {
    return *(_uval.dictionary);
  }
#endif

#if 1
  // Insert a key-obj pair to dictionary.
  void insertKey(const PDFString& key, PDFObject obj) {
    _uval.dictionary = new PDFDictionary_t();
    PDFDictionary_t &dict = *(_uval.dictionary);
    dict[key] = obj;
  }
  void insertKey(const char* key, PDFObject obj) {
    _uval.dictionary = new PDFDictionary_t();
    PDFDictionary_t &dict = *(_uval.dictionary);
    dict[PDFString(key)] = obj;
  }
  // Replace value of key, adding it if it does not exist
  void replaceKey(const PDFString& key, PDFObject obj) {
    _uval.dictionary->at(key) = obj;
  }
  // Remove key, do nothing if key does not exist
  void removeKey(const PDFString& key) {
    _uval.dictionary->erase(key);
  }
#endif

};

} /* namespace LilPDF */

#endif /* EXPS_INC_PDF_DICTIONARY_H_ */
