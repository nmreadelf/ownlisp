#include <iostream>
#include <string>

#include <readline/history.h>
#include <readline/readline.h>

#include "mpc.h"

int main() {
  // Create Some Parsers
  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *lispy = mpc_new("lispy");

  // Define them with the following Language
  mpca_lang(MPCA_LANG_DEFAULT, "						\
				number : /-?[0-9]+/ ;				\
				operator : '+' | '-' | '*' | '/' ;		\
				expr : <number> | '(' <operator> <expr>+ ')' ; 	\
				lispy : /^/ <operator> <expr>+ /$/ ;		\
",
            Number, Operator, Expr, lispy);
  std::cout << "Lispy Version 0.0.0.0.1" << std::endl;
  std::cout << "Press Ctrl+c to Exit" << std::endl;

  std::string prompt("lispy> ");
  while (1) {
    char *line = readline(prompt.c_str());
    if (line == NULL) {
      return 0;
    }
    add_history(line);

    mpc_result_t r;
    if (mpc_parse("stdin>", line, lispy, &r)) {
      mpc_ast_print((mpc_ast_t*)r.output);
      mpc_ast_delete((mpc_ast_t*)r.output);
    } else {
      mpc_err_print((mpc_err_t*)r.output);
      mpc_err_delete(r.error);
    }
    free(line);
  }
  mpc_cleanup(4, Number, Operator, Expr, lispy);
  return 0;
}
