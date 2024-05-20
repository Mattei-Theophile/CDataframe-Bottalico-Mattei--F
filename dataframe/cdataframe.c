//
// Created by theop on 28/03/2024.
//
#include <stdlib.h>
#include "cdataframe.h"
#include "list.h"


// =================== Printing ===================

/**
* @breif: print the CDATAFRAME like table
* @param1: Pointer to the CDataframe
*/

/**
* @brief: Create Cdataframe type with columns size
* param1: pointer to the tab of  ENUM_type for each columns
* param2: number of columns
*/
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size){
    // on crée une liste 
    CDATAFRAME *cdf = lst_create_list();
    //on parcourt size pour créer un nombre de tableau == size + insérer à la dernière ligne
    for(int i = 0; i < size; i++){
        COLUMN *data = create_column("col", cdftype[i]);
        lnode *tmp = lst_create_lnode(data);
        lst_insert_tail(cdf,tmp);
    }
    return cdf;
}


void print_CDATAFRAME(CDATAFRAME *cdf){
    if (cdf != NULL){
        char str[100];
        print_column_name(cdf);
        lnode* node = cdf->head;
        unsigned int j = 0;
        COLUMN* col = node->data;
        while(j < col->logical_size){

            printf("\n[%d]", j);
            while(node != NULL){

                convert_value(col, j, str, 100);
                printf(" %s", str);

                node = node->next;
                if (node != NULL) col = node->data;
            }
            node = cdf->head;
            col = node->data;
            j++;
        }
    }
}


/**
* @brief: print the name of column of CDATAFRAME
* param1: Pointer to the CDataframe
*/

void print_column_name(CDATAFRAME *cdf){
    printf("\n");
    if (cdf != NULL){
        lnode *tmp = cdf->head;
        COLUMN  *col = tmp->data;

        while (tmp != cdf->tail){
            printf(" %s",col->name);
            tmp = tmp->next;
            col = tmp->data;
        }
        if (tmp == cdf->tail){
            printf(" %s",col->name);
        }
    }
}



/**
* @brief: print of selection columns
* param1: Pointer to the CDataframe
* param2: start of the print columns
* param3: the end of the print columns
 * we follow this system [start , finish[
*/

void print_cols_CDATAFRAME(CDATAFRAME *cdf, int start, int finish){
    if (cdf != NULL){
        char str[100];
        print_column_name(cdf);
        lnode* node = cdf->head;
        unsigned int j = 0;
        COLUMN* col = node->data;
        while(j < col->logical_size){
            int i = start;
            printf("\n[%d]", j);
            while(i < finish){

                convert_value(col, j, str, 100);
                printf(" %s", str);
                if (node != NULL) {
                    node = node->next;
                    if (node != NULL) col = node->data;
                }
                i++;
            }
            node = cdf->head;
            col = node->data;
            j++;
        }
    }
}


/**
* @brief: print of selection rows
* param1: Pointer to the CDataframe
* param2: start of the print columns
* param3: the end of the print columns
 * we follow this system [start , finish[
*/
void print_rows_CDATAFRAME(CDATAFRAME *cdf, int start, int finish){
    if (cdf != NULL){
        char str[100];
        print_column_name(cdf);
        lnode* node = cdf->head;
        unsigned int j = start;
        COLUMN* col = node->data;
        while(j < finish){

            printf("\n[%d]", j);
            while(node != NULL){

                convert_value(col, j, str, 100);
                printf(" %s", str);

                node = node->next;
                if (node != NULL) col = node->data;
            }
            node = cdf->head;
            col = node->data;
            j++;
        }
    }
}



/**
* @breif: hard filling of the CDATAFRAME
* @param1: Pointer to the CDataframe
* @param2: size of each column CDATAFRAME
*/
void hard_filling_CDATAFRAME(CDATAFRAME*cdf, unsigned int col_size) {
    int zero = 0;
    unsigned int cpt;
    lnode *ptr = cdf->head;
    while (ptr != NULL) {
        COLUMN *col = ptr->data;
        cpt = 0;
        while (cpt < col_size) {

            insert_value(col, &zero);
            cpt++;
        }
        ptr = ptr->next;
    }
}




