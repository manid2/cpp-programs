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
  union UValue {
    bool boolean;
    int integer;
    double real;
    PDFString *string;
    PDFString *name;
    PDFArray_t *array;
    PDFDictionary_t *dictionary;
    PDFObject *stream;
  };

protected:
  void init(void);
  void clear(void);

  ePDF_object_type _type;
  UValue _uval;

public:
  // ctor's and dtor
  PDFObject();
  PDFObject(ePDF_object_type type);
  explicit PDFObject(bool b);
  explicit PDFObject(int i);
  explicit PDFObject(double r);
  explicit PDFObject(const PDFString &s);
  explicit PDFObject(const char *c);
  explicit PDFObject(const PDFArray_t &a);
  explicit PDFObject(const PDFDictionary_t &d);
  //explicit PDFObject(const PDFObject *strm); // not copy constructor
  PDFObject(const PDFObject &x); // copy constructor
  virtual ~PDFObject();

  // overloaded operators
  PDFObject &operator=(const PDFObject &x);
  PDFObject &operator=(const bool b);
  PDFObject &operator=(const int i);
  PDFObject &operator=(const double r);
  PDFObject &operator=(const PDFString &s);
  PDFObject &operator=(const char *c);
  PDFObject &operator=(const PDFArray_t &a);
  PDFObject &operator=(const PDFDictionary_t &d);
  //PDFObject &operator=(const PDFObject *strm);

  friend PDFOStream &operator<<(PDFOStream &ps, const PDFObject &obj);
  friend PDFObject &operator>>(PDFIStream &ps, PDFObject &obj);

  // helper methods
  void swap(PDFObject &x);
  void copy(const PDFObject &x);

  //! Converts the PDF object to its string representation.
  virtual PDFString toString(void) const/*=0*/;
  //! Constructs a PDF object from string.
  virtual PDFObject* fromString(const PDFString& str) const/*=0*/;
  //! writes the object to ostream
  virtual size_t serialize(PDFOStream &ps);

 private:
  template<typename T> PDFObject(const T *);  // to prevent implicit conversion to bool
};

}  // namespace LilPDF
