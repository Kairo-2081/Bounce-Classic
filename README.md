# Bounce Classic

A side-scrolling platform game written in C++. You guide a bouncing ball through three levels of blocks, spikes and patrolling spiders, collect a score as you go, and compete for a place on the leaderboard. It is built on the iGraphics library (OpenGL, GLUT and SDL2), and the game window is titled "Bounce Classico".

## Contents

- [Gameplay](#gameplay)
- [Controls](#controls)
- [Menus, saving and the leaderboard](#menus-saving-and-the-leaderboard)
- [Build and run](#build-and-run)
- [Project layout](#project-layout)
- [Notes](#notes)
- [Credits](#credits)

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

## Project layout

```text
.
├── iMain.cpp            The game: setup, drawing, input, collisions, saving and the leaderboard
├── assets/              fonts/, images/ (bg, levels, sprites) and sounds/
├── leaderboard.txt      Top scores, one "Name score" per line
├── saved.txt            Saved game: level x y health score
├── iGraphics.h, iSound.h, iFont.h   iGraphics library headers
├── build.sh, runner.sh  Linux build and run scripts
├── build.bat, runner.bat, release.bat   Windows scripts
├── iGraphics.cbp        Code::Blocks project
├── bin/                 Windows runtime DLLs (and build output)
├── OpenGL/, include/, lib/, libexec/, mingw32/, share/, var/   Bundled headers, libraries and toolchain files from the iGraphics template
└── examples/, tests/    iGraphics demo programs and test scripts
```

Most of the roughly 2,300 tracked files belong to the bundled iGraphics template and toolchain. The game itself is `iMain.cpp` plus `assets/`.

## Notes

- Load Game opens `saved.txt` without checking that it exists, so keep that file in the project folder.
- Names are stored as a single word. A name with a space is not read back correctly from `leaderboard.txt`.
- The window is fixed at 1280 x 720.

## Credits

The graphics, input and sound layer is the iGraphics library (v0.6.0 in `iGraphics.h`) by Mahir Labib Dihan, see [github.com/mahirlabibdihan](https://github.com/mahirlabibdihan). Check the upstream project for the library's terms; this repository has no license file of its own.
