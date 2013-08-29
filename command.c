#include "cli.h"
#include "command.h"

struct cli_command_t cli_list[] = {
    {"foo", &foo, "foo"},
    {"bar", &bar, "bar"},
    {"foobar", &foobar, "foobar"},
    {"barfoo", &barfoo, "barfoo"},
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

int barfoo(int *res)
{
    *res = 5;
    return 3;
}

int foobar(int *res)
{
    *res = 6;
    return 2;
}
