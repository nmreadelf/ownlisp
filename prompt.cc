#include <iostream>
#include <string>

#include <readline/history.h>
#include <readline/readline.h>

int main() {
  std::cout << "Lispy Version 0.0.0.0.1" << std::endl;
  std::cout << "Press Ctrl+c to Exit" << std::endl;

  std::string prompt("lispy> ");
  while (1) {
    std::string out;
    char *line = readline(prompt.c_str());
    if (line == NULL) {
      return 0;
    }
    add_history(line);
    out = line;
    std::cout << "No you're a " << out << std::endl;
  }
  return 0;
}
