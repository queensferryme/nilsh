#ifndef _NILSH_UTILS_H
#define _NILSH_UTILS_H

#define LINE_MAX_LENGTH 1024
#define VAR_MAX_LENGTH 128

typedef struct {
  char cwd[VAR_MAX_LENGTH];
  char username[VAR_MAX_LENGTH];
} Environ;

// output debug information
void shell_debug();

// initialize shell environment
void shell_init();

// accept *one* line of input from stdin,
// store as characters in given string.
// @params:
//   char* -> location to store input chars
void shell_input(char*);

// output user prompt string
void shell_prompt();

#endif
