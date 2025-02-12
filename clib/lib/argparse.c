#include "stdlib.h"

static int count_words(char *str)
{
    int w = 0;
    int i = 0;
    int in_word = 0;

    while (str && str[i]) {
        if (in_word && c_isspace(str[i]))
            in_word = 0;
        if (!in_word && !c_isspace(str[i])) {
            in_word = 1;
            w++;
        }
        i++;
    }

    return w;
}

static int get_wlen(char *str, int from)
{
    int i = from;

    while (str && str[i] && !c_isspace(str[i]))
        i++;
    return i - from;
}

/// Will parse an array "word word, word" into { "word", "word,", "word" }
/// WARN: It only handles spaces, new lines and tabs because of c_isspace
char **argparse(char *str)
{
    char **out = (char **)mem_alloc(sizeof(char *) * (count_words(str) + 1));
    char *word = 0;
    int outi = 0;
    int wordi = 0;
    int stri = 0;

    while (str && str[stri]) {
        if (word && c_isspace(str[stri])) {
            word[wordi] = 0;
            out[outi] = word;
            word = 0;
            wordi = 0;
            outi++;
        }
        if (!word && !c_isspace(str[stri]))
            word = (char *)mem_alloc(sizeof(char) * (get_wlen(str, stri) +1));
        if (word && !c_isspace(str[stri])) {
            word[wordi] = str[stri];
            wordi++;
        }
        stri++;
    }
    if (word && !c_isspace(str[stri - 1]))
        out[outi++] = word;
    out[outi] = 0;
    return out;
}
