/* 
 * markov_chain.c
 * Generate sentences using a markov chain
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "nouns.h"
#include "verbs.h"
#include "connectives.h"

static const int FOREVER = 1;

struct state {
    struct state *nxt[2];
    float prob[2];
    void (*function)(void);
};

void state1function(void);
void state2function(void);
void state3function(void);
void state4function(void);
struct state * chaindecision(struct state *current);

int main(void)
{
    struct state state1;
    struct state state2;
    struct state state3;
    struct state state4;
    struct state *tmpstate;
    
    state1.nxt[0] = &state2;
    state1.nxt[1] = &state3;
    state1.prob[0] = 0.70;
    state1.prob[1] = 0.30;
    state1.function = &state1function;
    
    state2.nxt[0] = &state3;
    state2.nxt[1] = &state4;
    state2.prob[0] = 0.5;
    state2.prob[1] = 0.5;
    state2.function = &state2function;
    
    state3.nxt[0] = &state1;
    state3.nxt[1] = &state2;
    state3.prob[0] = 0.8;
    state3.prob[1] = 0.2;
    state3.function = &state3function;
    
    state4.nxt[0] = &state1;
    state4.nxt[1] = &state2;
    state4.prob[0] = 0.95;
    state4.prob[1] = 0.05;
    state4.function = &state4function;
    
    tmpstate = &state1;
    
    srand(time(NULL));
    
	for (int i = 0; i <= 10; i++) {
        tmpstate->function();
        tmpstate = chaindecision(tmpstate);
    }
    while(FOREVER);
	return 0;
}

/*
 * Use cumulative probability to choose next state
 */
struct state *chaindecision(struct state *current)
{
    float cumulative = 0;
    float prob = (float)rand() / (float)RAND_MAX;
    
    for (int i = 0; i <= 2; i++) {
        cumulative += current->prob[i];
        if (prob <= cumulative)
            return current->nxt[i];
    }
    
    printf("chaindecision error!!!");
    return NULL;
}

void state1function(void)
{
    printf("%s ", getverb());
}

void state2function(void)
{
    printf("%s ", getnoun());
}

void state3function(void)
{
    printf(".\n");
}

void state4function(void)
{
    printf("%s ", getconnective());
}