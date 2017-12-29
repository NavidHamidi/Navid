#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "lexer.h"
#include "queue.h"

struct ast *ast_create(void)
{
  struct ast *a = malloc(sizeof (struct ast));
  a->token = NULL;
  a->left = NULL;
  a->right = NULL;
  return a;
}

int max(int a, int b)
{
  return a > b ? a : b;
}

int height(struct ast *ast)
{
  if (!ast)
    return -1;
  if (!(ast->left && ast->right))
    return 0;
  return 1 + max(height(ast->left), height(ast->right));
}


// add INTEGER
struct ast *ast_add_leaf(struct ast *a, struct ast *new_node)
{
  if (!a)
    return new_node;
  if (!a->left)
    a->left = new_node;
  else if (!a->right)
    a->right = new_node;
  else
  {
    ast_add_leaf(a->left, new_node);
    ast_add_leaf(a->right, new_node);
  }
  return a;
}

// add PARENTHESIS, OPERATORS, UNARY
struct ast *ast_add_root(struct ast *a, struct ast *new_node)
{
  if (!a)
    return new_node;
  new_node->left = a;
  return new_node;
}

struct ast *ast_right_rotation(struct ast *ast)
{
  struct ast *tmp = ast->left;
  ast->left = tmp->right;
  tmp->right = ast;
  ast = tmp;
  return ast;
}

/*void ast_print(struct ast *a)
{
  if (!a)
    return;

  struct queue *q = queue_create();
  queue_push(q, a);

  while (q->size > 0)
  {
    struct ast *node = queue_pop(q);

    if (node->token->type == INTEGER)
      printf("%d --> %d  ", node->token->data, node->token->type);
    else
      printf("%c --> %d  ", node->token->data, node->token->type);

    if (q->size <= 1)
      printf("\n");
    if (node->left)
      queue_push(q, node->left);
    if (node->right)
      queue_push(q, node->right);
  }
  printf("\n");
}*/

void rec_ast_print(struct ast *node)
{
  if (!node)
    return;
  if (node->token->type == INTEGER)
    //printf("%d --> %d  ", node->token->data, node->token->type);
    printf("%d  ", node->token->data);
  else
    //printf("%c --> %d  ", node->token->data, node->token->type);
    printf("%c  ", node->token->data);
  rec_ast_print(node->left);
  /*if (node->token->type == INTEGER)
    printf("%d --> %d  ", node->token->data, node->token->type);
  else
    printf("%c --> %d  ", node->token->data, node->token->type);*/
  rec_ast_print(node->right);
}

void ast_print(struct ast *node)
{
  if (!node)
    return;
  rec_ast_print(node);
  printf("\n");
}
