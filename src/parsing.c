#include <stdio.h>
#include <stdlib.h>

/* If we are compiling on Windows compile these functions */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* Fake add_history function */
// Empty function
void add_history(char* unused) {}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#include "mpc.h"

#endif

int main(int argc, char** argv) {

    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Lispy    = mpc_new("lispy");

     mpca_lang(MPCA_LANG_DEFAULT,
              "                                                     \
    number   : /-?[0-9]+\.[0-9]+/ | /-?[0-9]+/ ;                             \
    operator : '+' | '-' | '*' | '/' | '%' | \"add\" | \"sub\" | \"mul\" | \"div\";                  \
    expr     : <number> | '(' (<expr> <operator>)* <expr>  ')' ;  \
    lispy    : /^/ (<expr> <operator>)* <expr> /$/ ;             \
  ", Number, Operator, Expr, Lispy);

  puts("Lispy Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  while (1) {

    /* Now in either case readline will be correctly defined */
    char* input = readline("lispy> ");
    add_history(input); // On a Windows machine this won't do anything.

      /* Attempt to Parse the user Input */
      mpc_result_t r;
      if (mpc_parse("<stdin>", input, Lispy, &r)) { // <stdin> is just for showing error messages.
          /* On Success Print the AST */
          mpc_ast_print(r.output);
          mpc_ast_delete(r.output); // Clear the object
      } else {
          /* Otherwise Print the Error */
          mpc_err_print(r.error);
          mpc_err_delete(r.error); // Clear the object
      }
    free(input);

  }
    mpc_cleanup(4, Number, Operator, Expr, Lispy);
  return 0;
}

#pragma clang diagnostic pop