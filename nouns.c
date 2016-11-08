#include <stdlib.h>
#include <stdio.h>

#include "nouns.h"

static const char* n1 = "banana";
static const char* n2 = "lemur";
static const char* n3 = "gorilla";

const char *getnoun(void)
{
    char const *nouns[] = { n1, n2, n3 };
    unsigned int size = sizeof(nouns) / sizeof(char*);
    float cumprob = 1/(float)size;
    float cumulative = 0;
    float prob = (float)rand() / (float)RAND_MAX;
    
    for (int i = 0; i <= size; i++) {
        cumulative += cumprob;
        if (prob <= cumulative)
            return nouns[i];
    }
    
    printf("error in getnoun");
    return NULL;
}