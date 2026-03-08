
#define Q_STRING_LENGTH 50
#define A_STRING_LENGTH 20
/* N of questions asked for each difficulty */
#define N_EASY_QUESTIONS 5
#define N_MED_QUESTIONS 10
#define N_HARD_QUESTIONS 20
/* How many questions the list can hold, uses only the difficulty amount */
#define QUESTION_LIST_MAX 30

typedef enum { false, true } bool;

typedef struct {
  char name[25];
  int id;
  int wins;
  int losses; /* idk if we keep this tbh */
  int lives;
} User;

typedef struct {
  int q_difficulty;
  char question[Q_STRING_LENGTH];
  char correct_a[A_STRING_LENGTH];
  char incorrect_a[3][A_STRING_LENGTH]; /* Array of 3 strings */
} Question;

void game_start();

Question *create_questions(Question *question_list);

void play_loop(Question *question_list);
