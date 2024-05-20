//
// Created by theop on 25/04/2024.
//

#ifndef CDATAFRAME_BOTTALICO_MATTEI__F_SETTING_H
#define CDATAFRAME_BOTTALICO_MATTEI__F_SETTING_H

typedef enum
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
}ENUM_TYPE;


typedef union {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
}COL_TYPE;


typedef struct{
    char *name;
    unsigned int physical_size;
    unsigned int logical_size;
    ENUM_TYPE type;
    COL_TYPE **data; // pointeur sur le tableau de pointeur
} COLUMN;

typedef struct lnode_ {
    void *data; // Pointeur sur la colonne
    struct lnode_ *prev;
    struct lnode_ *next;
} lnode;

typedef struct list_ {
    lnode *head;
    lnode *tail;
} list;

typedef list CDATAFRAME;

typedef enum {
    False, True
}BOOL;

typedef enum {
    lower, equal, higher
}STATE;


#endif //CDATAFRAME_BOTTALICO_MATTEI__F_SETTING_H
