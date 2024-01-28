#include "libs_cat.h"

void keyDefinition(char* argv[], int argc, char* key, int* id_key) {
  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '-') {
      *id_key = i;
      if (!strcmp(argv[i], "--number-nonblank") || argv[i][1] == 'b') {
        *key = 'b';
      } else if (argv[i][1] == 'e' || argv[i][1] == 'E') {
        *key = 'e';
      } else if (!strcmp(argv[i], "--number") || argv[i][1] == 'n') {
        *key = 'n';
      } else if (!strcmp(argv[i], "--squeeze-blank") || argv[i][1] == 's') {
        *key = 's';
      } else if (argv[i][1] == 't' || argv[i][1] == 'T') {
        *key = 't';
      } else {
        *id_key = 0;
      }
      break;
    }
  }
}

void keys(char* argv[], const int i, int* count, char key, char* old_number) {
  char ch = ' ';
  FILE* file = fopen(argv[i], "r");
  if (file == NULL) {
    printf("n/a\n");
    return;
  }

  if (key == 'b') {
    keyB(file, ch, count, old_number);
  } else if (key == 'e') {
    keyV(file, 0, ch);
  } else if (key == 'n') {
    keyN(file, ch, count, old_number);
  } else if (key == 's') {
    keyS(file, ch);
  } else if (key == 't') {
    keyV(file, 1, ch);
  } else if (key == 0) {
    notKeys(file, ch);
  } else {
    printf("n/a\n");
  }
  fclose(file);
}

void keyS(FILE* file, char ch) {
  int chet = 0;

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      chet++;
    } else {
      chet = 0;
    }
    if (chet < 3) {
      putchar(ch);
    }
  }
}

void keyN(FILE* file, char ch, int* count, char* old_number) {
  int chet = 1;

  while ((ch = fgetc(file)) != EOF) {
    if (chet && *old_number == '\n') {
      printf("%6d\t", *count);
      *count += 1;
      chet = 0;
    }
    *old_number = ch;
    putchar(ch);
    if (ch == '\n') {
      chet = 1;
    }
  }
}

void keyV(FILE* file, int show_tabs, int ch) {
  while ((ch = fgetc(file)) != EOF) {
    if (ch >= 32) {
      if (ch < 127)
        printf("%c", ch);
      else if (ch == 127) {
        printf("^?");
      } else {
        printf("M-");
        if (ch >= 128 + 32) {
          if (ch < 128 + 127)
            printf("%c", ch - 128);
          else {
            printf("^?");
          }
        } else {
          printf("^");
          printf("%c", ch - 128 + 64);
        }
      }
    } else if (ch == '\t' && !show_tabs)
      printf("\t");
    else if (ch == '\n') {
      if (!show_tabs) {
        printf("$");
      }
      printf("\n");
    } else {
      printf("^%c", ch + 64);
    }
  }
}

void keyB(FILE* file, char ch, int* count, char* old_number) {
  int chet = 1;

  while ((ch = fgetc(file)) != EOF) {
    if (chet && ch != '\n' && *old_number == '\n') {
      printf("%6d\t", *count);
      *count += 1;
      chet = 0;
    }
    *old_number = ch;
    putchar(ch);
    if (ch == '\n') {
      chet = 1;
    }
  }
}

void notKeys(FILE* file, char ch) {
  while ((ch = fgetc(file)) != EOF) {
    putchar(ch);
  }
}