#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)
#define MAX_LINE (1024)
#define FILE_NOT_OPEN (-1)
#define FAILED_MEMORY_ALLOCATION (NULL)
#define HASH_TABLE_SIZE 11

struct _town;
typedef struct _town* TownPosition;
typedef struct _town {
    char name[MAX_LENGTH];
    int population;
    TownPosition next;
    TownPosition left;
    TownPosition right;
} Town;

struct _country;
typedef struct _country* CountryPosition;
typedef struct _country {
    char name[MAX_LENGTH];
    CountryPosition next;
    CountryPosition left;
    CountryPosition right;
    Town townHead;
    TownPosition townRoot;
} Country;

struct _hash_table {
    CountryPosition buckets[HASH_TABLE_SIZE];
};
typedef struct _hash_table HashTable;


CountryPosition readAndFillCountries(CountryPosition countryHead, CountryPosition countryRoot, HashTable* hashTable);
int createNewCountryFromBuffer(char* fileName, char* countryName, CountryPosition* countries);
CountryPosition createNewCountry(char* countryName);
TownPosition createNewTown(char* name, int population);
int insertSortedNewTown(TownPosition townHead, TownPosition newTown);
int insertTownAfter(TownPosition currentTown, TownPosition newTown);
TownPosition insertNewTownTree(TownPosition townRoot, TownPosition newTown);
int insertSortedNewCountry(CountryPosition countryHead, CountryPosition newCountry);
int insertCountryAfter(CountryPosition currentCountry, CountryPosition newCountry);
CountryPosition insertNewCountryTree(CountryPosition countryRoot, CountryPosition newCountryTree);
int printCountryList(CountryPosition countryHead);
int printCountryTree(CountryPosition countryRoot);
int printTownList(TownPosition townHeadList);
int printTownTree(TownPosition townRootTree);
HashTable* createHashTable(void);
unsigned int calculateHash(char* countryName);
void insertCountryIntoHashTable(HashTable* hashTable, CountryPosition newCountry);
CountryPosition searchCountryInHashTable(HashTable* hashTable, char* countryName);
int printAllCountriesFromHash(HashTable* hashTable);
int findCountries(CountryPosition countryHead, CountryPosition countryRoot, CountryPosition* countries);
CountryPosition searchCountryTree(CountryPosition countryRoot, char* countryName);

int main(void) {
    Country countryHead = {
        .name = {0},
        .next = NULL,
        .left = NULL,
        .right = NULL,
        .townHead = {
            .population = 0,
            .name = {0},
            .next = NULL,
            .left = NULL,
            .right = NULL
        },
        .townRoot = NULL,
    };

    CountryPosition countryRoot = NULL;
    CountryPosition countries[] = { NULL, NULL };
    CountryPosition countryCurrentList = NULL;
    CountryPosition countryCurrentTree = NULL;
    HashTable* hashTable = createHashTable();

    countryRoot = readAndFillCountries(&countryHead, countryRoot, hashTable);

    printf("LIST");
    printCountryList(&countryHead);
    printf("\n\n\n");
    printf("TREE");
    printCountryTree(countryRoot);
    printf("\n\n\n");
    printf("HASH");
    printAllCountriesFromHash(hashTable);


    findCountries(&countryHead, countryRoot, countries);

    countryCurrentList = countries[0];
    countryCurrentTree = countries[1];

    printf("\nCountry list: %s", countryCurrentList->name);
    printf("\nCountry tree: %s", countryCurrentTree->name);

    char search[MAX_LENGTH] = { 0 };
    printf("\nEnter country name to search in the hash table: ");
    scanf(" %s", search);

    CountryPosition found = searchCountryInHashTable(hashTable, search);

    if (found != NULL) {
        printf("\nCountry found in the hash table: %s", found->name);
    }
    else {
        printf("\nCountry not found in the hash table.");
    }

    return EXIT_SUCCESS;
}

CountryPosition readAndFillCountries(CountryPosition countryHead, CountryPosition countryRoot, HashTable* hashTable) {
    FILE* filePtr = NULL;
    char countryName[MAX_LENGTH] = { 0 };
    char fileName[MAX_LINE] = { 0 };
    char nullString[MAX_LENGTH] = { 0 };
    CountryPosition newCountryList = NULL;
    CountryPosition newCountryRoot = NULL;
    CountryPosition newCountryHash = NULL;
    CountryPosition countries[] = { NULL, NULL, NULL };

    filePtr = fopen("drzave.txt", "r");
    if (!filePtr)
    {
        printf("Failed to open file!\n");
        return NULL;
    }

    while (!feof(filePtr)) {
        fscanf(filePtr, " %s %s", countryName, fileName);
        createNewCountryFromBuffer(fileName, countryName, countries);
        newCountryList = countries[0];
        newCountryRoot = countries[1];
        newCountryHash = countries[2];
        insertSortedNewCountry(countryHead, newCountryList);
        countryRoot = insertNewCountryTree(countryRoot, newCountryRoot);
        insertCountryIntoHashTable(hashTable, newCountryHash);
        strcpy(countryName, nullString);
        strcpy(fileName, nullString);
    }

    fclose(filePtr);

    return countryRoot;
}

