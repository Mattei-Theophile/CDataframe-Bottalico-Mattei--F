//
// Created by theop on 28/03/2024.
//
#include <stdlib.h>

#include "cdataframe.h"
#include "list.h"

/*Information du fichier
 *
 *Projet de programmation C - CDataframe - Matteï Théophile et Bottalico Thomas
 * le fichier consiste à avoir toutes les fonctions principales d'analyse, de statistque et d'affichage du projet
 */


// ~~~~~~ CDATAFRAME ~~~~~~

/**
* @brief: création d'un CDATAFRAME
* param1: Pointeur sur un type/tableau de type pour chaque colonne
* param2: nombre de colonnes
*/
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size){
    CDATAFRAME *cdf = lst_create_list();
    for(int i = 0; i < size; i++){
        COLUMN *data = create_column("col", cdftype[i]);
        lnode *tmp = lst_create_lnode(data);
        lst_insert_tail(cdf,tmp);
    }
    return cdf;
}

/**
* @brief: suppression du CDATAFRAME
* param1: Pointeur sur le CDATAFRAME
*/
void delete_cdataframe(CDATAFRAME **cdf){
    lst_erase(*cdf);
    free(cdf);
}

/**
* @breif: remplissage en dur du CDATAFRAME
* @param1: Pointeur sur le CDATAFRAME
* @param2: taille de chaque colonne
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


// ~~~~~~ affichage ~~~~~~

/**
* @breif: afficher le CDATAFRAME dans le format d'un tableau
* @param1: Pointeur sur un CDATAFRAME
*/
void print_CDATAFRAME(CDATAFRAME *cdf){
    if (cdf != NULL){
        char str[100];

        lnode* node = cdf->head;
        unsigned int j = 0;
        COLUMN* col = node->data;
        print_column_name(cdf);
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
* @brief: affiche le nom des colonnes
* param1: Pointeur sur le CDATAFRAME
*/

void print_column_name(CDATAFRAME *cdf){

    if (cdf != NULL){
        printf("\n");
        lnode *node = cdf->head;
        COLUMN  *col = node->data;

        while (node != cdf->tail){
            printf(" %s",col->name);
            node = node->next;
            col = node->data;
        }
        if (node == cdf->tail){
            printf(" %s",col->name);
        }
    }
}



/**
* @brief: affiche des colonnes du CDATAFRAME avec une sélection
* param1: Pointeur sur le CDATAFRAME
* param2: début de l'affichage du CDATAFRAME
* param3: Fin de l'affichage du CDATAFRAME
 * pour l'affichage, on prends les bornes [start , finish[
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
* @brief: affiche des lignes du CDATAFRAME avec une sélection
* param1: Pointeur sur le CDATAFRAME
* param2: début de l'affichage du CDATAFRAME
* param3: Fin de l'affichage du CDATAFRAME
 * pour l'affichage, on prends les bornes [start , finish[
*/

void print_rows_CDATAFRAME(CDATAFRAME *cdf, int start, int end){
    if (cdf != NULL){
        char str[100];
        print_column_name(cdf);
        lnode* node = cdf->head;
        unsigned int j = start;
        COLUMN* col = node->data;
        while(j < end){

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


// ~~~~~~ information ~~~~~~

/**
* @breif: avoir la taille des colonnes du CDATAFRAME
* @param1: Pointeur sur le CDATAFRAME
*/
unsigned int get_cdataframe_cols_size(CDATAFRAME *cdf){
    COLUMN *col = cdf->head->data;
    return col->logical_size;
}

/**
* @breif: avoir la taille des lignes du CDATAFRAME
* @param1: Pointeur sur le CDATAFRAME
*/
unsigned int get_cdataframe_rows_size( CDATAFRAME *cdf){
    int rows_size = 0;
    lnode *node = NULL;
    if (cdf != NULL){
        node = cdf->head;
        while (node != NULL){
            node = node->next;
            rows_size++;
        }
    }
    return rows_size;
}


// ~~~~~~ analyse ~~~~~~

/**
* @breif: avoir une valeur du CDATAFRAME grâce à la position dans les lignes et les colonnes
* @param1: Pointeur sur le CDATAFRAME
* @param2: position de la ligne
* @param3: position de la colonne
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


/**
* @breif: remplacer une valeur dans un CDATAFRAME grâce à la position dans les lignes et les colonnes
* @param1: Pointeur sur le CDATAFRAME
* @param2: position de la ligne
* @param3: position de la colonne
* @param4: pointeur sur la nouvelle valeur
*/
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


/**
* @breif: comparer une valeur avec toutes les valeurs du CDATAFRAME
* @param1: Pointeur sur le CDATAFRAME
* @param2: Pointeur sur la valeur à comparer
* @param3: type de valeur à comparer
* @param3: état de la comparaison : plus petit, égal, plus grand (définition disponible avec la structure STATE)
*/
int compare(CDATAFRAME *cdf, void *value, ENUM_TYPE value_type, STATE state){
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
                    case lower:
                        if (result < 0) cpt ++;
                        break;
                    case equal:
                        if (result == 0) cpt ++;
                        break;
                    case higher:
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

/**
* @brief: chercher la présence d'une valeur dans le CDATAFRAME
* param1: Pointeur sur le CDATAFRAME
* param2: Pointeur sur la valeur à trouver
* param2: le type de la valeur à trouver
*/
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