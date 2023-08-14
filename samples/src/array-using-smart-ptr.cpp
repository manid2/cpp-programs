// function template
#include <iostream>
#include <cstdio>
#include <cstring>
#include <memory>

#define ARR_SIZE 5
#define ARR_INIT 0

using namespace std;

typedef unsigned char u8_t;

int main(int argc, char **argv)
{
  int size = 6;
  std::unique_ptr<u8_t[]> p(new u8_t[size]());
  if (p)
  {
    for (int i = 0; i < size; ++i)
    {
      p[i] = i;
    }
    for (int i = 0; i < size; ++i)
    {
      printf("p[%d]=%d\n", i, p[i]);
    }
    char *c = reinterpret_cast<char *>(p.get());
    printf("\n");
    for (int i = 0; i < size; ++i)
    {
      c[i] = c[i] + 1;
      printf("c[%d]=%d\n", i, c[i]);
    }
    char *ch = new char[size]();
    memcpy(ch, p.get(), size);
    printf("\n");
    for (int i = 0; i < size; ++i)
    {
      printf("ch[%d]=%d\n", i, ch[i]);
    }
  }
  return 0;
}
