// unique_ptr constructor example
#include <iostream>
#include <memory>

#include "pdf_object.h"
#include "debug_macros.h"

using namespace std;

int main(int argc, char **argv) {
  PDFObject p(2.1);
  cout << "val of p = " << p.toString() << endl;

  p = false;
  cout << "val of p = " << p.toString() << endl;

  p = true;
  cout << "val of p = " << p.toString() << endl;

  return 0;
}
