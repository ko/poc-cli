#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdint.h>

#include "command.h"
#include "cli.h"

int command_execute(char * cmd)
{
    int i;
    uint64_t rc = -1;
    int args;   // TODO handle arguments

    // check for invalid cmd
    int cmd_len = strlen(cmd);
    if (cmd_len == 0) {
        return rc;
    } else {
        // ignore tab completion attempts
        if (cmd[cmd_len-1] == '\t')
            return rc;
    }

    for (i = 0; i < cli_entries; i++) {
        if (strcmp(cli_list[i].name, cmd) == 0) {
            rc = (uint64_t)cli_list[i].fn(&args);
            break;
        }
    }
    if (rc == -1) {
        printf("Unknown commanad: %s\n", cmd);
    }
    return rc;
}

int command_completion(char * partialcmd)
{
    int i, j;
    char is_match = TRUE;
    char * s;
    char matches[256] = "";
    char * pm = matches;
    for (i = 0; i < cli_entries; i++) { 
        is_match = TRUE;    // reset the is_match counter every potential cmd
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
                // On newline, execute cmd
                command_execute(cmd);
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

       if (next == '\n') {
           memset(cmd, 0, MAX_CMD_LEN);
       }
    }
}

int main(void) 
{
    shell_proc();
    return 0;
}




