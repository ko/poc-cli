
#define MAX_CMD_LEN 128

#define FALSE 0
#define TRUE 1

typedef struct cli_command_t {
    char name[64];
    void (*fn)();
    char desc[128];
} cli_command;




extern cli_command cli_list[];
extern unsigned int cli_entries;
