//
// Created by theop on 28/03/2024.
//

#ifndef CDATAFRAME_BOTTALICO_MATTEI__F_CDATAFRAME_H
#define CDATAFRAME_BOTTALICO_MATTEI__F_CDATAFRAME_H
#include <stdio.h>
#include <string.h>

#include "../setting.h"
#include "column.h"


/**
* @brief Création d'un dataframe
* @param1: Type of column
* @param2: size of CDATAFRAME
 */
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);

// =================== Printing ===================

/**
* @breif: print the CDATAFRAME like table
* @param1: Pointer to the CDataframe
*/


void print_CDATAFRAME(CDATAFRAME *cdf);


/**
* @brief: print the name of column of CDATAFRAME
* param1: Pointer to the CDataframe
*/

void print_column_name(CDATAFRAME *cdf);

/**
* @brief: print of selection columns
* param1: Pointer to the CDataframe
* param2: start of the print columns
* param3: the end of the print columns
 * we follow this system [start , finish[
*/

void print_cols_CDATAFRAME(CDATAFRAME *cdf, int start, int end);

/**
* @brief: print of selection rows
* param1: Pointer to the CDataframe
* param2: start of the print columns
* param3: the end of the print columns
 * we follow this system [start , finish[
*/
void print_rows_CDATAFRAME(CDATAFRAME *cdf, int start, int end);

/**
* @breif: hard filling of the CDATAFRAME
* @param1: Pointer to the CDataframe
* @param2: size of each column CDATAFRAME
*/
void hard_filling_CDATAFRAME(CDATAFRAME*cdf, unsigned int col_size) ;



// ========================

/**
* @breif: Get the size of all columns from the CDATAFRAME
* @param1: Pointer to the CDataframe
*/
unsigned int get_cdataframe_cols_size(CDATAFRAME *cdf);

/**
* @breif: Get the size of all rows from the CDATAFRAME
* @param1: Pointer to the CDataframe
*/
unsigned int get_cdataframe_rows_size( CDATAFRAME *cdf);


/**
* @brief: rename a column
* param1: Pointer to the CDataframe
* param2: index of the column to rename
* param3: Pointer to the new name
*/
void rename_column(CDATAFRAME *cdf, int index, char *new_name);



// ======================== Analyse et statistiques ========================

/**
* @breif: Get the size of all column from the CDATAFRAME
* @param1: Pointer to the CDataframe
*/
void get_value_by_index(CDATAFRAME *cdf, unsigned int row, unsigned int col);

void replace_value_by_index(CDATAFRAME *cdf, unsigned int row, unsigned int col, void* value);

int compare(CDATAFRAME *cdf, void *value, ENUM_TYPE value_type, STATE state);


BOOL search_value(CDATAFRAME *cdf, void *value, ENUM_TYPE value_type);




#endif //CDATAFRAME_BOTTALICO_MATTEI__F_CDATAFRAME_H
