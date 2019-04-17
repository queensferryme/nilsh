#include <stdbool.h>

#include "execute.h"
#include "parse.h"
#include "utils.h"

int main(int argc, char* argv[]) {
  _Bool debug = (argc > 1);
  char line[LINE_MAX_LENGTH];
  shell_init();
  while (true) {
    shell_prompt();
    shell_input(line);
    parse_line_command(line);
    if (debug) shell_debug();
    execute_line_command();
  }
  return 0;
}
