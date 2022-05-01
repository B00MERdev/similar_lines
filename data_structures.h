//
// Created by kuba on 30.08.2021.
//

#ifndef POPRAWKA_MAE_ZADANIE_DATA_STRUCTURES_H
#define POPRAWKA_MAE_ZADANIE_DATA_STRUCTURES_H
#define STARTING_LINE_LENGTH 64
#define STARTING_WORD_TABLE_LENGTH 8
#define STARTING_NUMBER_TABLE_LENGTH 8
#define STARTING_GROUP_TABLE_LENGTH 8
#define STARTING_INT_TABLE_LENGTH 8
#include <stdbool.h>
#include <stdlib.h>

typedef struct word {
    char *tableOfChars;
    unsigned int wordLength;
} Word;

typedef struct line {
    int NumberOfLine;
    char *lineChars;
    Word *tableOfNaNs;
    unsigned int tableOfNansLength;
    long double *tableOfNumbers;
    unsigned int tableOfNumbersLength;
    bool empty;
} Line;

typedef struct group {
    Line sample;
    int *tableOfLineIndices;
    unsigned int numberOfLines;
    unsigned int maxNumberOfLines;
} Group;

// dodaje nowy znak do tablicy
char *addNewChar(char* line, unsigned int *maxLineLength, unsigned int *i,
                 char input);

// dodaje nowe słowo do tablicy
Word *addNewWord(Word *wordTable, unsigned int *maxWordTableLength, unsigned
int *i, Word input);

// dodaje liczbę do tablicy liczb o wartości usuwanego ciągu znaków
long double *addANumberAndDeleteWord(long double *tableOfNumbers, unsigned
int *maxTableOfNumbersLength, unsigned int *tableOfNumbersLength, long double
                                     doubleConvertedFromWord, Word
                                     *tableOfWords, unsigned int
                                     *tableOfWordsLength, unsigned int i);

Group *addNewGroup(Group *tableOfGroups, unsigned int *maxNumberOfGroups,
                   unsigned int *numberOfGroups, Group input);

// dodaje nowy indeks linii do grupy
int *addNewLineIndex(int* tableOfLineIndices, unsigned int *maxNumberOfLines,
                     unsigned int *numberOfLines, int input);

// zwalnia pamięć po grupach
void freeGroups(unsigned int numberOfGroups, Group* tableOfGroups);

// tworzy nowe słowo na podstawie danych
Word createNewWord(char *tableOfChars, unsigned int wordLength);

void freeLine(Line lineToFree);

void *secureMalloc(size_t size);
#endif //POPRAWKA_MAE_ZADANIE_DATA_STRUCTURES_H
