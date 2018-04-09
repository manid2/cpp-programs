/*
 * cjpegdecoder.h
 *
 *  Created on: 07-Apr-2018
 *      Author: mani
 */

#ifndef CJPEGDECODER_H_
#define CJPEGDECODER_H_

#include "jpegcommondefs.h"

#include <cstdlib>
#include <cstdio>

#include <string>

namespace mani_JPEG {

class CJpegDecoder {
 public:
  //! default ctor
  CJpegDecoder();
  //! parameterized ctor
  CJpegDecoder(std::string i, std::string o = "default_name.raw");
  //! dtor
  virtual ~CJpegDecoder();

 public:
  //! Decoder API
  bool decode(void);

 private:
  bool fWriteBytesToFile(JSAMPROW bytes, size_t size);

 private:
  std::string i_file_name;
  std::string o_file_name;

  //! libjpeg decompresion structure
  struct jpeg_decompress_struct cinfo;
  //! custom libjpeg error manager
  struct my_error_mgr jerr;
  //! source file stream
  FILE * i_fp;
  //! dest file stream
  FILE * o_fp;
  //! output row buffer
  JSAMPARRAY o_row_buffer;

  //! Points to large array of R,G,B-order data
  JSAMPLE * image_buffer;
  //! Number of rows in image
  int image_height;
  //! Number of columns in image
  int image_width;
  //! physical row width in output buffer
  int row_stride;
};

} /* namespace mani_JPEG */

#endif /* CJPEGDECODER_H_ */
