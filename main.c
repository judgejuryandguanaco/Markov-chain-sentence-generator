/* 
 * markov_chain.c
 * Generate sentences using a markov chain
 * 
 * Bigram generator currently works, don't know how it handles new lines
 * 
 * The bigram generator skips the last line of an input file
 * 3. Get text from other sources (reddit? 4chan?)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "markov.h"
#include "bigrams.h"
#include "mitchstring.h"

static const int FOREVER = 1;

/**
 * @brief 
 * @param size
 * @return 
 */
int main(void)
{
    struct _mkvstate *tmpstate;
    struct _mkvset *mkvset = malloc(sizeof(*mkvset));
    struct _bgrmset *bgrmset = NULL;
    char *filename = "corpus.txt";
    bool isnewsentence = true;
    char *tmpstr = malloc(sizeof(*tmpstr));
    srand(time(NULL));
    bgrmset = analysecorpus(filename);
    mkvset = analysebigrams(bgrmset);
    
    tmpstate = mkvset->state[0];
    
    for (int i = 0; i <= 100; i++) {
        tmpstr = realloc(tmpstr, sizeof(*tmpstr) * strlen(tmpstate->str) + 1);
        strcpy(tmpstr, tmpstate->str);
        if (isnewsentence == true)
            sentencecase(tmpstr);
        printf("%s", tmpstr);
        isnewsentence = isendofsentence(tmpstr);
        tmpstate = chaindecision(tmpstate);
        if (!(tmpstate->typ == grm || tmpstate->typ == eos))
            printf(" ");     
    }
    /* Finish the sentence */
    if (!(strcmp(tmpstate->str, ".") == 0)) {
        bool isend = false;
        while(isend == false) {
            tmpstr = realloc(tmpstr, sizeof(*tmpstr) * strlen(tmpstate->str) + 1);
            strcpy(tmpstr, tmpstate->str);
            printf("%s", tmpstr);
            isend = isendofsentence(tmpstr);
            tmpstate = chaindecision(tmpstate);
            if (!(tmpstate->typ == grm || tmpstate->typ == eos))
                printf(" ");     
        }
    }
    freemkvset(mkvset);
    freebgrmset(bgrmset);
    while(FOREVER);
	return 0;
}

struct _bgrmset *analysecorpus(const char* filename)
{
    struct _bgrmset *bgrmset = newbgrmset();
    FILE* file = fopen(filename, "r");
    char ptr[700];
    char str1[60];
    char str2[60];
    char *tmp = NULL;
    bool isEOF = false;
    
    /* Get the feeling the do loop could be much slicker */
    /* Look into this... eventually! */
    fgets(ptr, 600, file);
    strcpy(str1, strtok(ptr, " \n"));
    tolower(str1);
    strcpy(str2, strtok(NULL, " \n"));
    tolower(str2);
    do {
        if (feof(file)) {
            isEOF = true;
        } else if(!isEOF) {
            if (isadded(bgrmset, str1, str2))
                getbgrm(bgrmset, str1, str2)->n++;
            else {
                newbgrm(bgrmset, str1, str2);
            }
            strcpy(str1, str2);
            tmp = strtok(NULL, " \n");
            while (tmp == NULL) {
                fgets(ptr, 700, file);
                tmp = strtok(ptr, " \n");
            }
            strcpy(str2, tmp);
            tolower(str2);
        }
    } while (!isEOF);
    
    return bgrmset;
}

/* 
 * analysebigrams
 * Take bigrams and turn these into a set of markov chain
 * states
 */
struct _mkvset *analysebigrams(struct _bgrmset *bgrmset)
{
    struct _mkvset *mkvset = newmkvset();
    for (int i = 0; i < bgrmset->n; i++) {
        struct _bgrm *bgrm = bgrmset->bgrm[i];
        if(!isstate(mkvset, bgrm->str1)) {
            addstate(mkvset, bgrm->str1);
        } else if (!isstate(mkvset, bgrm->str2)) {
            addstate(mkvset, bgrm->str2);
        }
    }
    
    /* 
     * For each markov state, identify each unique next state,
     * track number of occurences, and then calculate probability
     */
    for (int i = 0; i < mkvset->n; i++) {
        char *str2[5000];
        float occurrence[5000];
        float totaloccurrence = 0;
        int size = 0;
        /* Cycle through bigrams to find those relevant to specific state */
        for (int j = 0; j < bgrmset->n; j++) {
            struct _bgrm *bgrm = bgrmset->bgrm[j];
            struct _mkvstate *state = mkvset->state[i];
            if (strcmp(state->str, bgrm->str1) == 0) {
                str2[size] = bgrm->str2;
                occurrence[size] = (float)bgrm->n;
                totaloccurrence += occurrence[size];
                size++;
            }
        }
        /* For all of the strings and probs, create a new markov chain link */
        for (int j = 0; j < size; j++) {
            struct _mkvstate *state = mkvset->state[i];
            float probability = occurrence[j] / totaloccurrence;
            linkstates(mkvset, state->str, str2[j], probability);
        }
    }
    /* If a state has no next states, */
    return mkvset;
}