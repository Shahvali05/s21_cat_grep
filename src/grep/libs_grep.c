#include "libs_grep.h"

#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void listFiles(const char* baseDir, const char* dir,
               char files[MAX_FILES][MAX_FILES], int* len_files) {
  DIR* dp;
  struct dirent* entry;
  struct stat statbuf;

  // Открытие директории
  if ((dp = opendir(dir)) == NULL) {
    perror("Ошибка открытия директории");
    return;
  }

  // Переход по всем элементам в директории
  while ((entry = readdir(dp)) != NULL) {
    // Создание полного пути для текущего элемента
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

    // Получение информации о файле
    if (lstat(path, &statbuf) == -1) {
      perror("Ошибка получения информации о файле");
      continue;
    }

    // Рекурсивный вызов для поддиректорий
    if (S_ISDIR(statbuf.st_mode)) {
      if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
        listFiles(baseDir, path, files, len_files);
      }
    } else {
      // Вывод относительного пути к файлу
      // strcpy(files[*len_files], path + strlen(baseDir) + 1);
      strcpy(files[*len_files], strdup(path));
      *len_files += 1;
    }
  }

  // Закрытие директории
  closedir(dp);
}

void toLower(char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] = str[i] + 32;
    }
  }
}

int divisionOfArguments(int argc, char* argv[], char* flags, char* valid_flags,
                        char files[MAX_FILES][MAX_FILES],
                        char templates[MAX_TEMPLATES][MAX_TEMPLATES],
                        int* len_flags, int* len_files, int* len_templates) {
  int error = 0, len_files_for_f = 0, e = -1;
  char files_for_f[MAX_FILES][MAX_FILES];
  for (int i = 1; i < argc; i++) {
    if (argv[i - 1][0] == '-' && checkForOccurrence('e', argv[i - 1]) &&
        e != i - 1) {
      strcpy(templates[*len_templates], argv[i]);
      *len_templates += 1;
      e = i;
    } else if (argv[i - 1][0] == '-' && checkForOccurrence('f', argv[i - 1]) &&
               e != i - 1) {
      if (getMatchingFiles(argv[i], &len_files_for_f, files_for_f)) {
        error = 1;
      }
      for (int id = 0; id < len_files_for_f; id++) {
        if (keyF(files_for_f[id], templates, len_templates)) {
          error = 1;
        }
      }
    } else if (argv[i][0] == '-') {
      for (int j = 1; argv[i][j] != '\0'; j++) {
        if (checkForOccurrence(argv[i][j], valid_flags)) {
          flags[*len_flags] = argv[i][j];
          *len_flags += 1;
        } else {
          error = 1;
        }
      }
    } else if (*len_templates > 0 &&
               !getMatchingFiles(argv[i], len_files, files)) {
    } else if (*len_templates == 0) {
      strcpy(templates[*len_templates], argv[i]);
      *len_templates += 1;
    } else {
      printf("n/a\n");
    }
  }
  if (*len_templates == 0 || *len_files == 0) {
    error = 1;
  }
  return error;
}

int keyF(char* str, char templates[MAX_TEMPLATES][MAX_TEMPLATES],
         int* len_templates) {
  FILE* file = fopen(str, "r");
  if (file == NULL) {
    return 1;
  }
  int gg = 0, i = 0;
  char ch = ' ';
  char num[MAX_TEMPLATES];
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n' || ch == '\t' || ch == '\0' || ch == ' ') {
      if (gg == 1) {
        num[i] = '\0';
        i = 0;
        strcpy(templates[*len_templates], num);
        (*len_templates)++;
      }
      gg = 0;
    } else {
      num[i] = ch;
      i++;
      gg = 1;
    }
  }

  fclose(file);
  return 0;
}

