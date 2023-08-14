#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
} Node;

typedef struct
{
    Node *begin;
    Node *end;
    int size;
} List;

List *List_create()
{
    List *list = (List *)calloc(1, sizeof(List));
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;

    return list;
}

Node *Node_create(int val)
{
    Node *node = (Node *)calloc(1, sizeof(Node));
    node->value = val;
    node->next = NULL;

    return node;
}

void List_add_first(List *list, int val)
{
    Node *new = Node_create(val);

    if (list->begin == NULL)
        list->end = new;

    new->next = list->begin;
    list->begin = new;
    list->size++;
}

int List_get_value(List *list, int index)
{
    if (list->size == 0)
        printf("ERROR. Empty list.\n");
    else
    {
        if (index < 0 || index >= list->size)
            printf("ERROR. Invalid index.\n");
        else
        {
            int i = 0;
            Node *aux = list->begin;
            while (index != i)
            {
                aux = aux->next;
                i++;
            }
            return aux->value;
        }
    }
    return -1;
}

void List_add_position(List *list, int val, int index)
{
    if (index < 0 || index > list->size)
        printf("ERROR. Invalid index.\n");
    else
    {
        Node *new = Node_create(val);
        if (index == 0)
        {
            new->next = list->begin;
            list->begin = new;
        }
        else
        {
            Node *aux = list->begin;
            for (int i = 0; i < index - 1; i++)
                aux = aux->next;

            new->next = aux->next;
            aux->next = new;
        }

        if (new->next == NULL)
            list->end = new;

        list->size++;
    }
}

Node *List_get_pointer(List *list, int val)
{
    Node *aux = list->begin;

    while (aux && aux->value != val)
        aux = aux->next;

    if (aux)
        return aux;
    else
        printf("ERROR. Value not found.\n");

    return NULL;
}

void List_add_last(List *list, int val)
{
    Node *new = Node_create(val);
    if (list->begin == NULL)
        list->begin = new;
    else
        list->end->next = new;

    list->end = new;
    list->size++;
}

void List_remove(List *list, int val)
{
    if (list->begin)
    {
        Node *pos = list->begin;
        Node *prev = NULL;

        while (pos && pos->value != val)
        {
            prev = pos;
            pos = pos->next;
        }

        if (pos) // valor encontrado
        {
            if (list->end == pos) // último elemento
                list->end = prev;

            if (list->begin == pos) // primeiro elemento
                list->begin = pos->next;
            else // elemento no meio da lista
                prev->next = pos->next;

            free(pos);
            list->size--;
        }
    }
}

void List_print(const List *list)
{
    Node *aux = list->begin;

    printf("Size: %d\n", list->size);

    while (aux)
    {
        printf("[%d] ", aux->value);
        aux = aux->next;
    }
    printf("\n");
}

void List_destroy(List **list_ref)
{
    List *list = *list_ref;

    Node *p = list->begin;
    Node *aux = NULL;

    while (list->begin)
    {
        aux = p;
        p = p->next;
        free(aux);
    }

    free(list);
    *list_ref = NULL;
}

void List_concatenate(List *list1, List *list2)
{
    list1->end->next = list2->begin;
    list1->end = list2->end;
    list1->size += list2->size;
}

void List_copy(List *list, List *copy)
{
    Node *aux = list->begin;

    while (aux)
    {
        List_add_last(copy, aux->value);
        aux = aux->next;
    }
}

void List_reverse(List *list)
{
    Node *current = list->begin;
    Node *nex = NULL;
    Node *prev = NULL;

    list->end = list->begin;

    while (current)
    {
        nex = current->next;
        current->next = prev;
        prev = current;
        current = nex;
    }
    
    list->begin = prev;
}

void List_add_sort(List *list, int val)
{
    Node *new = Node_create(val);

    if (list->begin == NULL) //Empty list
    {
        list->begin = new;
        list->end = new;
    }
    else 
    {
        if (list->begin->value >= val) //first position
        {
            new->next = list->begin;
            list->begin = new;
        }
        else //mid or end of list
        {
            Node *aux = list->begin;

            while (aux->next && aux->next->value < val)
                aux = aux->next;

            new->next = aux->next;
            aux->next = new;

            if (new->next == NULL)
                list->end = new;
        }
    }
    list->size++;
}

void List_sort(List *list)
{
    List *sorted = List_create();
    Node *aux = list->begin;

    while (aux)
    {
        List_add_sort(sorted, aux->value);
        aux = aux->next;
    }
    
    list->begin = sorted->begin;
    list->end = sorted->end;
}

int main()
{
    List *list = List_create();

    List_add_last(list,15);
    List_add_first(list,5);
    List_add_first(list,4);
    List_add_sort(list,3);
    List_add_sort(list,10);
    List_add_sort(list,20);
    List_sort(list);
    List_print(list);
    List_destroy(&list);

    return 0;
}