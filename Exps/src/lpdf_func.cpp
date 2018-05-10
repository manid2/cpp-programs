/*
 * main.cpp
 *
 *  Created on: 20-Mar-2018
 *      Author: Mani Kumar
 */

#include <lpdfcommon.h>

#include <cstdio>
#include <stdarg.h>

#include <dirent.h>

namespace LilPDF {

/*
 * Returns the date time string in:
 * (D:YYYYMMDDHHmmSSOHH'mm') format
 */
PDFString getPdfDateTime(void) {
  struct timeval tv;
  gettimeofday(&tv, 0);

  struct tm ltm;
  localtime_r(&tv.tv_sec, &ltm);

  char timeret[80];
  // TODO: YTI universal time support.
  strftime(timeret, sizeof timeret, "(D:%Y%m%d%H%M%SZ00'00')", &ltm);

  return PDFString(timeret);
}

PDFString getLogDateTime(void) {
  struct timeval tv;
  gettimeofday(&tv, 0);

  struct tm ltm;
  localtime_r(&tv.tv_sec, &ltm);

  char timeBuf[80];
  size_t len = strftime(timeBuf, sizeof timeBuf, "%m/%d %H:%M:%S", &ltm);
  sprintf(timeBuf + len, "%06ld", tv.tv_usec);

  return PDFString(timeBuf);
}

// borrowed from opencv 2.4 code
PDFString cv_format(const char* fmt, ...) {
  char buf[1 << 16];
  va_list args;
  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  return PDFString(buf);
}

std::vector<std::string> getFileNamesFromFolder(const char *folderPath) {
  std::string strFolderPath = folderPath;
  if (NULL == folderPath || strFolderPath.empty()) {
    printf("folderpath is NULL or empty!\n");
    return std::vector<std::string>();
  } else {
    printf("folderPath is [%s].\n", strFolderPath.c_str());
  }
  std::string fileName;
  std::vector<std::string> vFileNames;
  struct dirent *dir_entry;
  DIR *dir = opendir(folderPath);
  if (dir == NULL) {
    printf("opendir(%s) returned NULL.\n", strFolderPath.c_str());
    printf("opendir(%s) returned NULL.\n", strFolderPath.c_str());
    return std::vector<std::string>();
  } else {
    printf("opendir(%s), is successful.\n", strFolderPath.c_str());
  }
  while ((dir_entry = readdir(dir)) != NULL) {
    // Ignore the hidden files and dir entries starting with "."
    if ('.' != dir_entry->d_name[0]) {
      fileName = dir_entry->d_name;
      printf("File name [%s], is not hidden.\n", fileName.c_str());
      vFileNames.push_back(fileName);
    }
  }
  closedir(dir);
  printf("closedir(%s), is successful.\n", strFolderPath.c_str());
  return vFileNames;
}

PDFString getStringFromEnum(ePDF_file_type etype) {
  PDFString stype("eUknown");
  switch (etype) {
    case eLinearized_PDF:
      stype = "LPDF";
      break;
    case eNonSearchable_PDF:
      stype = "NSPDF";
      break;
    case eSearchable_PDF:
      stype = "SPDF";
      break;
  }
  return stype;
}

ePDF_file_type getEnumFromString(PDFString stype) {
  ePDF_file_type etype = eUknown;
  if (!stype.compare("LPDF"))
    etype = eLinearized_PDF;
  else if (!stype.compare("NSPDF"))
    etype = eNonSearchable_PDF;
  else if (!stype.compare("SPDF"))
    etype = eSearchable_PDF;
  return etype;
}

/* C-style String manipulation APIs */
int to_lower(const char* i_str, char* o_str) {
  int i = 0;
  if (i_str && o_str) {
    while (i_str[i]) {
      o_str[i] = tolower(i_str[i]);
      i++;
    }
    o_str[i] = '\0';
  }
  return i;
}

int to_upper(const char* i_str, char* o_str) {
  int i = 0;
  if (i_str && o_str) {
    while (i_str[i]) {
      o_str[i] = toupper(i_str[i]);
      i++;
    }
    o_str[i] = '\0';
  }
  return i;
}

int starts_with(const char* str, const char* sub_str) {
  size_t strl = strlen(str);
  size_t subl = strlen(sub_str);
  if (!str || !sub_str)  // to prevent seg fault
    return 0;
  if (!strncmp(str, sub_str, subl))
    return 1;
  else
    return -1;
}

int ends_with(const char* str, const char* sub_str) {
  size_t strl = strlen(str);
  size_t subl = strlen(sub_str);
  if (!str || !sub_str)  // to prevent seg fault
    return 0;
  if (!strncmp(str + (strl - subl), sub_str, subl))
    return 1;
  else
    return -1;
}

int istarts_with(const char* str, const char* sub_str) {
  if (!str || !sub_str)  // to prevent seg fault
    return 0;
  char *tmp = (char*) malloc(strlen(sub_str) * sizeof(char));
  if (!tmp)
    return -1;
  strncpy(tmp, sub_str, strlen(sub_str));
  int ret = to_lower(str, tmp);
  ret = starts_with(str, tmp);
  if (tmp)
    free(tmp);
  return ret;
}

int iends_with(const char* str, const char* sub_str) {
  if (!str || !sub_str)  // to prevent seg fault
    return 0;
  char *tmp = (char*) malloc(strlen(sub_str) * sizeof(char));
  if (!tmp)
    return -1;
  strncpy(tmp, sub_str, strlen(sub_str));
  int ret = to_lower(str, tmp);
  ret = ends_with(str, tmp);
  if (tmp)
    free(tmp);
  return ret;
}

}  // namespace LilPDF


/********************************* For Testing - begin **********************************/
#ifdef LPDF_BUILD_AS_EXE
#include <pdf_object.h>
#include <pdf_dictionary.h>

bool LilPDF::LPDF_DEBUG = false;
LilPDF::ePDF_file_type LilPDF::PDF_TYPE = LilPDF::eUknown;

void LilPDF::parseCmdLineArgs(int argc, char **argv) {
  char *arg = new char[100];
  for (int opt = 1; opt < argc; opt++) {
    DEBUG_INF("in pcla(), agv[%d]=[%s]\n", opt, argv[opt]);
    if (!strcmp("-d", argv[opt])) {
      LPDF_DEBUG = true;
      DEBUG_INF("LPDF_DEBUG = [%d]\n", LPDF_DEBUG);
    }
    if (starts_with(argv[opt], "--type=") == 1) {
      arg = strstr(argv[opt], "=");
      PDF_TYPE = getEnumFromString(PDFString(arg + 1));
      DEBUG_INF("PDF_TYPE = [%d]\n", PDF_TYPE);
    }
  }
}

/* main function that executes the APIs. */
int LilPDF::execute(int argc, char **argv) {

  parseCmdLineArgs(argc, argv);
  int ret = 0;

  do {
    LilPDF::PDFDictionary_t dict;
    LilPDF::PDFObject p;
    p = 2;
    dict["hi"] = &p;
    p = 4.7;
    dict["mi"] = &p;

    LilPDF::PDFDictionary d;
    d = dict;
    std::cout << d;
  } while (0);

  return ret;
}

#endif // LPDF_BUILD_AS_EXE
/********************************* For Testing - end **********************************/

