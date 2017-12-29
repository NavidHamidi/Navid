#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "operator.h"

struct token *token_create(void) //don't need
{
  struct token *t = malloc(sizeof (struct token));
  t->next = NULL;
  return t;
}

struct token *token_push(struct token *t, enum type type, int data, int prec)
{
  struct token *new = token_create();
  new->data = data;
  new->type = type;
  new->precedence = prec;

  if (!t)
    t = new;
  else
  {
    struct token *tmp = t;
    for (; tmp->next; tmp = tmp->next)
      continue;
    tmp->next = new;
  }
  return t;
}

struct token *token_fill(struct token *t, char *expr)
{
  enum type type;
  int data = 0;
  int nb = 0;
  int i = 0;
  int p = 0;
  int new_p = 0;
  while (expr[i])
  {
    nb = expr[i];
    data = expr[i];
    if (is_integer(data))
    {
      nb = data - '0';
      i++;
      while (expr[i] && is_integer(expr[i]))
      {
        nb = nb * 10 + expr[i] - '0';
        i++;
      }
      p = PRECEDENCE_INTEGER;
      type = INTEGER;
    }
    else if (is_symbol(data))
    {
      type = data == '(' ? LPARENTHESIS : RPARENTHESIS;
      new_p = data == '(' ? new_p + 1 : new_p - 1;
      p = PRECEDENCE_PARENTHESES;
      i++;
    }
    else if (is_operator(data))
    {
      switch(data)
      {
        case '+':
          p = PRECEDENCE_ADD_SUB + new_p;
          type = ADD_OP;
          break;
        case '-':
          p = PRECEDENCE_ADD_SUB + new_p;
          type = SUB_OP;
          break;
        case '*':
          p = PRECEDENCE_MUL_DIV + new_p;
          type = MUL_OP;
          break;
        case '/':
          p = PRECEDENCE_MUL_DIV + new_p;
          type = DIV_OP;
          break;
        case '%':
          p = PRECEDENCE_MUL_DIV + new_p;
          type = MOD_OP;
          break;
        case '^':
          p = PRECEDENCE_POW + new_p;
          type = POW_OP;
          break;
      }
      i++;
    }
    else // TODO implement variables, functions...
    {
      i++;
      continue;
    }

    data = nb;
    t = token_push(t, type, data, p);
  }
  return t;
}

void token_print(struct token *t)
{
  if (!t)
    return;
  for (struct token *tmp = t; tmp; tmp = tmp->next)
  {
    if (tmp->type == INTEGER)
      printf("data: %d  type:%d  prec:%d\n", tmp->data, tmp->type, tmp->precedence);
    else
      printf("data: %c  type:%d  prec:%d\n", tmp->data, tmp->type, tmp->precedence);
  }
}

void token_free(struct token *t)
{
  if (!t)
    return;
  token_free(t->next);
  free(t);
}
