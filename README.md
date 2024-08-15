C++ programs
============

Example C++ programs to learn and reuse for development tasks.

Build & test
------------

This repository uses Gnu Makefile to build & test, format source code.

```bash
make <source>        # build a test binary from .cpp source file
make <source>-check  # run the test binary
make <source>-format # format .cpp source file

SHOW_TEST_OUTPUT=1 make <source>-check # run test with debug output
```
