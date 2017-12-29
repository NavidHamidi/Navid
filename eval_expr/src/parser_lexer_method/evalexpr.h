#ifndef EVALEXPR_H
# define EVALEXPR_H

char *remove_space(char *expr);
struct ast *parse_token(struct token *t, struct ast *ast);
int calculate(char *expr);
int evaluate_ast(struct ast *ast);

#endif
