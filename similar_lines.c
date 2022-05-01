//
// Created by kuba on 30.08.2021.
//

#include "similar_lines.h"
#include "data_structures.h"
#include "input-output.h"
#include <stdio.h>
#include <stdlib.h>

// sprawdza czy słowo zaczynające się znakiem '+' lub '-' jest liczbą
// szesnastkową lub dziesiętną
long double *processSignedWord(unsigned int *i, unsigned int
*maxTableOfNumbersLength, long double *tableOfNumbers, Word *tableOfWords,
                               unsigned int *tableOfNumbersLength, bool *proceedToFloatingPointNumbers,
                               unsigned int *tableOfWordsLength, unsigned long long *convertedFromWord) {
    char *testPointer;
    bool proceedToDec = false;
    long long signedConvertedFromWord;

    if (wordCanBeSignedHex(tableOfWords[*i].tableOfChars, tableOfWords[*i]
            .wordLength)) {
        *convertedFromWord = strtoull(&(tableOfWords[*i].tableOfChars[1]),
                                      &testPointer, HEX);

        if (*testPointer == NUL_CHAR) {
            if (signedWordStartsWith0X(tableOfWords[*i].tableOfChars,
                                       tableOfWords[*i].wordLength)) {
                (*i)++;
            } else {
                *proceedToFloatingPointNumbers = true;
            }
        } else {
            proceedToDec = true;
        }
    } else {
        proceedToDec = true;
    }
    if (proceedToDec) {
        signedConvertedFromWord = strtoll(tableOfWords[*i].tableOfChars,
                                          &testPointer, DEC);
        if (*testPointer == NUL_CHAR) {
            tableOfNumbers = addANumberAndDeleteWord(tableOfNumbers,
                                                     maxTableOfNumbersLength,
                                                     tableOfNumbersLength,
                                                     (long double)
                                                             signedConvertedFromWord,
                                                     tableOfWords,
                                                     tableOfWordsLength, *i);
        } else {
            *proceedToFloatingPointNumbers = true;
        }
    }

    return tableOfNumbers;
}

// sprawdza czy słowo niezaczynające się od znaku '+' ani '-' jest liczbą w
// systemie ósemkowym, dziesiętnym oraz szesnastkowym
long double *processUnsignedWord(unsigned int *i, unsigned int
*maxTableOfNumbersLength, long double *tableOfNumbers, Word *tableOfWords,
                                 unsigned int *tableOfNumbersLength, bool
                                 *proceedToFloatingPointNumbers,
                                 unsigned int *tableOfWordsLength) {
    bool proceedToDec = false;
    bool proceedToHex = false;
    char *testPointer;
    unsigned long long convertedFromWord;
    if (wordStartsWithZero(tableOfWords[*i].tableOfChars)) {
        convertedFromWord = strtoull(tableOfWords[*i].tableOfChars,
                                     &testPointer, OCT);

        if (*testPointer == NUL_CHAR) {
            tableOfNumbers = addANumberAndDeleteWord(tableOfNumbers,
                                                     maxTableOfNumbersLength,
                                                     tableOfNumbersLength,
                                                     (long double)
                                                             convertedFromWord,
                                                     tableOfWords,
                                                     tableOfWordsLength, *i);
        } else {
            proceedToDec = true;
        }
    } else {
        proceedToDec = true;
    }

    if (proceedToDec) {
        convertedFromWord = strtoull(tableOfWords[*i].tableOfChars,
                                     &testPointer, DEC);

        if (*testPointer == NUL_CHAR) {

            tableOfNumbers = addANumberAndDeleteWord(tableOfNumbers,
                                                     maxTableOfNumbersLength,
                                                     tableOfNumbersLength,
                                                     (long double)
                                                             convertedFromWord,
                                                     tableOfWords,
                                                     tableOfWordsLength, *i);
        } else {
            proceedToHex = true;
        }
    }

    if (proceedToHex) {
        if (unsignedWordStartsWith0X(tableOfWords[*i].tableOfChars,
                                     tableOfWords[*i].wordLength)) {
            convertedFromWord = strtoull(tableOfWords[*i].tableOfChars,
                                         &testPointer, HEX);

            if(*testPointer == NUL_CHAR) {
                tableOfNumbers = addANumberAndDeleteWord(tableOfNumbers,
                                                         maxTableOfNumbersLength,
                                                         tableOfNumbersLength,
                                                         (long double)
                                                                 convertedFromWord,
                                                         tableOfWords,
                                                         tableOfWordsLength,
                                                         *i);
            } else {
                *proceedToFloatingPointNumbers = true;
            }
        } else {
            *proceedToFloatingPointNumbers = true;
        }
    }

    return tableOfNumbers;
}

