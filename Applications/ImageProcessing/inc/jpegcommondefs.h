/*
 * jpegcommondefs.h
 *
 *  Created on: 07-Apr-2018
 *      Author: mani
 */

#ifndef JPEGCOMMONDEFS_H_
#define JPEGCOMMONDEFS_H_

extern "C" {
#include <stdlib.h>
#include <stdio.h>
#include "jpeglib.h"
}

#include <setjmp.h>

namespace mani_JPEG {

struct my_error_mgr {
  struct jpeg_error_mgr pub;  /* "public" fields */

  jmp_buf setjmp_buffer;  /* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}

}  // namespace mani_JPEG


#endif /* JPEGCOMMONDEFS_H_ */
