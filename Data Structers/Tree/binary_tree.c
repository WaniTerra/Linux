#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
    int data;
    struct tree *left;
    struct tree *right;

} tree;

tree *create_node(int data)
{
    tree *node = malloc(sizeof(tree));

    node->data = data;
    node->right = NULL;
    node->left = NULL;

    return node;
}

void insert(int data, tree **root)
{

    if (*root == NULL)
    {
        *root = create_node(data);
        return;
    }

    tree *temp_root = *root;

    while (1)
    {

        if (data < temp_root->data)
        {
            if (temp_root->left == NULL)
            {

                temp_root->left = create_node(data);
                return;
            }
            temp_root = temp_root->left;
        }

        else if (data > temp_root->data)
        {
            if (temp_root->right == NULL)
            {
                temp_root->right = create_node(data);
                return;
            }
            temp_root = temp_root->right;
        }

        else
        {

            return;
        }
    }
}

void print_tree(tree *root)
{
    if (root == NULL)
        return;

    print_tree(root->left);
    printf("%d ", root->data);
    print_tree(root->right);
}

tree *search(int searched, tree *root)
{
    if (root == NULL)
        return NULL;

    if (root->data == searched)
    {
        return root;
    }

    if (root->data > searched)
    {

        return search(searched, root->left);
    }

    if (root->data < searched)
    {
        return search(searched, root->right);
    }
}

int main()
{
    tree *root = create_node(15);
    tree *t1 = create_node(10);
    tree *t2 = create_node(20);

    root->left = t1;
    root->right = t2;

    insert(12, &root);

    print_tree(root);

    tree *search_tree = search(15, root);

    printf("\nWe found : %d ", search_tree->data);

    return 0;
}