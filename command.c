#include <stdio.h>
#include "cli.h"
#include "command.h"

struct cli_command_t cli_list[] = {
    {"foo", &foo, "foo"},
    {"bar", &bar, "bar"},
    {"foobar", &foobar, "foobar"},
    {"barfoo", &barfoo, "barfoo"},
};

unsigned int cli_entries = sizeof(cli_list) / sizeof(cli_command);

#define FUNCTION_ENTRY  \
    do {    \
        printf("%s:entry\n",__FUNCTION__);  \
    } while(0);

#define FUNCTION_EXIT   \
    do {    \
        printf("%s:exit\n",__FUNCTION__);   \
    } while(0);

/*
 * Commands
 */
int foo(int *res)
{
    *res = 3;
    FUNCTION_ENTRY
    FUNCTION_EXIT
    return 1;
}

int bar(int *res)
{
    *res = 2;
    FUNCTION_ENTRY
    FUNCTION_EXIT
    return 0;
}

int barfoo(int *res)
{
    *res = 5;
    FUNCTION_ENTRY
    FUNCTION_EXIT
    return 3;
}

int foobar(int *res)
{
    *res = 6;
    FUNCTION_ENTRY
    FUNCTION_EXIT
    return 2;
}
