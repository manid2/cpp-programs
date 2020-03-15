/*
 * LinearizePDF.h
 *
 *  Created on: 30-Mar-2018
 *      Author: mani
 */

#ifndef INC_LINEARIZEDPDF_H_
#define INC_LINEARIZEDPDF_H_

// C headers
#include <cctype>
#include <cstring>

// Linux headers
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

// Cpp headers
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip> // for setw and setfill
#include <vector>

// Others
#include <lpdflogger.h>

namespace LilPDF {

// generic typedefs
typedef unsigned int uint_t;

// PDF specific types
typedef char PDFByte;
typedef std::string PDFString;
typedef std::ostream PDFOStream;
typedef std::istream PDFIStream;
typedef std::stringstream PDFSStream;

// PDF syntax constants
static const PDFString PDF_NEW_LINE("\n");
static const PDFString PDF_HEADER_VER("%PDF-1.7");
static unsigned char BIN_CHARS[] = { 37, 225, 226, 227, 28 };  // %áâãä
static const PDFString PDF_HEADER_BIN(reinterpret_cast<char*>(BIN_CHARS));
static const PDFString PDF_EOF("%%EOF");

static const PDFString PDF_DICT_BGN("<<");
static const PDFString PDF_DICT_END(">>");
static const PDFString PDF_ARRAY_BGN("[");
static const PDFString PDF_ARRAY_END("]");

// Size of fixed size PDF objects
static const int PDF_0th_OBJ_GEN_NUM = 65535;
static const int PDF_LPD_STR_MAX_SIZE = 200;
static const int PDF_FIRST_PAGE_XREF_ENTRIES_SIZE = 7;
static const int PDF_FIRST_PAGE_XREF_TABLE_ENTRY_SIZE = 20;
static const int PDF_FIRST_PAGE_TRAILER_SIZE = 120;
static const float PDF_DEFAULT_USER_SPACE_UNIT = 72.0f;

// PDF creation error codes.
enum ePDF_error_code {
  eOK = 0,
  eGenericError = -100,
  eFileWriteError
};

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

// PDF file types
enum ePDF_file_type {
  eUknown = -1,
  eLinearized_PDF,
  eNonSearchable_PDF,
  eSearchable_PDF,
};

// Image structures
typedef struct tagPDF_ImgAttrs {
  int width;
  int height;
  int bitsPerComp;
  PDFString colorSpace;
  PDFString filter;

  tagPDF_ImgAttrs()
      : width(0),
        height(0),
        bitsPerComp(0) {
  }
} stPDF_ImgAttrs;

PDFString getStringFromEnum(ePDF_file_type);
PDFString getStringFromEnum(ePDF_object_type);
ePDF_file_type getEnumFromString(PDFString);

/* Returns the date time string. */
PDFString getPdfDateTime(void);

/* Returns the formatted string */
PDFString cv_format(const char* fmt, ...);

/* Returns file names from folder. */
std::vector<std::string> getFileNamesFromFolder(const char *folderPath);

/* Returns no of bits in an int. */
inline int getBitsCount(int val) {
  return (val == 0 ? 0 : (1 + getBitsCount(val >> 1)));
}

/* C-style String manipulation APIs */
int to_lower(const char*, const char*);
int to_upper(const char*, const char*);
int starts_with(const char*, const char*);
int ends_with(const char*, const char*);
int istarts_with(const char*, const char*, int);
int iends_with(const char*, const char*, int);


#define LPDF_BUILD_AS_EXE // for testing purpose

#ifdef LPDF_BUILD_AS_EXE
// extern is used to avoid multiple definitions error
extern bool LPDF_DEBUG;
extern ePDF_file_type PDF_TYPE;
extern void parseCmdLineArgs(int argc, char **argv);
extern int execute(int argc, char **argv);
#endif // LPDF_BUILD_AS_EXE

} /* namespace LPDF */

#endif /* INC_LINEARIZEDPDF_H_ */
