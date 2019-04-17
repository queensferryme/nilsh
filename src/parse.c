#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "parse.h"

CommandPool commands;

// parse a command without pipe
// @params:
//   char* -> command string without pipe
//   Command* -> location to store parsed result
void parse_command(char* line, Command* cmd) {
  int pos = 0;
  char *split = " \t",
       *token = strtok(line, split);
  cmd->in[0] = cmd->out[0] = '\0';
  // seprate line by space, handle in/out redirection
  while (token != NULL) {
    if (!strcmp(token, "<"))
      strcpy(cmd->in, strtok(NULL, split));
    else if (!strcmp(token, ">"))
      strcpy(cmd->out, strtok(NULL, split));
    else cmd->args[pos++] = token;
    token = strtok(NULL, split);
  }
  cmd->args[pos] = NULL;
}

void parse_line_command(char* line) {
  Command* cmd = commands.list;
  char *split = "|", *token;
  // split line by pipe sign "|" and parse for-each
  while (token = strsep(&line, split)) {
    while (isspace(*token)) token++;
    parse_command(token, cmd++);
  }
  commands.count = cmd - commands.list;
}
