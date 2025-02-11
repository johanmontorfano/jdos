int s_strcmp(char *s1, char *s2)
{
    unsigned int i;

    i = 0;
    if (!s1 || !s2)
        return 1;
    while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
        i++;
    return (s1[i] - s2[i]);
}
