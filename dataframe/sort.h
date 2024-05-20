//
// Created by theop on 28/03/2024.
//

#ifndef CDATAFRAME_BOTTALICO_MATTEI__F_SORT_H
#define CDATAFRAME_BOTTALICO_MATTEI__F_SORT_H
#include "../setting.h"

CDATAFRAME sort_CDATAFRAME(CDATAFRAME *cdf, int axis, int ascending, ENUM_TYPE *by);

CDATAFRAME sort_CDATAFRAME_by_ascending(int axis, char *by);

CDATAFRAME sort_CDATAFRAME_by_descending(int axis, char *by);

void search_value_into_CDATAFRAME( CDATAFRAME *cdf, char *value);

#endif //CDATAFRAME_BOTTALICO_MATTEI__F_SORT_H
