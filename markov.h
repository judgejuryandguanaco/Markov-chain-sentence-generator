/*
 * markov.h
 */

#include <stdbool.h>

/**
 * @brief Container for set of Markov chain states 
 */
struct _mkvset {
    /** Dynamic array containing mkvstate pointers 
     */
    struct _mkvstate **state;
    /** Number of pointers in array 
     */
    int n;
} mkvset;

/**
 * @brief Markov chain state, including text string, address of next states,
 *          and probabilities
 */
struct _mkvstate {
    /** Dynamic array containing pointers to linked states 
     */
    struct _mkvstate **nxt;
    /** Number of linked states
     */
    int n;
    /** Dynamic array containing probabilities for each linked state
      * These are expressed in %'s and should never add up to more than 1
      */ 
    float *prob;
    /** The unique string the state represents
     */
    char *str;
    /** WIP - Word type, eg noun, punctuation, verb...
     */
    int typ;
} mkvstate;

/**
 */
enum { gramm, pnoun, noun, adj, pron } words;

/**
 * @brief Use cumulative probability to choose next Markov state
 * @param state The Markov state you want to branch from
 * @return The address of the next Markov state
 */
struct _mkvstate *chaindecision(const struct _mkvstate *state);
/**
 * @brief Create a new Markov state
 * @return Address of new Markov state
 */
struct _mkvstate *newnode(void);
/**
 * @brief Add Markov state to state set
 * @param set The collection of Markov states
 * @param str1 String of state
 */
void addstate(struct _mkvset *set, const char *str1);
/**
 * @brief Clear the contents of a Markov state, and free the memory
 * @param state Markov state to be cleared
 */
void freemkvstate(struct _mkvstate *state);
/**
 * @brief Link two states together, and assign probability. Must belong to same
 *          set
 * @param set The set the states belong to
 * @param str1 UID of first state
 * @param str2 UID of seconf state
 * @param prob Probability of going from state 1 to state2
 */
void linkstates(const struct _mkvset *set, const char* str1, const char* str2,
                const float prob);
/**
 * @brief 
 * @param state
 * @param nxt
 * @param prob
 */
void addnextstate(struct _mkvstate *state, struct _mkvstate *nxt, float prob);
/**
 * @brief Check if state belongs to set
 * @param set The set you want to search through
 * @param str1 UID of state you're looking for
 * @return True if exists in set, otherwise false
 */
bool isstate(const struct _mkvset *set, const char *str1);
/**
 * @brief Check if state links to other state
 * @param state The state you want to search through
 * @param str2 
 * @return 
 */
bool isnxtstate(const struct _mkvstate *state, const char *str2);
/**
 * @brief Get address of Markov state
 * @param set The set the state belongs to
 * @param str State UID
 * @return Address of state if exists, otherwise NULL
 */
struct _mkvstate *getmkvstate(const struct _mkvset *set, const char *str);
/**
 * @brief Create new container for Markov state set, and allocate memory
 * @return Address of new state
 */
struct _mkvset *newmkvset(void);
/**
 * @brief 
 * @param set
 */
void freemkvset(struct _mkvset *set);
/**
 * @brief 
 * @param state
 */
float getprob(struct _mkvstate *state);