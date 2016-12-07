/*
 * markov.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "markov.h"
#include "mitchstring.h"
 
/*
 * dchaindecision()
 * Use cumulative probability to determine next state.
 */
struct _mkvstate *chaindecision(const struct _mkvstate *state)
{
    float cum = 0;
    float prob = (float)rand() / (float)RAND_MAX;
    for (int i = 0; i <= state->n; i++) {
        cum += state->prob[i];
        if (prob <= cum)
            return state->nxt[i];
    }
    return NULL;
}

/*
 * addnode()
 * Add a node (?) to the markov chain
 */
struct _mkvstate *newnode(void)
{
    struct _mkvstate *state = malloc(sizeof(*state));
    state->n = 1;
    return state;
}

void addstate(struct _mkvset *set, const char *str1)
{
    struct _mkvstate *state = malloc(sizeof(*state));
    state->n = 0;
    state->str = malloc(strlen(str1) + 1);
    if(state->str == NULL)
        printf("addstate: dstate->str == NULL\n");
    strcpy(state->str, str1);
    state->typ = getwordtype(state->str);
    set->n++;
    set->state = realloc(set->state, sizeof(*set->state) * set->n);
    if(set->state == NULL)
        printf("addstate: dstates->dstates == NULL\n");
    set->state[set->n - 1] = state;
    return;
}

void freemkvstate(struct _mkvstate *state)
{
    memset(state->str, 0, strlen(state->str) + 1);
    state->n = 0;
    state->typ = na;
    free(state->str);
    state->str = NULL;
    free(state);
    state = NULL;
    return;
}

void linkstates(const struct _mkvset *set, const char* str1, 
                const char* str2, const float prob)
{
    struct _mkvstate *state = getmkvstate(set, str1);
    struct _mkvstate *nxt = getmkvstate(set, str2);
    addnextstate(state, nxt, prob);
    return;
}
/*
 * addnextstate()
 * 
 */
void addnextstate(struct _mkvstate *state, struct _mkvstate *nxt,
                  float prob)
{
    if(state->n == 0) {
        state->nxt = malloc(sizeof(state->nxt) * (state->n + 1));
        state->prob = malloc(sizeof(state->prob) * (state->n + 1));
    } else {
        if ((getprob(state) + prob) > 1.001) {
            printf("New probability would be greater than 1.");
            return;
        }
        state->nxt = realloc(state->nxt, sizeof(state->nxt) * (state->n + 1));
        state->prob = realloc(state->prob, sizeof(state->prob) * (state->n + 1));
    }
    state->nxt[state->n] = nxt;
    state->prob[state->n] = prob;
    state->n++;
    return;
}

/* 
 * isstate()
 */
bool isstate(const struct _mkvset *set, const char *str1)
{
    for (int i = 0; i < set->n; i++) {
        if (strcmp(set->state[i]->str, str1) == 0)
            return true;
    }
    return false;
}

/*
 * isnxtstate()
 * Cycle through nxt to find state with matching string.
 * Returns true is exists, false if not.
 * 
 * state: state to search through to find a matching next state
 * str2: string contained in target next state.
 * 
 * Returns true if exists, false if not.
 */
bool isnxtstate(const struct _mkvstate *state, const char *str2)
{
    for (int i = 0; i < state->n; i++) {
        if (strcmp(state->nxt[i]->str, str2) == 0)
            return true;
    }
    return false;
}

/* 
 * getdstate()
 * Cycle through all states contained in dstates unti find one with matching
 * UID, then return its address
 * 
 * dstates: collection of states to cycle through
 * str: string to find
 * 
 * Returns address if valid, NULL if doesn't exist.
 */
struct _mkvstate *getmkvstate(const struct _mkvset *set, const char *str)
{
    for(int i = 0; i < set->n; i++) {
        if (strcmp(set->state[i]->str, str) == 0)
            return set->state[i];
    }
    return NULL;
}

/*
 * newdstates
 * Creates a new dstructs object and returns its address
 */
struct _mkvset *newmkvset(void)
{
    struct _mkvset *set = malloc(sizeof(*set));
    set->n = 0;
    set->state = NULL;
    return set;
}

void freemkvset(struct _mkvset *set)
{
    for (int i = 0; i < set->n; i++) {
        freemkvstate(set->state[i]);
        set->state[i] = NULL;
    }
    free(set);
    return;
}

/*
 * getprob()
 */
float getprob(struct _mkvstate *state)
{
    float prob = 0;
    for (int i = 0; i < state->n; i++) {
        prob += state->prob[i];
    }
    return prob;
}
