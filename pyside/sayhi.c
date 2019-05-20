#include <Python.h>
#include "hello.h"

int main() {
  Py_Initialize();
  char *hi = say_hi();
  printf("%s\n", hi);
  Py_Finalize();
}
