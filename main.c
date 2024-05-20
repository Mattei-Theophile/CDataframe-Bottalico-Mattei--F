#include "dataframe/cdataframe.h"

int main() {
    ENUM_TYPE cdftype[] = {INT, CHAR, INT};

    CDATAFRAME *cdf = create_cdataframe(cdftype, 3);


    unsigned int col_size = 7;
    hard_filling_CDATAFRAME(cdf, col_size);
    print_CDATAFRAME(cdf);
    int a = 0;
    char b = 'c';
    int c= 13;
    void *tab[] = {&a, &b, &c };
    unsigned int result = compare(cdf, &a, INT, 1);
    print_CDATAFRAME(cdf);

    printf("\n%d", result);
    return 0;
}

