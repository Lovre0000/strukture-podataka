#include<stdio.h>
#include<stdlib.h>

struct _element;
typedef struct _element* Position;
typedef struct _element {
    int num;
    Position next;
    Position prev;
}Element;

int menu(Position Head);
int enterElement(Position Head);
Position createElement(void);
int printList(Position First);
int deleteList(Position Head);
int deleteFromBehind(Position Head);
Position findSecondToLast(Position Head);
int deleteElement(Position Head);

int main(void) {

    Element Head = { .num = 0, .next = NULL, .prev = NULL };

    menu(&Head);

    return 0;
}

int menu(Position Head)
{
    char c;

    while (1)
    {
        printf("A - enter list, B - print list, C - delete list, D - delete from behind, E - delete element\n");
        scanf(" %c", &c);
        switch (c)
        {
        case 'A':
        case 'a':
            enterElement(Head);
            continue;

        case 'B':
        case 'b':
            printList(Head->next);
            continue;

        case 'C':
        case 'c':
            deleteList(Head);
            continue;

        case 'D':
        case 'd':
            deleteFromBehind(Head);
            continue;

        case 'E':
        case 'e':
            deleteElement(Head);
            continue;

        }
    }
    return EXIT_SUCCESS;
}

int enterElement(Position Head)
{
    Position newElement = createElement();

    newElement->next = Head->next;
    Head->next = newElement;
    newElement->prev = Head;
    if (newElement->next)
    {
        newElement->next->prev = newElement;
    }
    return EXIT_SUCCESS;
}

Position createElement(void)
{
    int num = 0;
    Position newElement = NULL;

    newElement = (Position)malloc(sizeof(Element));
    if (!newElement)
    {
        printf("Failed to allocate memory!\n");
        return NULL;
    }

    printf("Enter num: ");
    scanf("%d", &num);

    newElement->num = num;

    return newElement;
}

int printList(Position First)
{
    if (!First)
    {
        printf("Empty list!\n");
        return EXIT_FAILURE;
    }
    while (First)
    {
        printf("%d\n", First->num);
        First = First->next;
    }
    return EXIT_SUCCESS;
}

int deleteList(Position Head)
{
    if (!Head->next)
    {
        printf("Empty list!\n");
        return EXIT_SUCCESS;
    }
    while (Head->next)
    {
        Position toDelete = Head->next;
        Head->next = toDelete->next;
        free(toDelete);
    }
    return EXIT_SUCCESS;
}

int deleteFromBehind(Position Head)
{
    Position toDelete = NULL;
    Position Last = NULL;
    while (Head->next)
    {
        Last = findSecondToLast(Head);
        toDelete = Last->next;
        Last->next = toDelete->next;
        free(toDelete);
    }
    return EXIT_SUCCESS;
}

Position findSecondToLast(Position Head)
{
    Position Last = Head;
    Position SecondToLast = NULL;

    while (Last->next)
    {
        SecondToLast = Last;
        Last = Last->next;
    }
    return SecondToLast;
}


int deleteElement(Position Head)
{
    Position temp = NULL;
    int num1 = 0;

    printf("Enter num to find: ");
    scanf("%d", &num1);

    while (Head->next && Head->next->num != num1)
    {
        Head = Head->next;
    }
    if (Head->next->num == num1)
    {
        temp = Head->next;
        Head->next = temp->next;
        if (temp->next)
            temp->next->prev = Head;
        free(temp);
    }
    return EXIT_SUCCESS;
}