#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *next_node;
    struct node *previous_node;
    int data;

} node;

void add_list(node **head, int data)
{

    node *temp_node = malloc(sizeof(node));

    temp_node->data = data;
    temp_node->next_node = NULL;
    temp_node->previous_node = NULL;

    if (*head == NULL)
    {

        (*head) = temp_node;
        return;
    }

    node *current = *head;

    

    while (current->next_node != NULL)
    {
        current = current->next_node;
    }

    current->next_node = temp_node;
    temp_node->previous_node = current;
    return;
}

void print_list(node *head)
{

    while (head != NULL)
    {
        if (head->previous_node != NULL)
        {
            printf("Current %d, Previouse %d \n", head->data, head->previous_node->data);
        }
        else
        {
            printf("Current %d \n", head->data);
        }

        head = head->next_node;
    }
}

int main()
{
    node *root = NULL;

    add_list(&root, 10);
    add_list(&root, 20);
    add_list(&root, 30);

    print_list(root);

    return 0;
}