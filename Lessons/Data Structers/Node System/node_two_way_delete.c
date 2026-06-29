#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

// Wrapper struct to make appends O(1) and keep code clean
typedef struct LinkedList {
    Node *head;
    Node *tail;
} LinkedList;

// Helper function to safely allocate memory
Node* create_node(int data) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE); 
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Appends to the tail instantly without traversing the whole list
void append(LinkedList *list, int data) {
    Node *new_node = create_node(data);

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        return;
    }

    list->tail->next = new_node;
    new_node->prev = list->tail;
    list->tail = new_node; // Move tail pointer to the end
}

// Cleaned up deletion logic
void delete_node(LinkedList *list, int value) {
    Node *current = list->head;

    while (current != NULL && current->data != value) {
        current = current->next;
    }

    if (current == NULL) return; // Value not found

    // If updating the head
    if (current == list->head) {
        list->head = current->next;
    } else {
        current->prev->next = current->next;
    }

    // If updating the tail
    if (current == list->tail) {
        list->tail = current->prev;
    } else {
        current->next->prev = current->prev;
    }

    free(current);
}

void print_list(LinkedList *list) {
    Node *current = list->head;
    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    while (current != NULL) {
        if (current->prev != NULL) {
            printf("Current: %d, Previous: %d\n", current->data, current->prev->data);
        } else {
            printf("Current: %d (Head)\n", current->data);
        }
        current = current->next;
    }
    printf("---------------------------\n");
}

// Free all memory to prevent memory leaks
void free_list(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

int main() {
    // Initialize empty list wrapper
    LinkedList list = {NULL, NULL};
    
    append(&list, 10);
    append(&list, 20);
    append(&list, 30);
    append(&list, 40);
    append(&list, 50);
    print_list(&list);

    delete_node(&list, 30); // Middle
    print_list(&list);

    delete_node(&list, 10); // Head
    print_list(&list);

    delete_node(&list, 50); // Tail
    print_list(&list);

    // Clean up cleanly before exiting
    free_list(&list);
    
    return 0;
}