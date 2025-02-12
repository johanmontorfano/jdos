#include "shell.h"
#include "drivlib.h"
#include "stdlib.h"

static void print_shell_info(void)
{
    print(SHELL_NAME);
    print(" v");
    write_int(SHELL_VER);
    print("\n");
}

static void print_help(void)
{
    print("EXIT                 Halt the CPU\n");
    print("CLEAR                Clear the screen\n");
    print("SHELL                Print shell version\n");
    print("KEY.LAY <code>       Changes keyboard layout\n");
    print("KEY.GLAY             Get all available layouts\n");
}

static void print_layouts(void)
{
    print("AZERTY           code: 0\n");
    print("QWERTY           code: 1\n");
}

void on_line(char *str)
{
    char **args = argparse(str);

    if (!s_strcmp(args[0], "EXIT")) {
        print("CPU halted");
        asm volatile("hlt");
    }
    if (!s_strcmp(args[0], "SHELL"))
        print_shell_info();
    if (!s_strcmp(args[0], "HELP"))
        print_help();
    if (!s_strcmp(args[0], "KEY.GLAY"))
        print_layouts();
    if (!s_strcmp(args[0], "KEY.LAY"))
        update_kb_layout(atoi(args[1]));
    if (!s_strcmp(args[0], "CLEAR"))
        clear_screen();
    print("> ");
}
