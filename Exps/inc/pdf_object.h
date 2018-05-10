/*
 * pdf_object.h
 *
 *  Created on: 10-May-2018
 *      Author: Mani Kumar
 */

#ifndef EXPS_INC_PDF_OBJECT_H_
#define EXPS_INC_PDF_OBJECT_H_

#include <lpdfcommon.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <string.h>

namespace LilPDF {

class PDFObject;

typedef std::vector<PDFObject*> PDFArray_t;
typedef std::map<PDFString, PDFObject*> PDFDictionary_t;

class PDFObject {
 public:
  // ctor's and dtor
  PDFObject();
  PDFObject(ePDF_object_type type);
  explicit PDFObject(bool b);
  explicit PDFObject(int i);
  explicit PDFObject(double r);
  explicit PDFObject(const PDFString &s);
  explicit PDFObject(const char *c);
  // NOTE: need to implement these separately
  //explicit PDFObject(const PDFArray_t &a);
  //explicit PDFObject(const PDFObject *strm); // not copy constructor
  PDFObject(const PDFObject &x);  // copy constructor
  virtual ~PDFObject();

  // overloaded operators
  PDFObject &operator=(const PDFObject &x);
  PDFObject &operator=(const bool b);
  PDFObject &operator=(const int i);
  PDFObject &operator=(const double r);
  PDFObject &operator=(const PDFString &s);
  PDFObject &operator=(const char *c);
  //PDFObject &operator=(const PDFArray_t &a);
  //PDFObject &operator=(const PDFObject *strm);

  friend PDFOStream &operator<<(PDFOStream &ps, /*const*/PDFObject &obj);
  friend PDFObject &operator>>(PDFIStream &ps, PDFObject &obj);

  // helper methods
  void copy(const PDFObject &x);

  //! Converts the PDF object to its string representation.
  virtual PDFString toString(void) const/*=0*/;
  //! Constructs a PDF object from string. NOTE: [Partially implemented]
  virtual PDFObject* fromString(const PDFString& str) const/*=0*/;
  //! writes the object to ostream
  virtual size_t serialize(PDFOStream &ps);

  //! setters
  void setObjNum(int o) {
    objNum = o;
  }
  void setGenNum(int g) {
    genNum = g;
  }
  void setStartOffset(size_t s) {
    objStart = s;
  }
  void setObjCount(int oc) {
    objCount = oc;
  }
  /*void setObjType(ePDF_object_type t) {
    _type = t;
   }*/
  void setIndirectFlag(bool flag) {
    isIndirect = flag;
  }
  void setReferencedFlag(bool flag) {
    isReferenced = flag;
  }

  //! getters
  int getObjNum(void) const {
    return objNum;
  }
  int getGenNum(void) const {
    return genNum;
  }
  size_t getStartOffset(void) const {
    return objStart;
  }
  size_t getEndOffset(void) const {
    return objEnd;
  }
  int getObjCount(void) const {
    return objCount;
  }
  ePDF_object_type getObjType(void) const {
    return _type;
  }
  bool getIndirectFlag(void) const {
    return isIndirect;
  }
  bool getReferencedFlag(void) const {
    return isReferenced;
  }
  size_t getSize(void) const {
    return getEndOffset() - getStartOffset();
  }

 protected:
  void setEndOffset(size_t e) {
    objEnd = e;
  }

 private:
  template<typename T> PDFObject(const T *);  // to prevent implicit conversion to bool

 protected:
  union UValue {
    bool boolean;
    int integer;
    double real;
    PDFString *string;
    PDFString *name;
    PDFArray_t *array;
    PDFDictionary_t *dictionary;
    PDFByte *stream;
  };

 protected:
  void init(void);
  void clear(void);

 protected:
  ePDF_object_type _type;
  UValue _uval;

 private:
  //! obj num
  int objNum;
  //! gen num
  int genNum;
  //! The obj's start and end offsets.
  size_t objStart, objEnd;
  //! No of objs this object holds;
  int objCount;
  //! other attributes
  bool isIndirect;
  bool isReferenced;
};

}  // namespace LilPDF

#endif // EXPS_INC_PDF_OBJECT_H_
