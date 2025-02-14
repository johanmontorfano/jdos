#ifndef CLIB
    #define CLIB
    #define MEM_PAGE_SIZE 0x1000
    #include "ctypes.h"

int c_isalphanum(char c);
int c_isalpha(char c);
int c_isnum(char c);
int c_isspace(char c);
int c_isalphalow(char c);
int c_isalphaup(char c);
int c_isprintable(char c);
int s_strlen(char *str);
int s_strcmp(char *s1, char *s2);
int atoi(char *str);
int uint16bitst(uint16_t nb, int bit);
void s_strcpy(char *dest, char *src);
void mem_set(unsigned char *dest, unsigned int size);
void mem_copy(unsigned char *source, unsigned char *dest, int n);
void write(char *str, int n);
void write_int(int nb);
void write_uint(unsigned int nb);
void write_hex(unsigned int nb);
void *mem_alloc(unsigned int size);
char **argparse(char *str);
uint32_t ui16c32(uint16_t a, uint16_t b);
uint64_t ui32c64(uint32_t a, uint32_t b);
uint64_t ui16c64(uint16_t a, uint16_t b, uint16_t c, uint16_t d);

#endif
