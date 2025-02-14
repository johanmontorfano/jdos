#include "clib.h"
#include "drivlib.h"
#include "kernel/shell.h"

/// Print a program name and its version.
void print_program_handle(char *name, int version)
{
    print(name);
    print(" v");
    write_int(version);
    print("\n");
}
