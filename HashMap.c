#include <stdio.h>
#include <stdlib.h>
#include "HashMap.h"


// convertir une chaı̂ne de caractères en un indice dans la table de hachage.
unsigned long simple_hash(const char *str){

    unsigned long converted_str;

    for(int i=0; str[i]!= '\0'; i++){
        converted_str+= str[i];
    }
    
    return converted_str;
}

HashMap* hashmap_create(){

    HashMap* hash = malloc(sizeof(HashMap));

    if (!hash){
        fprintf(stderr,"Erreur d'allocation de la table de hachage %s %s %d \n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    }

    hash->size=127;
    hash->table= malloc(sizeof(HashEntry)*127); 

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

    if (!map || !(map->table)){
        fprintf (stderr,"table de hachage non existente %s %s %d \n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        exit(64);
    }

    int indice_insert= simple_hash(key);

    map->table[indice_insert].key=key;
    map->table[indice_insert].value=value;

    return indice_insert;

}


void* hashmap_get(HashMap *map, const char *key){


}


int hashmap_remove(HashMap *map, const char *key){


    return 0;
}


void hashmap_destroy(HashMap *map){


}