//
// Created by kuba on 30.08.2021.
//
#include "data_structures.h"
#include "input-output.h"
#include <stdlib.h>
#include <stdio.h>
#define DEFAULT_CHAR '*'

// czyta ciąg znaków aż do znaku końca linii bądź EOF i przekazuje dalej
char *readLine(unsigned int *LineLength) {
    unsigned int maxLineLength = STARTING_LINE_LENGTH;
    char *line = secureMalloc(maxLineLength * sizeof(*line));
    int input = getchar();
    if (input == 255) {
        input = DEFAULT_CHAR;
    }
    unsigned int i = 0;

    while ((char)input != END_OF_LINE && (char)input != EOF) {
        line = addNewChar(line, &maxLineLength, &i, (char)input);

        input = getchar();
        if (input == 255) {
            input = DEFAULT_CHAR;
        }
    }

    line = addNewChar(line, &maxLineLength, &i, END_OF_LINE);

    (*LineLength) = i;

    return line;
}


// wypisuje zawartość grup
void printGroups(unsigned int numberOfGroups, Group* tableOfGroups) {
    for (unsigned int i = 0; i < numberOfGroups; i++) {
        for (unsigned int j = 0; j < tableOfGroups[i].numberOfLines; j++) {
            if (j == tableOfGroups[i].numberOfLines - 1) {
                printf("%d\n", tableOfGroups[i].tableOfLineIndices[j]);
            } else {
                printf("%d ", tableOfGroups[i].tableOfLineIndices[j]);
            }
        }
    }
}

// sprawdza czy znak jest białym znakiem
bool isWhiteChar(char asciiValueOfChar) {
    if ((asciiValueOfChar >= BLANK_MIN_ASCII_VALUE && asciiValueOfChar <=
                                                      BLANK_MAX_ASCII_VALUE) ||
        asciiValueOfChar == SPACE) {
        return true;
    }

    return false;
}
// sprawdza czy znak należy do znaków słowa
bool isWordChar(char asciiValueOfChar) {
    if (asciiValueOfChar >= WORD_MIN_ASCII_VALUE && asciiValueOfChar <=
                                                    WORD_MAX_ASCII_VALUE) {
        return true;
    }

    return false;
}
// sprawdza czy znak jest wielką literą
bool isUppercaseChar(char asciiValueOfChar) {
    if (asciiValueOfChar >= UPPERCASE_MIN_ASCII_VALUE && asciiValueOfChar <=
    UPPERCASE_MAX_ASCII_VALUE) {
        return true;
    }

    return false;
}

bool wordStartsWithSign(char *word) {
    if (word[0] == PLUS || word[0] == MINUS) {
        return true;
    }

    return false;
}

bool wordStartsWithZero(char *word) {
    if (word[0] == ZERO_CHAR) {
        return true;
    }

    return false;
}

void makeAllCharsLowercase(char *line, unsigned int lineLength) {
    unsigned int i = 0;

    while (i < lineLength) {
        char asciiValueOfChar = line[i];

        if (isUppercaseChar(asciiValueOfChar)) {
            line[i] += UPPERCASE_TO_LOWERCASE;
        }

        i++;
    }
}
// sprawdza, czy w linii są niedozwolone znaki
bool lineIsCorrect(char *line, unsigned int length) {
    bool correct = true;
    unsigned int i = 0;

    while (correct && i < length) {
        char asciiValueOfChar = line[i];

        if (!(isWhiteChar(asciiValueOfChar) || isWordChar(asciiValueOfChar))) {
            correct = false;
        }

        i++;
    }

    return correct;
}
// sprawdza, czy program powinien ignorować linię
bool shouldIgnoreLine(char *line, unsigned int length) {
    bool ignore = true;
    unsigned int i = 0;

    if (line[i] == COMMENT_SIGN) {
        return ignore;
    }

    while (ignore && i < length) {
        char asciiValueOfChar = line[i];

        if (!isWhiteChar(asciiValueOfChar)) {
            ignore = false;
        }

        i++;
    }

    return ignore;
}

// znajduje indeks końca danego słowa w linii
unsigned int endOfWordIndex(char *line, unsigned int lineLength, unsigned
int startingIndex) {
    unsigned int i = startingIndex;
    bool found = false;

    while (!found && i < lineLength) {
        char asciiValueOfChar = line[i];

        if (isWhiteChar(asciiValueOfChar)) {
            found = true;
        }

        i++;
    }

    return i-1;
}

// wstawia znaki '\0' po każdym słowie, aby móc potem odczytać je funkcją
// strtoull lub strtold
// oraz przekazuje tablicę słów
Word *createStrings(char *line, unsigned int lineLength, unsigned int
*numberOfWords) {
    unsigned int maxWordTableLength = STARTING_WORD_TABLE_LENGTH;
    Word *wordTable = secureMalloc(maxWordTableLength * sizeof(*wordTable));
    unsigned int i = 0;
    *numberOfWords = 0;

    while (i < lineLength) {
        unsigned int j = endOfWordIndex(line, lineLength, i);
        unsigned int wordLength = j - i;
        line[j] = NUL_CHAR;

        if (wordLength != 0) {
            Word newWord = createNewWord(&line[i], wordLength);

            wordTable = addNewWord(wordTable, &maxWordTableLength,
                                   numberOfWords, newWord);
        }

        i = j;
        i++;
    }

    return wordTable;
}

// sprawdza czy słowo ma w sobie znak 'x'
bool wordWrittenInHex(char *word, unsigned int wordLength) {
    unsigned int i = 0;
    bool isAHex = false;

    while (!isAHex && i < wordLength) {
        char asciiValueOfChar = word[i];
        if (asciiValueOfChar == HEX_SPECIFIC_ASCII_VALUE) {
            isAHex = true;
        }

        i++;
    }

    return isAHex;
}

bool unsignedWordStartsWith0X(char *word, unsigned int wordLength) {
    if (wordLength >= 2) {
        return (word[0] == ZERO_CHAR && word[1] == HEX_SPECIFIC_ASCII_VALUE);
    } else {
        return false;
    }
}

bool signedWordStartsWith0X(char *word, unsigned int wordLength) {
    if (wordLength >= 3) {
        return (word[1] == ZERO_CHAR && word[2] == HEX_SPECIFIC_ASCII_VALUE);
    } else {
        return false;
    }
}

// sprawdza, czy w słowie znajduje się któraś z liter od 'a' do 'f'
bool wordCanBeSignedHex(char *word, unsigned int wordLength) {
    unsigned int i = 1;

    while (i < wordLength) {
        if (word[i] == 'a' || word[i] == 'b' || word[i] == 'c' || word[i] ==
        'd' || word[i] == 'e' || word[i] == 'f' ||
            word[i] == HEX_SPECIFIC_ASCII_VALUE) {
            return true;
        }

        i++;
    }

    return false;
}