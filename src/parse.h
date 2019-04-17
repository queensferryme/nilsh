#ifndef _NILSH_PARSE_H
#define _NILSH_PARSE_H

#include <stddef.h>

#include "utils.h"

typedef struct {
  char* args[VAR_MAX_LENGTH];
  char in[VAR_MAX_LENGTH];
  char out[VAR_MAX_LENGTH];
} Command;

typedef struct {
  Command list[VAR_MAX_LENGTH];
  size_t count;
} CommandPool;


// parse *one* line of commands,
// commands may be nested by pipe.
// @params:
//   char* -> commands string
void parse_line_command(char*);

#endif
