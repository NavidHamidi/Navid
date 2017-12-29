#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"

int parenthesis_count(struct token *token)
{
  int nb_par = 0;
  for (struct token *t = token; t; t = t->next)
  {
    if (t->type == LPARENTHESIS || t->type == RPARENTHESIS)
      nb_par++;
  }
  return nb_par % 2 == 0 ? 0 : -1;
}


int parser(struct token *token)
{
  if (parenthesis_count(token) == -1)
  {
    fprintf(stderr, "Syntax error parenthesis not closed\n");
    return -1;
  }
  for (struct token *t = token; t; t = t->next)
  {
    if (t->type >= 2 && t->type < 9 && t->next && t->next->type == 1)
    {
      fprintf(stderr, "Syntax error near ')' parenthesis\n");
      return -1;
    }
  }
  return 0;
}
