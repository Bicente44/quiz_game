#include "qg_utils.h"
#include "qg_work.h"

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

int get_n_questions(int difficulty) {
  int n_questions = 0;
  switch (difficulty) {
  case 1:
    n_questions = N_EASY_QUESTIONS;
    break;
  case 2:
    n_questions = N_MED_QUESTIONS;
    break;
  case 3:
    n_questions = N_HARD_QUESTIONS;
    break;
  }
  return n_questions;
}

void shuffle_questions() {}
int game_clean() { return 0; }

/* DEBUG ? */

void print_list_details(int n_questions, int difficulty,
                        Question *question_list) {

  printf("Difficulty: %d. Number of questions: %d\n", difficulty, n_questions);
  for (int i = 0; i < n_questions; i++) {
    printf("Question %d: %s\n", i + 1, question_list[i].question);
    printf("  Correct Answer: %s\n", question_list[i].correct_a);

    printf("  Incorrect Answers:\n");
    for (int j = 0; j < 3; j++) {
      printf("    %d. %s\n", j + 1, question_list[i].incorrect_a[j]);
    }
    printf("\n");
  }
}
