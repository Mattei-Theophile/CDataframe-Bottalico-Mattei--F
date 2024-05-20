//
// Created by theop on 28/03/2024.
//
#include <stdlib.h>
#include <stdio.h>

#include "column.h"

/*Information du fichier
 *Projet de programmation C - CDataframe - Matteï Théophile et Bottalico Thomas
 *
 * Column.c permet d'avoir toutes les fonctions permettant de gérer le CDATAFRAME comme la supression et l'ajout
 * de colonne/ligne mais aussi changer le nom des colonnes, la conversion des valeurs en chaine de caractère
 * et l'ajout dans le tableau
 */


//
// ~~~~~~ colonnes ~~~~~~
//

/**
* @brief: création d'une colonne
* param1: nom de la colonne
* param2: type de la colonne
*/
COLUMN *create_column(char *title, ENUM_TYPE type) {

    COLUMN *col = (COLUMN *) malloc(sizeof(COLUMN));
    if (col == NULL) return NULL;
    else{
        col->name = title;
        col->physical_size = 0;
        col->logical_size = 0;
        col->type = type;
        col->data = NULL;
        return col;
    }
}

/**
* @brief: ajoute une colonne à la queue du CDATAFRAME
* param1: pointeur sur le CDATAFRAME
* param2: pointeur sur le nom de la nouvelle colonne
* param3: type de la nouvelle colonne
*/
void add_column(CDATAFRAME *cdf, char* title, ENUM_TYPE type){
    COLUMN *data = create_column(title, type);
    lnode *node = lst_create_lnode(data);
    lst_insert_tail(cdf,node);
}

/**
* @breif: supression de la colonne
* @param1: pointeur sur le CDATAFRAME
* @param2: position de la colonne à supprimer, toujours prendre
*/
void delete_column(CDATAFRAME *cdf, int index){
    lnode *node = cdf->head;
    COLUMN *col;
    //parcour le tableau jusqu'à colonne == index
    for( int i = 0; i <= index; i++) {
        node = node->next;
    }
    col = node->data;
    lst_delete_lnode(cdf, node);
    free(col->data);
    free(col);

}

/**
* @brief: renommer une colonne
* param1: Pointeur sur le CDATAFRAME
* param2: la position de la colonne à renommer
* param3: Pointeur sur le nouveau nom de la colonne
*/
void rename_column(CDATAFRAME *cdf, int index, char *new_name){
    printf("\n");
    if (cdf != NULL){
        lnode *tmp = cdf->head;
        COLUMN  *col = tmp->data;
        for (int i=0; i <= index; i++){
            tmp = tmp->next;
            col = tmp->data;
        }
        col->name = new_name;
    }
}


//
// ~~~~~~ Lignes ~~~~~~
//


/**
* @brief: ajout d'une ligne au CDATAFRAME
* param1: Pointeur sur le CDATAFRAME
* param2: la position de la nouvelle ligne à rajouter
* param2: tableau de pointeur qui stocke tous les types de valeurs
*/
void add_row(CDATAFRAME *cdf, unsigned  int index, void* value_tab){
    if (cdf != NULL){

        lnode* node = cdf->head;
        unsigned int i= 0;
        while(node != NULL){
            COLUMN* col = node->data;

            if(col->physical_size <= col->logical_size){
                COL_TYPE *tmp = realloc(col->data, REALLOC_SIZE);
                if(tmp == NULL) printf("Problème dans l'ajout de la ligne");
                col->physical_size = col->physical_size + REALLOC_SIZE;
                *col->data = tmp;
                free(tmp);
            }


            insert_value(col, &value_tab);
            void * tampon;
            for (unsigned int k= col->logical_size; index == k; k--){
                tampon =col->data[k+1];
                col->data[k+1] = col->data[k];
            }
            col->data[index]= tampon;
            node = node->next;
            i ++;
        }
    }
}

/**
* @brief: supression d'une colonne
* param1: Pointeur sur le CDATAFRAME
* param2: la position de la ligne à supprimer
*/
void delete_row(CDATAFRAME *cdf, unsigned int index){
    if (cdf != NULL){
        unsigned int row_size = get_cdataframe_rows_size(cdf);
        lnode* node = cdf->head;
        for (int i = 0; i < row_size ; i++){
            COLUMN* col = node->data;

            for (unsigned int k= index; k < col->logical_size; k++){
                col->data[k] = col->data[k+1];
            }
            free(col->data[col->logical_size]);
            col->logical_size --;
            if (node->next != NULL){
                node = node->next;
            }
        }
    }
}

//
// ~~~~~~ valeur et conversion ~~~~~~
//

