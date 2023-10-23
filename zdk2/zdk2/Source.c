#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX_LENGTH (50)

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

Position findLast(Position Head);

int main()
{
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .year = 0 };
	char com;
	Position = NULL;
	
	while (1)
	{
		printf("Type the command\n");
		printf("Type A for new element, ...\n");
		scanf("%c", &com);
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
			/*person = findPerson(Head.next);
			person ? printPerson(person) : printf("cant find the person");
			*/
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