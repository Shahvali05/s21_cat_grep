#include <stdio.h>
#include <string.h>

void notKeys(FILE* file, char ch);
void keys(char* argv[], const int i, int* count, char key, char* old_number);
void keyB(FILE* file, char ch, int* count, char* old_number);
void keyN(FILE* file, char ch, int* const, char* old_number);
void keyS(FILE* file, char ch);
void keyV(FILE* file, int show_tabs, int ch);
void keyDefinition(char* argv[], int argc, char* key, int* id_key);