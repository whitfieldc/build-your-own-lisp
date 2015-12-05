#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#ifdef _WIN32
#include <string.h>

static char buffer [2048];

/* fake readline function*/
char* readline(char* prompt){
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy = malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1] = '\0';
	return cpy
}

/* fake add_history function*/
void add_history(char* unused){}

/*otherwise include editline */
#else
#include <editline/readline.h>
#endif

/* use operator to see which operation to perform */
long eval_op(long x, char* op, long y){
	if (strcmp(op, "+") == 0) { return x + y; }
	if (strcmp(op, "-") == 0) { return x - y; }
	if (strcmp(op, "*") == 0) { return x * y; }
	if (strcmp(op, "/") == 0) { return x / y; }
	return 0;
}

long eval(mpc_ast_t* t) {

	/* if tagged as number return directly */
	if (strstr(t->tag, "number")){
		return atoi(t->contents);
	}

	/* operator is always second child*/
	char* op = t->children[1]->contents;

	/* we store 3rd child in 'x' */
	long x = eval(t->children[2]);

	/* iterate remaining children and combine */
	int i = 3;
	while (strstr(t->children[i]->tag, "expr")){
		x = eval_op(x, op, eval(t->children[i]));
		i++;
	}

	return x;

}

typedef struct {
  int type;
  long num;
  int err;
} lval;

/* Create a new number type lval */
lval lval_num(long x) {
  lval v;
  v.type = LVAL_NUM;
  v.num = x;
  return v;
}

/* Create a new error type lval */
lval lval_err(int x) {
  lval v;
  v.type = LVAL_ERR;
  v.err = x;
  return v;
}

/* Create Enumeration of Possible lval Types */
enum { LVAL_NUM, LVAL_ERR };

/* Create Enumeration of Possible Error Types */
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

/* Print an "lval" */
void lval_print(lval v) {
  switch (v.type) {
    /* In the case the type is a number print it */
    /* Then 'break' out of the switch. */
    case LVAL_NUM: printf("%li", v.num); break;

    /* In the case the type is an error */
    case LVAL_ERR:
      /* Check what type of error it is and print it */
      if (v.err == LERR_DIV_ZERO) {
        printf("Error: Division By Zero!");
      }
      if (v.err == LERR_BAD_OP)   {
        printf("Error: Invalid Operator!");
      }
      if (v.err == LERR_BAD_NUM)  {
        printf("Error: Invalid Number!");
      }
    break;
  }
}

/* Print an "lval" followed by a newline */
void lval_println(lval v) { lval_print(v); putchar('\n'); }


int main(int argc, char** argv){

	/* create some parsers */
	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr = mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");

	/* define them with the following language */
	mpca_lang(MPCA_LANG_DEFAULT,
  "                                                     \
    number   : /-?[0-9]+/ ;                             \
    operator : '+' | '-' | '*' | '/' ;                  \
    expr     : <number> | '(' <operator> <expr>+ ')' ;  \
    lispy    : /^/ <operator> <expr>+ /$/ ;             \
  ",
  Number, Operator, Expr, Lispy);

	/*print version and exit info*/
	puts ("Lisp Clone v 0.0.0.0.1");
	puts ("Press Ctrl+c to Exit\n");

	/*never-ending loop*/
	while (1){

		/*output prompt and get input*/
		char* input = readline("lisp clone> ");

		/* read a line of user input max size 2048*/
		add_history(input);

		/* Attempt to Parse the user Input */
		mpc_result_t r;
		if (mpc_parse("<stdin>", input, Lispy, &r)) {
		  /* On Success Print the AST */
		  // mpc_ast_print(r.output);
		  long result = eval(r.output);
			printf("%li\n", result);
			mpc_ast_delete(r.output);
		  mpc_ast_delete(r.output);
		} else {
		  /* Otherwise Print the Error */
		  mpc_err_print(r.error);
		  mpc_err_delete(r.error);
		}


		/*free retrieved input*/
		free(input);
	}
	/* Undefine and Delete our Parsers */
	mpc_cleanup(4, Number, Operator, Expr, Lispy);
	return 0;
}
