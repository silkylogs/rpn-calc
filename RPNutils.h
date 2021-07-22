#include <stdio.h>
#include <math.h>
#include "charsimplestack.h"
#include "doublesimplestack.h"

#ifndef RPNUTILS_H
#define RPNUTILS_H

int IsNumber(char *str);
double Operator(char* op, double num1, double num2);
double RpnEval(CStackNode *exprHead);
void StringExprToRpn(char *expr, CStackNode **outStack);

#endif
