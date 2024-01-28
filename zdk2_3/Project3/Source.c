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
typedef struct _Person* Position;
typedef struct _Person{
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int year;
	Position next;
}Person;

int addToFront(Position Head);
Position createPerson();
int addToBack(Position Head);
int printList(Position Head);
Position findPerson(Position Head);
int printPerson(Position person);
int deletePerson(Position Head);
int addAfter(Position person);
Position findPrev(Position Head);
int printListInDoc(Position Head);
int printListFromDoc();

int main()
{
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .year = 0 };
	char com;
	Position person = NULL;
	Position prev = NULL;
	while (1)
	{
		printf("enter A to add person to front, B to print list, C to add person to back, D to find person by surname, E to delete person by surname, F to add person after another person, G to add person behinf+d another Person, H to write list in file, I to read list from file\n");
		scanf(" %c", &com);
		
		switch (com)
		{
		case'A':
		case'a':
			addToFront(&Head);
			continue;
		case'B':
		case'b':
			printList(Head.next);
			continue;
		case'C':
		case'c':
			addToBack(&Head);
		case'd':
		case'D':
			person = findPerson(&Head);
				person ? printPerson(person) : printf("cant find person");
				continue;
		case'E':
		case'e':
			switch (deletePerson(&Head))
			{
			case EXIT_SUCCESS:
				printf("person deeted\n");
				break;
			case EMPTY_LIST:
				printf("empty lst\n");
				break;
			case NO_PERSON_FOUND_INT:
				printf("no person found\n");
				break;
			}
		case 'F':
		case'f':
			person = findPerson(&Head);
			person ? addAfter(person) : printf("cant find person\n");
			continue;
		case'G':
		case'g':
			prev = findPrev(&Head);
			prev ? addAfter(prev) : printf("cant find person\n");
			continue;
		case'H':
		case'h':
			printListInDoc(Head.next);
			continue;
		case'I':
		case'i':
			printListFromDoc();
			continue;


		}
	}

}
int addToFront(Position Head)
{
	Position newStudent;
	newStudent = createPerson();

	newStudent->next = Head->next;
	Head->next = newStudent;

	return EXIT_SUCCESS;

 }

Position createPerson()
{
	Position newPerson = NULL;
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int year;
	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson)
	{
		printf("cant allocate");
		return NULL;
	}
	printf("enter name\n");
	scanf("%s", name);
	printf("enter surname\n");
	scanf("%s", surname);
	printf("enter year\n");
	scanf("%d", &year);

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->year = year;

	return newPerson;
}

int printList(Position Head)
{
	if (!Head)
	{
		printf("empty");
		return NO_PERSON_FOUND_INT;
	}
	while (Head)
	{
		printf("%s %s %d\n", Head->name, Head->surname, Head->year);
		Head = Head->next;
	}
	return EXIT_SUCCESS;
}

int addToBack(Position Head)
{
	Position newStudent = NULL;

	newStudent = createPerson();

	while (Head->next != NULL)
	{
		Head = Head->next;
	}
	newStudent->next = Head->next;
	Head->next = newStudent;

	return EXIT_SUCCESS;
}
Position findPerson(Position Head)
{
	char surname[MAX_LENGTH];

	printf("enter surname\n");
	scanf("%s", surname);

	while (Head->next && strcmp(surname, Head->surname) != 0)
	{
		Head = Head->next;
	}
	if (strcmp(Head->surname, surname) == 0)
	{
		return Head;
	}

	return NO_PERSON_FOUND;
}
int printPerson(Position person)
{
	printf("%s %s %d\n", person->name, person->surname, person->year);
	return EXIT_SUCCESS;
}

int deletePerson(Position Head)
{

	char surname[MAX_LENGTH];

	if (Head->next)
	{
		Position prev=NULL;
		printf("emter surname to elete\n");
		scanf("%s", surname);
		while (Head && strcmp(Head->surname, surname) != 0)
		{
			prev = Head;
			Head = Head->next;
		}
		if (strcmp(Head->surname, surname) == 0)
		{
			prev->next = Head->next;
			free(Head);
			return EXIT_SUCCESS;
		}
		
	}
	else
	{
		return EMPTY_LIST;
	}

	return NO_PERSON_FOUND_INT;

}
int addAfter(Position person)
{
	Position newPerson = NULL;
	newPerson = createPerson();

	newPerson->next = person->next;
	person->next = newPerson;

	return EXIT_SUCCESS;


}
Position findPrev(Position Head)
{
	Position prev = NULL;
	if (Head->next)
	{
		char surname[MAX_LENGTH];
		printf("enter surname\n");
		scanf("%s", surname);
		while (Head && strcmp(Head->surname, surname) != 0)
		{
			prev = Head;
			Head = Head->next;
		}
		if (strcmp(Head->surname, surname) == 0)
		{
			return prev;
		}
	}
	else
		return NULL;

	return NO_PERSON_FOUND;

}

int printListInDoc(Position Head)
{

	FILE* filePtr=NULL;

	filePtr = fopen("list.txt", "w");
	if (!filePtr)
	{
		printf("cant open file\n");
		return EXIT_FAILURE;
	}
	while (Head)
	{
		fprintf(filePtr, "%s %s %d\n", Head->name, Head->surname, Head->year);
		Head = Head->next;
	}
	fclose(filePtr);
	return EXIT_SUCCESS;
}
int printListFromDoc()
{
	FILE* filePtr = NULL;
	filePtr = fopen("list.txt", "r");

	if (!filePtr)
	{
		printf("cant open\n");
		return EXIT_FAILURE;
	}

	while (!feof(filePtr))
	{
		char name[MAX_LENGTH];
		char surname[MAX_LENGTH];
		int year;

		fscanf(filePtr, "%s %s %d", name, surname, &year);
		printf("%s %s %d", name, surname, year);

	}
	return EXIT_SUCCESS;
}
