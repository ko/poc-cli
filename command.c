#include "cli.h"
#include "command.h"

struct cli_command_t cli_list[] = {
    {"foo", &foo, "foobar"},
    {"bar", &bar, "barfoo"},
};

unsigned int cli_entries = sizeof(cli_list) / sizeof(cli_command);

/*
 * Commands
 */
int foo(int *res)
{
    *res = 3;
    return 1;
}

int bar(int *res)
{
    *res = 2;
    return 0;
}


