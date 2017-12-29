#ifndef QUEUE_H
# define QUEUE_H

#include "ast.h"

struct list
{
  struct ast *ast;
  struct list *next;
};

struct queue
{
  int size;
  struct list *head;
  struct list *tail;
};

struct queue *queue_create(void);
void queue_push(struct queue *q, struct ast *a);
struct ast *queue_pop(struct queue *q);
void free_queue(struct queue *q);
void queue_print(struct queue *q);

#endif
