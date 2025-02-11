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
    print("EXIT             Halt the CPU\n");
    print("SHELl            Print shell version\n");
    print("KB.LAY <code>    Changes keyboard layout\n");
}

void on_line(char *str)
{
    if (!s_strcmp(str, "EXIT")) {
        print("CPU halted");
        asm volatile("hlt");
    }
    if (!s_strcmp(str, "SHELL"))
        print_shell_info();
    if (!s_strcmp(str, "HELP"))
        print_help();
    print("> ");
}
