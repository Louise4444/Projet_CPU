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

    while(current){

        if (current->start = start && current->size >= size) break;

        *prev = current ;
        current  = current-> next ;
    }

    if (!current){
        *prev = NULL;
    }

    return current ;
}



int create_segment(MemoryHandler *handler, const char *name,int start, int size){

    Segment* new_seg;
    Segment* prev = NULL; 
    Segment* seg_free= find_free_segment(handler, start, size, &prev);

    if (seg_free){
        
        if (seg_free->size = size){
            prev->next= seg_free->next;
            new_seg= seg_free;    
        }

        else {
            seg_free->start += size;
            seg_free->size -= size;
            new_seg= malloc (sizeof(Segment));
            new_seg->start=start;
            new_seg->size= size;
            new_seg->next=NULL;
            
        }

        hashmap_insert ( handler, name,new_seg);
        return -1;
        
    }

    return -1;
}


int remove_segment(MemoryHandler *handler, const char *name){


    return 0;
}