#include <stdbool.h>

enum _wordtyp { grm, eos, pnn, na };

void *tolower(char *string);
void sentencecase(char *str);
bool isgrammar(char *str);
bool isendofsentence(char *str);
int getwordtype(char *str);