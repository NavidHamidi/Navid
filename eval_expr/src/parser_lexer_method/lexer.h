#ifndef LEXER_H
# define LEXER_H

#define PRECEDENCE_PARENTHESES 4
#define PRECEDENCE_ASSIGN      4
#define PRECEDENCE_POW         3
#define PRECEDENCE_UNARY       2
#define PRECEDENCE_MUL_DIV     1
#define PRECEDENCE_ADD_SUB     0
#define PRECEDENCE_INTEGER    -1


enum type
{
  //parenthesis
  LPARENTHESIS = 0,
  RPARENTHESIS,

  //operators
  ADD_OP,
  SUB_OP,
  MUL_OP,
  DIV_OP,
  POW_OP,
  MOD_OP,

  //unary
  MINUS_UNARY,

  //integer
  INTEGER,
  VARIABLE,

  //assignation ex: a = 1
  ASSIGN
};

struct token
{
  enum type type;
  int precedence;
  int data;
  struct token *next;
};

struct token *token_create(void); //don't need
void token_print(struct token *t);
void token_free(struct token *t);

struct token *token_fill(struct token *t, char *expr);

#endif
