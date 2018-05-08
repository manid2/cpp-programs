#include "pdf_object.h"

#include "debug_macros.h"

PDFObject::PDFObject()
    : _type(null_type),
      _uVal() {
  DEBUG_INF(" in PDFObject()\n");
}

PDFObject::PDFObject(ePDF_object_type type) {
  init();
  DEBUG_INF(" in PDFObject()\n");
}

PDFObject::PDFObject(bool b)
    : _type(boolean_type) {
  _uVal.boolean = b;
  DEBUG_INF(" in PDFObject()\n");
}

PDFObject::PDFObject(int i)
    : _type(integer_type) {
  _uVal.integer = i;
  DEBUG_INF(" in PDFObject()\n");
}

PDFObject::PDFObject(double r)
    : _type(real_type) {
  _uVal.real = r;
  DEBUG_INF(" in PDFObject()\n");
}

PDFObject::PDFObject(const PDFString &s)
    : _type(string_type) {
  _uVal.string = new PDFString(s);
  DEBUG_INF(" in PDFObject(%s)\n", _uVal.string->c_str());
}

/*PDFObject::PDFObject(const PDFString &n)
 : type_(eName) {
 u_.name_ = new PDFString(n);
 }*/

PDFObject::PDFObject(const PDFArray_t &a)
    : _type(array_type) {
  _uVal.array = new PDFArray_t(a);
  DEBUG_INF(" in PDFObject()\n");
}

PDFObject::PDFObject(const PDFDictionary_t &d)
    : _type(dictionary_type) {
  _uVal.dictionary = new PDFDictionary_t(d);
  DEBUG_INF(" in PDFObject()\n");
}

PDFObject::PDFObject(const PDFObject *strm)
    : _type(stream_type) {
  //u_.stream_ = strm; // TODO: YTI
  DEBUG_INF(" in PDFObject()\n");
}

PDFObject::PDFObject(const PDFObject &x) {
  copy(x);
  DEBUG_INF(" in PDFObject()\n");
}

PDFObject &PDFObject::operator=(const PDFObject &x) {
  copy(x);
  DEBUG_INF(" in operator=\n");
  return *this;
}

PDFObject &PDFObject::operator=(const bool b) {
  _type = boolean_type;
  _uVal.boolean = b;
  DEBUG_INF(" in operator=\n");
  return *this;
}

PDFObject::~PDFObject() {
  clear();
}

void PDFObject::init() {
#define INIT(x, v)\
  case x##_type:\
      _uVal.x = v;\
      break;

  switch (_type) {
    INIT(boolean, false)
    INIT(integer, 0)
    INIT(real, 0.0)
    INIT(string, new PDFString())
    INIT(name, new PDFString())
    INIT(array, new PDFArray_t())
    INIT(dictionary, new PDFDictionary_t())
    INIT(stream, NULL)
    default:
      break;
  }

#undef INIT
}

void PDFObject::clear() {
#define DEINIT(x)\
  case x##_type:\
      if (_uVal.x){\
        delete _uVal.x;\
        _uVal.x = NULL;\
      }\
      break;

  switch (_type) {
    DEINIT(string)
    DEINIT(name)
    DEINIT(dictionary)
    DEINIT(stream)
    default:
      break;
  }

#undef DEINIT
}

void PDFObject::swap(PDFObject &x) {
  std::swap(_type, x._type);
  std::swap(_uVal, x._uVal);
}

void PDFObject::copy(const PDFObject &p) {
  _type = p._type;
  _uVal = p._uVal;

#define COPY(x, v)\
  case x##_type:\
    _uVal.x = v;\
    break;

  switch (_type) {
    COPY(string, new PDFString(*p._uVal.string))
    COPY(name, new PDFString(*p._uVal.name))
    default:
      break;
  }

#undef COPY
}

PDFString PDFObject::toString() const {
  PDFSStream ss;

#define CHR_STR(x, v)\
  case x##_type:\
      ss << v;\
      break;

#define STR_STR(x)\
  case x##_type:\
      ss << *_uVal.x;\
      break;

#define PRI_STR(x)\
  case x##_type:\
      ss << _uVal.x;\
      break;

  switch (_type) {
    CHR_STR(null, "null")
    CHR_STR(boolean, (_uVal.boolean ? "true" : "false"))
    PRI_STR(integer)
    PRI_STR(real)
    STR_STR(string)
    STR_STR(name)
      /*AS_STR(array, true)
       AS_STR(dictionary, true)*/
      // AS_STR(stream) // TODO, YTI
    default:
      ss << ("NONE");
      break;
  }

#undef CHR_STR
#undef STR_STR
#undef PRI_STR

  return ss.str();
}

size_t PDFObject::serialize(PDFOStream &ps) {
  //ps.seekp(getStartOffset());
  ps << this->toString();
  return ps.tellp();
}
