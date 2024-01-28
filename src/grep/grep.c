#include "libs_grep.h"

#define MAX_FLAGS 10

// grep функция
int grep(char* flags, char files[MAX_FILES][MAX_FILES],
         char templates[MAX_TEMPLATES][MAX_TEMPLATES], int* len_files,
         int* len_templates, int dir);
void initGrepStruct(grep_struct* GREP, int len);

int main(int argc, char* argv[]) {
  char flags[MAX_FLAGS] = {'0'};
  char files[MAX_FILES][MAX_FILES];
  char templates[MAX_TEMPLATES][MAX_TEMPLATES];
  int len_flags = 0, len_files = 0, len_templates = 0, dir = 1;

  if (divisionOfArguments(argc, argv, flags, "eivclnhsfo", files, templates,
                          &len_flags, &len_files, &len_templates)) {
    if (!checkForOccurrence('s', flags)) {
      printf("n/a\n");
      return 1;
    }
  }

  for (int i = 1; i < argc; i++) {
    if (!strcmp(files[0], argv[i])) {
      dir = 0;
    }
  }

  grep(flags, files, templates, &len_files, &len_templates, dir);

  return 0;
}

int grep(char* const flags, char files[MAX_FILES][MAX_FILES],
         char templates[MAX_TEMPLATES][MAX_TEMPLATES], int* len_files,
         int* len_templates, int dir) {
  grep_struct* GREP = malloc(sizeof(grep_struct) * MAX_LINE_LENGTH);
  if (GREP == NULL) {
    return 1;
  }
  initGrepStruct(GREP, MAX_LINE_LENGTH);
  int len_GREP = 0, printf_file = 0, v = 0, c = 0, l = 0, s = 1, o = 0, h = 0,
      print_n = 0;
  repackForKeys(flags, &c, &v, &l, &print_n, &s, &o, &h);
  keyNotOrO(GREP, &len_GREP, files, *len_files, templates, *len_templates,
            &printf_file, flags, o, s);
  if (v) {
    keyV(GREP, len_GREP);
  }
  if (o && v) {
    ;
  } else if (l) {
    keyL(len_GREP, GREP, s);
  } else if (c) {
    keyC(GREP, len_GREP, len_files, dir, h, s);
  } else {
    printForKonsol(GREP, len_GREP, h, len_files, dir, print_n, s);
  }
  free(GREP);
  return 0;
}

void initGrepStruct(grep_struct* GREP, int len) {
  for (int i = 0; i < len; i++) {
    strcpy(GREP[i].file, "file");
    strcpy(GREP[i].line, "line");
    GREP[i].n = 0;
    GREP[i].print_file = 0;
    GREP[i].print_line = 0;
  }
}
