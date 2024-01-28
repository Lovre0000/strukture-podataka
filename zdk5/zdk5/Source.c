#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
#define MAX_LENGTH (1024)

struct _StackElement;
typedef struct _StackElement* Position;
typedef struct _StackElement {
    double number;
    Position next;
}StackElement;

int calculatePostFix(Position Head, char* fileName, double* result);
int readFile(char* fileName, char* buffer);
int stringIntoPostFix(Position Head, char* buffer, double* result);
int popAndOperation(Position Head, char operation, double* number);
Position createStackElement(double number);
int push(Position Head, Position newStackElement);
int printStack(Position First);
int pop(Position Head, double* operand);
int checkStackAndGetResult(Position Head, double* result);

int main(void)
{
    StackElement Head = { .number = 0, .next = NULL };
    double result = 0;

    if (calculatePostFix(&Head, "postfix.txt", &result) == EXIT_SUCCESS)
    {
        printf("Result : %0.1lf\n", result);
    }
    return EXIT_SUCCESS;
}

int calculatePostFix(Position Head, char* fileName, double* result)
{
    char buffer[MAX_LENGTH] = { 0 };
    int status = 0;

    if (readFile(fileName, buffer) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    status = stringIntoPostFix(Head, buffer, result);
    if (status != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int readFile(char* fileName, char* buffer)
{
    FILE* filePtr = NULL;
    filePtr = fopen(fileName, "r");
    if (!filePtr)
    {
        printf("Can't open file!\n");
        return EXIT_FAILURE;
    }
    fgets(buffer, MAX_LENGTH, filePtr);
    printf("|%s|\n", buffer);

    fclose(filePtr);

    return EXIT_SUCCESS;
}

int stringIntoPostFix(Position Head, char* buffer, double* result)
{
    char* currentBuffer = buffer;
    int status = 0;
    int numBytes = 0;
    char operation = 0;
    double number = 0.0;
    Position newStackElement = NULL;

    while (strlen(currentBuffer) > 0)
    {
        status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
        if (status != 1)
        {
            sscanf(currentBuffer, " %c %n", &operation, &numBytes);
            status = popAndOperation(Head, operation, result);
            if (status != EXIT_SUCCESS)
            {
                return EXIT_FAILURE;
            }
            number = *result;
        }
        newStackElement = createStackElement(number);
        if (!newStackElement)
        {
            return EXIT_FAILURE;
        }

        currentBuffer += numBytes;
        printf("|%s| <-->", currentBuffer);
        push(Head, newStackElement);

    }
    return checkStackAndGetResult(Head, result);
}
int popAndOperation(Position Head, char operation, double* number)
{
    double operand1 = 0;
    double operand2 = 0;
    int status1 = 0;
    int status2 = 0;

    status1 = pop(Head, &operand1);
    if (status1 != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    status2 = pop(Head, &operand2);
    if (status2 != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    switch (operation)
    {
    case '+':
        *number = operand2 + operand1;
        break;
    case '-':
        *number = operand2 - operand1;
        break;
    case '*':
        *number = operand2 * operand1;
        break;
    case '/':
        *number = operand2 / operand1;
        break;
    default:
        printf("Wrong operation!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

Position createStackElement(double number)
{
    Position newStackElement = NULL;

    newStackElement = (Position)malloc(sizeof(StackElement));
    if (!newStackElement)
    {
        printf("Failed to allocate memory!\n");
        return NULL;
    }

    newStackElement->next = NULL;
    newStackElement->number = number;

    return newStackElement;
}

int push(Position Head, Position newStackElement)
{
    newStackElement->next = Head->next;
    Head->next = newStackElement;

    printStack(Head->next);

    return EXIT_SUCCESS;
}

int printStack(Position First)
{
    Position current = First;

    while (current)
    {
        printf("%0.1lf", current->number);
        current = current->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int pop(Position Head, double* operand)
{
    Position toDelete = NULL;

    toDelete = Head->next;
    if (!toDelete)
    {
        printf("Empty stack!\n");
        return -1;
    }

    Head->next = toDelete->next;
    *operand = toDelete->number;
    free(toDelete);

    return EXIT_SUCCESS;
}

int checkStackAndGetResult(Position Head, double* result)
{
    int status = EXIT_SUCCESS;

    status = pop(Head, result);

    if (status != EXIT_SUCCESS)
    {
        return status;
    }

    if (Head->next)
    {
        system("cls");
        printf("Invalid postfix, please check the file!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}