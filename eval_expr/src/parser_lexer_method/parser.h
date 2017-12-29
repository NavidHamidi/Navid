#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"

int parenthesis_count(struct token *t);
int parser(struct token *t);


#endif
