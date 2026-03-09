#include "qg_work.h"
#include "qg_utils.h"

int difficulty = -1; /* 1, 2, 3  */
Question *question_list;

void game_start() {
  printf("Difficulty options:\n1. Easy\n2. Medium\n3. Hard\n> ");
  while ((difficulty = option_input(3)) == -1)
    ;
  question_list = create_questions(question_list);
  if (!question_list) {
    printf("Failed to load questions, aborting...\n");
    return;
  }
  shuffle_questions(question_list, difficulty);
  play_loop(question_list);
}

Question *create_questions(Question *question_list) {
  int n_questions = 0;
  n_questions = get_n_questions(difficulty);
  if (question_list != NULL) {
    free(question_list);
    question_list = NULL;
  }
  question_list = malloc(sizeof(Question) * QUESTION_LIST_MAX);
  if (!question_list)
    return NULL;
  sqlite3_stmt *stmt;
  int i = 0;

  const char *sql = "SELECT * FROM QUESTIONS WHERE Q_DIFFICULTY = ? ORDER BY "
                    "RANDOM() LIMIT ?;";
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
    free(question_list);
    return NULL;
  }
  sqlite3_bind_int(stmt, 1, difficulty);
  sqlite3_bind_int(stmt, 2, get_n_questions(difficulty));

  while (sqlite3_step(stmt) == SQLITE_ROW && i < n_questions) {
    strncpy(question_list[i].question, (char *)sqlite3_column_text(stmt, 1),
            Q_STRING_LENGTH - 1);
    question_list[i].question[Q_STRING_LENGTH - 1] = '\0';

    question_list[i].q_difficulty = sqlite3_column_int(stmt, 2);

    strncpy(question_list[i].correct_a, (char *)sqlite3_column_text(stmt, 3),
            A_STRING_LENGTH - 1);
    question_list[i].correct_a[A_STRING_LENGTH - 1] = '\0';

    for (int j = 0; j < 3; j++) {
      const char *inc = (const char *)sqlite3_column_text(stmt, 4 + j);
      if (inc) {
        strncpy(question_list[i].incorrect_a[j], inc, A_STRING_LENGTH - 1);
        question_list[i].incorrect_a[j][A_STRING_LENGTH - 1] = '\0';
      }
    }
    i++;
  }
  sqlite3_finalize(stmt);
  return question_list;
}

void play_loop(Question *question_list) {
  int n_questions;
  char display_options[4][A_STRING_LENGTH];
  int answer = 0;
  int correct = 0;
  int incorrect = 0;

  n_questions = get_n_questions(difficulty);

  for (int i = 0; i < n_questions; i++) {
    printf("Question %d / %d\n", i + 1, n_questions);
    if ((n_questions - i) < 1) {
      printf("Here is the final Question!\n");
    } else {
      printf("Next question is:\n");
    }

    strcpy(display_options[0], question_list[i].correct_a);
    for (int j = 1; j < 4; j++) {
      strcpy(display_options[j], question_list[i].incorrect_a[j - 1]);
    }
    for (int j = 3; j > 0; j--) {
      int k = rand() % (j + 1);

      char temp[A_STRING_LENGTH];
      strcpy(temp, display_options[j]);
      strcpy(display_options[j], display_options[k]);
      strcpy(display_options[k], temp);
    }

    printf("%s\n", question_list[i].question);
    for (int j = 0; j < 4; j++) {
      printf("(%d): %s\n", 1 + j, display_options[j]);
    }

    bool loop = true;
    printf("Enter a valid awnser between 1 - 4:\n> ");
    while (loop) {
      if ((answer = option_input(4)) <= 0) {
        continue;
      } else {
        loop = false;
      }
    }

    if (strcmp(display_options[answer - 1], question_list[i].correct_a) != 0) {
      printf("Thats incorrect!\n");
      printf("The correct answer is: '%s'\n", question_list[i].correct_a);
      incorrect++;
    } else {
      printf("Thats correct!\n");
      correct++;
    }
  }
  printf("You finished the game!\nYou got %d correct and %d incorrect\n",
         correct, incorrect);
  // TODO: once reached here it should mean win, (has enough lives at the
  // end)
}
