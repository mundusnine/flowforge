#pragma once

#include <stdio.h>
#include <stddef.h>

typedef enum {
    OP_ROOT,
    OP_VALUE,
    OP_INSTRUCTION,
    OP_FUNC,
    OP_FUNCCALL,
    OP_MAX
} OpType;

typedef struct command command_t;

typedef struct {
    command_t** items;
    size_t count;
    size_t capacity;
} commands;

struct command {
    char* name;
    OpType type;
    commands sub_cmds;
};
#ifdef __cplusplus
extern "C" {
#endif

void create_command(command_t* command,char* name,OpType type);
void command_add_sub(command_t* command,command_t* sub);
char* command_as_string(command_t* command);
void gen_code(command_t* root);

#ifdef __cplusplus
}
#endif
