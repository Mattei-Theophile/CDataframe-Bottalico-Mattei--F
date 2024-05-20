#include "dataframe/cdataframe.h"

/*Information du fichier
 *
 *Projet de programmation C - CDataframe - Matteï Théophile et Bottalico Thomas
 *
 * C'est le fichier principal qui permet de tester toute la librairie,
 * il a seulement besoin d'inclure le fichier cdataframe.h qui fait le lien avec tous les autres fichiers de la bibliothèque
 */


int main() {
    ENUM_TYPE cdftype[] = {UINT, INT, FLOAT, DOUBLE, };

    CDATAFRAME *cdf = create_cdataframe(cdftype, 4);
    unsigned int col_size = 7;
    hard_filling_CDATAFRAME(cdf, col_size);
    print_CDATAFRAME(cdf);

    printf("\ntaille des colonnes : %d \n taille des lignes : %d", get_cdataframe_cols_size(cdf),
           get_cdataframe_rows_size(cdf));
    int a = 10;
    printf("\nvaleur inferieure a %d : %d", a, compare(cdf, &a, INT, higher));
    printf("\nvaleur egale a %d : %d", a, compare(cdf, &a, INT, equal));
    printf("\nvaleur superieure a %d : %d", a, compare(cdf, &a, INT, lower));

    float b = 0;
    printf("\nvaleur inferieure a %f : %d", b, compare(cdf, &b, FLOAT, higher));
    printf("\nvaleur egale a %f : %d", b, compare(cdf, &b, FLOAT, equal));
    printf("\nvaleur inferieure a %f : %d", b, compare(cdf, &b, FLOAT, lower));
    return 0;
}