# Bienvenue sur Pandac, 
## La bibliothèqe pandas recodé en C

Ceci est un projet open source que vous pouvez retrouver sur github [lien du github](https://github.com/Mattei-Theophile/CDataframe-Bottalico-Mattei--F)

réalisé par Bottalico Thomas et Matteï Théophile, deux étudiants d'Efrei Paris de la promotion 2028

Il n'existe aucun affichage affichage, c'est pour cela qu'à la fin du README




**langage utilisé** : C version C23

**prérequis** : un compilateur ou bien Clion 

## Possibilité de la bibliothèque 
    
    la bibliothèque permet de créer des tableaux de données avec différents types de donnée par colonne
    Elle utilise les listes doublements chainées pour permettre d'avoir une flexibilité et une rapidité d'éxécution
    
    L'utilité de la bibliothèque CPandas est de trier, organiser et modifier un tableau soit remplis en dur ou bien via l'utilisateur



## Fonctionnement du programme
### CDATAFRAME.C/.H
    
    Ce fichier consiste à avoir toutes les fonctions principales d'analyse, de statistque et d'affichage du projet
    comme par exemple: la comparaison d'une valeur avec toute l'entierté du CDATAFRAME 
    ou bien la recherche d'une valeur dans le CDATAFRAME

### COLUMN.C/.H

    Column.c permet d'avoir toutes les fonctions permettant de gérer le CDATAFRAME comme la supression et l'ajout
    de colonne/ligne mais aussi changer le nom des colonnes, la conversion des valeurs en chaine de caractère
    et l'ajout dans le tableau

### LIST.C/.H

    Les listes doublement chainées viennent de ce fichier qui a aussi développé d'autre fonction permettant 
    d'intégrer les listes, les noeuds ou bien les supprimers plus facilement

### setting.H
    
    le fichier regroupe toutes les structures afin d'éviter 
    des problèmes de synchronisation entre tous les fichiers


## Exemple de code à exploiter

### 1er exemple

    ENUM_TYPE cdftype[] = {UINT, INT, FLOAT, DOUBLE, };

    CDATAFRAME *cdf = create_cdataframe(cdftype, 4);
    unsigned int col_size = 7;
    hard_filling_CDATAFRAME(cdf, col_size);
    print_CDATAFRAME(cdf);

    rename_column(cdf, 1, "test");
    print_CDATAFRAME(cdf);
    printf("\n");
    print_rows_CDATAFRAME(cdf, 1,2);
    printf("\n");
    print_cols_CDATAFRAME(cdf, 1,2);

### 2ème exemple

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


### Copyright © 2024 Matteï Théophile