int getMatchingFiles(const char* regexPattern, int* len_files,
                     char files[MAX_FILES][MAX_FILES]) {
  DIR* dir;
  struct dirent* entry;
  regex_t regex;

  if (!inRegex(regexPattern)) {
    if (directoryExists(regexPattern)) {
      listFiles(regexPattern, regexPattern, files, len_files);
    } else {
      strcpy(files[*len_files], regexPattern);
      *len_files += 1;
    }
    return 0;
  }

  // Компилируем регулярное выражение
  if (regcomp(&regex, regexPattern, REG_EXTENDED) != 0) {
    perror("n/a");
    return 1;
  }

  // Открываем текущую директорию
  dir = opendir(".");
  if (dir == NULL) {
    perror("n/a");
    return 1;
  }

  // Читаем файлы в текущей директории и проверяем их на соответствие
  // регулярному выражению
  while ((entry = readdir(dir)) != NULL) {
    if (regexec(&regex, entry->d_name, 0, NULL, 0) == 0) {
      strcpy(files[*len_files], entry->d_name);
      if (directoryExists(files[*len_files])) {
        listFiles(files[*len_files], files[*len_files], files, len_files);
      } else {
        *len_files += 1;
      }
    }
  }

  // Закрываем директорию
  closedir(dir);

  // Освобождаем регулярное выражение
  regfree(&regex);

  return 0;
}

int inRegex(const char* world) {
  regex_t regex;
  int res = 1;

  if (regcomp(&regex, world, REG_NOSUB | REG_EXTENDED)) {
    regfree(&regex);
    return 1;
  }

  res = regexec(&regex, world, 0, NULL, 0);

  regfree(&regex);

  return res != 0;
}

int checkRegex(char* str_1, char* str_2, int printf_file, int* print) {
  int res = 1;
  regex_t regex;
  if (regcomp(&regex, str_2, 0)) {
    perror("n/a");
    return 1;
  }
  if (regexec(&regex, str_1, 0, NULL, 0) == 0) {
    res = 0;
  }

  regfree(&regex);

  if (!res && printf_file) {
    *print = 1;
  }

  return res;
}

int directoryExists(const char* name) {
  int res = 0;
  struct stat st;
  if (stat(name, &st) == 0 && S_ISDIR(st.st_mode)) {
    res = 1;
  }
  return res;
}

int fileExists(const char* name) {
  int res = 0;
  FILE* file = fopen(name, "r");
  if (file != NULL) {
    fclose(file);
    res = 1;
  }
  return res;
}

int checkForOccurrence(char const num, char* const str) {
  int res = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (num == str[i]) {
      res = 1;
    }
  }
  return res;
}

void printForKonsol(grep_struct* GREP, int len_GREP, int h, int* len_files,
                    int dir, int print_n, int s) {
  for (int i = 0; i < len_GREP; i++) {
    if ((GREP + i)->print_file == 2) {
      if (s) {
        printf("n/a\n");
      }
      continue;
    }
    if (!h && (GREP + i)->print_file == 1 && (*len_files > 1 || dir == 1)) {
      printf("%s:", (GREP + i)->file);
    }
    if ((GREP + i)->print_line == 1) {
      if (print_n) {
        printf("%d:", (GREP + i)->n);
      }
      printf("%s", (GREP + i)->line);
    }
  }
}

void keyC(grep_struct* GREP, int len_GREP, int* len_files, int dir, int h,
          int s) {
  char str[MAX_LINE_LENGTH] = {'o'};
  int res_c = 0;
  for (int i = 0; i < len_GREP; i++) {
    if ((GREP + i)->print_line == 1) {
      res_c++;
    }
    if ((GREP + i)->print_file != 2) {
      if (strcmp(str, (GREP + i)->file) &&
          ((*len_files > 1 || dir == 1) && !h)) {
        printf("%s:", (GREP + i)->file);
      } else if (i + 1 == len_GREP ||
                 strcmp((GREP + i)->file, (GREP + (i + 1))->file)) {
        printf("%d\n", res_c);
        res_c = 0;
      }
      strcpy(str, (GREP + i)->file);
    } else if (s) {
      printf("n/a\n");
    }
  }
}

void keyL(int len_GREP, grep_struct* GREP, int s) {
  char line[MAX_LINE_LENGTH] = {'o'};
  for (int i = 0; i < len_GREP; i++) {
    if ((GREP + i)->print_line == 1) {
      if (strcmp(line, (GREP + i)->file)) {
        printf("%s\n", (GREP + i)->file);
      }
      strcpy(line, (GREP + i)->file);
    } else if (s && (GREP + i)->print_line == 2) {
      printf("n/a\n");
    }
  }
}

