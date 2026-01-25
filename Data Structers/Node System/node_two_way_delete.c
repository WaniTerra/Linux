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

void delete_node(node **head, int delete_value)
{
    node *current = *head;

    while (current != NULL && current->data != delete_value)
    {
        current = current->next_node;
    }

    if (current == NULL)
        return;

    if (current == *head)
    {
        *head = current->next_node;

        if (*head != NULL)
        {
            (*head)->previous_node = NULL;
        }

        free(current);
        return;
    }

    if (current->next_node == NULL)
    {
        current->previous_node->next_node = NULL;
        free(current);

        return;
    }

    current->previous_node->next_node = current->next_node;
    current->next_node->previous_node = current->previous_node;
    free(current);
    return;
}
int main()
{
    node *root = NULL;
    
    printf("--- 1. Liste Olusturuluyor (10, 20, 30, 40, 50) ---\n");
    add_list(&root, 10);
    add_list(&root, 20);
    add_list(&root, 30);
    add_list(&root, 40);
    add_list(&root, 50);
    print_list(root);

   
    printf("\n--- 2. Ortadan Silme Testi (30 Siliniyor) ---\n");
    delete_node(&root, 30);
    print_list(root);

  
    printf("\n--- 3. Bastan Silme Testi (10 Siliniyor - Head Degismeli) ---\n");
    delete_node(&root, 10);
    print_list(root);

    
    printf("\n--- 4. Sondan Silme Testi (50 Siliniyor) ---\n");
    delete_node(&root, 50);
    print_list(root);

   
    printf("\n--- 5. Olmayan Elemani Silme Testi (99 Siliniyor) ---\n");
    delete_node(&root, 99);
    print_list(root);

   
    
    return 0;
}