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
typedef struct _Person {
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int year;
	Position next;
}Person;

int addNewStudentToFront(Position Head);
Position createPerson();
int printList(Position firstItem);


int main(){
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .year = {0} };
	Position person = NULL;
	char com;

	while (1)
	{
		printf("Type A to add new element to the front, B to print list, \n");
		scanf("%c", &com);
		switch (com)
		{
		case'A':
		case'a':
			addNewStudentToFront(&Head);
			continue;
		case'B':
		case'b':
			printList(Head.next);
			continue;
		case'D':
		case'd':
			person = findPerson(Head.next);
			person ? printPerson(person) : printf("cant find person");
			continue;




		}
	}





}

Position createPerson()
{
	Position newStudent;
	char name[MAX_LENGTH] = { 0 };
	char surname[MAX_LENGTH] = { 0 };
	int year = 0;

	newStudent = (Position)malloc(sizeof(Person));
	if (!newStudent)
	{
		printf("cant allocate ");
		return 0;
	}
	printf("enter name: \n");
	scanf("%s", name);
	printf("enter surname: \n");
	scanf("%s", surname);
	printf("enter year: \n");
	scanf("%d", &year);
	strcpy(newStudent->name, name);
	strcpy(newStudent->surname, surname);
	newStudent->year = year;

	return newStudent;

}
int addNewStudentToFront(Position Head)
{
	Position newStudent = NULL;
	newStudent = createPerson();
	if (newStudent)
	{
		newStudent->next = Head->next;
		Head->next = newStudent;
		return EXIT_SUCCESS;
	}
}
int printList(Position firstItem)
{

	Position currentItem = firstItem;
	while (!currentItem)
	{
		printf("empty list");
	}
	while (currentItem)
	{
		printf("%s %s %d\n", currentItem->name, currentItem->surname, currentItem->year);
		currentItem = currentItem->next;
	}
	return EXIT_SUCCESS;
}