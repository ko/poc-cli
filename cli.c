#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "command.h"
#include "cli.h"

int command_completion(char * partialcmd)
{
    int i, j;
    char is_match = TRUE;
    char * s;
    char matches[256] = "";
    char * pm = matches;
    for (i = 0; i < cli_entries; i++) { 
        s = strstr(cli_list[i].name, partialcmd); 
        if (s) {
            for (j = 0; j < strlen(s); j++) {
                // not a match for completion
                if (s[j] != cli_list[i].name[j]) {
                    is_match = FALSE;
                    break;
                }
            }
            if (is_match) {
                pm = strncat(pm, s, sizeof(s));
                pm = strncat(pm, " ", 1);
            }

        }
    }
    printf("\nDid you mean: %s", matches);
    return 0;
}

/*
 * CLI
 */
int shell_proc()
{
    char cmd[MAX_CMD_LEN];
    char next;
    int cmd_len = 0;
    static struct termios oldt, newt;
    memset(cmd, 0, MAX_CMD_LEN);

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);


    while (1) {
        next = getchar(); 
        switch (next) {
            case '\t':
                command_completion(cmd);
                break;
            case '\n':
                // Did this even work?
                if (!strncmp(cmd, "exit", MAX_CMD_LEN))
                    exit(0);
                break;
        }

        cmd_len = strlen(cmd);
        if (cmd_len < MAX_CMD_LEN)
        cmd[cmd_len] = next;
        // note the carriage return; not a newline
        if (!strncmp(cmd, "exit\r", MAX_CMD_LEN))
            exit(0);
        else if (!strncmp(cmd, "\rexit\r", MAX_CMD_LEN))
            exit(0);


        if (next == '\n')
            memset(cmd, 0, MAX_CMD_LEN);
    }
}

int main(void) 
{
    int r1, r2;

    cli_list[0].fn(&r1);
    cli_list[1].fn(&r2);
    cli_list[2].fn(&r1);
    cli_list[3].fn(&r2);

    printf("%s: %d: %s\n", cli_list[0].name, r1, cli_list[0].desc);
    printf("%s: %d: %s\n", cli_list[1].name, r2, cli_list[1].desc);
    printf("%s: %d: %s\n", cli_list[2].name, r1, cli_list[2].desc);
    printf("%s: %d: %s\n", cli_list[3].name, r2, cli_list[3].desc);

    shell_proc();


    return 0;
}




