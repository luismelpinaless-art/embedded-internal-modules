#include <buffer.h>


void buffer_init(BUFFER *bff){
if(bff == NULL){
	return;
}

bff->head = 0;
bff->tail = 0;
for(int i = 0; i < BUFFER_SIZE; i++){
	bff->data[i] = 0;
	}
}

static bool buffer_empty(const BUFFER *bff){
if(bff == NULL){
	return false;
	}
if(bff->head == bff->tail){
	return true;
}

return false;
}

static bool buffer_full(const BUFFER *bff){
if(bff == NULL){
	return false;
	}
if(((bff->head+1) % BUFFER_SIZE) == bff->tail){
	return true;
}

return false;
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
return true;
}

bool buffer_read(BUFFER *bff, char *data){
if(bff == NULL || data == NULL){
	return false;
	}

if(buffer_empty(bff)){
	return false;
}

*data = bff->data[bff->tail];
CYCLE(bff->tail);
return true;
}



