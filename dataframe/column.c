//
// Created by theop on 28/03/2024.
//
#include <stdlib.h>
#include <stdio.h>

#include "column.h"

// Vous pouvez lire le projet pour comprendre un peu le code parce que le prof explique certaines fonctions

/**
* @brief: create a column
* param1: name of the column
* param2: type of the column
*/
COLUMN *create_column(char *title, ENUM_TYPE type) {

    COLUMN *col = (COLUMN *) malloc(sizeof(COLUMN));
    if (col == NULL) {
        return NULL;
    }
    else{
        col->name = title;
        col->physical_size = 0;
        col->logical_size = 0;
        col->type = type;
        col->data = NULL;
        col->index = NULL;
        return col;
    }
}

/**
* @brief: Column deletion
* param1: Pointer to the CDataframe to delete
*/
void delete_cdataframe(CDATAFRAME **cdf){
    lst_erase(*cdf);
    free(cdf);
}


/**
* @brief: add a column in the CDATAFRAME at the end
* param1: Pointer to the CDataframe
* param2: Pointer to the name of the new column
* param3: type of the new column
*/
void add_column(CDATAFRAME *cdf, char* title, ENUM_TYPE type){
    COLUMN *data = create_column(title, type);
    lnode *tmp = lst_create_lnode(data);
    lst_insert_tail(cdf,tmp);
}

/**
* @breif: Delete column by name
* @param1: Pointer to the CDataframe
* @param2: Column name
 * quelques problèmes
*/
void delete_column(CDATAFRAME *cdf, int index){
    lnode *tmp = cdf->head;
    COLUMN *col;
    for( int i = 0; i < index; i++) {
        tmp = tmp->next;
    }
    col = tmp->data;
    lst_delete_lnode(cdf, tmp);
    free(col->data);
    free(col);

}


/**
* @brief: add a row in the CDATAFRAME
* param1: Pointer to the CDataframe to delete
* param2: index of the new row start at 0
*/
void add_row(CDATAFRAME *cdf, unsigned  int index, void* value_tab){
    if (cdf != NULL){

        lnode* node = cdf->head;
        unsigned int i= 0;
        while(node != NULL){
            COLUMN* col = node->data;

            if(col->physical_size <= col->logical_size){
                COL_TYPE *tmp = realloc(col->data, REALOC_SIZE);
                if(tmp == NULL) printf("Problème dans l'ajout de la ligne");
                col->physical_size = col->physical_size + REALOC_SIZE;
                *col->data = tmp;
                tmp = NULL;
            }


            insert_value(col, &value_tab);
            void * tampon;
            for (unsigned int k= col->logical_size; index == col->logical_size; k--){
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
* @brief: Column deletion
* param1: Pointer to the CDataframe
* param2: index of the delete row start at 0
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



/**
* @brief: convert a specific value of the column in strings
* param1: Pointer to the column
* param2: index for know the data to convert
* param3: Pointer to the stockage of result
* param4: size of strings
*/
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size){
    // la fonction snprintf permet de transformer un type choisi en chaîne de caractère stocké dans str avec une taille <= à la taille de str
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
* @brief: insert_value at the end of the column
* param1: Pointer to the column
* param1: Pointer on the value to be add
*/
int insert_value(COLUMN *col, void *value){
    if (col != NULL){

        // on regarde s'il existe déjà un tableau sinon on lui alloue de l'espace
        if (col->physical_size == 0){
            // l'espace donné doit avoir la taille stocker le type de colonne
            // donc on demande la taille que fait un type et on le multiplie avec le nombre de case qu'on veut
            col->data = (COL_TYPE**) malloc(sizeof(COL_TYPE)*REALOC_SIZE);
            if (col->data == NULL) return 0;
            col->physical_size = 256;

        }
        // quand le tableau est plein, on lui redonne plus d'espace
        if(col->physical_size <= col->logical_size){
            COL_TYPE *tmp = realloc(col->data, col->physical_size + REALOC_SIZE);
            if(tmp == NULL) return 0;
            // on indique qu'on a augmenté la taille pour dire au programme que c'est bon il n'a aucun problème
            col->physical_size = col->physical_size + REALOC_SIZE;
            // on fait pointer le nouveau tableau sur les paramètres de la structure afin qu'on puisse y acéder
            *col->data = tmp;
            tmp = NULL;
        }

        // on regarde le type de la structure (ENUM_type qu'on peut retrouver dans le column.h)
        switch(col->type){
            //ce sera la même utilité pour chaque case
            //on donne un espace en fonction du type de la colonne
            // puis on fait un cast de cette valeur/de l'espace dans le tableau pour changer les types

            case NULLVAL:
                col->data[col->logical_size] = (COL_TYPE *) malloc (sizeof(void*));
                *((void**)col->data[col->logical_size])= *((void**)value);
                break;

            case UINT:
                col->data[col->logical_size] = (COL_TYPE *) malloc (sizeof(unsigned int));
                *((unsigned int*)col->data[col->logical_size])= *((unsigned int*)value);
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
* @brief: convert a random value who isn't in the CDATAFRAME
* param1: Pointer to the value
* param2: type of the value
* param3: Pointer to the strings who the new value is storage
* param4: size of the new strings
*/

void convert_research(void *value, ENUM_TYPE type, char *str, int size){
    switch(type){
        case NULLVAL:
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