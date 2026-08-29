#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(int value)
{
    Node *node = malloc(sizeof(Node));

    if (node == NULL)
    {
        return NULL;
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Node *insert(Node *root, int value)
{
    if (root == NULL)
    {
        return create_node(value);
    }

    if (value < root->value)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = insert(root->right, value);
    }

    return root;
}

Node *search(Node *root, int value)
{
    if (root == NULL || root->value == value)
    {
        return root;
    }

    if (value < root->value)
    {
        return search(root->left, value);
    }

    return search(root->right, value);
}

Node *find_min(Node *root)
{
    Node *current = root;

    while (current != NULL && current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

Node *delete(Node *root, int value)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (value < root->value)
    {
        root->left = delete(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = delete(root->right, value);
    }
    else
    {
        /*
         * Case 1: No children.
         */
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        /*
         * Case 2: Only right child.
         */
        if (root->left == NULL)
        {
            Node *temp = root->right;

            free(root);

            return temp;
        }

        /*
         * Case 2: Only left child.
         */
        if (root->right == NULL)
        {
            Node *temp = root->left;

            free(root);

            return temp;
        }

        /*
         * Case 3: Two children.
         * Replace the node with its in-order successor.
         */
        Node *successor = find_min(root->right);

        root->value = successor->value;

        root->right = delete(root->right, successor->value);
    }

    return root;
}

void inorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    inorder(root->left);
    printf("%d ", root->value);
    inorder(root->right);
}

void preorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%d ", root->value);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->value);
}

void free_tree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);

    free(root);
}

int main(void)
{
    Node *root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("In-order: ");
    inorder(root);
    printf("\n");

    printf("Pre-order: ");
    preorder(root);
    printf("\n");

    printf("Post-order: ");
    postorder(root);
    printf("\n");

    if (search(root, 40) != NULL)
    {
        printf("Search 40: found\n");
    }
    else
    {
        printf("Search 40: not found\n");
    }

    root = delete(root, 30);

    printf("After deleting 30: ");
    inorder(root);
    printf("\n");

    free_tree(root);

    return 0;
}