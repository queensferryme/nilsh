#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "parse.h"
#include "utils.h"

Environ environ;

void shell_debug() {
  int i, j;
  extern CommandPool commands;
  printf("\033[0;32m%s\033[0m", "Debug:\n");
  // output command(s), one each line
  for (i = 0; i < commands.count; i++) {
    Command cmd = commands.list[i];
    // output command string
    printf("  {\033[0;32m%s\033[0m\"", "cmd: ");
    for (j = 0; cmd.args[j] != NULL; j++)
      printf("%s ", cmd.args[j]);
    printf("\b\", ");
    // output in/out target, including stdin/stdout/pipe/files
    if (commands.count > 1) {
      if (i == 0) {
        printf("\033[0;32m%s\033[0m%s, ", "in: ", cmd.in[0] ? cmd.in : "stdin");
        printf("\033[0;32m%s\033[0m%s}\n", "out: ", "pipe");
      }
      else if (i == commands.count - 1) {
        printf("\033[0;32m%s\033[0m%s, ", "in: ", "pipe");
        printf("\033[0;32m%s\033[0m%s}\n", "out: ", cmd.out[0] ? cmd.out : "stdout");
      }
      else {
        printf("\033[0;32m%s\033[0m%s, ", "in: ", "pipe");
        printf("\033[0;32m%s\033[0m%s}\n", "out: ", "pipe");
      }
    }
    else {
      printf("\033[0;32m%s\033[0m%s, ", "in: ", cmd.in[0] ? cmd.in : "stdin");
      printf("\033[0;32m%s\033[0m%s}\n", "out: ", cmd.out[0] ? cmd.out : "stdout");
    }
  }
  printf("\033[0;32m%s\033[0m\n", "Result: ");
}

void shell_init() {
  extern Environ environ;
  getcwd(environ.cwd, VAR_MAX_LENGTH);
  strcpy(environ.username, getpwuid(geteuid())->pw_name);
}

void shell_prompt() {
  extern Environ environ;
  printf("\033[0;32m%s\033[0m at ", environ.username);
  printf("\033[0;33m%s\033[0m\n$ ", environ.cwd);
}

void shell_input(char* line) {
  char *start = line, *end = line;
  do {
    *end = getchar();
    if (*end == '\n') *end = '\0';
  } while (*(end++) && end - start < LINE_MAX_LENGTH);
}
