#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX_LENGHT (50)
#define MAX_LINE (1024)

typedef struct _student {
	char name[MAX_LENGHT];
	char surname[MAX_LENGHT];
	double points;
}Student;


int countRows(FILE* filePtr);
void newStudent(Student* students, FILE* filePtr, int i);
void printStudents(Student* students, int i);
int main()
{
	Student* students=NULL;
	FILE* filePtr=NULL;
	int noRows = 0;

	filePtr = fopen("students.txt", "r");

	if (!filePtr)
	{
		printf("fail to open file\n");
		return EXIT_FAILURE;
	}

	noRows = countRows(filePtr);
	students = (Student*)malloc(sizeof(Student) * noRows);
	
	for (int i = 0;i < noRows;i++)
	{
		newStudent(students, filePtr, i);
	}
	for (int i = 0;i < noRows;i++)
	{
		printStudents(students, i);
	}
	free(students);
	free(filePtr);
	return 0;
}

//function counts number of rows
int countRows(FILE* filePtr)
{
	int noRows = 0;
	char buffer[MAX_LINE] = { 0 };
	while (!feof(filePtr))
	{
		fgets(buffer, MAX_LINE, filePtr);
		noRows++;
	}
	rewind(filePtr);

	return noRows;
}

//function reads data from the file
void newStudent(Student* students, FILE* filePtr, int i)
{
	fscanf(filePtr, "%s %s %lf", students[i].name, students[i].surname, &students[i].points);
	return 0;
}

void printStudents(Student* students, int i)
{
	printf("%s %s  %lf %lf\n", students[i].name, students[i].surname, students[i].points, students[i].points / 10 * 100);
	return 0;
}
