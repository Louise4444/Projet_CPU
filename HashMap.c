#include <stdio.h>
#include <stdlib.h>
#include "HashMap.h"

// convertir une chaı̂ne de caractères en un indice dans la table de hachage.
unsigned long simple_hash(const char *str){

    unsigned long converted_str;

    for(int i=0; str[i]!= '\0'; i++){
        converted_str+= str[i];
    }
    
    return converted_str % 127;
}

HashMap* hashmap_create(){

    HashMap* hash = (HashMap*) malloc(sizeof(HashMap));

    if (!hash){
        fprintf(stderr,"Erreur d'allocation de la table de hachage %s %s %d \n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        return NULL;
    }

    hash->size=TABLE_SIZE;
    hash->table= (HashEntry*) malloc(sizeof(HashEntry)*TABLE_SIZE); 

    if (!hash->table){
        fprintf(stderr,"Erreur d'allocation de la table de hachage %s %s %d \n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    }

    for(int i =0; i<hash->size; i++){
        hash -> table[i].key = NULL;
        hash -> table[i].value = NULL;
    }

    return hash;

}


int hashmap_insert(HashMap *map, const char *key, void *value){


    return 0;

}


void* hashmap_get(HashMap *map, const char *key){


}


int hashmap_remove(HashMap *map, const char *key){


    return 0;
}


void hashmap_destroy(HashMap *map){


}
