#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stm32f4xx_hal.h>
#include <timer.h>

typedef enum{
ST_DB_IDLE,
ST_DB_DEBOUNCE,
ST_DB_CLEAR,
ST_DB_OFF,
}ST_DEBOUNCE;

typedef enum{
EVT_DB_IDLE,
EVT_DB_SIGNAL,
EVT_DB_FINISH,
EVT_DB_RELEASE,
EVT_DB_OFF,
}EVT_DEBOUNCE;

typedef struct{
uint8_t st_before;
uint8_t st_now;
uint32_t pin;
GPIO_TypeDef *port;
TIMER timer;
EVT_DEBOUNCE event;
ST_DEBOUNCE state;
}DEBOUNCER;

void debouncer_init(DEBOUNCER *db, uint32_t pin, GPIO_TypeDef *port);
void process_bounce(DEBOUNCER *db);
bool pressed(DEBOUNCER const *db);
#endif
