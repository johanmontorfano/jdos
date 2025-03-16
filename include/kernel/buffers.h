#ifndef BUFFERS
    #define BUFFERS
    #include "ctypes.h"

extern char *stdin;
extern uint32_t stdin_size;

void stdin_write(char c);
void stdin_flush(void);
void stdin_init(void);

#endif
