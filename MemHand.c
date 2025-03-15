#include "MemHand.h"





MemoryHandler *memor_init(int size){

    MemoryHandler * mem= (MemoryHandler*) malloc(sizeof(MemoryHandler));
    mem->total_size= size;
    mem->free_list=malloc(sizeof(Segment));
    mem->free_list->size=mem->total_size;
    mem->free_list->start=0;
    mem->free_list->next=NULL;
    mem->allocated=hashmap_create();

    return mem;

}




Segment* find_free_segment(MemoryHandler* handler, int start, int size, Segment** prev){

    Segment* current = handler->free_list;

    while(current  && current->start!= start && current->size != size){
        *prev = current ;
        current  = current-> next ;
    }

    if (!current){
        *prev = NULL;
    }

    return current ;
}



int create_segment(MemoryHandler *handler, const char *name,int start, int size){

    return 0;
}


int remove_segment(MemoryHandler *handler, const char *name){


    return 0;
}