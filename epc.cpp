#ifndef EPC_H_
#define EPC_H_

#include <stdio.h>
#include "epc.h"

double doublefun(double b) {
  printf("c(%g)", b);
  return b + 12.5;
}

float floatfun(float b) {
  printf("c(%f)", b);
  return b + 12.5;
}

int intfun(int b) {
  printf("c(%d)", b);
  return b + 12.5;
}

#endif
