#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

typedef struct
{
    node *front; // Exit
    node *rear;
} queue;

void enqueue(queue *q, int data)
{

    node *temp_node = malloc(sizeof(node));
    temp_node->data = data;
    temp_node->next = NULL;

    if (q->rear == NULL && q->front == NULL)
    {
        q->rear = temp_node;
        q->front = temp_node;
    }
    else
    {
        q->rear->next = temp_node;
        q->rear = temp_node;
    }
}

int dequeue(queue *q)
{
    if (q->front == NULL)
    {
        return 0;
    }

    int data = q->front->data;
    node *free_node = q->front;

    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(free_node);

    return data;
}

void print_list(queue *q)
{
    node *temp_q = q->front;

    while (temp_q != NULL)
    {
        printf("%d \n", temp_q->data);
        temp_q = temp_q->next;
    }
}

int main()
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->front = NULL;
    q->rear = NULL;

    enqueue(q, 5);
    enqueue(q, 8);
    enqueue(q, 10);

    print_list(q);

    printf("Dequeue %d \nNew List \n", dequeue(q));

    print_list(q);

    return 0;
}