/*
 * mitchstring.c
 * 
 * Custom string stuff
 */
#include <string.h>

#include "mitchstring.h"
 
void *tolower(char *string)
{
    for(int i = 0; i < strlen(string); i++){
        switch(string[i]) {
        case 'A':
            string[i] = 'a';
            break;
        case 'B':
            string[i] = 'b';
            break;
        case 'C':
            string[i] = 'c';
            break;
        case 'D':
            string[i] = 'd';
            break;
        case 'E':
            string[i] = 'e';
            break;
        case 'F':
            string[i] = 'f';
            break;
        case 'G':
            string[i] = 'g';
            break;
        case 'H':
            string[i] = 'h';
            break;
        case 'I':
            string[i] = 'i';
            break;
        case 'J':
            string[i] = 'j';
            break;
        case 'K':
            string[i] = 'k';
            break;
        case 'L':
            string[i] = 'l';
            break;
        case 'M':
            string[i] = 'm';
            break;
        case 'N':
            string[i] = 'n';
            break;
        case 'O':
            string[i] = 'o';
            break;
        case 'P':
            string[i] = 'p';
            break;
        case 'Q':
            string[i] = 'q';
            break;
        case 'R':
            string[i] = 'r';
            break;
        case 'S':
            string[i] = 's';
            break;
        case 'T':
            string[i] = 't';
            break;
        case 'U':
            string[i] = 'u';
            break;
        case 'V':
            string[i] = 'v';
            break;
        case 'W':
            string[i] = 'w';
            break;
        case 'X':
            string[i] = 'x';
            break;
        case 'Y':
            string[i] = 'y';
            break;
        case 'Z':
            string[i] = 'z';
            break;
        default:
            break;
        }
    }
    return NULL;
}

void sentencecase(char *str)
{
    switch(str[0]) {
    case 'a':
        str[0] = 'A';
        break;
    case 'b':
        str[0] = 'B';
        break;
    case 'c':
        str[0] = 'C';
        break;
    case 'd':
        str[0] = 'D';
        break;
    case 'e':
        str[0] = 'E';
        break;
    case 'f':
        str[0] = 'F';
        break;
    case 'g':
        str[0] = 'G';
        break;
    case 'h':
        str[0] = 'H';
        break;
    case 'i':
        str[0] = 'I';
        break;
    case 'j':
        str[0] = 'J';
        break;
    case 'k':
        str[0] = 'K';
        break;
    case 'l':
        str[0] = 'L';
        break;
    case 'm':
        str[0] = 'M';
        break;
    case 'n':
        str[0] = 'N';
        break;
    case 'o':
        str[0] = 'O';
        break;
    case 'p':
        str[0] = 'P';
        break;
    case 'q':
        str[0] = 'Q';
        break;
    case 'r':
        str[0] = 'R';
        break;
    case 's':
        str[0] = 'S';
        break;
    case 't':
        str[0] = 'T';
        break;
    case 'u':
        str[0] = 'U';
        break;
    case 'v':
        str[0] = 'V';
        break;
    case 'w':
        str[0] = 'W';
        break;
    case 'x':
        str[0] = 'X';
        break;
    case 'y':
        str[0] = 'Y';
        break;
    case 'z':
        str[0] = 'Z';
        break;
    default:
        break;
    }
    return;
}

bool isgrammar(char *str)
{
    switch(*str) {
    case '.':
        return true;
    case ',':
        return true;
    case ';':
        return true;
    case ':':
        return true;
    case '?':
        return true;
    case '!':
        return true;
    default:
        return false;
    }
}

bool isendofsentence(char *str)
{
    switch(*str) {
    case '.':
        return true;
    case '!':
        return true;
    case '?':
        return true;
    default:
        return false;
    }
    return false;
}

/* 
 * gettype()
 * Returns the word type of str1
 */
int getwordtype(char *str)
{
    if (isgrammar(str)) {
        return grm;
    } else if (isendofsentence(str)) {
        return eos;
    } else {
        return na;
    }
}