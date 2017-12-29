#ifndef AST_H
# define AST_H

#include "lexer.h"

struct ast
{
  struct token *token;
  struct ast *left;
  struct ast *right;
};

struct ast *ast_create(void);
struct ast *ast_add_leaf(struct ast *a, struct ast *new_node);
struct ast *ast_add_root(struct ast *a, struct ast *new_node);
struct ast *ast_right_rotation(struct ast *ast);
void ast_print(struct ast *ast);
void rec_ast_print(struct ast *ast);

int max(int a, int b);
int height(struct ast *ast);

#endif