int createNewCountryFromBuffer(char* fileName, char* countryName, CountryPosition* countries) {
    FILE* countryFilePointer = NULL;
    CountryPosition newCountryList = NULL;
    CountryPosition newCountryTree = NULL;
    CountryPosition newCountryHash = NULL;
    TownPosition newTownHash = NULL;
    TownPosition newTownList = NULL;
    TownPosition newTownTree = NULL;
    char townName[MAX_LENGTH] = { 0 };
    int townPopulation = 0;

    countryFilePointer = fopen(fileName, "r");
    if (!countryFilePointer)
    {
        printf("Failed to open file!\n");
        return EXIT_FAILURE;
    }

    newCountryList = createNewCountry(countryName);
    newCountryTree = createNewCountry(countryName);
    newCountryHash = createNewCountry(countryName);

    while (!feof(countryFilePointer))
    {
        fscanf(countryFilePointer, " %s %d", townName, &townPopulation);
        newTownList = createNewTown(townName, townPopulation);
        newTownTree = createNewTown(townName, townPopulation);
        newTownHash = createNewTown(townName, townPopulation);
        insertSortedNewTown(&newCountryTree->townHead, newTownList);
        newCountryList->townRoot = insertNewTownTree(newCountryList->townRoot, newTownTree);
        newCountryHash->townRoot = insertNewTownTree(newCountryHash->townRoot, newTownHash);
        newTownList = NULL;
    }

    countries[0] = newCountryList;
    countries[1] = newCountryTree;
    countries[2] = newCountryHash;

    fclose(countryFilePointer);

    return EXIT_SUCCESS;
}

CountryPosition createNewCountry(char* countryName) {
    char nullString[MAX_LENGTH] = { 0 };
    CountryPosition country = NULL;
    country = (CountryPosition)malloc(sizeof(Country));
    if (!country) {
        printf("Can't allocate memory!\n");
        return FAILED_MEMORY_ALLOCATION;
    }


    strcpy(country->name, countryName);
    country->next = NULL;
    country->left = NULL;
    country->right = NULL;
    country->townRoot = NULL;
    strcpy(country->townHead.name, nullString);
    country->townHead.population = 0;
    country->townHead.next = NULL;
    country->townHead.left = NULL;
    country->townHead.right = NULL;

    return country;
}

TownPosition createNewTown(char* name, int population) {
    TownPosition newTown = NULL;
    newTown = (TownPosition)malloc(sizeof(Town));
    if (!newTown)
    {
        printf("Failed to allocate memory!\n");
        return NULL;
    }

    strcpy(newTown->name, name);
    newTown->next = NULL;
    newTown->left = NULL;
    newTown->right = NULL;
    newTown->population = population;

    return newTown;
}

int insertSortedNewTown(TownPosition townHead, TownPosition newTown) {
    TownPosition currentTown = townHead;

    while (currentTown->next && strcmp(currentTown->next->name, newTown->name) < 0)
        currentTown = currentTown->next;

    insertTownAfter(currentTown, newTown);

    return EXIT_SUCCESS;
}

int insertTownAfter(TownPosition currentTown, TownPosition newTown) {
    newTown->next = currentTown->next;
    currentTown->next = newTown;

    return EXIT_SUCCESS;
}

TownPosition insertNewTownTree(TownPosition townRoot, TownPosition newTown) {
    if (townRoot == NULL)
        return newTown;

    if (newTown->population > townRoot->population)
        townRoot->left = insertNewTownTree(townRoot->left, newTown);
    else if (newTown->population <= townRoot->population)
        townRoot->right = insertNewTownTree(townRoot->right, newTown);

    return townRoot;
}

int insertSortedNewCountry(CountryPosition countryHead, CountryPosition newCountry) {
    CountryPosition currentCountry = countryHead;

    while (currentCountry->next && strcmp(currentCountry->next->name, newCountry->name) < 0)
        currentCountry = currentCountry->next;

    insertCountryAfter(currentCountry, newCountry);

    return EXIT_SUCCESS;
}

