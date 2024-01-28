#include <stdio.h>

#define True 1
#define False 0

int file_test(char* argv[]) {
  char ch_1 = 'a', ch_2 = 'a';
  int f_1 = 1, f_2 = 1, res = True;
  FILE* file_1 = fopen(argv[2], "r");
  if (file_1 == NULL) {
    res = False;
  }
  FILE* file_2 = fopen(argv[3], "r");
  if (file_2 == NULL) {
    if (res == True) {
      fclose(file_1);
    }
    return False;
  }
  do {
    f_1 = (ch_1 = fgetc(file_1));
    f_2 = (ch_2 = fgetc(file_2));
    if (ch_1 != ch_2) {
      res = False;
    }
  } while (f_1 != EOF && f_2 != EOF);

  if (f_1 != EOF || f_2 != EOF) {
    res = False;
  }
  fclose(file_1);
  fclose(file_2);

  return res;
}

int main(int argc, char* argv[]) {
  if (argc < 4) {
    printf("n/a\n");
    return 1;
  }
  int test = file_test(argv);
  printf("Test \"%s\": ", argv[1]);
  if (test) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }

  return 0;
}