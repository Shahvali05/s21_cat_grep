#include "libs_cat.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("n/a");
    return 1;
  }

  int count = 1, id_key = 0;
  char key = 0, old_number = '\n';

  keyDefinition(argv, argc, &key, &id_key);

  for (int i = 1; i < argc; i++) {
    if (i == id_key) {
      continue;
    }
    keys(argv, i, &count, key, &old_number);
  }

  return 0;
}
