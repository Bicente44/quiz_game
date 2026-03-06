#include "qg_work.h"

int option_input() {
  char str_option[3];
  int int_option = -1;
  printf("Please enter a valid integer between 1 - 4:\n>");
  if (fgets(str_option, sizeof(str_option), stdin) != NULL) {
    if ((int_option = atoi(str_option)) >= 1 && int_option <= 4) {
      return int_option;
    } else {
      printf("Number is not witin 1-4 try again\n");
      return -1;
    }
  } else {
    printf("input read failure, NULL error\n");
    return -1;
  }
}

int main() {
  bool loop = true;
  int option = -1;

  while (loop) {
    if ((option = option_input()) <= 0)
      continue;

    switch (option) {
      /* Start Game */
    case 1:
      break;
      /* Edit questions */
    case 2:
      /* check if not admin, if true then print cant do that and continue */
      break;
      /* Help */
    case 3:
      break;
      /* Exit */
    case 4:
      printf("Exiting the program...");
      loop = false;
      break;
    default:
      break;
    }
  }

  return 0;
}
