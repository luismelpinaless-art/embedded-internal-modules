#ifndef BUFFER_H
#define BUFFER_H
#define BUFFER_SIZE 32
#define CYCLE(var) (var) = (((var)+1) % BUFFER_SIZE)

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct{
volatile char data[BUFFER_SIZE];
volatile uint8_t head;
volatile uint8_t tail;
}BUFFER;

bool buffer_write(BUFFER *bff, char *data);
bool buffer_read(BUFFER *bff, char *data);
void buffer_init(BUFFER *bff);

#endif
