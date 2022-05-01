//
// Created by kuba on 30.08.2021.
//

#include "data_structures.h"
#include <stdlib.h>

void increase(unsigned int *length) {
    (*length) *= 2;
}

// zwiększa tablicę
char *extendTable(char *table, unsigned int *length) {
    increase(length);
    table = realloc(table, *length * sizeof(*table));

    return table;
}
// dodaje nowy znak do tablicy
char *addNewChar(char* line, unsigned int *maxLineLength, unsigned int *i,
                 char input) {
    if (*i == *maxLineLength) {
        line = extendTable(line, maxLineLength);
    }

    line[*i] = input;
    (*i)++;

    return line;
}

Word *extendTableOfWords(Word *table, unsigned int *length) {
    increase(length);
    table = realloc(table, *length * sizeof(*table));

    return table;
}
// dodaje nowe słowo do tablicy
Word *addNewWord(Word *wordTable, unsigned int *maxWordTableLength, unsigned
int *i, Word input) {
    if (*i == *maxWordTableLength) {
        wordTable = extendTableOfWords(wordTable, maxWordTableLength);
    }

    wordTable[*i] = input;
    (*i)++;

    return wordTable;
}

long double *extendTableOfNumbers(long double *table, unsigned int *length) {
    increase(length);
    table = realloc(table, *length * sizeof(*table));

    return table;
}

long double *addNewNumber(long double *tableOfNumbers, unsigned int
*maxTableOfNumbersLength, unsigned int *i,
                          long double input) {
    if (*i == *maxTableOfNumbersLength) {
        tableOfNumbers = extendTableOfNumbers(tableOfNumbers, maxTableOfNumbersLength);
    }

    tableOfNumbers[*i] = input;
    (*i)++;

    return tableOfNumbers;
}

// usuwa słowo z tablicy słów
void deleteWordFromTable(Word *tableOfWords, unsigned int
*tableOfWordsLength, unsigned int i) {
    if (i < *tableOfWordsLength - 1) {
        tableOfWords[i].tableOfChars = tableOfWords[*tableOfWordsLength - 1]
                .tableOfChars;
        tableOfWords[i].wordLength = tableOfWords[*tableOfWordsLength - 1]
                .wordLength;
    }

    (*tableOfWordsLength)--;
}

// dodaje liczbę do tablicy liczb o wartości usuwanego ciągu znaków
long double *addANumberAndDeleteWord(long double *tableOfNumbers, unsigned
int *maxTableOfNumbersLength, unsigned int *tableOfNumbersLength, long double
                                     doubleConvertedFromWord, Word *tableOfWords, unsigned int
                                     *tableOfWordsLength, unsigned int i) {

    tableOfNumbers = addNewNumber(tableOfNumbers, maxTableOfNumbersLength, tableOfNumbersLength,
                                  doubleConvertedFromWord);

    deleteWordFromTable(tableOfWords, tableOfWordsLength, i);

    return tableOfNumbers;
}

Group *extendTableOfGroups(Group *table, unsigned int *length) {
    increase(length);
    table = realloc(table, *length * sizeof(*table));

    return table;
}

Group *addNewGroup(Group *tableOfGroups, unsigned int *maxNumberOfGroups,
                   unsigned int *numberOfGroups, Group input) {
    if (*numberOfGroups == *maxNumberOfGroups) {
        tableOfGroups = extendTableOfGroups(tableOfGroups, maxNumberOfGroups);
    }

    tableOfGroups[*numberOfGroups] = input;
    (*numberOfGroups)++;

    return tableOfGroups;
}

int *extendTableOfIntegers(int *table, unsigned int *length) {
    increase(length);
    table = realloc(table, *length * sizeof(*table));

    return table;
}

// dodaje nowy indeks linii do grupy
int *addNewLineIndex(int* tableOfLineIndices, unsigned int *maxNumberOfLines,
                     unsigned int *numberOfLines, int input) {
    if (*numberOfLines == *maxNumberOfLines) {
        tableOfLineIndices = extendTableOfIntegers(tableOfLineIndices,
                                                   maxNumberOfLines);
    }

    tableOfLineIndices[*numberOfLines] = input;
    (*numberOfLines)++;

    return tableOfLineIndices;
}

void freeLine(Line lineToFree) {
    free(lineToFree.tableOfNumbers);
    free(lineToFree.tableOfNaNs);
    free(lineToFree.lineChars);
}

// zwalnia pamięć po grupach
void freeGroups(unsigned int numberOfGroups, Group* tableOfGroups) {
    for (unsigned int i = 0; i < numberOfGroups; i++) {
        freeLine(tableOfGroups[i].sample);
        free(tableOfGroups[i].tableOfLineIndices);
    }
    free(tableOfGroups);
}


// tworzy nowe słowo na podstawie danych
Word createNewWord(char *tableOfChars, unsigned int wordLength) {
    Word newWord;
    newWord.tableOfChars = tableOfChars;
    newWord.wordLength = wordLength;

    return newWord;
}

void *secureMalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        exit(1);
    }

    return ptr;
}