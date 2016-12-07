/*
 * bigrams.h
 */
 
#include <stdbool.h>

/**
 * @brief Container for a set of bigrams
 */
struct _bgrmset {
    struct _bgrm **bgrm; /**< Dynamic array containing pointers to bigrams*/
    int n; /**< Number of bigrams contained in bgrm */
};

/**
 * @brief A single bigram for text
 */
struct _bgrm {
    /** First string in the bigram */
    char* str1;
    /** Second string in the bigram */
    char* str2;
    /** Number of times bigram appears in corpus */
    int n;
};

/**
 * @brief Allocate memory for new bigram set
 * @return Address of new container for bigram set 
 */
struct _bgrmset *newbgrmset(void);
/**
 * @brief Allocate memory for new bigram, and assign its contents
 * @return Address of new bigram
 */
struct _bgrm *newbgrm(struct _bgrmset *bgrmset, const char* str1,
                        const char* str2);
/**
 * @brief Get address of bigram belonging to a set
 * @param bgrmset The bigram set you want to search
 * @param str1 First term of bigram you're looking for
 * @param str2 Second term of bigram you're looking for
 * @return The address of the bigram. Returns NULL if doesn't exist.
 */
struct _bgrm *getbgrm(struct _bgrmset* bgrmset, const char *str1,
                        const char *str2);
/**
 * @brief Check if bigram exists in set.
 * @param bgrmset The bigram set you want to search
 * @param str1 First term of bigram generator you're looking for
 * @param str2 Second term of bigram generator you're looking for
 * @return Returns true if exists, otherwise false
 */
bool isadded(const struct _bgrmset *bgrmset, const char *str1,
                const char *str2);
/**
 * @brief Check to see if this is the bigram you're looking for
 * @param bgrm The bigram to be inspected
 * @param str1 First term you're looking for
 * @param str2 Second term you're looking for
 * @return True if the same bigram, false if not
 */
bool isbgrm(const struct _bgrm *bgrm, const char *str1,
            const char *str2);
/**
 * @brief Add a bigram to a set
 * @param bgrmset The container for a bigram set
 * @param bgrm The bigram to be added to the set
 */
void addbgrm(struct _bgrmset *bgrmset, struct _bgrm *bgrm);
/**
 * @brief Free memory for a container for a bigram set, 
 *         and the bigrams contained within
 * @param bgrmset The set to be freed
 */
void freebgrmset(struct _bgrmset *bgrmset);
/**
 * @brief Free memory allocated to bigram and clear data
 * @param bgrm The bigram to be freed
 */
void freebgrm(struct _bgrm *bgrm);