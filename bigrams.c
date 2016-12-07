#include <stdlib.h>
#include <string.h>

#include "bigrams.h"

struct _bgrm *newbgrm(struct _bgrmset *bgrmset, const char* str1, 
                            const char* str2)
{
    struct _bgrm *bgrm = malloc(sizeof(*bgrm));
    bgrm->str1 = malloc(strlen(str1) + 1);
    bgrm->str2 = malloc(strlen(str2) + 1);
    strcpy(bgrm->str1, str1);
    strcpy(bgrm->str2, str2);
    bgrm->n = 1;
    addbgrm(bgrmset, bgrm);
    return bgrm;
}

void freebgrm(struct _bgrm *bgrm)
{
    memset(bgrm->str1, 0, strlen(bgrm->str1));
    free(bgrm->str1);
    bgrm->str1 = NULL;
    memset(bgrm->str2, 0, strlen(bgrm->str2));
    free(bgrm->str2);
    bgrm->str2 = NULL;
    free(bgrm);
    bgrm = NULL;
    return;
}

struct _bgrmset *newbgrmset(void)
{
    struct _bgrmset *bgrmset = malloc(sizeof(*bgrmset));
    bgrmset->n = 0;
    return bgrmset;
}

void freebgrmset(struct _bgrmset *bgrmset)
{
    for (int i = 0; i < bgrmset->n; i++) {
        freebgrm(bgrmset->bgrm[i]);
    }
    free(bgrmset);
    return;
}

void addbgrm(struct _bgrmset *bgrmset, struct _bgrm *bgrm)
{
    if(bgrmset->n == 0) {
        bgrmset->n = 1;
        bgrmset->bgrm = malloc(sizeof(*bgrmset->bgrm));
    } else {
        bgrmset->n++;
        bgrmset->bgrm = realloc(bgrmset->bgrm, 
                            sizeof(*bgrmset->bgrm) * bgrmset->n);
    }
    bgrmset->bgrm[bgrmset->n - 1] = bgrm;
    return;
}

bool isadded(const struct _bgrmset *bgrmset, const char *str1, const char *str2)
{
    bool isadded = false;
    for (int i = 0; i < bgrmset->n; i++) {
        struct _bgrm *bgrm = bgrmset->bgrm[i];
        if (isbgrm(bgrm, str1, str2))
            isadded = true;
    }

    return isadded;
}

struct _bgrm *getbgrm(struct _bgrmset* bgrmset, const char *str1, 
                        const char *str2)
{
    int i = 0;
    struct _bgrm *bgrm = bgrmset->bgrm[i];
    while(!isbgrm(bgrm, str1, str2)) {
        bgrm = bgrmset->bgrm[i];
        i++;
    }
    return bgrmset->bgrm[i];
}

bool isbgrm(const struct _bgrm *bgrm, const char *str1, const char *str2)
{
    bool str1eq = false;
    bool str2eq = false;
    if (strcmp(bgrm->str1, str1) == 0)
        str1eq = true;
    if (strcmp(bgrm->str2, str2) == 0)
        str2eq = true;
    return str1eq && str2eq ? true : false;
}