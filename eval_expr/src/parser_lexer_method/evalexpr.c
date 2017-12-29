#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "ast.h"
#include "evalexpr.h"
#include "lexer.h"
#include "operator.h"
#include "parser.h"


int main(void)
{
  while (1)
  {
    char *expr = readline("> ");
    if (strncmp("exit", expr, 4) == 0)
      break;

    expr = remove_space(expr);
    printf("%d\n", calculate(expr));

  }
  return 0;
}

int evaluate_ast(struct ast *ast)
{
  if (!ast)
    return 0;
  if (ast->token->type != INTEGER)
  {
    if (ast->token->type == ADD_OP)
      return evaluate_ast(ast->left) + evaluate_ast(ast->right);
    if (ast->token->type == SUB_OP)
      return evaluate_ast(ast->left) - evaluate_ast(ast->right);
    if (ast->token->type == MUL_OP)
      return evaluate_ast(ast->left) * evaluate_ast(ast->right);
    if (ast->token->type == DIV_OP)
    {
      if (ast->right->token->type == INTEGER && ast->right->token->data == 0)
      {
        fprintf(stderr, "Error argument can't divide by 0\n");
        return INT_MIN;
      }
      return evaluate_ast(ast->left) / evaluate_ast(ast->right);
    }
    if (ast->token->type == MOD_OP)
    {
      if (ast->right->token->type == INTEGER && ast->right->token->data == 0)
      {
        fprintf(stderr, "Error argument can't divide by 0\n");
        return INT_MIN;
      }
      return evaluate_ast(ast->left) % evaluate_ast(ast->right);
    }
    else //POW_OP
      return evaluate_ast(ast->left) + evaluate_ast(ast->right);
  }
  else
    return ast->token->data;
}

char *remove_space(char *expr)
{
  int i = 0;
  while (expr[i])
  {
    if (expr[i] == ' ')
    {
      int j = i;
      while (expr[j])
      {
        expr[j] = expr[j + 1];
        j++;
      }
    }
    else
      i++;
  }
  expr[i] = '\0';
  //printf("%s\n", expr);
  return expr;
}

struct ast *parse_token(struct token *token, struct ast *ast)
{
  for (struct token *t = token; t; t = t->next)
  {
    struct ast *new_node = ast_create();
    new_node->token = t;
    if (t->type == INTEGER)
      ast = ast_add_leaf(ast, new_node);
    else if (t->type > 1)
      ast = ast_add_root(ast, new_node);
    else
      continue;
    if (ast->left && ast->token->type != INTEGER &&
        ast->left->token->type != INTEGER &&
        ast->token->precedence > ast->left->token->precedence)
    {
      ast = ast_right_rotation(ast);
    }
  }
  return ast;
}

int calculate(char *expr)
{
  struct token *t = NULL;
  t = token_fill(t, expr);
  if (parser(t) == -1)
    return INT_MIN;
  //token_print(t);
  struct ast *ast = NULL;
  ast = parse_token(t, ast);
  //ast_print(ast);
  if (height(ast->left) - height(ast->right) == 2)
    ast = ast_right_rotation(ast);
  return evaluate_ast(ast);
}
