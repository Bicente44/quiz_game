#include "qg_utils.h"
#include "qg_work.h"

const int n_menu_options = 4;

int main() {
  srand(time(NULL));

  init_db();
  if (is_db_empty()) {
    printf("Database is empty?? Populating from questions.txt\n");
    populate_db();
  }

  bool loop = true;
  int option = -1;
  // TODO Ask for login, or play as guest and optionally sign in later
  while (loop) {
    printf("Menu options:\n1. Start quiz\n2. Login/Logout\n3. Help\n4. "
           "Exit\n> ");
    // IF logged in: printf("Playing as %s", user.name);
    if ((option = option_input(n_menu_options)) <= 0)
      continue;

    switch (option) {
      /* Start Game */
    case 1:
      game_start();
      break;
      /* Login/Logout */
    case 2:
      // TODO call login page
      // TODO if logged in, logout
      break;
      /* Help */
    case 3:
      print_help();
      break;
      /* Exit */
    case 4:
      printf("Exiting the program...\n");
      game_clean();
      loop = false;
      break;
    default:
      break;
    }
  }

  return 0;
}
