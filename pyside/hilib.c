#include <Python.h>
#include "hello.h"
#include "hilib.h"

void pyhi() {
  Py_Initialize();
  char *hi = say_hi();
  printf("%s\n", hi);
  Py_Finalize();
}
