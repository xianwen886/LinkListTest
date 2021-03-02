#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  


typedef struct __node {
    int value;
    struct __node *next;
} node_t;

static inline void list_add_node_t(node_t **list, node_t *node_t)
{
    node_t->next = *list;
    *list = node_t;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

static bool list_is_ordered(node_t *list)
{
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}


static void list_display(node_t *list)
{
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

static inline void list_concat(node_t **left, node_t *right)
{
    while (*left)
        left = &((*left)->next);
    *left = right;
}

void quicksort(node_t **list)
{
    if (!*list) {
        return;    	
	}


    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);
    }
	////////////////////////////////////////////////////////////////////////
    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot);
	list_concat(&result, right);

    *list = result;
}


static node_t* list_make_node_t(node_t *list, int value)
{
    node_t* pNode_t = (node_t *)malloc(sizeof(node_t));
    pNode_t->value = value;
    pNode_t->next = NULL;
    if (list == NULL) {
        list = pNode_t;
    } else {
        node_t *tmp = list;
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = pNode_t;
    }

    return list;
}

static void list_free(node_t **list)
{
    node_t *ptr = *list;
    node_t *tmp = NULL;
    int i = 0;
    if (ptr == NULL) {
    	return;
	}
    while(ptr->next != NULL) {

        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
        i++;
    }

    if (ptr != NULL) {
        i++;
        free(ptr);
    }
}

int main(int argc, char **argv)
{
    size_t count = 20;
	time_t t;
    node_t *list = NULL;
    srand((unsigned) time(&t));
    while (count--)
        list = list_make_node_t(list, rand() % 1024);

    list_display(list);
    quicksort(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}
