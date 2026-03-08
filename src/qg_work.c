#include "qg_work.h"
#include "qg_utils.h"

int difficulty = -1; /* 1, 2, 3  */
Question *question_list;

void game_start() {
  while ((difficulty = option_input(3)) == -1)
    ;
  question_list = create_questions(question_list);

  play_loop(question_list);
}

Question *create_questions(Question *question_list) {
  int n_questions = 0;
  n_questions = get_n_questions(difficulty);
  question_list = malloc(sizeof(Question) * QUESTION_LIST_MAX);

  // TEMP hardcoded questions:
  question_list[0] = (Question){1,
                                "What is the capital of france?",
                                "Paris",
                                {"Berlin", "London", "Rome"}};

  question_list[1] = (Question){1,
                                "What is the largest planet ?",
                                "Jupiter",
                                {"Mars", "Venus", "Saturn"}};

  question_list[2] = (Question){1,
                                "Which ocean is the largest?",
                                "Pacific",
                                {"Atlantic", "Indian", "Arctic"}};

  question_list[3] = (Question){1,
                                "What is the chemical symbol for water?",
                                "H2O",
                                {"CO2", "O2", "NaCl"}};

  question_list[4] = (Question){
      1, "How many continents are there on Earth?", "7", {"5", "6", "8"}};

  question_list[5] =
      (Question){1,
                 "Who painted the Mona Lisa?",
                 "Leonardo da Vinci",
                 {"Vincent van Gogh", "Pablo Picasso", "Claude Monet"}};

  // TODO
  // - Parse the ../data/questions.txt OR database (SqlLite)
  // - For each question, populate and validate a Question struct array index
  // - Check if n_questions > sizeof(list), if so theres a problem. Right now
  //   its fine(testing)
  // - Shuffle list
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
    printf("Question %d / %d\n", i, n_questions);
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
    while (loop) {
      if ((answer = option_input(4)) <= 0) {
        continue;
      } else {
        loop = false;
      }
    }

    if (strcmp(display_options[answer - 1], question_list[i].correct_a) != 0) {
      printf("Thats incorrect!\n");
      incorrect++;
    } else {
      printf("Thats correct!\n");
      correct++;
    }
    printf("You finished the game!\nYou got %d correct and %d incorrect\n",
           correct, incorrect);
  }
  // TODO: once reached here it should mean win, (has enough lives at the
  // end)
}