// usuwa z tablicy słów słowa będące liczbami i ich wartości zapisuje w tablicy
long double *separateNumbersAndNans(Word *tableOfWords, unsigned int
*tableOfWordsLength, unsigned int *tableOfNumbersLength) {
    unsigned int maxTableOfNumbersLength = STARTING_NUMBER_TABLE_LENGTH;
    long double *tableOfNumbers = secureMalloc(maxTableOfNumbersLength * sizeof
    (*tableOfNumbers));
    unsigned int i = 0;
    *tableOfNumbersLength = 0;
    unsigned long long convertedFromWord;

    while (i < *tableOfWordsLength) {
        char *testPointer;
        bool proceedToFloatingPointNumbers = false;

        if (wordStartsWithSign(tableOfWords[i].tableOfChars)) {

            tableOfNumbers = processSignedWord(&i, &maxTableOfNumbersLength,
                                               tableOfNumbers, tableOfWords,
                                               tableOfNumbersLength,
                                               &proceedToFloatingPointNumbers,
                                               tableOfWordsLength,
                                               &convertedFromWord);

        } else {

            tableOfNumbers = processUnsignedWord(&i, &maxTableOfNumbersLength,
                                                 tableOfNumbers, tableOfWords,
                                                 tableOfNumbersLength,
                                                 &proceedToFloatingPointNumbers,
                                                 tableOfWordsLength);
        }

        if (proceedToFloatingPointNumbers) {
            long double doubleConvertedFromWord = strtold(tableOfWords[i]
                                                                  .tableOfChars, &testPointer);

            if (*testPointer == NUL_CHAR && doubleConvertedFromWord ==
                                            doubleConvertedFromWord &&
                !wordWrittenInHex(tableOfWords[i].tableOfChars, tableOfWords[i]
                        .wordLength)) {

                tableOfNumbers = addANumberAndDeleteWord(tableOfNumbers,
                                                         &maxTableOfNumbersLength,
                                                         tableOfNumbersLength,
                                                         doubleConvertedFromWord,
                                                         tableOfWords,
                                                         tableOfWordsLength, i);
            } else {
                i++;
            }
        }
    }

    return tableOfNumbers;
}

int compareNumbers (const void * a, const void * b) {
    long double _a = *(long double*)a;
    long double _b = *(long double*)b;

    if (_a < _b) return -1;
    else if (_a == _b) return 0;
    else return 1;
}

// porównuje słowa najpierw według długości, a potem alfabetycznie
int compareNuns (const void * a, const void * b) {
    Word _a = *(Word*)a;
    Word _b = *(Word*)b;

    if (_a.wordLength < _b.wordLength) {
        return -1;
    } else if (_a.wordLength > _b.wordLength) {
        return 1;
    } else {
        unsigned int i = 0;

        while(i < _a.wordLength) {
            if (_a.tableOfChars[i] != _b.tableOfChars[i]) {
                if (_a.tableOfChars[i] < _b.tableOfChars[i]) {
                    return -1;
                } else {
                    return 1;
                }
            }

            i++;
        }

        return 0;
    }
}


// sprawdza czy nieliczby są identyczne
bool nansAreTheSame(char *nan1, unsigned int nan1Length, char *nan2,
                    unsigned int nan2Length) {
    if (nan1Length == nan2Length) {
        unsigned int i = 0;
        bool different = false;

        while (!different && i < nan1Length) {
            if (nan1[i] != nan2[i]) {
                different = true;
            }

            i++;
        }

        return !different;
    } else {
        return false;
    }
}

// sprawdza, czy linie mają takie same zbiory nieliczb
bool linesHaveTheSameNans(Line a, Line b) {
    if (a.tableOfNansLength == b.tableOfNansLength) {
        unsigned int i = 0;
        bool different = false;

        while (!different && i < a.tableOfNansLength) {
            if (!nansAreTheSame(a.tableOfNaNs[i].tableOfChars, a
                                        .tableOfNaNs[i].wordLength,
                                b.tableOfNaNs[i].tableOfChars, b
                                        .tableOfNaNs[i].wordLength)) {
                different = true;
            }

            i++;
        }

        return !different;
    } else {

        return false;
    }
}

