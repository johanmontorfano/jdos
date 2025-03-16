#include "ctypes.h"

int s_strlen(char *str)
{
    uint32_t i = 0;

    for (; str && str[i]; i++);
    return i;
}
