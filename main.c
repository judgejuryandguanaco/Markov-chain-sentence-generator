/* 
 * markov_chain.c
 * Generate sentences using a markov chain
 * 
 * Bigram generator currently works, don't know how it handles new lines
 * Converting the bigrams to markov chain states is quite tricky, worth 
 * trying to think about the design a lot more before it becomes confusing!!
 * Maybe put the bigram generator in one library and the markov chain in
 * another?
 * 
 * Trouble in analysebigrams() at i = 4, j = 667, line 402
 * Not sure what's going on yet
 * 
 * The bigram generator skips the last line of an input file
 * 3. Get text from other sources (reddit? 4chan?)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

/*
#include "nouns.h"
#include "verbs.h"
#include "connectives.h"
#include "adverbs.h"

#define NOUNS 0
#define VERBS 1
#define ADJECTIVES 2
#define CONNECTIVES 3
#define FULLSTOP 4
#define ADVERBS 5
*/
static const int FOREVER = 1;

struct _dstates {
    struct _dstate **dstates;
    int size;
};

struct _dstate {
    struct _dstate **nxt;
    unsigned long size;
    float *prob;
    const char *(*function)(void);
    char *str;
    int strsiz;
};

struct _bigrams {
    struct _bigram **bigrams;
    int size;
};

struct _bigram {
    char* str1;
    char* str2;
    int instances;
};

struct _dstate *chaindecision(const struct _dstate *current);
const char *getfullstop(void);
struct _dstate *addnode(const char *(*function)(void));
void addnextstate(struct _dstate *state, struct _dstate *nxt,
                  float prob);
struct _bigram *newbigram(struct _bigrams *bigrams, const char* str1, 
                            const char* str2);
void newinstance(struct _bigram *bigram);
struct _bigrams *analysecorpus(const char* filename);
float getprob(struct _dstate *state);
struct _bigrams *newbigrams(void);
void addbigrams(struct _bigrams *bigrams, struct _bigram *bigram);
bool isadded(const struct _bigrams *bigrams, const char *str1, const char *str2);
struct _bigram *getbigram(struct _bigrams* bigrams, const char *str1, 
                        const char *str2);
struct _dstates *analysebigrams(struct _bigrams *bigrams);
bool isstate(const struct _dstates *dstates, const char *str1);
struct _dstate *getdstate(const struct _dstates *dstates, 
                                const char *str1);
                                
/*
 * main()
 */
int main(int size)
{
    struct _dstate *tmpstate;
    struct _dstates *dstates = malloc(sizeof(*dstates));
    struct _bigrams *bigrams = NULL;
    char *filename = "corpus.txt";
    srand(time(NULL));
    /*
    states[NOUNS] = addnode(&getnoun);
    states[VERBS] = addnode(&getverb);
    states[ADVERBS] = addnode(&getadverb);
    states[CONNECTIVES] = addnode(&getconnective);
    states[FULLSTOP] = addnode(&getfullstop);
    addnextstate(states[NOUNS], states[VERBS], 0.4);
    addnextstate(states[NOUNS], states[ADVERBS], 0.3);
    addnextstate(states[NOUNS], states[CONNECTIVES], 0.1);
    addnextstate(states[ADVERBS], states[VERBS], 1);
    addnextstate(states[VERBS], states[CONNECTIVES], 0.7);
    addnextstate(states[VERBS], states[FULLSTOP], 0.3);
    addnextstate(states[CONNECTIVES], states[NOUNS], 0.5);
    addnextstate(states[CONNECTIVES], states[ADVERBS], 0.5);
    addnextstate(states[FULLSTOP], states[NOUNS], 0.5);
    addnextstate(states[FULLSTOP], states[VERBS], 0.5);
    tmpstate = states[NOUNS];
    for (int i = 0; i <= 30; i++)
    {
        printf("%s ", tmpstate->function());
        tmpstate =  chaindecision(tmpstate);
    }
     */
    bigrams = analysecorpus(filename);
    dstates = analysebigrams(bigrams);
    
    tmpstate = dstates->dstates[0];
    
    for (int i = 0; i <= 300; i++) {
        printf("%s ", tmpstate->str);
        tmpstate = chaindecision(tmpstate);
    }
    while(FOREVER);
	return 0;
}

/*
 * *dchaindecision()
 * Make a chain decision, return the address of the next state
 */
struct _dstate *chaindecision(const struct _dstate *current)
{
    float cum = 0;
    float prob = (float)rand() / (float)RAND_MAX;
    for (int i = 0; i <= current->size; i++) {
        cum += current->prob[i];
        if (prob <= cum)
            return current->nxt[i];
    }
    return NULL;
}

