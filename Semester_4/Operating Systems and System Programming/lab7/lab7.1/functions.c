#include "functions.h"

//---------------------------------------------
// Additionary:
//---------------------------------------------
void instructions()
{
    puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    printf("+p -- add producer\n"
           "+c -- add consumer\n"
           "-p -- delete producer\n"
           "-c -- delete consumer\n"
           "l -- list of threads\n"
           "i -- show information\n"
           "q -- exit\n");
    puts("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
}


int rand_generator() {
	int number;
	do {
		number = rand() % 257;
	} while(number == 0);
	return number;
}


//---------------------------------------------
// Ring buffer:
//---------------------------------------------
struct message init_msg() {
	struct message msg;
	msg.size = rand_generator();
	msg.hash = msg.size;
	for(int i = 0; i < msg.size; i++) {
		msg.data[i] = rand_generator();
		msg.hash += msg.data[i];
	}
	return msg;
}


void init_ring_buffer(struct ring_buffer* buffer_ptr) {
    buffer_ptr->buffer = (struct message*)malloc(sizeof(struct message) * RING_BUFFER_LENGTH);
    buffer_ptr->read_index = 0;
    buffer_ptr->write_index = 0;
    buffer_ptr->size = RING_BUFFER_LENGTH;
    buffer_ptr->full = 0;
    buffer_ptr->empty = 1;
    buffer_ptr->push_msg = 0;
    buffer_ptr->pop_msg = 0;
}


void push_msg(struct ring_buffer* buffer_ptr, struct message msg){
	if(buffer_ptr->full != 1) {
		buffer_ptr->buffer[buffer_ptr->write_index] = msg;
		if((buffer_ptr->write_index + 1) == buffer_ptr->size) {
			buffer_ptr->write_index = 0;
		} else {
			buffer_ptr->write_index += 1;
		}
		buffer_ptr->push_msg += 1;
		buffer_ptr->empty = 0;
		
		if(buffer_ptr->write_index == buffer_ptr->read_index){
			buffer_ptr->full = 1;
		}
	}
}


struct message pop_msg(struct ring_buffer* buffer_ptr){
	struct message msg = {0, 0, 0, {0}};
	if(buffer_ptr->empty != 1){
		msg = buffer_ptr->buffer[buffer_ptr->read_index];
		if((buffer_ptr->read_index + 1) == buffer_ptr->size){
			buffer_ptr->read_index = 0;
		} else {
			buffer_ptr->read_index += 1;
		}
		buffer_ptr->pop_msg += 1;
		buffer_ptr->full = 0;
		
		if(buffer_ptr->write_index == buffer_ptr->read_index){
			buffer_ptr->empty = 1;
		}
	}
	return msg;
}
