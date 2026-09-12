#include "buffer.h"


void buffer_init(BUFFER *bff){
if(bff == NULL){
	return;
}

bff->head = 0;
bff->tail = 0;
bff->is_full = false;
for(int i = 0; i < BUFFER_SIZE; i++){
	bff->data[i] = 0;
	}
}

static bool buffer_empty(const BUFFER *bff){
if(bff == NULL){
	return false;
	}

if((bff->head == bff->tail) && !bff->is_full){
	return true;
	}
return false;
}

static bool buffer_full(const BUFFER *bff){
if(bff == NULL){
	return false;
	}
return bff->is_full;
}


bool buffer_write(BUFFER *bff, char *data){
if(bff == NULL || data == NULL){
	return false;
}

if(buffer_full(bff)){
	return false;
}

bff->data[bff->head] = *data;
CYCLE(bff->head);
if(bff->head == bff->tail){
	bff->is_full = true;
	}
return true;	
}

void buffer_read(BUFFER *bff, char *data){
if(bff == NULL || data == NULL){
	return;
	}

if(buffer_empty(bff)){
	return;
}

*data = bff->data[bff->tail];
CYCLE(bff->tail);
bff->is_full = false;

}








