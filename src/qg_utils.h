#ifndef QG_WORK_H
#define QG_WORK_H

#include "qg_work.h"
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DB_NAME "quiz_game.db"

extern sqlite3 *db;

int option_input(int n);

int get_n_questions(int difficulty);

int init_db();

int is_db_empty();

int populate_db();

Question *shuffle_questions(Question *question_list, int n_questions);

int game_clean();

void print_help();

#endif
