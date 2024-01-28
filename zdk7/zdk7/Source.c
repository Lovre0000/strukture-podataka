#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

struct _Directory;
typedef struct _Directory* PositionDirectory;
typedef struct _Directory
{
    char name[MAX_NAME_LENGTH];
    PositionDirectory subDirectory;
    PositionDirectory next;
}Directory;

struct _LevelStack;
typedef struct _LevelStack* PositionLevelStack;
typedef struct _LevelStack {
    PositionDirectory directoryLevel;
    PositionLevelStack next;
}LevelStack;


PositionDirectory createDirectory(char name[MAX_NAME_LENGTH]);
int push(PositionLevelStack headLevelStack, PositionDirectory currentDirectory);
PositionDirectory createSubdirectory(char* directoryName, PositionDirectory currentDirectory);
PositionDirectory changeDirectory(char* name, PositionDirectory currentDirectory);
PositionDirectory pop(PositionLevelStack headLevelStack);
int listDirectoryContents(PositionDirectory currentDirectory);
PositionLevelStack createNewLevelStack(PositionDirectory directoryLevel);

int main(void)
{
    Directory headDirectory = {
        .name = {0},
        .subDirectory = NULL,
        .next = NULL
    };

    PositionDirectory rootDirectory = createDirectory("C:");
    headDirectory.next = rootDirectory;

    PositionDirectory currentDirectory = rootDirectory;

    LevelStack headLevelStack = {
        .directoryLevel = NULL,
        .next = NULL
    };

    push(&headLevelStack, currentDirectory);

    while (1)
    {
        printf("\nMenu:\n");
        printf("1 - md (Create directory)\n");
        printf("2 - cd (Change directory)\n");
        printf("3 - cd.. (Go Up)\n");
        printf("4 - dir (List Contents)\n");
        printf("5 - exit\n");

        char choice[10];
        printf("Enter your choice: ");
        scanf("%s", choice);

        if (strcmp(choice, "1") == 0) {
            char directoryName[MAX_NAME_LENGTH];
            printf("Enter directory name: ");
            scanf("%s", directoryName);
            createSubdirectory(directoryName, currentDirectory);
        }
        else if (strcmp(choice, "2") == 0)
        {
            char directoryName[MAX_NAME_LENGTH];
            printf("Enter directory name: ");
            scanf("%s", directoryName);
            currentDirectory = changeDirectory(directoryName, currentDirectory);
            push(&headLevelStack, currentDirectory);
        }
        else if (strcmp(choice, "3") == 0)
        {
            if (currentDirectory != rootDirectory)
            {
                currentDirectory = pop(&headLevelStack);
                printf("Currently in '%s' \n", currentDirectory->name);
            }
            else {
                printf("Already in root dir.\n");
            }
        }
        else if (strcmp(choice, "4") == 0) {
            listDirectoryContents(currentDirectory);
        }
        else if (strcmp(choice, "5") == 0) {
            printf("Exiting...\n");
            break;
        }
        else {
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    free(rootDirectory);

    return 0;
}

PositionDirectory createDirectory(char name[MAX_NAME_LENGTH])
{
    PositionDirectory newDirectory = NULL;

    newDirectory = (PositionDirectory)malloc(sizeof(Directory));
    if (!newDirectory)
    {
        printf("Failed to allocate memory!\n");
        return NULL;
    }

    strcpy(newDirectory->name, name);
    newDirectory->subDirectory = NULL;
    newDirectory->next = NULL;

    return newDirectory;
}

int push(PositionLevelStack headLevelStack, PositionDirectory currentDirectory)
{
    PositionLevelStack newLevelStackElement = NULL;

    newLevelStackElement = createNewLevelStack(currentDirectory);
    if (!newLevelStackElement)
    {
        perror("Error in creating new element!\n");
        return EXIT_FAILURE;
    }

    newLevelStackElement->next = headLevelStack->next;
    headLevelStack->next = newLevelStackElement;

    return EXIT_SUCCESS;
}

PositionDirectory createSubdirectory(char* directoryName, PositionDirectory currentDirectory)
{
    PositionDirectory newDirectory = NULL;

    newDirectory = createDirectory(directoryName);
    if (!newDirectory)
    {
        printf("Failed to create new directory!\n");
        return NULL;
    }

    newDirectory->next = currentDirectory->subDirectory;
    currentDirectory->subDirectory = newDirectory;

    return newDirectory;
}

PositionDirectory changeDirectory(char* name, PositionDirectory currentDirectory)
{
    PositionDirectory subdirectory = currentDirectory->subDirectory;
    while (subdirectory != NULL)
    {
        if (strcmp(name, subdirectory->name) == 0) {
            return subdirectory;
        }
        subdirectory = subdirectory->next;
    }

    printf("Directory '%s' not found.\n", name);
    return currentDirectory;
}

PositionDirectory pop(PositionLevelStack headLevelStack)
{
    PositionLevelStack toDelete = NULL;
    PositionDirectory directoryLevel = NULL;

    toDelete = headLevelStack->next;
    if (!toDelete)
    {
        printf("Stack is empty! Nothing to pop!\n");
        return NULL;
    }

    headLevelStack->next = toDelete->next;
    directoryLevel = toDelete->directoryLevel;
    free(toDelete);

    return directoryLevel;
}

int listDirectoryContents(PositionDirectory currentDirectory)
{
    printf("Contents of directory '%s' : \n", currentDirectory->name);
    PositionDirectory subdirectory = currentDirectory->subDirectory;
    while (subdirectory != NULL) {
        printf("m - %s", subdirectory->name);
        subdirectory = subdirectory->subDirectory;
    }

    if (currentDirectory->subDirectory == NULL)
    {
        printf(" (empty)\n");
    }

    return EXIT_SUCCESS;
}

PositionLevelStack createNewLevelStack(PositionDirectory directoryLevel)
{
    PositionLevelStack newLevelStackElement = NULL;

    newLevelStackElement = (PositionLevelStack)malloc(sizeof(LevelStack));
    if (!newLevelStackElement)
    {
        printf("Can't allocate memory!\n");
        return NULL;
    }

    newLevelStackElement->directoryLevel = directoryLevel;
    newLevelStackElement->next = NULL;

    return newLevelStackElement;
}