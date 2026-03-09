# quiz_game

- This is a simple quiz game made entirely in C.
- In the future I am considering to add a GUI for UX and for my own learning experience.

### TODO:
- [ ] Leaderboard ?
- [ ] GUI ??
- [ ] User login, handles wins, losses, lives (temp?), id and name. (no paswd verif)
- [ ] Add save stats to file & auto save after each win/loss.
- [ ] Finish Help screen

### How the game I envision to work:
On start you will be prompted to login (optional, may login later). Then you will be prompted the game options to
play, help, quit and such (Main loop). Then on game start you will be in the game play loop where you are prompted
questions until a specific n times. For each entire game won you get +1 win and if you fail then +1 loss. You will
have a set amount of lives per game (implement difficulty ?)
