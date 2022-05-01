//
// Created by kuba on 30.08.2021.
//

#ifndef POPRAWKA_MAE_ZADANIE_INPUT_OUTPUT_H
#define POPRAWKA_MAE_ZADANIE_INPUT_OUTPUT_H
#define WORD_MIN_ASCII_VALUE 33
#define WORD_MAX_ASCII_VALUE 126
#define BLANK_MIN_ASCII_VALUE 9
#define BLANK_MAX_ASCII_VALUE 13
#define UPPERCASE_MIN_ASCII_VALUE 65
#define UPPERCASE_MAX_ASCII_VALUE 90
#define UPPERCASE_TO_LOWERCASE 32
#define END_OF_LINE '\n'
#define SPACE ' '
#define COMMENT_SIGN '#'
#define PLUS '+'
#define MINUS '-'
#define ZERO_CHAR '0'
#define NUL_CHAR '\0'
#define OCT 8
#define HEX 16
#define DEC 10
#define HEX_SPECIFIC_ASCII_VALUE 120
#include <stdbool.h>

// czyta ciąg znaków aż do znaku końca linii bądź EOF i przekazuje dalej
char *readLine(unsigned int *LineLength);

// wypisuje zawartość grup
void printGroups(unsigned int numberOfGroups, Group* tableOfGroups);

bool wordStartsWithSign(char *word);

bool wordStartsWithZero(char *word);

void makeAllCharsLowercase(char *line, unsigned int lineLength);

// sprawdza, czy w linii są niedozwolone znaki
bool lineIsCorrect(char *line, unsigned int length);

// sprawdza, czy program powinien ignorować linię
bool shouldIgnoreLine(char *line, unsigned int length);

// wstawia znaki '\0' po każdym słowie, aby móc potem odczytać je funkcją
// strtoull lub strtold
// oraz przekazuje tablicę słów
Word *createStrings(char *line, unsigned int lineLength, unsigned int
*numberOfWords);

// sprawdza czy słowo ma w sobie znak 'x'
bool wordWrittenInHex(char *word, unsigned int wordLength);

bool unsignedWordStartsWith0X(char *word, unsigned int wordLength);

bool signedWordStartsWith0X(char *word, unsigned int wordLength);

// sprawdza, czy w słowie znajduje się któraś z liter od 'a' do 'f'
bool wordCanBeSignedHex(char *word, unsigned int wordLength);

#endif //POPRAWKA_MAE_ZADANIE_INPUT_OUTPUT_H
