#include "qg_utils.h"
#include "qg_work.h"

const int n_menu_options = 5;

int main() {

  init_db();
  if (is_db_empty()) {
    printf("Database is empty?? Populating from questions.txt\n");
    populate_db();
  }

  bool loop = true;
  int option = -1;
  // TODO Ask for login, or play as guest and optionally sign in later
  while (loop) {
    printf(
        "Menu options:\n1. Start quiz\n2. ???\n3. ???\n4. Help\n5. Exit\n> ");
    if ((option = option_input(n_menu_options)) <= 0)
      continue;

    switch (option) {
      /* Start Game */
    case 1:
      game_start();
      break;
      /* Add a question (no data persistance) */
    case 2:
      break;
      /* Edit questions */
    case 3:
      /* check if not admin, if true then print cant do that and continue */
      break;
      /* Help */
    case 4:
      break;
      /* Exit */
    case 5:
      printf("Exiting the program...\n");
      // game_clean();
      loop = false;
      break;
    default:
      break;
    }
  }

  return 0;
}
