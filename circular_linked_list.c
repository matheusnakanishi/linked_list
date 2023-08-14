#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
    struct node *prev;
} Cnode;

typedef struct
{
    Cnode *begin;
    Cnode *end;
    int size;
} Clist;

Clist *List_create()
{
    Clist *list = (Clist*) calloc(1,sizeof(Clist));
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;

    return list;
}

Cnode *Node_create(int val)
{
    Cnode *new = (Cnode*) calloc(1,sizeof(Cnode));
    new->value = val;
    new->next = new;
    new->prev = new;

    return new;
}

void Node_destroy(Cnode **node)
{
    Cnode *aux = *node;
    free(aux);
    *node = NULL;
}

void List_destroy(Clist **list)
{
    Clist *l = *list;
    Cnode *p = l->begin;
    Cnode *aux = NULL;

    while (p != l->end)
    {
       aux = p;
       p = p->next;
       Node_destroy(&aux);
    }
    Node_destroy(&p);
    free(l);
    *list = NULL;
}

void add_first(Clist *list, int val)
{
    Cnode *new = Node_create(val);

    if (list->begin == NULL) //Empty
        list->end = new;
    else
    {
        new->next = list->begin;
        list->begin->prev = new;
        new->prev = list->end;
        list->end->next = new;
    }
    list->begin = new;
    list->size++;
}

void add_last(Clist *list, int val)
{
    Cnode *new = Node_create(val);

    if (list->begin == NULL) //Empty
        list->begin = new;
    else
    {
        new->next = list->begin;
        new->prev = list->end;
        list->end->next = new;
        list->begin->prev = new;
    }
    list->end = new;
    list->size++;
}

void List_print(const Clist *list)
{
    Cnode *aux = list->begin;

    if (list->begin != NULL)
    {
        do{
            printf("[%d]->",aux->value);
            aux = aux->next;
        } while (aux != list->begin);
    }
    printf("NULL\n");
    printf("Size: %d\n\n",list->size);
}

void List_print2(const Clist *list)
{
    Cnode *aux = list->begin;

    if (list->begin != NULL)
    {
        for (int i = 0; i < list->size; i++)
        {
            printf("[%d]->",aux->value);
            aux = aux->next;
        }
        
    }
    printf("NULL\n");
    printf("Size: %d\n\n",list->size);
}

void List_inverted_print(const Clist *list)
{
    Cnode *aux = list->end;

    if (list->begin != NULL)
    {
        do{
            printf("[%d]->",aux->value);
            aux = aux->prev;
        } while (aux != list->end);
    }
    printf("NULL\n");
    printf("Size: %d\n\n",list->size);


}

void List_remove(Clist *list, int val)
{
    if(list->begin != NULL) //not empty
    {
        Cnode *aux = list->begin;

        if (list->begin->value == val) //first element
        {
            if (list->size == 1) //one element
                list->begin = list->end = NULL;
            else //more than one element
            {
                list->begin = aux->next;
                list->begin->prev = list->end;
                list->end->next = list->begin;
            }
            Node_destroy(&aux);
            list->size--;
        }
        else //mid or end
        {
            aux = aux->next;

            while (aux != list->begin){
                if (aux->value != val)
                {
                    if (list->end == aux) //end
                        list->end = aux->prev;
                    
                    aux->prev->next = aux->next;
                    aux->next->prev = aux->prev;
                    Node_destroy(&aux);
                    list->size--;
                    break;
                }
                else
                    aux = aux->next;
            } 
        }
    }
}

int main()
{
    Clist *list = List_create();

    add_first(list,1);
    add_first(list,2);
    add_first(list,3);
    add_last(list,5);
    List_print2(list);
    List_remove(list,1);
    List_print2(list);
    List_print2(list);
    List_destroy(&list);

    return 0;
}