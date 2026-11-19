# Bounce Classic

A side-scrolling platform game written in C++. You guide a bouncing ball through three levels of blocks, spikes and patrolling spiders, collect a score as you go, and compete for a place on the leaderboard. It is built on the iGraphics library (OpenGL, GLUT and SDL2), and the game window is titled "Bounce Classico".

## Gameplay

- The ball rolls across a scrolling level. Move right to progress; jump to get onto or under blocks.
- Each of the three levels has its own layout of upper and lower blocks, spikes and spiders.
- You start every level with 100 health. Touching a spike or a spider costs 10 health per tick, and the game ends when health reaches 0.
- Moving right adds to your score and moving left takes points away.
- Reaching the end of a level moves you to the next one with health refilled. Your score carries over.
- Finish level 3 to see the "Congratulations" screen with your final score.
- After a game over or a finish, you type a name and your score goes to the leaderboard.

## Controls

| Input | Action |
| --- | --- |
| Left / Right arrow | Move left / right |
| Up arrow | Jump |
| Mouse | Click the main menu buttons; click the speaker icon during play to switch sound on or off |
| Home | Return to the main menu |
| End | Save your progress to `saved.txt` and quit |
| C | Continue from the score screen, or leave the leaderboard and game-over screens |
| Letters, space, Backspace, Enter | Type, edit and submit your name |

## Menus, saving and the leaderboard

The main menu has buttons for starting a new game, loading a saved game, the leaderboard and help, plus an exit button.

- **Save and load**: pressing End writes `level x y health score` to `saved.txt`. Load Game reads that file and resumes from it.
- **Leaderboard**: `leaderboard.txt` holds one `Name score` line per player, best first. A player keeps only their best score, and the leaderboard screen shows the top five.
- **Names**: the name prompt asks for a surname. Use a single word, because the leaderboard reads each line as one name followed by one score.

## Build and run

Run all commands from the repository root. The game loads its images, fonts and sounds by relative path (`assets/...`).

### Linux

Install the SDL2, SDL2_mixer, FreeGLUT, FreeType and OpenGL development packages. On Debian or Ubuntu that is roughly:

```bash
sudo apt install build-essential libsdl2-dev libsdl2-mixer-dev freeglut3-dev libfreetype-dev libglu1-mesa-dev
```

Then build and run:

```bash
chmod +x build.sh runner.sh
./runner.sh          # builds iMain.cpp into bin/opengl and starts it
./build.sh           # build only
```

Both scripts take an optional source file as an argument and default to `iMain.cpp`.

### Windows

`build.bat` and `runner.bat` call a MinGW compiler from a folder named `MINGW` next to them. That folder is git-ignored, so it is not in this repository: add a MinGW toolchain there first. The SDL2, FreeGLUT and FreeType DLLs the game needs are already in `bin/`. An `iGraphics.cbp` Code::Blocks project is also included.
