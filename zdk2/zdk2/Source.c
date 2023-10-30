#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX_LENGTH (50)
#define NO_PERSON_FOUND (NULL)
#define EMPTY_LIST (-1)
#define NO_PERSON_FOUND_INT (-2)
#define SINGLE_PERSON_IN_LIST (-3)

struct _Person;
typedef struct _Person*Position;
typedef struct _Person {
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int year;
	Position next;
}Person;

int addNewStudentToTheFront(Position Head);
Position createPerson();
int printList(Position firstItem);
int printPerson(Position Head);
int addNewStudentToTheBack(Position Head);
Position findLast(Position Head);
char* enterSurname();
Position findPerson(Position Head);
int deletePerson(Position Head);
int main()
{
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .year = 0 };
	char com;
	Position person = NULL;
	
	while (1)
	{
		printf("Type the command\n");
		printf("Type A for new element, B for print list, C for new element to the back, D to find person, E to delete person\n");
		scanf(" %c", &com);
		switch (com)
		{
		case 'A':
		case 'a':
			addNewStudentToTheFront(&Head);
			continue;
		case'B':
		case'b':
			printList(Head.next);
			continue;
		case'C':
		case'c':
			addNewStudentToTheBack(&Head);
			continue;
		case'D':
		case'd':
			person = findPerson(Head.next);
			person ? printPerson(person) : printf("cant find the person");
			continue;
		case 'E':
		case 'e':
			switch (deletePerson(&Head))
			{
			case EXIT_SUCCESS:
				printf("Person deleted\n");
				break;
			case EMPTY_LIST:
				printf("Empty list\n");
				break;
			case NO_PERSON_FOUND_INT:
				printf("Can't find person\n");
				break;
			default:
				break;
			}
		}
	}


	return 0;
}
Position createPerson()
{
	Position newStudent;

	char name[MAX_LENGTH]={0};
	char surname[MAX_LENGTH]={0};
	int year=0;

	newStudent = (Position)malloc(sizeof(Person));
	if (!newStudent)
	{
		printf("Can't allocate memory");
		return 0;
	}
	printf("Enter name: \n");
	scanf("%s", name);
	printf("Enter surname: \n");
	scanf("%s", surname);
	printf("Enter birth year: \n");
	scanf("%d", &year);

	strcpy(newStudent->name, name);
	strcpy(newStudent->surname, surname);
	newStudent->year = year;

	return newStudent;
}
int addNewStudentToTheFront(Position Head)
{
	Position newStudent = NULL;
	newStudent = createPerson();
	if (newStudent)
	{
		newStudent->next = Head->next;
		Head->next = newStudent;
	}
	return EXIT_SUCCESS;
}
int printList(Position firstItem)
{

	Position currentItem = firstItem;
	while (!currentItem)
	{
		printf("Empty list");
	}
	while (currentItem)
	{
		printf("%s %s %d\n", currentItem->name, currentItem->surname, currentItem->year);
		currentItem = currentItem->next;

	}
	return EXIT_SUCCESS;
}
int addNewStudentToTheBack(Position Head)
{
	Position newStudent = NULL;
	Position  last = NULL;
	newStudent = createPerson();
	if (newStudent)
	{
		last = findLast(Head);
		newStudent->next = last->next;
		last->next = newStudent;
	}
	return EXIT_SUCCESS;
	
}
Position findLast(Position Head)
{
	Position temp = Head;


	while (temp->next)
	{
		temp = temp->next;
	}
	return temp;

}


 char* enterSurname()
{
	char Surname[MAX_LENGTH];

	printf("Enter surname: ");
	scanf("%s", Surname);
	return Surname;
}

Position findPerson(Position Head)
{
	char Surname[MAX_LENGTH] = { 0 };
	
	
	Position newPerson=NULL;
	if (!Head)
	{
		printf("Empty list\n");
		return NO_PERSON_FOUND;
	}
	strcpy(Surname, enterSurname());
	while (Head && strcmp(Head->surname, Surname)!=0)
	{
		Head = Head->next;
	}
	newPerson = Head;
	return newPerson;

}
int printPerson(Position Head)
{
	printf("%s %s %d\n", Head->name, Head->surname, Head->year);
	return EXIT_SUCCESS;
}
int deletePerson(Position Head)
{
	Position current = Head;
	char Surname[MAX_LENGTH]={0};
	strcpy(Surname, enterSurname());
	if (Head->next)
	{
		Position previous = NULL;
		while (current->next && strcmp(current->surname, Surname) != 0)
		{
			previous = current;
			current = current->next;
		}

		if (previous && previous->next && strcmp(current->surname, Surname)==0)
		{
			printPerson(current);
				previous->next=current->next;
				free(current);
		}
		else
		{
			return NO_PERSON_FOUND_INT;
		}
	}
	else
	{
		return EMPTY_LIST;
	}
	return EXIT_SUCCESS;
}