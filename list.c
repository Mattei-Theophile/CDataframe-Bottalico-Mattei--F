#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*Information du fichier
 *Projet de programmation C - CDataframe - Matteï Théophile et Bottalico Thomas
 *
 * le fichier consiste à intégrer le système de liste linéaire doublement chaînée
 * avec des fonctions supplémentaires que seulement la création et la supression des listes
 */

/**
* @brief: création d'un noeud
* param1: pointeur sur la column à pointer par le noeud
* @return: un noeud
*/
lnode *lst_create_lnode(COLUMN *dat) {
    lnode *ptmp = (lnode *) malloc(sizeof(lnode));
    ptmp->data = dat;
    ptmp->next = NULL;
    ptmp->prev = NULL;
    return ptmp;
}
/**
* @brief: création d'une liste
 *@return: une liste
*/
list *lst_create_list() {
    list *lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
    lst->tail = NULL;
    return lst;
}
/**
* @brief: suppresion d'une liste avec tous les noeuds à l'intérieur
* param1: Pointeur sur la liste
*/
void lst_delete_list(list * lst) {
    lst_erase(lst);
    free(lst);
}
/**
* @brief: insérer un noeud à la tête de la liste
* param1: Pointeur sur la liste
* param2: Pointeur sur le  nouveau noeud à insérer
*/
void lst_insert_head(list * lst, lnode * pnew) {
    if (lst->head == NULL) {
        lst->head = pnew;
        lst->tail = pnew;
        return;
    }
    pnew->next = lst->head;
    pnew->prev = NULL;
    lst->head = pnew;
    pnew->next->prev = pnew;
}

/**
* @brief: insérer un noeud à la queue de la liste
* param1: Pointeur sur la liste
* param2: Pointeur sur le  nouveau noeud à insérer
*/
void lst_insert_tail(list * lst, lnode * pnew) {
    if (lst->head == NULL) {
        lst->head = pnew;
        lst->tail = pnew;
        return;
    }
    pnew->next = NULL;
    pnew->prev = lst->tail;
    lst->tail = pnew;
    pnew->prev->next = pnew;
}

/**
* @brief: insérer un noeud après un autre noeud
* param1: Pointeur sur la liste
* param2: Pointeur sur le nouveau noeud à insérer
* param2: Pointeur sur le noeud de référence
*/
void lst_insert_after(list * lst, lnode * pnew, lnode * ptr) {
    if (lst->head == NULL) {
        lst->head = pnew;
        lst->tail = pnew;
    } else if (ptr == NULL) {
        return;
    } else if (lst->tail == ptr) {
        lst_insert_tail(lst, pnew);
    } else {
        pnew->next = ptr->next;
        pnew->prev = ptr;
        pnew->next->prev = pnew;
        pnew->prev->next = pnew;
    }
}


/**
* @brief: supprime le pointeur à la tête de la liste
* param1: Pointeur sur la liste
*/
void lst_delete_head(list * lst) {
    if (lst->head->next == NULL) {
        free(lst->head);
        lst->head = NULL;
        lst->tail = NULL;
        return;
    }
    lst->head = lst->head->next;
    free(lst->head->prev);
    lst->head->prev = NULL;
}

/**
* @brief: supprime le pointeur à la queue de la liste
* param1: Pointeur sur la liste
*/
void lst_delete_tail(list * lst) {
    if (lst->tail->prev == NULL) {
        free(lst->tail);
        lst->head = NULL;
        lst->tail = NULL;
        return;
    }
    lst->tail = lst->tail->prev;
    free(lst->tail->next);
    lst->tail->next = NULL;
}

/**
* @brief: supprime un à la tête de la liste
* param1: Pointeur sur la liste
*/
void lst_delete_lnode(list * lst, lnode * ptr) {
    if (ptr == NULL)
        return;
    if (ptr == lst->head) {
        lst_delete_head(lst);
        return;
    }
    if (ptr == lst->tail) {
        lst_delete_tail(lst);
        return;
    }
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;
    free(ptr);
}

/**
* @brief: efface tous les noeuds qui sont dans la liste
* param1: Pointeur sur la liste
*/
void lst_erase(list * lst) {
    if (lst->head == NULL)
        return;
    while (lst->head != lst->tail) {
        lst->head = lst->head->next;
        free(lst->head->prev);
    }
    free(lst->head);
    lst->head = NULL;
    lst->tail = NULL;
}

/**
* @brief: retourne le premier noeud de la liste
* param1: Pointeur sur la liste
*/
lnode *get_first_node(list * lst) {
    if (lst->head == NULL)
        return NULL;
    return lst->head;
}

/**
* @brief: retourne le dernier noeud de la liste
* param1: Pointeur sur la liste
*/
lnode *get_last_node(list * lst) {
    if (lst->tail == NULL)
        return NULL;
    return lst->tail;
}

/**
* @brief: retourne le prochain noeud de la liste
* param1: Pointeur sur la liste
* param2: Pointeur sur le noeud
*/
lnode *get_next_node(list * lst, lnode * lnode) {
    if (lnode == NULL)
        return NULL;
    return lnode->next;
}

/**
* @brief: retourne le précédent noeud de la liste
* param1: Pointeur sur la liste
* param1: Pointeur sur le noeud
*/
void *get_previous_elem(list * lst, lnode * lnode) {
    if (lnode == NULL)
        return NULL;
    return lnode->prev;
}

