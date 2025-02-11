/// WARN: Doesn't check if dest is long enough
void s_strcpy(char *dest, char *src)
{
    int i = 0;

    while (src && src[i]) {
        dest[i] = src[i];
        i++;
    }
}
