#ifndef LIBS_GREP_H
#define LIBS_GREP_H

#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 500
#define MAX_FILES 100
#define MAX_TEMPLATES 100

typedef struct grep_struct {
  char line[MAX_LINE_LENGTH];
  char file[MAX_LINE_LENGTH];
  int n;
  int print_line;
  int print_file;
} grep_struct;

// Функция делит аргументы мейна на флаги, файлы и шаблоны
int divisionOfArguments(int argc, char* argv[], char* flags, char* valid_flags,
                        char files[MAX_FILES][MAX_FILES],
                        char templates[MAX_TEMPLATES][MAX_TEMPLATES],
                        int* len_flags, int* len_files, int* len_templates);
// Проверяет входит ли символ в строку
int checkForOccurrence(char const num, char* const str);
// Проверяет существует ли директория
int directoryExists(const char* name);
// Проверяет существует ли файл
int fileExists(const char* name);
// Проверяет подходит ли регулярное выражение к слову
int checkRegex(char* str_1, char* str_2, int printf_file, int* print);
// Добавляет дириктории и файлы в массив массивов files
int getMatchingFiles(const char* regexPattern, int* len_files,
                     char files[MAX_FILES][MAX_FILES]);
// Проверяет есть ли в строке символы регулярных выражений
int inRegex(const char* world);
// Читает файл и все слова передает в список
int keyF(char* str, char templates[MAX_TEMPLATES][MAX_TEMPLATES],
         int* len_templates);
// Заменяет вверхние регистры на нижные
void toLower(char* str);
// Проходится по директориям и смотрит что в файлах
void listFiles(const char* baseDir, const char* dir,
               char files[MAX_FILES][MAX_FILES], int* len_files);
// флаг -v
void keyV(grep_struct* GREP, int len_GREP);
// функция проходится по файлам
void keyNotOrO(grep_struct* GREP, int* len_GREP,
               char files[MAX_FILES][MAX_FILES], int len_files,
               char templates[MAX_TEMPLATES][MAX_TEMPLATES],
               const int len_templates, int* printf_file, char* flags, int o,
               const int s);
// функция переписывает все что есть в файлах
void printGrep(grep_struct* GREP, int* len_GREP, char* line, FILE* file,
               char files[MAX_FILES][MAX_FILES], int f, int len_templates,
               char* str_1, char* str_2,
               char templates[MAX_TEMPLATES][MAX_TEMPLATES], char* flags,
               int* printf_file, int* n, int o);
// проверяет какие есть ключи
void repackForKeys(char* flags, int* c, int* v, int* l, int* print_n, int* s,
                   int* o, int* h);
// ключ l
void keyL(int len_GREP, grep_struct* GREP, int s);
// ключ c
void keyC(grep_struct* GREP, int len_GREP, int* len_files, int dir, int h,
          int s);
// выводит результат на экран
void printForKonsol(grep_struct* GREP, int len_GREP, int h, int* len_files,
                    int dir, int print_n, int s);

#endif
