#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *previous;
    int data;
} node;

void push(int data, node **top)
{
    node *temp_node = malloc(sizeof(node));

    temp_node->data = data;

    temp_node->previous = *top;

    *top = temp_node;
}

int pop(node **top)
{

    if (*top == NULL)
    {
        return 0;
    }

    int data = (*top)->data;

    node *free_node = (*top);

    *top = (*top)->previous;

    free(free_node);

    return data;
}

void print_list(node *top)
{

    while (top != NULL)
    {
        printf("%d \n", top->data);
        top = top->previous;
    }
}

int main()
{

    node *list = NULL;

    push(5, &list);
    push(8, &list);
    push(10, &list);

    print_list(list);

    printf("POP %d \nNew List \n", pop(&list));

    print_list(list);

    return 0;
}