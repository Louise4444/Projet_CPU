#include <stdio.h>    
#include <stdlib.h> 
#include <stdint.h>   
#include <math.h>     
#include <string.h>
#include "segment.h"
MemoryHandler *memory_init(int size){
MemoryHandler* new_MH = (MemoryHandler*) malloc(sizeof(MemoryHandler));
	if(new_MH==NULL)
		return NULL;

new_MH->memory = (void **)malloc(size * sizeof(void *));
	if (new_MH->memory == NULL) {
        	free(new_MH);
        	return NULL;
   	 }
  
Segment *segment = (Segment *)malloc(sizeof(Segment));
	if (segment == NULL) {
		free(new_MH->memory);
        	free(new_MH);
        	return NULL;
    	}

segment->start = 0;
segment->size = size;
segment->next = NULL;

new_MH->total_size = size;
new_MH->free_list = segment;
new_MH->allocated = hashmap_create();

return new_MH;
}

Segment* find_free_segment(MemoryHandler* handler, int start, int size, Segment** prev) {
    Segment* courant = handler->free_list;
    *prev = NULL; 

    while (courant != NULL && courant->size != size  && courant->start!= start) {
            *prev=courant;
             courant  = courant-> next ;
        }
        
    return courant;
}

int create_segment(MemoryHandler *handler, const char *name,
int start, int size){// a revoir !!!!!!!!!
Segment*prev=NULL;
Segment*res= find_free_segment(handler, start,size, &prev);
	if (res!=NULL){
		Segment *new_seg = (Segment *)malloc(sizeof(Segment));
		if (!new_seg) {
        		return -1; 
    		}
    		
		new_seg->start = 0;
		new_seg->size = size;
		new_seg->next = NULL;
		
		if (hashmap_insert(handler->allocated, name, new_seg) != 0) {
        		free(new_seg);//si je peux pas inserer je supp 
        		return -1;
    		}
		
		Segment *nv_seg=(Segment *)malloc(sizeof(Segment));
		if (!nv_seg) {
        		return -1; 
    		}
		nv_seg->start=start+size;
		nv_seg->size=res->start-(start+size);
		nv_seg->next=res->next;
		
		res->size=start-res->start;
		res->next=new_seg;
		
		
		return 1;
	}
	else{
		return -1;}

		
    	}
	
int remove_segment(MemoryHandler *handler, const char *name){
Segment *segment = (Segment *) hashmap_get(handler->allocated, name);
	if (segment==NULL) {
        return -1;
        printf("le segment existe pas dans la table de hachage");
        
hashmap_remove(handler->allocated, name);

Segment **prev = NULL;
Segment *courant = handler->free_list;

	while(courant!=NULL && current->start < segment->start){
		*prev=courant;
		courant=courant->next;
	}
	segment->next=courant;
	*prev->next=segment;
	
	if(*prev==NULL)
		 handler->free_list = segment;
		 
	// refaire linvers de la fontion passée 
	
 

    }

  	
    	


































int main(){
return 0;}



