#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "execute.h"

extern CommandPool commands;
extern Environ environ;

// check if a command is built-in
// @params:
//   char* -> name of command
// @return:
//   _Bool -> true or false
_Bool is_builtin_command(char* cmd) {
  return (
    strcmp(cmd, "cd") == 0 ||
    strcmp(cmd, "exit") == 0
  );
}

// execute a built-in command
// @params:
//   Command* -> command to be executed
void execute_builtin_command(Command* cmd) {
  if (!strcmp(cmd->args[0], "cd")) {
    if (chdir(cmd->args[1]))
      return;
    getcwd(environ.cwd, VAR_MAX_LENGTH);
  }
  else if (!strcmp(cmd->args[0], "exit"))
    exit(0);
}

// execute a external command
// @params:
//   Command* -> command to be executed
void execute_external_command(Command* cmd) {
  pid_t pid = fork();
  if (pid == 0) {
    if (cmd->in[0])
      freopen(cmd->in, "r", stdin);
    if (cmd->out[0])
      freopen(cmd->out, "w", stdout);
    if (execvp(cmd->args[0], cmd->args))
      fprintf(stderr, "\033[0;31m%s\033[0m", "no such command\n");
    exit(0);
  }
  else waitpid(pid, NULL, 0);
}

// execute *one* command without pipe
// @params
//   Command* -> command to be executed
void execute_command(Command* cmd) {
  if (is_builtin_command(cmd->args[0]))
    execute_builtin_command(cmd);
  else execute_external_command(cmd);
}

// execute several piped commands
void execute_piped_commands() {
  int i, in = 0, fd[2];
  pid_t pid;
  // create n child proccess connected with pipes
  for (i = 0; i < commands.count - 1; i++) {
    pipe(fd);
    if ((pid = fork())== 0) {
      if (in != 0) { dup2(in, 0); close(in); }
      if (fd[1] != 1) { dup2(fd[1], 1); close(fd[1]); }
      execvp(commands.list[i].args[0], commands.list[i].args);
    }
    close(fd[1]); in = fd[0];
  }
  // execute last of the commands mannually
  if ((pid = fork()) == 0) {
    if (in != 0) { dup2(in, 0); close(in); }
    execvp (commands.list[i].args[0], commands.list[i].args);
    exit(0);
  }
  else waitpid(pid, NULL, 0);
}

void execute_line_command() {
  if (commands.count == 1)
    execute_command(commands.list);
  else execute_piped_commands();
}
