# C++ code examples

C++ code examples for common reusable problems such as:

- Structured data handing
- CMake or Autotools template project, etc.

Also for coding practice.

## How to build

Clone the repo and use `cmake` or `autotools` to build project.

Use `out-of-source` build to separate source and build files.

```bash
mkdir cpp-code-examples_top
cd cpp-code-examples_top
git clone https://github.com/manid2/cpp-code-examples.git

# cd cpp-code-examples_top
mkdir build && cd build
```

### CMake

```bash
# cd build
# Generate cmake build files and optional eclipse project files.
cmake ../cpp-code-examples \
    -G"Eclipse CDT4 - Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Debug
    # Eclipse CDT project options (optional)
    #-DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE
    #-DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j4
    #-DCMAKE_ECLIPSE_VERSION=4.17
# Build project
make # -j4 optional parallel builds
```

### Autotools

```bash
# cd cpp-code-examples
# Generate configure script, *.in & *.m4 files
autoreconf -i

# cd build
# Generate build files
../cpp-code-examples/configure # with optional configure options
# Build project
make # -j4 optional parallel builds
```

## Useful commands

Format all source code using `clang-format`.

```bash
# using find and xargs
find . -name "*.hh" -o -name "*.cc" -type f | \
xargs clang-format -i -style=file
```

## TODO

- Add forked [manid2/googletest][manid2_gtest_link] as git submodule
- Add `autotools` support
- Use pre-commit hooks to format source code

<!-- External links-->
[manid2_gtest_link]: https://github.com/manid2/googletest