// ========================

/**
* @breif: Get the size of all columns from the CDATAFRAME
* @param1: Pointer to the CDataframe
*/
unsigned int get_cdataframe_cols_size(CDATAFRAME *cdf){
    COLUMN *col = cdf->head->data;
    return col->logical_size;
}

/**
* @breif: Get the size of all rows from the CDATAFRAME
* @param1: Pointer to the CDataframe
*/
unsigned int get_cdataframe_rows_size( CDATAFRAME *cdf){
    int rows_size = 0;
    lnode *tmp = NULL;
    if (cdf != NULL){
        tmp = cdf->head;
        while (tmp != NULL){
            tmp = tmp->next;
            rows_size++;
        }
    }
    return rows_size;
}



/**
* @brief: rename a column
* param1: Pointer to the CDataframe
* param2: index of the column to rename
* param3: Pointer to the new name
*/
void rename_column(CDATAFRAME *cdf, int index, char *new_name){
    printf("\n");
    if (cdf != NULL){
        lnode *tmp = cdf->head;
        COLUMN  *col = tmp->data;
        for (int i=0; i < index; i++){
            tmp = tmp->next;
            col = tmp->data;
        }
        col->name = new_name;
    }
}



// ======================== Analyse et statistiques ========================

/**
* @breif: Get the size of all column from the CDATAFRAME
* @param1: Pointer to the CDataframe
*/
void get_value_by_index(CDATAFRAME *cdf, unsigned int row, unsigned int col){
    if (cdf != NULL) {
        char str[100];
        lnode *node = cdf->head;
        for (int i=0; i < col; i++){
            node = node->next;
        }
        COLUMN *column = node->data;
        convert_value(column, row, str, 100);
        printf(" %s", str);
    }

}


void replace_value_by_index(CDATAFRAME *cdf, unsigned int row, unsigned int col, void* value){
    if (cdf != NULL) {
        lnode *node = cdf->head;
        for (int i=0; i < col; i++){
            node = node->next;
        }
        COLUMN *column = node->data;
        column->data[row] = value;
    }
}

int compare(CDATAFRAME *cdf, void *value, ENUM_TYPE value_type, int state){
    int cpt = 0;
    BOOL error = False;
    if (cdf != NULL){
        char str[100];
        char str2[100];
        lnode* node = cdf->head;
        unsigned int j = 0;
        COLUMN* col = node->data;
        convert_research(value, value_type, str, 100);
        while(j < col->logical_size){

            while(node != NULL){
                convert_value(col, j, str2, 100);
                int result = strcmp(str, str2);
                switch (state) {
                    case 0:
                        if (result < 0) cpt ++;
                        break;
                    case 1:
                        if (result == 0) cpt ++;
                        break;
                    case 2:
                        if (result > 0) cpt ++;
                        break;
                    default:
                        error = True;
                }

                node = node->next;
                if (node != NULL) col = node->data;
            }
            node = cdf->head;
            col = node->data;
            j++;
        }
    }
    if (error == True){
        printf("Erreur, vous avez choisi un état non renseigné ");
        return -1;
    }
    return cpt;
}

BOOL search_value(CDATAFRAME *cdf, void *value, ENUM_TYPE value_type) {
    BOOL find = False;
    if (cdf != NULL){
        char str[100];
        char str2[100];

        lnode* node = cdf->head;
        unsigned int j = 0;
        COLUMN* col = node->data;
        convert_research(value, value_type, str, 100);
        while(j < col->logical_size){

            while(node != NULL && find == False){

                convert_value(col, j, str2, 100);
                int result = strcmp(str, str2);
                if (result ==0) find = True;
                node = node->next;
                if (node != NULL) col = node->data;
            }
            node = cdf->head;
            col = node->data;
            j++;
        }
    }

    return find;
}