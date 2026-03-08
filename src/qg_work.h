
typedef enum { false, true } bool;

struct User {
  char name[25];
  int id;
  int wins;
  int losses; /* idk if we keep this tbh */
  int lives;
};

struct Question {
  char question[50];
  char correctA[20];
  char incorrectA[3][20]; /* Array of 3 strings */
};

void game_start();

void create_questions();

void shuffle_questions();

void add_questions();
