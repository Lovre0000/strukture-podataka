#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


struct _node;
typedef struct _node* Position;
typedef struct _node {
    int value;
    Position left;
    Position right;
}Node;

int random1(void);
Position insert(Position root, int value);
Position createNode(int value);
int levelOrder(Position root);
int replace(Position root);
int inOrder(Position root);
int postOrder(Position root);
int preOrder(Position root);
Position search(Position root, int value);
Position deleteNode(Position root, int value);

int main(void)
{
    Position root = NULL;
    Position randomRoot = NULL;
    srand((int)time(0));

    root = insert(root, 2);
    insert(root, 5);
    insert(root, 7);
    insert(root, 8);
    insert(root, 11);
    insert(root, 1);
    insert(root, 4);
    insert(root, 2);
    insert(root, 3);
    insert(root, 7);

    levelOrder(root);
    printf("\n");
    inOrder(root);

    replace(root);

    printf("\n");
    levelOrder(root);

    printf("\n");
    inOrder(root);


    randomRoot = insert(randomRoot, random1());
    for (int i = 0; i < 10;i++) {
        insert(randomRoot, random1());
    }

    printf("\n");
    levelOrder(randomRoot);

    printf("\n");
    root = deleteNode(root, 1);
    levelOrder(root);

    return EXIT_SUCCESS;
}

Position insert(Position root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }

    if (value < root->value)
    {
        root->left = insert(root->left, value);

    }
    else if (value >= root->value)
    {
        root->right = insert(root->right, value);
    }
    return root;
}

Position createNode(int value)
{
    Position newNode = NULL;

    newNode = (Position)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Failed to allocate memory!\n");
        return NULL;
    }

    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int levelOrder(Position root)
{
    if (root == NULL)
    {
        return EXIT_FAILURE;
    }
    Position queue[100] = { 0 };
    int rear = 0, front = 0;

    queue[rear++] = root;

    while (front < rear)
    {
        Position current = queue[front++];

        printf("%d ", current->value);

        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }

    return EXIT_SUCCESS;
}

int replace(Position root) {
    if (root == NULL) {
        return 0;
    }

    int leftValue = replace(root->left);
    int rightValue = replace(root->right);

    int originalValue = root->value;

    root->value = leftValue + rightValue;

    return originalValue + root->value;
}

int inOrder(Position root)
{
    if (root) {
        inOrder(root->left);
        printf("%d ", root->value);
        inOrder(root->right);
    }
    return EXIT_SUCCESS;
}

int preOrder(Position root) {
    if (root) {
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
    return EXIT_SUCCESS;
}

int postOrder(Position root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->value);
    }
    return EXIT_SUCCESS;
}

int random1(void) {
    return (rand() % (90 - 10 + 1)) + 10;
}

Position search(Position root, int value) {
    if (root == NULL || root->value == value)
        return root;

    if (value < root->value) {
        return search(root->left, value);
    }

    return search(root->right, value);
}

Position deleteNode(Position root, int value) {
    if (root == NULL)
        return root;

    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else {

        if (root->left == NULL) {
            Position temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Position temp = root->left;
            free(root);
            return temp;
        }

        Position temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        root->value = temp->value;

        root->right = deleteNode(root->right, temp->value);
    }

    return root;
}