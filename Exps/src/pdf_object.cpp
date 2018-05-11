#include <pdf_object.h>

namespace LilPDF {

/****************** ctor's and dtor definitions ******************/
PDFObject::PDFObject() {
  init();
  _type = Unknown;
  _uval = UValue();
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
}

PDFObject::PDFObject(ePDF_object_type type) {
  init();
  _type = type;
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
}

PDFObject::PDFObject(bool b) {
  init();
  _type = boolean_type;
  _uval.boolean = b;
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
}

PDFObject::PDFObject(int i) {
  init();
  _type = integer_type;
  _uval.integer = i;
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
}

PDFObject::PDFObject(double r) {
  init();
  _type = real_type;
  _uval.real = r;
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
}

PDFObject::PDFObject(const PDFString &s) {
  init();
  _type = Unknown;
  PDFObject* p = fromString(s);
  copy(*p);
  delete p;
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
}

PDFObject::PDFObject(const char *c) {
  init();
  _type = Unknown;
  PDFString s(c);
  PDFObject* p = fromString(s);
  copy(*p);
  delete p;
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
}

PDFObject::PDFObject(const PDFDictionary_t &d) {
  init();
  _type = dictionary_type;
  _uval.dictionary = new PDFDictionary_t(d);
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
}

/*PDFObject::PDFObject(const PDFArray_t &a)
 : _type(array_type) {
 init();
 _uval.array = new PDFArray_t(a);
 DEBUG_INF(" _type = %d\n", _type);
 }

 PDFObject::PDFObject(const PDFObject *strm)
 : _type(stream_type) {
 //u_.stream_ = strm; // TODO: YTI
 DEBUG_INF(" _type = %d\n", _type);
 }*/

PDFObject::PDFObject(const PDFObject &x) {
  copy(x);
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
}

PDFObject::~PDFObject() {
  clear();
}

/****************** overloaded operators definitions ******************/
PDFObject &PDFObject::operator=(const PDFObject &x) {
  copy(x);
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
  return *this;
}

PDFObject &PDFObject::operator=(const bool b) {
  init();
  _type = boolean_type;
  _uval.boolean = b;
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
  return *this;
}

PDFObject &PDFObject::operator=(const int i) {
  init();
  _type = integer_type;
  _uval.integer = i;
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
  return *this;
}

PDFObject &PDFObject::operator=(const double r) {
  init();
  _type = real_type;
  _uval.real = r;
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
  return *this;
}

PDFObject &PDFObject::operator=(const PDFString &s) {
  init();
  PDFObject* p = fromString(s);
  copy(*p);
  delete p;
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
  return *this;
}

PDFObject &PDFObject::operator=(const char *c) {
  init();
  PDFString s(c);
  PDFObject* p = fromString(s);
  copy(*p);
  delete p;
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
  return *this;
}

PDFObject &PDFObject::operator=(const PDFDictionary_t &d) {
  init();
  _type = array_type;
  _uval.dictionary = new PDFDictionary_t(d);
  DEBUG_INF(" _type = %d (%s), \n", _type, getStringFromEnum(_type).c_str());
  return *this;
}

/*PDFObject &PDFObject::operator=(const PDFArray_t &a) {
 init();
 _type = array_type;
 _uval.array = new PDFArray_t(a);
 DEBUG_INF(" _type = %d\n", _type);
 return *this;
 }
 */

PDFOStream &/*PDFObject::*/operator<<(PDFOStream &ps, /*const*/PDFObject &obj) {
  obj.serialize(ps);
  return ps;
}

PDFObject &/*PDFObject::*/operator>>(PDFIStream &ps, PDFObject &obj) {
  std::string str { std::istreambuf_iterator<char>(ps),
      std::istreambuf_iterator<char>() };
  PDFObject *p = obj.fromString(str);
  obj = PDFObject(*p);
  delete p;
  DEBUG_INF(" _type = %d (%s), \n", obj._type,
            getStringFromEnum(obj._type).c_str());
  return obj;
}

/****************** init() definition ******************/
void PDFObject::init() {
#define INIT(x, v)\
  case x##_type:\
  _uval.x = v;\
      break;

  switch (_type) {
    INIT(boolean, false)
    INIT(integer, 0)
    INIT(real, 0.0)
    INIT(string, NULL)
    INIT(name, NULL)
    INIT(array, NULL)
    INIT(dictionary, NULL)
    INIT(stream, NULL)
    default:
      break;
  }

#undef INIT

  setObjNum(0);
  setGenNum(0);
  setStartOffset(0);
  setEndOffset(0);
  setObjCount(0);
  setIndirectFlag(true);
  setReferencedFlag(false);
}

/****************** clear() definition ******************/
void PDFObject::clear() {
#define DEINIT(x)\
  case x##_type:\
      if (_uval.x){\
        delete _uval.x;\
        _uval.x = NULL;\
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

/****************** helper methods definitions ******************/
void PDFObject::copy(const PDFObject &p) {
  _type = p._type;
  _uval = p._uval;

#define COPY(x, v)\
  case x##_type:\
    _uval.x = v;\
    break;

  switch (_type) {
    COPY(string, new PDFString(*p._uval.string))
    COPY(name, new PDFString(*p._uval.name))
    default:
      break;
  }

#undef COPY

  setObjNum(p.getObjNum());
  setGenNum(p.getGenNum());
  setStartOffset(p.getStartOffset());
  setEndOffset(p.getEndOffset());
  setObjCount(p.getObjCount());
  setIndirectFlag(p.getIndirectFlag());
  setReferencedFlag(p.getReferencedFlag());
}

PDFString PDFObject::toString() const {
  PDFSStream ss;

#define CHR_STR(x, v)\
  case x##_type:\
      ss << v;\
      break;

#define STR_STR(x)\
  case x##_type:\
      ss << *_uval.x;\
      break;

#define PRI_STR(x)\
  case x##_type:\
      ss << _uval.x;\
      break;

  switch (_type) {
    CHR_STR(null, "null")
    CHR_STR(boolean, (_uval.boolean ? "true" : "false"))
    PRI_STR(integer)
    PRI_STR(real)
    STR_STR(string)
    STR_STR(name)
      /*AS_STR(array, true)
       AS_STR(dictionary, true)
       AS_STR(stream) // TODO, YTI*/
    default:
      ss << ("NONE");
      break;
  }

#undef CHR_STR
#undef STR_STR
#undef PRI_STR

  return ss.str();
}

PDFObject* PDFObject::fromString(const PDFString& str) const {
  PDFObject* p = new PDFObject();

  // NOTE: Only partially implemented!
  if (starts_with(str.c_str(), "/")) {
    p->_type = name_type;
    p->_uval.name = new PDFString(str);
    DEBUG_INF(", p->_type=[%d], p->_uval.name=[%s]\n", p->_type,
              p->_uval.name->c_str());
  } else if ((starts_with(str.c_str(), "(") && ends_with(str.c_str(), ")"))
      || (starts_with(str.c_str(), "<") && ends_with(str.c_str(), ">"))) {
    p->_type = string_type;
    p->_uval.string = new PDFString(str);
    DEBUG_INF(", p->_type=[%d], p->_uval.string=[%s]\n", p->_type,
              p->_uval.string->c_str());
  } else if (!str.compare("null")) {
    p->_type = null_type;
    DEBUG_INF(", p->_type=[%d], [null]\n", p->_type);
  }

  return p;
}

size_t PDFObject::serialize(PDFOStream &ps) {
  ps.seekp(getStartOffset());

  if (getIndirectFlag() && getReferencedFlag()) {
    ps << getObjNum() << " " << getGenNum() << " " << " R";
  } else if (getIndirectFlag() && !getReferencedFlag()) {
    ps << getObjNum() << " " << getGenNum() << " obj" << PDF_NEW_LINE;
    ps << this->toString();
    ps << "endobj" << PDF_NEW_LINE;
  }

  setEndOffset(ps.tellp());
  return getSize();
}

}  // namespace LilPDF