int insertCountryAfter(CountryPosition currentCountry, CountryPosition newCountry) {
    newCountry->next = currentCountry->next;
    currentCountry->next = newCountry;

    return EXIT_SUCCESS;
}

CountryPosition insertNewCountryTree(CountryPosition countryRoot, CountryPosition newCountryTree) {
    if (countryRoot == NULL)
        return newCountryTree;

    if (strcmp(countryRoot->name, newCountryTree->name) > 0)
        countryRoot->left = insertNewCountryTree(countryRoot->left, newCountryTree);
    else if (strcmp(countryRoot->name, newCountryTree->name) <= 0)
        countryRoot->right = insertNewCountryTree(countryRoot->right, newCountryTree);

    return countryRoot;
}

int printCountryList(CountryPosition countryHead) {
    CountryPosition currentCountry = countryHead->next;
    while (currentCountry != NULL) {
        printf("\n%s", currentCountry->name);
        printTownTree(currentCountry->townRoot);
        currentCountry = currentCountry->next;
    }
    return EXIT_SUCCESS;
}

int printCountryTree(CountryPosition countryRoot) {
    if (countryRoot) {
        printCountryTree(countryRoot->left);
        printf("\n%s", countryRoot->name);
        printTownList(&countryRoot->townHead);
        printCountryTree(countryRoot->right);
    }
    return EXIT_SUCCESS;
}

int printTownList(TownPosition townHeadList) {
    TownPosition currentTown = townHeadList->next;
    while (currentTown != NULL) {
        printf("\n\t%s %d", currentTown->name, currentTown->population);
        currentTown = currentTown->next;
    }
    return EXIT_SUCCESS;
}

int printTownTree(TownPosition townRootTree) {
    if (townRootTree) {

        printTownTree(townRootTree->left);
        printf("\n\t%s %d", townRootTree->name, townRootTree->population);
        printTownTree(townRootTree->right);
    }
    return EXIT_SUCCESS;
}

int findCountries(CountryPosition countryHead, CountryPosition countryRoot, CountryPosition* countries) {
    CountryPosition countryCurrentList = countryHead->next;
    CountryPosition countryCurrentTree = countryRoot;
    char countryName[MAX_LENGTH] = { 0 };
    printf("\n\nEnter country name: ");
    scanf(" %s", countryName);

    while (countryCurrentList != NULL && strcmp(countryCurrentList->name, countryName)) {
        countryCurrentList = countryCurrentList->next;
    }

    countryCurrentTree = searchCountryTree(countryRoot, countryName);

    countries[0] = countryCurrentList;
    countries[1] = countryCurrentTree;

    return EXIT_SUCCESS;
}

CountryPosition searchCountryTree(CountryPosition countryRoot, char* countryName) {
    if (countryRoot == NULL || strcmp(countryRoot->name, countryName) == 0)
        return countryRoot;

    if (strcmp(countryRoot->name, countryName) > 0)
        return searchCountryTree(countryRoot->left, countryName);

    return searchCountryTree(countryRoot->right, countryName);
}

HashTable* createHashTable(void) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    if (!hashTable) {
        printf("Can't allocate memory for hash table!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable->buckets[i] = NULL;
    }

    return hashTable;
}

unsigned int calculateHash(char* countryName) {
    unsigned int hashValue = 0;
    int i = 0;
    while (i < 5 && countryName[i] != '\0') {
        hashValue += (unsigned int)countryName[i];
        i++;
    }
    return hashValue % HASH_TABLE_SIZE;
}

void insertCountryIntoHashTable(HashTable* hashTable, CountryPosition newCountry) {
    unsigned int index = calculateHash(newCountry->name);

    if (hashTable->buckets[index] == NULL) {
        hashTable->buckets[index] = newCountry;
        newCountry->next = NULL;
    }
    else {

        newCountry->next = hashTable->buckets[index];
        hashTable->buckets[index] = newCountry;
    }
}

CountryPosition searchCountryInHashTable(HashTable* hashTable, char* countryName) {
    unsigned int index = calculateHash(countryName);
    CountryPosition currentCountry = hashTable->buckets[index];

    while (currentCountry != NULL && strcmp(currentCountry->name, countryName) != 0) {
        currentCountry = currentCountry->next;
    }

    return currentCountry;
}

int printAllCountriesFromHash(HashTable* hashTable) {
    for (int index = 0; index < HASH_TABLE_SIZE; index++) {
        CountryPosition currentCountry = NULL;
        currentCountry = hashTable->buckets[index];

        while (currentCountry != NULL) {
            printf("\n%s", currentCountry->name);
            printTownTree(currentCountry->townRoot);
            currentCountry = currentCountry->next;
        }
    }
    return EXIT_SUCCESS;
}