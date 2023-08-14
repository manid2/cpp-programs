/*
 * https://stackoverflow.com/questions/693788/is-it-better-to-use-c-void-arguments-void-foovoid-or-not-void-foo
 *
 * Read answer https://stackoverflow.com/a/29942180
 *
 * Exact copy of the answer
 * ============================================================================
 * Besides syntactical differences, many people also prefer using void
 * function(void) for practical reasons:
 *
 * If you're using the search function and want to find the implementation of
 * the function, you can search for function(void), and it will return the
 * prototype as well as the implementation.
 *
 * If you omit the void, you have to search for function() and will therefore
 * also find all function calls, making it more difficult to find the actual
 * implementation.
 * ============================================================================
 *
 * Sample try-out log
 * ============================================================================
 * $ grep -Irnw "f(void)" .
 * ./void-func-param.cpp:26:int f(void);
 * ./void-func-param.cpp:36:int f(void) { return 2; }
 *
 * $ grep -Irnw "g()" .
 * ./void-func-param.cpp:27:int g();
 * ./void-func-param.cpp:32:  std::cout << "g()=" << g() << std::endl;
 * ./void-func-param.cpp:37:int g() { return 4; }
 * ============================================================================
 */

#include <iostream>

int f(void);
int g();

int main(int argc, char **argv)
{
  std::cout << "f()=" << f() << std::endl;
  std::cout << "g()=" << g() << std::endl;
  return 0;
}

int f(void) { return 2; }
int g() { return 4; }
