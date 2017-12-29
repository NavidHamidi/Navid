CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra -g
LDLIBS = -lreadline

OBJ = evalexpr.o lexer.o parser.o operator.o ast.o queue.o

evalexpr: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDLIBS)

clean:
	rm -f *.o evalexpr
