#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "ast_print.h"
#include "lexer.h"
#include "queue.h"
#include "operator.h"

struct ast *parse_token(struct token *token, struct ast *ast)
{
  for (struct token *tmp = token; tmp; tmp = tmp->next)
  {
    struct ast *new_node = ast_create();
    new_node->token = tmp;
    if (tmp->type == INTEGER)
      ast = ast_add_leaf(ast, new_node);
    else
      ast = ast_add_root(ast, new_node);
  }
  return ast;

}


int main(void)
{
  struct token *t = NULL;
  char *expr = "2+3-4";
  t = token_fill(t, expr);
  //token_print(t);
  struct ast *ast = NULL;
  ast = parse_token(t, ast);
  ast_main(ast);

  return 0;
}
