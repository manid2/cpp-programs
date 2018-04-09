/*
 * cjpegdecoder.cpp
 *
 *  Created on: 07-Apr-2018
 *      Author: mani
 */

#include "cjpegdecoder.h"

namespace mani_JPEG {

CJpegDecoder::CJpegDecoder()
    : i_file_name("default_name.jpg"),
      o_file_name("default_name.raw"),
      i_fp(NULL),
      o_fp(NULL),
      o_row_buffer(NULL),
      image_buffer(NULL),
      image_height(0),
      image_width(0),
      row_stride(0) {
}

CJpegDecoder::CJpegDecoder(std::string i, std::string o)
    : i_file_name(i),
      o_file_name(o),
      i_fp(NULL),
      o_fp(NULL),
      o_row_buffer(NULL),
      image_buffer(NULL),
      image_height(0),
      image_width(0),
      row_stride(0) {
}

CJpegDecoder::~CJpegDecoder() {
  // do nothing.
}

bool CJpegDecoder::decode() {
  bool ret_val = true;

  do {  // for common error handling

    // open input jpeg file to decode
    if ((i_fp = fopen(i_file_name.c_str(), "rb")) == NULL) {
      fprintf(stderr, "can't open %s\n", i_file_name.c_str());
      ret_val = false;
      break;
    }

    /* Step 1: allocate and initialize JPEG decompression object */
    // setup the error handler for libjpeg
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    if (setjmp(jerr.setjmp_buffer)) {
      /* If we get here, the JPEG code has signaled an error.
       * We need to clean up the JPEG object, close the input file, and return.
       */
      jpeg_destroy_decompress(&cinfo);
      fclose(i_fp);
      ret_val = false;
      break;
    }

    /* Now we can initialize the JPEG decompression object. */
    jpeg_create_decompress(&cinfo);

    /* Step 2: specify data source (eg, a file) */
    jpeg_stdio_src(&cinfo, i_fp);

    /* Step 3: read file parameters with jpeg_read_header() */
    (void) jpeg_read_header(&cinfo, TRUE);

    /* Step 4: set parameters for decompression */
    // ignore this for now
    /* Step 5: Start decompressor */
    (void) jpeg_start_decompress(&cinfo);

    /* JSAMPLEs per row in output buffer */
    row_stride = cinfo.output_width * cinfo.output_components;
    /* Make a one-row-high sample array that will go away when done with image */
    o_row_buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo,
    JPOOL_IMAGE,
                                              row_stride, 1);

    /* Step 6: while (scan lines remain to be read) */
    /*           jpeg_read_scanlines(...); */
    while (cinfo.output_scanline < cinfo.output_height) {
      /* jpeg_read_scanlines expects an array of pointers to scanlines.
       * Here the array is only one element long, but you could ask for
       * more than one scanline at a time if that's more convenient.
       */
      (void) jpeg_read_scanlines(&cinfo, o_row_buffer, 1);
      /* Assume put_scanline_someplace wants a pointer and sample count. */
      fWriteBytesToFile(o_row_buffer[0], row_stride);
    }

    /* Step 7: Finish decompression */
    (void) jpeg_finish_decompress(&cinfo);

    /* Step 8: Release JPEG decompression object */
    /* This is an important step since it will release a good deal of memory. */
    jpeg_destroy_decompress(&cinfo);
    fclose(i_fp);

  } while (0);

  return ret_val;
}

bool CJpegDecoder::fWriteBytesToFile(JSAMPROW bytes, size_t len) {
  bool ret_val = true;
  do {
    if (o_fp)
      fwrite(bytes, 1, len, o_fp);
    else if ((o_fp = fopen(o_file_name.c_str(), "wb")) == NULL) {
      fprintf(stderr, "can't open %s\n", o_file_name.c_str());
      ret_val = false;
      break;
    }
  } while (0);
  return ret_val;
}

} /* namespace mani_JPEG */
