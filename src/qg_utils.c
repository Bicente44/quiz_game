#include "qg_utils.h"
#include "qg_work.h"
#include "sqlite3.h"

sqlite3 *db;

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

int init_db() {
  char *err_msg = 0;
  int return_code;

  return_code = sqlite3_open(DB_NAME, &db);

  if (return_code != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  } else {
    fprintf(stderr, "Database opened successfully\n");
  }

  const char *sql = "CREATE TABLE IF NOT EXISTS USERS("
                    "ID INTEGER PRIMARY KEY NOT NULL AUTOINCREMENT,"
                    "NAME CHAR(25) NOT NULL,"
                    "WINS INT NOT NULL,"
                    "LOSSES INT NOT NULL);"

                    "CREATE TABLE IF NOT EXISTS QUESTIONS("
                    "Q_ID INTEGER PRIMARY KEY NOT NULL AUTOINCREMENT,"
                    "QUESTION CHAR(50) NOT NULL,"
                    "Q_DIFFICULTY INT,"
                    "CORRECT_A CHAR(20) NOT NULL,"
                    "INCORRECT_A1 CHAR(20) NOT NULL,"
                    "INCORRECT_A2 CHAR(20) NOT NULL,"
                    "INCORRECT_A3 CHAR(20) NOT NULL );";

  return_code = sqlite3_exec(db, sql, 0, 0, &err_msg);
  if (return_code != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return return_code;
  }
  fprintf(stdout, "Table created successfully\n");

  return 0;
}

int game_clean() {

  free(question_list);
  sqlite3_close(db);

  return 0;
}

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
