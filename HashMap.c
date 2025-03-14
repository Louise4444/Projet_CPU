#include <stdio.h>
#include <stdlib.h>
#include "HashMap.h"


// convertir une chaı̂ne de caractères en un indice dans la table de hachage.
unsigned long simple_hash(const char *str){

    unsigned long converted_str;

    for(int i=0; str[i]!= '\0'; i++){
        converted_str+= str[i];
    }
    
    return converted_str % TABLE_SIZE;
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

    unsigned long indice = simple_hash(key);
    int nb=map->size;
    while(nb>0 && map->table[indice].key!=NULL && map->table[indice].key!=TOMBSTONE){
        if (strcmp(map->table[indice].key, key) == 0) {
            map->table[indice].value = value; 
            return 1;
        }
        nb--;
        indice = (indice+ 1)% map->size;
    }

    if (nb>0){
        map->table[indice].key=strdup(key);
        map->table[indice].value=value;
        return indice; 
    }

    else{
        printf("table pleine"); 
        return -1;
    }

}

void* hashmap_get(HashMap *map, const char *key) {

    if (!map || !(map->table)) {
        fprintf(stderr, "Erreur : table de hachage inexistante - Fichier: %s, Fonction: %s, Ligne: %d\n",
                __FILE__, __PRETTY_FUNCTION__, __LINE__);
        exit(64);
    }

    unsigned long indice = simple_hash(key);
    int nb=map->size;
    while(nb>0 && map->table[indice].key!=key){
        nb--;
        indice = (indice+ 1)% map->size;
    }

    if (nb>0){
        return map->table[indice].value;
    }

    return "pas de clé trouvé"; 
}



int hashmap_remove(HashMap *map, const char *key){
    if (!map || !(map->table)) {
        fprintf(stderr, "Erreur : table de hachage inexistante - Fichier: %s, Fonction: %s, Ligne: %d\n",
                __FILE__, __PRETTY_FUNCTION__, __LINE__);
        exit(64);
    }

    map->table[simple_hash(key)].value=TOMBSTONE;
    map->table[simple_hash(key)].key=NULL;

    return 0;
}


void hashmap_destroy(HashMap *map){
    if (!map || !(map->table)) {
        fprintf(stderr, "Erreur : table de hachage inexistante - Fichier: %s, Fonction: %s, Ligne: %d\n",
                __FILE__, __PRETTY_FUNCTION__, __LINE__);
        exit(64);
    }

    free(map->table);
    free(map);


}