void repackForKeys(char* flags, int* c, int* v, int* l, int* print_n, int* s,
                   int* o, int* h) {
  if (checkForOccurrence('c', flags)) {
    *c = 1;
  }
  if (checkForOccurrence('v', flags)) {
    *v = 1;
  }
  if (checkForOccurrence('l', flags)) {
    *l = 1;
  }
  if (checkForOccurrence('n', flags)) {
    *print_n = 1;
  }
  if (checkForOccurrence('s', flags)) {
    *s = 0;
  }
  if (checkForOccurrence('o', flags)) {
    *o = 1;
  }
  if (checkForOccurrence('h', flags)) {
    *h = 1;
  }
}

void keyNotOrO(grep_struct* GREP, int* len_GREP,
               char files[MAX_FILES][MAX_FILES], int len_files,
               char templates[MAX_TEMPLATES][MAX_TEMPLATES],
               const int len_templates, int* printf_file, char* flags, int o,
               const int s) {
  char line[MAX_LINE_LENGTH];
  char str_1[MAX_LINE_LENGTH];
  char str_2[MAX_LINE_LENGTH];
  for (int f = 0; f < len_files; f++) {
    if (len_files > 1) {
      *printf_file = 1;
    }
    int n = 1;
    FILE* file = fopen(files[f], "r");
    if (file == NULL) {
      if (s) {
        (GREP + (*len_GREP))->print_file = 2;
        (GREP + (*len_GREP))->print_line = 2;
        (*len_GREP)++;
      }
      continue;
    }
    printGrep(GREP, len_GREP, line, file, files, f, len_templates, str_1, str_2,
              templates, flags, printf_file, &n, o);
    fclose(file);
  }
}

void printGrep(grep_struct* GREP, int* len_GREP, char* line, FILE* file,
               char files[MAX_FILES][MAX_FILES], int f, int len_templates,
               char* str_1, char* str_2,
               char templates[MAX_TEMPLATES][MAX_TEMPLATES], char* flags,
               int* printf_file, int* n, int o) {
  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    (GREP + (*len_GREP))->print_file = 0;
    (GREP + (*len_GREP))->print_line = 0;
    strcpy((GREP + (*len_GREP))->line, line);
    strcpy((GREP + (*len_GREP))->file, files[f]);
    for (int t = 0; t < len_templates; t++) {
      strcpy(str_1, line);
      strcpy(str_2, templates[t]);
      if (checkForOccurrence('i', flags)) {
        toLower(str_1);
        toLower(str_2);
      }
      if (checkRegex(str_1, str_2, *printf_file,
                     &((GREP + (*len_GREP))->print_file)) == 0) {
        (GREP + (*len_GREP))->print_line = 1;
      }
      if (o) {
        char* match = strstr(str_1, str_2);
        while (match != NULL) {
          snprintf((GREP + (*len_GREP))->line, MAX_LINE_LENGTH, "%.*s\n",
                   (int)strlen(templates[t]), match);
          if (checkRegex(str_1, str_2, *printf_file,
                         &((GREP + (*len_GREP))->print_file)) == 0) {
            (GREP + (*len_GREP))->print_line = 1;
            strcpy((GREP + (*len_GREP))->file, files[f]);
            (GREP + (*len_GREP))->n = *n;
          }
          match = strstr(match + 1, str_2);
          (*len_GREP)++;
          (GREP + (*len_GREP))->print_file = 0;
          (GREP + (*len_GREP))->print_line = 0;
        }
      }
    }
    (GREP + (*len_GREP))->n = *n;
    (*n)++;
    (*len_GREP)++;
  }
}

void keyV(grep_struct* GREP, int len_GREP) {
  for (int i = 0; i < len_GREP; i++) {
    if ((GREP + i)->print_file == 2 || (GREP + i)->print_line == 2) {
      continue;
    }
    (GREP + i)->print_file = (GREP + i)->print_file != 1;
    (GREP + i)->print_line = (GREP + i)->print_line != 1;
  }
}