/*
 * getfullstop()
 */
const char *getfullstop(void)
{
    return ".";
}

/*
 * addnode()
 * Add a node (?) to the markov chain
 */
struct _dstate *addnode(const char *(*function)(void))
{
    struct _dstate *dstate = malloc(sizeof(*dstate));
    dstate->size = 1;
    dstate->function = NULL;
    return dstate;
}

void addstate(struct _dstates *dstates, const char *str1)
{
    struct _dstate *dstate = malloc(sizeof(*dstate));
    dstate->strsiz = sizeof(str1);
    if(dstate == NULL)
        printf("addstate: dstate == NULL!\n");
    dstate->size = 1;
    dstate->function = NULL;
    dstate->str = malloc(sizeof(str1) + 1);
    strcpy(dstate->str, str1);
    dstates->size++;
    dstates->dstates = realloc(dstates->dstates, 
                                    sizeof(*dstates->dstates) * dstates->size);
    dstates->dstates[dstates->size - 1] = dstate;
    return;
}

void linkstates(const struct _dstates *dstates, const char* str1, 
                const char* str2, const float prob)
{
    struct _dstate *state = getdstate(dstates, str1);
    struct _dstate *nxt = getdstate(dstates, str2);
    addnextstate(state, nxt, prob);
    return;
}
/*
 * addnextstate()
 * 
 */
void addnextstate(struct _dstate *state, struct _dstate *nxt,
                  float prob)
{
    if(state->size == 1) {
        state->nxt = malloc(sizeof(state->nxt) * state->size);
        state->prob = malloc(sizeof(state->prob) * state->size);
    } else {
        if ((getprob(state) + prob) > 1) {
        printf("New probability would be greater than 1.\n");
        return;
        }
        state->nxt = realloc(state->nxt, sizeof(state->nxt) * state->size);
        state->prob = realloc(state->prob, sizeof(state->prob) * state->size);
    }
    state->nxt[state->size - 1] = nxt;
    state->prob[state->size - 1] = prob;
    state->size += 1;
    return;
}

/*
 * newbigram()
 */
struct _bigram *newbigram(struct _bigrams *bigrams, const char* str1, 
                            const char* str2)
{
    struct _bigram *bigram = malloc(sizeof(*bigram));
    bigram->str1 = malloc(sizeof(str1) + 1);
    bigram->str2 = malloc(sizeof(str2) + 1);
    strcpy(bigram->str1, str1);
    strcpy(bigram->str2, str2);
    bigram->instances = 1;
    addbigrams(bigrams, bigram);
    printf("New bigram! str1 = %s, str2 = %s\n", str1, str2);
    return bigram;
}

void newinstance(struct _bigram *bigram)
{
    bigram->instances += 1;
    printf("New instance of pair %s %s, %i\n", bigram->str1, bigram->str2,
            bigram->instances);
    return;
}

/*
 * analysecorpus()
 * For each word/grammar pair in a corpus, create a new bigram and count
 * the number of instances.
 * 
 * The longest a line can be is 200 chars
 * 
 * Returns the location of the bigrams
 */
struct _bigrams *analysecorpus(const char* filename)
{
    struct _bigrams *bigrams = newbigrams();
    FILE* file = fopen(filename, "r");
    char ptr[700];
    char str1[50];
    char str2[50];
    char *tmp;
    bool isEOF = false;
    printf("gets(ptr)\n");
    fgets(ptr, 600, file);
    printf("%s\n\n", ptr);
    printf("str1 = strtok(ptr, " ");\n");
    strcpy(str1, strtok(ptr, " \n"));
    printf("str2 = strtok(ptr, " ");\n");
    strcpy(str2, strtok(NULL, " \n"));
    
    printf("Analysing corpus\n");
    do {
        if (feof(file)) {
            isEOF = true;
        } else if(!isEOF) {
            printf("Checking... %s %s\n", str1, str2);
            //printf("tmp = %s\nptr = %s\n", tmp, ptr);
            if (isadded(bigrams, str1, str2))
                newinstance(getbigram(bigrams, str1, str2));
            else
                newbigram(bigrams, str1, str2);
            strcpy(str1, str2);
            tmp = strtok(NULL, " \n");
            while (tmp == NULL) {
                fgets(ptr, 700, file);
                tmp = strtok(ptr, " \n");
            }
            strcpy(str2, tmp);
        }
    } while (!isEOF);
    
    return bigrams;
}

/*
 * getprob()
 */
float getprob(struct _dstate *state)
{
    float prob = 0;
    for (int i = 0; i < state->size; i++) {
        prob += state->prob[i];
    }
    return prob;
}

