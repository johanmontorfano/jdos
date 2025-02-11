#ifndef MOD_STANDARD
    #define MOD_STANDARD
    #define MEM_PAGE_SIZE 0x1000

int c_isalphanum(char c);
int c_isalpha(char c);
int c_isnum(char c);
int s_strlen(char *str);
int s_strcmp(char *s1, char *s2);
void s_strcpy(char *dest, char *src);
void mem_set(unsigned char *dest, unsigned int size);
void mem_copy(unsigned char *source, unsigned char *dest, int n);
void write(char *str, int n);
void write_int(int nb);
void write_hex(unsigned int nb);
void *mem_alloc(unsigned int size);

#endif
