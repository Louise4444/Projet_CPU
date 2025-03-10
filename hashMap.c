#define TOMBSTONE (( void *) -1)
#define TABLE_SIZE 128
#include <stdio.h>    
#include <stdlib.h> 
#include <stdint.h>   
#include <math.h>     
#include <string.h>
#include "hashMap.h"


/* convertir une chaˆıne de caract`eres en un indice dans la table de hachage */
unsigned long simple_hash(const char *str){
    unsigned long somme=0;
    for (unsigned long i=0;str[i]!='\0';i++){
        somme+=str[i];
    }
    return somme;
}

HashMap *hashmap_create(){
    HashMap *new =(HashMap *)malloc (TABLE_SIZE*sizeof(HashMap ));
    if (new == NULL) {
        return NULL;  
    }
    new->size = TABLE_SIZE;  
    new->table = (HashEntry *)malloc(TABLE_SIZE * sizeof(HashEntry));

    for(int i=0;i<TABLE_SIZE;i++){
        new->table[i].value=NULL;
        new->table[i].key=NULL;
    }
    return new;

}

int hashmap_insert(HashMap *map, const char *key, void *value){
    unsigned long indice = simple_hash(key);
    while(map->table[indice].key!=NULL && map->table[indice].key!=TOMBSTONE){
        if (strcmp(map->table[indice].key, key) == 0) {
            map->table[indice].value = value;  // si elle existe on remet a jour la valeur de la cle
            return 1;
        }
        indice = (indice+ 1);// sinon je decale pour eviter les collisions
    }
    map->table[indice].key=strdup(key);
    map->table[indice].value=value;

    return 0;  
}

void *hashmap_get(HashMap *map, const char *key){
unsigned long indice = simple_hash(key);
   while(map->table[indice].key != NULL && map->table[indice].key != TOMBSTONE){
   	if(strcmp(map->table[indice].key,key)==0){
   		return map->table[indice].value;
   	}
   	indice=indice+1;//gerer les colllisions 
   }
return NULL;
}

int hashmap_remove(HashMap *map, const char *key){
	if (map == NULL || key == NULL) {
        	return 0;
        }
        
unsigned long indice = simple_hash(key);
while(map->table[indice].key != NULL && map->table[indice].key != TOMBSTONE){
   	if(strcmp(map->table[indice].key,key)==0){
   		map->table[indice].key=TOMBSTONE;
   		map->table[indice].value = NULL;
   		return 1;
  	
   	}
   	indice=indice+1;//gerer les colllisions 
   }
return 0 ;
}
   	
void hashmap_destroy(HashMap *map){
	if (map == NULL) {
        return; 
        }
        
	for(int i=0;i<map->size;i++){
		 if (map->table[i].key != NULL && map->table[i].key != TOMBSTONE) {
		 free(map->table[i].key);
		}
	}
	free(map->table);
	free(map);
return;
}
		