// sprawdza czy linie mają takie same zbiory liczb
bool linesHaveTheSameNumbers(Line a, Line b) {
    if (a.tableOfNumbersLength == b.tableOfNumbersLength) {
        unsigned int i = 0;
        bool different = false;

        while (!different && i < a.tableOfNumbersLength) {
            if (a.tableOfNumbers[i] != b.tableOfNumbers[i]) {
                different = true;
            }

            i++;
        }

        return !different;
    } else {

        return false;
    }
}

// wczytuje z wejścia jedną linię i na podstawie tego czy jest komentarzem/
// zawiera nielegalne znaki/
// zawiera jakiekolwiek słowa uzupełnia odpowiednie pola w strukturze Line
Line processLine(int lineNumber) {
    Line newLine;
    unsigned int lineLength;
    char *line = readLine(&lineLength);
    newLine.NumberOfLine = lineNumber;

    makeAllCharsLowercase(line, lineLength);

    newLine.lineChars = line;

    if (!shouldIgnoreLine(line, lineLength)) {
        if (lineIsCorrect(line, lineLength)) {
            unsigned int numberOfWords = 0;
            Word *tableOfWords = createStrings(line, lineLength,&numberOfWords);

            if (numberOfWords > 0) {
                newLine.empty = false;
            } else {
                newLine.empty = true;
            }

            unsigned int tableOfNumbersLength;
            long double *tableOfNumbers =
                    separateNumbersAndNans(tableOfWords, &numberOfWords,
                                           &tableOfNumbersLength);

            qsort(tableOfNumbers, tableOfNumbersLength, sizeof(*tableOfNumbers),
            compareNumbers);
            qsort(tableOfWords, numberOfWords, sizeof(*tableOfWords),
                  compareNuns);

            newLine.tableOfNaNs = tableOfWords;
            newLine.tableOfNansLength = numberOfWords;
            newLine.tableOfNumbers = tableOfNumbers;
            newLine.tableOfNumbersLength = tableOfNumbersLength;

            if (newLine.empty) {
                free(newLine.tableOfNaNs);
                free(newLine.tableOfNumbers);
            }

        } else {
            newLine.empty = true;
            fprintf(stderr, "ERROR %d\n", lineNumber);
        }
    } else {
        newLine.empty = true;
    }

    if (newLine.empty) {
        free(newLine.lineChars);
    }

    return newLine;
}

bool linesAreSimilar(Line a, Line b) {

    return (linesHaveTheSameNumbers(a, b) && linesHaveTheSameNans(a, b));
}

// tworzy grupy na podstawie podobieństwa linii
Group* createGroups(unsigned int *numberOfGroups, Group* tableOfGroups,
                    unsigned int *maxNumberOfGroups) {
    int numberOfLine = 1;
    int test;//potrzebny tylko po to by sprawdzać EOF

    while ((test = getchar()) != EOF) {
        ungetc(test, stdin);
        Line newLine = processLine(numberOfLine);
        if (!newLine.empty) {
            unsigned int i = 0;
            bool ShouldAddNewGroup = true;

            while (ShouldAddNewGroup && i < *numberOfGroups) {
                if (linesAreSimilar(tableOfGroups[i].sample, newLine)) {
                    ShouldAddNewGroup = false;
                    tableOfGroups[i].tableOfLineIndices = addNewLineIndex
                            (tableOfGroups[i].tableOfLineIndices,
                             &tableOfGroups[i].maxNumberOfLines,
                             &tableOfGroups[i].numberOfLines,
                             newLine.NumberOfLine);
                    freeLine(newLine);
                }

                i++;
            }

            if (ShouldAddNewGroup) {
                Group newGroup;
                newGroup.maxNumberOfLines = STARTING_INT_TABLE_LENGTH;
                newGroup.numberOfLines = 1;
                newGroup.tableOfLineIndices = malloc(newGroup.maxNumberOfLines *
                        sizeof(*newGroup.tableOfLineIndices));
                newGroup.sample = newLine;
                newGroup.tableOfLineIndices[0] = newLine.NumberOfLine;

                tableOfGroups = addNewGroup(tableOfGroups, maxNumberOfGroups,
                                            numberOfGroups, newGroup);

            }
        }
        numberOfLine++;
    }

    return tableOfGroups;
}

void similar_lines() {
    unsigned int maxNumberOfGroups = STARTING_GROUP_TABLE_LENGTH;
    Group *tableOfGroups = secureMalloc(maxNumberOfGroups * sizeof
            (*tableOfGroups));
    unsigned int numberOfGroups = 0;

    tableOfGroups = createGroups(&numberOfGroups, tableOfGroups,
                                 &maxNumberOfGroups);

    printGroups(numberOfGroups, tableOfGroups);

    freeGroups(numberOfGroups, tableOfGroups);
}