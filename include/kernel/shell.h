#ifndef KERNEL_SHELL
    #define KERNEL_SHELL
    #define SHELL_NAME "jdsh (johan's dumb shell)"
    #define SHELL_VER 0
    #define DISKSHELL_NAME "DISKSHELL"
    #define DISKSHELL_VER 0

void diskshell();
void on_line(char *str);
void print_program_handle(char *name, int version);

#endif
