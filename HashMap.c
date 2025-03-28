#include <stdio.h>
#include <stdlib.h>
#include "HashMap.h"


// convertir une chaı̂ne de caractères en un indice dans la table de hachage.
unsigned long simple_hash(const char *str){

    unsigned long converted_str=0;

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


int hashmap_insert(HashMap *map, const char *key, void *value) {
    unsigned long indice = simple_hash(key);
    int nb = map->size;

    while (nb > 0 && map->table[indice].key != NULL && map->table[indice].key !=(char*) TOMBSTONE) {
        if (strcmp(map->table[indice].key, key) == 0) {
            map->table[indice].value = value; 
            return 1;  // La clé existe déjà, on met à jour la valeur
        }
        nb--;
        indice = (indice + 1) % map->size;
    }

    // Si on rencontre un TOMBSTONE_KEY, on remplace la case et on insère la nouvelle clé-valeur
    if (nb > 0) {
        map->table[indice].key = strdup(key);  // Allouer et copier la nouvelle clé
        map->table[indice].value = value;      // Insérer la nouvelle valeur
        return indice;
    }

    printf("Table pleine\n");
    return -1;  // Table pleine, insertion échouée
}


void* hashmap_get(HashMap *map, const char *key) {

    if (!map || !(map->table)) {
        fprintf(stderr, "Erreur : table de hachage inexistante - Fichier: %s, Fonction: %s, Ligne: %d\n",
                __FILE__, __PRETTY_FUNCTION__, __LINE__);
        exit(64);
    }

    unsigned long indice = simple_hash(key);
    int nb = map->size;

    while (nb > 0 && map->table[indice].key != NULL) {
        // Si on rencontre un TOMBSTONE, on l'ignore et on continue la recherche
        if (map->table[indice].key == (char*)TOMBSTONE) {
            return NULL;  // Clé supprimée, donc on retourne NULL
        }
        if (strcmp(map->table[indice].key, key) == 0) {
            return map->table[indice].value;  // Clé trouvée, on retourne la valeur
        }
        nb--;
        indice = (indice + 1) % map->size;
    }

    return NULL;  // Clé non trouvée
}




int hashmap_remove(HashMap *map, const char *key) {
    if (!map || !(map->table)) {
        fprintf(stderr, "Erreur : table de hachage inexistante - Fichier: %s, Fonction: %s, Ligne: %d\n",
                __FILE__, __PRETTY_FUNCTION__, __LINE__);
        exit(64);
    }

    unsigned long indice = simple_hash(key);
    int nb = map->size;

    while (nb > 0 && map->table[indice].key != NULL && map->table[indice].key != (char*)TOMBSTONE) {
        if (strcmp(map->table[indice].key, key) == 0) {
            // Libérer la mémoire de la clé avant de la remplacer
            free(map->table[indice].key);
            map->table[indice].key =(char*) TOMBSTONE;  // Remplacer la clé par TOMBSTONE
            map->table[indice].value = TOMBSTONE;    // Remplacer la valeur par TOMBSTONE
            return indice;
        }
        nb--;
        indice = (indice + 1) % map->size;
    }

    return -1;  // Clé non trouvée
}



void hashmap_destroy(HashMap *map){
    if (!map || !(map->table)) {
        fprintf(stderr, "Erreur : table de hachage inexistante - Fichier: %s, Fonction: %s, Ligne: %d\n",
                __FILE__, __PRETTY_FUNCTION__, __LINE__);
        exit(64);
    }

    for(int i=0;i<map->size;i++){
        if (map->table[i].key != NULL && map->table[i].key != TOMBSTONE) {
        free(map->table[i].key);
       }
   }
   free(map->table);
   free(map);

}

