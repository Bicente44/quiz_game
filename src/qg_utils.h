#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_NAME "quiz_game.db"

int option_input(int n);

int get_n_questions(int difficulty);

int init_db();

int is_db_empty();

int populate_db();

void shuffle_questions();

int game_clean();