/*
 * newdstates
 * Creates a new dstructs object and returns its address
 */
struct _dstates *newdstates(void)
{
    struct _dstates *dstates = malloc(sizeof(*dstates));
    dstates->size = 0;
    dstates->dstates = NULL;
    return dstates;
}

/* 
 * newbigrams()
 */
struct _bigrams *newbigrams(void)
{
    struct _bigrams *bigrams = malloc(sizeof(*bigrams));
    bigrams->size = 0;
    return bigrams;
}

/*
 * addbigrams()
 */
void addbigrams(struct _bigrams *bigrams, struct _bigram *bigram)
{
    if(bigrams->size == 0) {
        bigrams->size = 1;
        bigrams->bigrams = malloc(sizeof(*bigrams->bigrams));
    } else {
        bigrams->size += 1;
        bigrams->bigrams = realloc(bigrams->bigrams, 
                                    sizeof(*bigrams->bigrams) * bigrams->size);
    }
    bigrams->bigrams[bigrams->size - 1] = bigram;
}

/*
 * isadded()
 */
bool isadded(const struct _bigrams *bigrams, const char *str1, const char *str2)
{
    bool isadded = false;
    for (int i = 0; i < bigrams->size; i++) {
        if (strcmp(bigrams->bigrams[i]->str1, str1) == 0 &&
            strcmp(bigrams->bigrams[i]->str2, str2) == 0)
            isadded = true;
    }

    return isadded;
}

struct _bigram *getbigram(struct _bigrams* bigrams, const char *str1, 
                        const char *str2)
{
    int i = 0;
    bool isbigram = false;
    while(!isbigram) {
        if (strcmp(bigrams->bigrams[i]->str1, str1) == 0 && 
            strcmp(bigrams->bigrams[i]->str2, str2) == 0)
                isbigram = true;
        i++;
    }
    return bigrams->bigrams[i];
}

/* 
 * analysebigrams
 * Take bigrams and turn these into a set of markov chain
 * states
 */
struct _dstates *analysebigrams(struct _bigrams *bigrams)
{
    struct _dstates *dstates = newdstates();
    /* For each unique str1, create a markov state */
    for (int i = 0; i < bigrams->size; i++) {
        if(!isstate(dstates, bigrams->bigrams[i]->str1)) {
            addstate(dstates, bigrams->bigrams[i]->str1);
            printf("New state %s, %i\n", bigrams->bigrams[i]->str1, dstates->size);
        }
        if(!isstate(dstates, bigrams->bigrams[i]->str2)) {
            addstate(dstates, bigrams->bigrams[i]->str2);
            if (dstates->size == 5)
                printf("New state %s, %i\n", bigrams->bigrams[i]->str2, dstates->size);
        }
    }
    
    /* 
     * For each markov state, identify each unique next state,
     * track number of occurences, and then calculate probability
     */
    for (int i = 0; i < dstates->size; i++) {
        char *str2[50];
        int occurrence[50];
        int totaloccurrence = 0;
        int size = 0;
        /* Cycle through bigrams to find those relevant to specific state */
        for (int j = 0; j < bigrams->size; j++) {
            /* Find bigrams for specific string */
            struct _dstate *dstate = dstates->dstates[i];
            struct _bigram *bigram = bigrams->bigrams[j];
            if (strcmp(dstates->dstates[i]->str, bigrams->bigrams[j]->str1) == 0) {
                str2[size] = bigrams->bigrams[j]->str2;
                occurrence[size] = bigrams->bigrams[j]->instances;
                totaloccurrence += occurrence[size];
                size++;
            }
        }
        /* For all of the strings and probs, create a new markov chain link */
        for (int j = 0; j < size; j++) {
            float probability = (float)occurrence[j] / (float)totaloccurrence;
            printf("New link, %s to %s, %f\n", dstates->dstates[i]->str,
                    str2[j], probability);
            linkstates(dstates, dstates->dstates[i]->str, str2[j], probability);
        }
    }
    /* If a state has no next states, */
    return dstates;
}


/* 
 * isstate()
 */
bool isstate(const struct _dstates *dstates, const char *str1)
{
    for (int i = 0; i < dstates->size; i++) {
        if (strcmp(dstates->dstates[i]->str, str1) == 0)
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
bool isnxtstate(const struct _dstate *state, const char *str2)
{
    for (int i = 0; i < state->size; i++) {
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
struct _dstate *getdstate(const struct _dstates *dstates, const char *str)
{
    for(int i = 0; i < dstates->size; i++) {
        if (strcmp(dstates->dstates[i]->str, str) == 0)
            return dstates->dstates[i];
    }
    return NULL;
}