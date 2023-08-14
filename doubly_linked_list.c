#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
    struct node *prev;
} Dnode;

typedef struct
{
    Dnode *begin;
    Dnode *end;
    int size;
} Dlist;

Dnode *Node_create(int val)
{
    Dnode *new = (Dnode*)calloc(1,sizeof(Dnode));
    new->value = val;
    new->next = NULL;
    new->prev = NULL;

    return new;
}

Dlist *List_create()
{
    Dlist *list = (Dlist*)calloc(1,sizeof(Dlist));
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;

    return list;
}

void List_destroy(Dlist **l_ref)
{
    Dlist *L = *l_ref;
    Dnode *p = L->begin;
    Dnode *aux = p;

    while(p)
    {
        p = p->next;
        free(aux);
    }

    free(L);
    *l_ref = NULL;
}

void List_add_first(Dlist *list, int val)
{
    Dnode *new = Node_create(val);

    if (list->begin == NULL)
        list->end = new;
    else
        list->begin->prev = new;

    new->next = list->begin;
    list->begin = new;
    list->size++;
}

void List_add_end(Dlist *list, int val)
{
    Dnode *new = Node_create(val);

    if (list->begin ==  NULL)
        list->begin = new;
    else
        list->end->next = new;
    
    new->prev = list->end;
    list->end = new;
    list->size++;
}

void List_print(const Dlist *list)
{
    Dnode *aux = list->begin;

    while (aux)
    {
        printf("[%d]->",aux->value);
        aux = aux->next;
    }
    printf("NULL\n");
    printf("Size: %d\n\n",list->size);
}

void List_reverse_print(Dlist *list)
{
    Dnode *aux = list->end;

    while (aux)
    {
        printf("[%d]->",aux->value);
        aux = aux->prev;
    }
    printf("NULL\n");
    printf("Size: %d\n\n",list->size);
}

void List_remove(Dlist *list, int val)
{
    if (list->begin) //The list is not empty
    {
        Dnode *aux = list->begin;

        if (list->begin->value == val) //first element
        {
            list->begin = aux->next;

            if (list->end == aux) //the list have one element
                list->end = NULL;
            else
                list->begin->prev = NULL;
            
            free(aux);
            list->size--;
        }
        else //End or mid of the list
        {
            aux = aux->next; //start from the second element

            while (aux && aux->value != val)
                aux = aux->next;

            if (aux)
            {
                aux->prev->next = aux->next;

                if (aux->next == NULL) //last one
                    list->end = aux->prev;
                else
                    aux->next->prev = aux->prev;
                
                free(aux);
                list->size--;
            }
        }
    }
}

int main()
{
    Dlist *list = List_create();

    List_add_end(list,4);
    List_add_end(list,7);
    List_add_first(list,2);
    List_add_first(list,10);
    List_print(list);
    List_reverse_print(list);
    List_remove(list,10);
    List_print(list);
    List_remove(list,7);
    List_print(list);
    List_add_first(list,1);
    List_remove(list,2);
    List_print(list);
    List_remove(list,4);
    List_remove(list,1);
    List_print(list);
    List_destroy(&list);

    return 0;
}