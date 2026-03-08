#include "qg_utils.h"

int option_input(int n) { // 'n' is number of questions
  char str_option[3];
  int int_option = -1;
  printf("Please enter a valid integer between 1 - %d:\n>", n);
  if (fgets(str_option, sizeof(str_option), stdin) != NULL) {
    if ((int_option = atoi(str_option)) >= 1 && int_option <= n) {
      return int_option;
    } else {
      printf("Number is not witin 1-%d try again\n", n);
      return -1;
    }
  } else {
    printf("input read failure, NULL error\n");
    return -1;
  }
}
