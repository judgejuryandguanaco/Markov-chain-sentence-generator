#include <stdlib.h>
#include <stdio.h>

#include "verbs.h"

const char* v1 = "fellate";
const char* v2 = "appreciate";
const char* v3 = "consume";
const char* v4 = "battle";
const char* v5 = "lift";
const char* v6 = "drop";


const char *getverb(void)
{
    char const *verbs[] = { v1, v2, v3, v4, v5, v6 };
    unsigned int size = sizeof(verbs) / sizeof(verbs[0]);
    float cumprob = 1/(float)size;
    float cumulative = 0;
    float prob = (float)rand() / (float)RAND_MAX;
    
    for (int i = 0; i <= size; i++) {
        cumulative += cumprob;
        if (prob <= cumulative)
            return verbs[i];
    }
    
    printf("error in getverb");
    return NULL;
}