#include "debouncer.h"

void debouncer_init(DEBOUNCER *db, uint32_t pin, GPIO_TypeDef *port){

if(db == NULL || port == NULL){
	return;
}

timer_init(&db->timer, 15, 1);
db->st_now = 0;
db->st_before = 0;
db->port = port;
db->pin = pin;
db->state = ST_DB_IDLE;
db->event = EVT_DB_IDLE;
}

static bool read_signal(DEBOUNCER *db, GPIO_TypeDef *port, uint32_t pin){

if(db == NULL || port == NULL){
	return false;
}

if(HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET){
	return true;
	}
return false;
}

void process_debounce(DEBOUNCER *db){
if(db == NULL){
	return;
}

switch (db->state) {
	case ST_DB_IDLE:
			if(read_signal(db, db->port, db->pin)){
			db->event = EVT_DB_SIGNAL;
			timer_set(&db->timer);
			timer_update(&db->timer);
			}
			if(db->event == EVT_DB_SIGNAL){
			db->state = ST_DB_DEBOUNCE;
			}
		break;

	case ST_DB_DEBOUNCE:
			if(db->timer.event == EVT_TIMER_DONE){
				if(read_signal(db, db->port, db->pin) == true){
				db->event = EVT_DB_FINISH;
				db->st_now = 1;
				timer_reset(&db->timer);
				}else{
				db->st_now = 0;
				db->event = EVT_DB_IDLE;
				db->state = ST_DB_IDLE;
				timer_reset(&db->timer);
				}
			}
			if(db->event == EVT_DB_FINISH){
				db->state = ST_DB_CLEAR;
			}
		break;
	case ST_DB_CLEAR:
				db->st_before = db->st_now;
			if(read_signal(db, db->port, db->pin) == false){
					db->event = EVT_DB_OFF;
					timer_set(&db->timer);
					timer_update(&db->timer);
				}
			if(db->event == EVT_DB_OFF){
				db->state = ST_DB_OFF;
			}
		break;
	case ST_DB_OFF:
		if(db->timer.event == EVT_TIMER_DONE){
			if(read_signal(db, db->port, db->pin) == false){
				timer_reset(&db->timer);
				db->event = EVT_DB_IDLE;
				db->st_now = 0;
			}else{
				db->event = EVT_DB_FINISH;
				db->state = ST_DB_CLEAR;
				db->st_now = 1;
				timer_reset(&db->timer);
			}
		}
				db->st_before = db->st_now;
				if(db->event == EVT_DB_IDLE){
					db->state = ST_DB_IDLE;
				}
		break;
	default:
		db->event = EVT_DB_IDLE;
		db->state = ST_DB_IDLE;
		db->st_before = 0;
		db->st_now = 0;
		break;
	}
}

