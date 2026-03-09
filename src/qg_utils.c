#include "qg_utils.h"

sqlite3 *db;

int option_input(int n) { // 'n' is number of questions
  char str_option[3];
  int int_option = -1;
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
                    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "NAME CHAR(25) NOT NULL,"
                    "WINS INT NOT NULL,"
                    "LOSSES INT NOT NULL);"

                    "CREATE TABLE IF NOT EXISTS QUESTIONS("
                    "Q_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "QUESTION CHAR(50) NOT NULL,"
                    "Q_DIFFICULTY INT,"
                    "CORRECT_A CHAR(20) NOT NULL,"
                    "INCORRECT_A1 CHAR(20) NOT NULL,"
                    "INCORRECT_A2 CHAR(20) NOT NULL,"
                    "INCORRECT_A3 CHAR(20) NOT NULL);";

  return_code = sqlite3_exec(db, sql, 0, 0, &err_msg);
  if (return_code != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return return_code;
  }
  return 0;
}

int is_db_empty() {
  sqlite3_stmt *result;
  int count = 0;
  const char *sql = "SELECT COUNT(*) FROM QUESTIONS;";

  if (sqlite3_prepare_v2(db, sql, -1, &result, NULL) != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare: %s\n", sqlite3_errmsg(db));
    return -1;
  }
  if (sqlite3_step(result) == SQLITE_ROW) {
    count = sqlite3_column_int(result, 0);
  }
  sqlite3_finalize(result);

  return (count == 0);
}

int populate_db() {
  FILE *fptr;
  char buffer[1024];
  char *token;
  Question db_q;

  fptr = fopen("data/questions.txt", "r");
  if (fptr == NULL) {
    printf("Cant open data/questions.txt, aborting..\n");
    return -1;
  }
  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
    buffer[strcspn(buffer, "\r\n")] = 0;

    token = strtok(buffer, ",");
    if (token == NULL)
      continue;
    db_q.q_difficulty = atoi(token);

    token = strtok(NULL, ",");
    if (token != NULL) {
      strncpy(db_q.question, token + 1, Q_STRING_LENGTH - 1);
      db_q.question[Q_STRING_LENGTH - 1] = '\0';
    }

    token = strtok(NULL, ",");
    if (token != NULL) {
      strncpy(db_q.correct_a, token + 1, A_STRING_LENGTH - 1);
      db_q.correct_a[A_STRING_LENGTH - 1] = '\0';
    }

    for (int i = 0; i < 3; i++) {
      token = strtok(NULL, ",");
      if (token != NULL) {
        strncpy(db_q.incorrect_a[i], token + 1, A_STRING_LENGTH - 1);
        db_q.incorrect_a[i][A_STRING_LENGTH - 1] = '\0';
      }
    }
    char *sql = sqlite3_mprintf(
        "INSERT INTO QUESTIONS (Q_DIFFICULTY, QUESTION, "
        "CORRECT_A, INCORRECT_A1, INCORRECT_A2, INCORRECT_A3) "
        "VALUES (%d, %Q, %Q, %Q, %Q, %Q);",
        db_q.q_difficulty, db_q.question, db_q.correct_a, db_q.incorrect_a[0],
        db_q.incorrect_a[1], db_q.incorrect_a[2]);

    if (sqlite3_exec(db, sql, NULL, NULL, NULL) != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_free(sql);
  }

  fclose(fptr);
  return 0;
}

Question *shuffle_questions(Question *question_list, int difficulty) {
  Question *shuffled_questions;
  int n_questions = 0;
  // Implement the fih shuffle method
  n_questions = get_n_questions(difficulty);
  shuffled_questions = question_list;

  for (int j = n_questions - 1; j > 0; j--) {
    int k = rand() % (j + 1);

    Question temp;
    temp = shuffled_questions[j];
    shuffled_questions[j] = shuffled_questions[k];
    shuffled_questions[k] = temp;
  }

  return shuffled_questions;
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

void print_help() {
  //
  //
}
