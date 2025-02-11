#include "shell.h"
#include "drivlib.h"
#include "stdlib.h"

static void dump_str_addr(char *addr)
{
    print("@ 0x");
    write_hex((unsigned int)addr);
    print(" >> '");
    print(addr);
    print("'\n");
}

static void print_shell_info(void)
{
    print(SHELL_NAME);
    print(" v");
    write_int(SHELL_VER);
    print("\n");
}

static void mem_alloc_test(void)
{
    char *str = (char *)mem_alloc(sizeof(char) * 8);
    char *str2 = (char *)mem_alloc(sizeof(char) * 20);

    s_strcpy(str, "HELLO");
    s_strcpy(str2, "WORLD from JOS");
    dump_str_addr(str);
    dump_str_addr(str2);
}

void on_line(char *str)
{
    if (!s_strcmp(str, "EXIT")) {
        print("CIAO");
        asm volatile("hlt");
    }
    if (!s_strcmp(str, "SHELL"))
        print_shell_info();
    if (!s_strcmp(str, "ALLOC.TEST"))
        mem_alloc_test();
    print("> ");
}
