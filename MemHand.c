#include "MemHand.h"


MemoryHandler *memor_init(int size){

    MemoryHandler * mem= (MemoryHandler*) malloc(sizeof(MemoryHandler));

    if(!mem)
        return NULL;
    
    mem->memory = (void **)malloc(size * sizeof(void *));
        if (mem->memory == NULL) {
            free(mem);
            return NULL;
        }

    mem->total_size= size;
    mem->free_list=malloc(sizeof(Segment));

    if ( !mem->free_list) {
		free(mem->memory);
        free(mem);
        return NULL;
    }


    mem->free_list->size=mem->total_size;
    mem->free_list->start=0;
    mem->free_list->next=NULL;
    mem->allocated=hashmap_create();

    return mem;

}

// ajouter art du metier
Segment* find_free_segment(MemoryHandler* handler, int start, int size, Segment** prev){

    Segment* current = handler->free_list;
    *prev = NULL;

    while(current){

        if (current->start <= start && size+start <= current->size+current->start) break;

        *prev = current ;
        current  = current-> next ;
    }

    if (!current){
        *prev = NULL;
    }

    return current ;
}



int create_segment(MemoryHandler *handler, const char *name,int start, int size){
    Segment* seg_free2;
    Segment* new_seg;
    Segment* prev = NULL; 
    Segment* seg_free= find_free_segment(handler, start, size, &prev);

    if (seg_free){
        
        if (start == seg_free->start && seg_free->size == size) {
            if (prev) prev->next = seg_free->next;
            else handler->free_list = seg_free->next; // Si c'était le premier segment libre

            new_seg = seg_free;    
        }

        else if(start==seg_free->start) {   // si plus grand on met a jour l'espace libre et on creer le nouveau segment alloué 
            seg_free->start += size;
            seg_free->size -= size; 
            new_seg= malloc (sizeof(Segment));
            new_seg->start=start;
            new_seg->size= size;
            new_seg->next=NULL;
        }

        else if(start > seg_free->start && start+size== seg_free->start + seg_free->size){
            seg_free->size= start-seg_free->start;
            new_seg= malloc (sizeof(Segment));
            new_seg->start=start;
            new_seg->size= size;
            new_seg->next=NULL;
        }
            
        else{
            int size_tot= seg_free->size;

            //premier segment qui reste libre
            seg_free->size =start-seg_free->start; 

            //le segment qui sera alloué
            new_seg= malloc (sizeof(Segment));
            new_seg->start=start;
            new_seg->size= size;
            new_seg->next=NULL;

            //dernier segment de libre a recup
            seg_free2= malloc (sizeof(Segment));
            seg_free2->start=start+size;
            seg_free2->size= size_tot-size - seg_free->size;
            seg_free2->next=NULL;  

        }

        

        if(hashmap_insert (handler->allocated, name,new_seg)){
            for (int i = start; i < start + size; i++) {
                handler->memory[i] = (void *) new_seg;
            }  
            return 0;          
        } 
        
    }

    return -1;
}


int remove_segment(MemoryHandler *handler, const char *name){

    Segment* seg_to_free =(Segment*) hashmap_get(handler->allocated,name);
    Segment* prec = NULL;

    if (seg_to_free) {

        hashmap_remove(handler->allocated, name);
        Segment * courant = handler->free_list; 

        while(courant && courant->start > seg_to_free->start){
            prec= courant;
            courant = courant->next;
        }

        if (!prec) {
            seg_to_free->next=handler->free_list;
            handler->free_list= seg_to_free;
        }

        else{
            seg_to_free->next=prec->next;
            prec->next=seg_to_free;
        }

        for (int i = seg_to_free->start; i < seg_to_free->start + seg_to_free->size; i++) {
                    handler->memory[i] = NULL;
                }

            
        //parcours de la liste pour la fusion des segments adjacents;
        while (courant && courant->next) {
            if (courant->start + courant->size == courant->next->start) {
                Segment* temp = courant->next;
                courant->size += temp->size;
                courant->next = temp->next;
                free(temp);
            } else {
                courant = courant->next;
            }
        }
    }

    return 0;
}