#include "qg_work.h"

int difficulty = -1; /* 0, 1, 2 (-1 means error) */

void game_start() {
  // TODO:
  // Prompt difficulty option

  // Create questions list (struct?)
  create_questions();
  // Ask user for input answer
  // Check if correct or incorrect
  // Correct continue, else take a life and and continue if GT 0
}

void create_questions() {
  // Parse the ../data/questions.txt
  // Populate and validate a Question struct array
  //
}

void shuffle_questions() {}