/**
* @brief: convertie une valeur spécifique dans un chaîne de caractère
* param1: Pointeur sur la colonne
* param2: position de la valeur dans la colonne de donnée
* param3: Pointeur sur le tableau qui stocke le résultat
* param4: taille du tableau
*/
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size){
    switch(col->type){
        case NULLVAL:
            snprintf(str, size, "%p", *((void**)col->data[i]));
            break;

        case UINT:
            snprintf(str, size, "%d", *((unsigned int*)col->data[i]));
            break;

        case INT:
            snprintf(str, size, "%d", *((int*)col->data[i]));
            break;

        case CHAR:
            snprintf(str, size, "%c", *((char*)col->data[i]));
            break;

        case FLOAT:
            snprintf(str, size, "%f", *((float*)col->data[i]));
            break;

        case DOUBLE:
            snprintf(str, size, "%lf", *((double*)col->data[i]));
            break;

        case STRING:
            snprintf(str, size, "%s", *((char**)col->data[i]));
            break;

        case STRUCTURE:
            snprintf(str, size, "%p", *((void**)col->data[i]));
            break;
    }

}


/**
* @brief: insère une valeur à la fin de la colonne
* param1: Pointeur sur la colonne
* param1: Pointeur sur l'adresse de la valeur à ajouter
*/
int insert_value(COLUMN *col, void *value){
    if (col != NULL){

        //allocation de la mémoire et réallo
        if (col->physical_size == 0){
            col->data = (COL_TYPE**) malloc(sizeof(COL_TYPE)*REALLOC_SIZE);
            if (col->data == NULL) return 0;
            col->physical_size = 256;

        }

        if(col->physical_size <= col->logical_size){
            COL_TYPE *tmp = realloc(col->data, col->physical_size + REALLOC_SIZE);
            if(tmp == NULL) return 0;

            col->physical_size = col->physical_size + REALLOC_SIZE;

            *col->data = tmp;
            tmp = NULL;
        }

        switch(col->type){

                case NULLVAL:
                    col->data[col->logical_size] = (COL_TYPE *) malloc (sizeof(void*));
                    *((void**)col->data[col->logical_size])= *((void**)value);
                    break;

                case UINT:
                    if (value >= 0) {
                        col->data[col->logical_size] = (COL_TYPE *) malloc(sizeof(unsigned int));
                        *((unsigned int *) col->data[col->logical_size]) = *((unsigned int *) value);
                    }
                    else {
                        return 0;
                    }
                    break;

                case INT:
                    col->data[col->logical_size] = (COL_TYPE *) malloc (sizeof( int));
                    *((int*)col->data[col->logical_size])= *((int*)value);
                    break;

                case CHAR:
                    col->data[col->logical_size] = (COL_TYPE *) malloc (sizeof(char));
                    *((char*)col->data[col->logical_size])= *((char*)value);
                    break;

                case FLOAT:
                    col->data[col->logical_size] = (COL_TYPE *) malloc (sizeof(float));
                    *((float*)col->data[col->logical_size])= *((float*)value);
                    break;

                case DOUBLE:
                    col->data[col->logical_size] = (COL_TYPE *) malloc (sizeof(double));
                    *((double*)col->data[col->logical_size])= *((double*)value);
                    break;

                case STRING:
                    col->data[col->logical_size] = (COL_TYPE *) malloc (sizeof(char*));
                    *((char**)col->data[col->logical_size])= *((char**)value);
                    break;

                case STRUCTURE:
                col->data[col->logical_size] = (COL_TYPE *) malloc (sizeof(void*));
                *((void**)col->data[col->logical_size])= *((void**)value);
                break;
        }
        col->logical_size++;
        return 1;
    }
    else{
        return 0;
    }
}

/**
* @brief: convertie une valeur hors d'un CDATAFRAME
* param1: Pointeur sur une valeur
* param2: type de la valeur à convertir
* param3: Pointeur sur le tableau qui stocke le résultat
* param4: taille du tableau
*/

void convert_research(void *value, ENUM_TYPE type, char *str, int size){
    switch(type){
        case NULLVAL:
            //fonction permettant de transformer un type précis en chaîne de caractère
            snprintf(str, size, "%p", *((void**)value));
            break;

        case UINT:
            snprintf(str, size, "%d", *((unsigned int*)value));
            break;

        case INT:
            snprintf(str, size, "%d", *((int*)value));
            break;

        case CHAR:
            snprintf(str, size, "%c", *((char*)value));
            break;

        case FLOAT:
            snprintf(str, size, "%f", *((float*)value));
            break;

        case DOUBLE:
            snprintf(str, size, "%lf", *((double*)value));
            break;

        case STRING:
            snprintf(str, size, "%s", *((char**)value));
            break;

        case STRUCTURE:
            snprintf(str, size, "%p", *((void**)value));
            break;
    }
}