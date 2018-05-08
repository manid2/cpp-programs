#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <string.h>

// PDF object type codes
enum ePDF_object_type {
  Unknown = -1,
  null_type,
  boolean_type,
  integer_type,
  real_type,
  string_type,
  name_type,
  array_type,
  dictionary_type,
  stream_type,
  // Additional object types that can occur in content streams
  operator_type,
  inlineimage_type
};

class PDFObject;

typedef std::string PDFString;
typedef std::ostream PDFOStream;
typedef std::stringstream PDFSStream;

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
  UValue _uVal;

public:
  PDFObject();
  PDFObject(ePDF_object_type type);
  explicit PDFObject(bool b);
  explicit PDFObject(int i);
  explicit PDFObject(double r);
  explicit PDFObject(const PDFString &s);
  //explicit PDFObject(const PDFString &n);
  explicit PDFObject(const PDFArray_t &a);
  explicit PDFObject(const PDFDictionary_t &d);
  explicit PDFObject(const PDFObject *strm); // not copy constructor
  PDFObject(const PDFObject &x); // copy constructor
  PDFObject &operator=(const PDFObject &x);
  PDFObject &operator=(const bool b);
  virtual ~PDFObject();

  void swap(PDFObject &x);
  void copy(const PDFObject &x);

  //! Converts the PDF object to its string representation.
  virtual PDFString toString(void) const/*=0*/;
  //! TODO: YTI Constructs a PDF object from string.
  //virtual IPDFObject fromString(PDFString& str) const=0;
  //! writes the object to ostream
  virtual size_t serialize(PDFOStream &ps);
};
