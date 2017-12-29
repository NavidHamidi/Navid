#include <stdio.h>

#include "operator.h"


int is_symbol(char c)
{
  return c == '(' || c == ')';
}

int is_operator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

int is_integer(char c)
{
  return c >= '0' && c <= '9';
}

int handle_error(int b, char op)
{
  if (b == 0 && (op == '/' || op == '%'))
    return 3;
  return -1;
}

