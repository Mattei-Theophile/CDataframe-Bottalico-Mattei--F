//
// Created by theop on 28/03/2024.
//

#ifndef CDATAFRAME_BOTTALICO_MATTEI__F_COLUMN_H
#define CDATAFRAME_BOTTALICO_MATTEI__F_COLUMN_H

#include "../setting.h"

#include "column.h"
#include "list.h"
#include "cdataframe.h"
#define REALOC_SIZE 256


/**
* Create a column
* @param1 : Column title
* @param2: type of the column
* @return : Pointer to created column
*/
COLUMN *create_column(char* title, ENUM_TYPE type);

void delete_cdataframe(CDATAFRAME**cdf);

/**
* @brief : Add a new value to a column
* @param1 : Pointer to a column
* @param2 : The value to be added
* @return : 1 if the value is added 0 otherwise
*/
int insert_value(COLUMN* col, void* value);

/**
* @brief: Print a column content
* @param: Pointer to a column
*/
void print_col(COLUMN* col);

/**
* @brief: Convert a value into a string
* @param1: Pointer to the column
* @param2: Position of the value in the data array
* @param3: The string in which the value will be written
* @param4: Maximum size of the string
*/
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);


void convert_research(void *value, ENUM_TYPE type, char *str, int size);
/**
* add a column
* @param1 : Column title
* @param2: type of the column

*/
void add_column(CDATAFRAME *cdf, char* title, ENUM_TYPE type);

/**
* @breif: Delete column by name
* @param1: Pointer to the CDataframe
* @param2: Column name
*/
void delete_column(CDATAFRAME *cdf, int index);

void add_row(CDATAFRAME *cdf, unsigned  int index, void* value_tab);
void delete_row(CDATAFRAME *cdf, unsigned  int index);



#endif //CDATAFRAME_BOTTALICO_MATTEI__F_COLUMN_H

