# quiz_game

- This is a simple quiz game made entirely in C.
- In the future I am considering to add a GUI for UX and for my own learning experience.

### TODO:
- [ ] Make option menu (start, help, edit questions (if admin ?), quit)
- [ ] Make game play loop
- [ ] Make data files so questions are not hardcoded fully, and are customizeable
- [ ] Leaderboard ?
- [ ] GUI ??
- [ ] Add a DB(Local to the machine)?
- [ ] User login, handles wins, losses, lives (temp), id and name. (no paswd verif)
- [ ] Add save stats to file & auto save after each win/loss.
- [ ] Difficulty options on game start ?


### How the game I envision to work:
On start you will be prompted to login (optional, may login later). Then you will be prompted the game options to
play, help, quit and such (Main loop). Then on game start you will be in the game play loop where you are prompted
questions until a specific n times. For each entire game won you get +1 win and if you fail then +1 loss. You will
have a set amount of lives per game (implement difficulty ?)
