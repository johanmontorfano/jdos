#include "clib.h"

/// Reads numbers from a string and create a number from it. Stops at the first
/// non numeral character encountered.
int atoi(char *str)
{
    int len = s_strlen(str);
    int out = 0;
    int i = 0;

    while(str && str[i] && c_isnum(str[len - i])) {
        out += str[len - i] - 48 * (i + 1);
        i++;
    }
    return out;
}
