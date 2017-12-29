#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct queue *queue_create(void)
{
  struct queue *q = malloc(sizeof (struct queue));
  q->size = 0;
  q->head = NULL;
  q->tail = NULL;
  return q;
}

void queue_push(struct queue *q, struct ast *ast)
{
  if (!q)
    return;
  struct list *new = malloc (sizeof(struct list));
  new->ast = ast;
  new->next = NULL;

  if (q->size == 0)
  {
    q->head = new;
    q->tail = new;
  }
  else
  {
    struct list *l = q->head;
    for (; l->next; l = l->next)
      continue;
    l->next = new;
    q->tail = new;
  }
  q->size++;
}

struct ast *queue_pop(struct queue *q)
{
  if (!q || q->size == 0)
    return NULL;
  struct list *l = q->head;
  if (q->size == 1)
  {
    q->head = NULL;
    q->tail = NULL;

  }
  else
    q->head = l->next;
  q->size--;
  return l->ast;
}

/*void queue_print(struct queue *q)
{
  if (!q)
    return;
  for (struct list *l = q->head; l; l = l->next)
    printf("%d ", l->data);
  printf("size = %d\n", q->size);
}*/
