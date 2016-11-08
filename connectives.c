#include <stdio.h>
#include <stdlib.h>

#include "connectives.h"

const char *c1 = "and";
const char *c2 = "then";
const char *c3 = "but";

const char *getconnective(void)
{
    char const *connectives[] = { c1, c2, c3 };
    unsigned int size = sizeof(connectives) / sizeof(connectives[0]);
    float cumprob = 1/(float)size;
    float cumulative = 0;
    float prob = (float)rand() / (float)RAND_MAX;
    
    for (int i = 0; i <= size; i++) {
        cumulative += cumprob;
        if (prob <= cumulative)
            return connectives[i];
    }
    
    printf("error in getconnective");
    return NULL;
}