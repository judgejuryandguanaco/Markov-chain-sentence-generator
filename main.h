/**
 *
 */

/**
 * @brief 
 * @return 
 */
int main(void);
/**
 * @brief 
 * @param filename
 * @return Set of bigrams corresponding to corpus
 */
struct _bgrmset *analysecorpus(const char* filename);
/**
 * @brief 
 * @param bgrmset Set of bigrams to turn into a Markov chain
 * @return Set of Markov states corresponding to bigrams
 */
struct _mkvset *analysebigrams(struct _bgrmset *bgrmset);