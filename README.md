<div align="center">

<img src="./.github/assets/readme/bounce-logo.svg" alt="Bounce Classic logo" width="88" />

# Bounce Classic

**Keep the ball bouncing.**

A side-scrolling platform game in C++. Roll and jump a ball through three
levels of blocks, spikes and spiders, then put your name on the leaderboard.

![C++](https://img.shields.io/badge/C%2B%2B-iGraphics-00599c?logo=cplusplus&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-GLUT%20%2B%20SDL2-5586a4?logo=opengl&logoColor=white)
![Levels](https://img.shields.io/badge/levels-3-555555)
![Platforms](https://img.shields.io/badge/Linux%20%7C%20Windows-supported-blue)

[Screens](#screens) ·
[Levels](#levels) ·
[Flows](#flows) ·
[Controls](#controls) ·
[Build and run](#build-and-run)

<img src="./.github/assets/readme/bounce-home.jpg" alt="Bounce Classic main menu with New Game, Load Game, Leaderboard, Help and Exit buttons" width="800" />

</div>

Bounce Classic is a one-file game, `iMain.cpp`, built on the iGraphics
library. You steer a ball to the right across a scrolling level, jumping onto
and under blocks and dodging spikes and spiders. Health starts at 100 for each
level, the score follows your progress, and the best scores are kept in a
leaderboard file. The game window is titled "Bounce Classico".

## At a glance

| | |
| --- | --- |
| **What it is** | A 2D side-scrolling platformer in C++ on iGraphics (OpenGL, GLUT, SDL2) |
| **Levels** | 3, each with its own blocks, spikes and spiders |
| **Health** | 100 at the start of every level; spikes and spiders cost 10 per tick |
| **Score** | Moving right adds points, moving left takes them away, and it carries across levels |
| **Persistence** | `saved.txt` for one saved game, `leaderboard.txt` for the top scores |
| **Window** | Fixed 1280 x 720 |
| **Platforms** | Linux (`runner.sh`) and Windows (`runner.bat`, MinGW) |

## Contents

- [At a glance](#at-a-glance)
- [Screens](#screens)
- [Levels](#levels)
- [Gameplay](#gameplay)
- [Flows](#flows)
- [Controls](#controls)
- [Menus, saving and the leaderboard](#menus-saving-and-the-leaderboard)
- [Build and run](#build-and-run)
- [Built with](#built-with)
- [Project layout](#project-layout)
- [Notes](#notes)
- [Status](#status)
- [Credits](#credits)

## Screens

These are the game's own menu screens, taken from `assets/images/bg/`. They are
the artwork the game draws, not captures of live play: gameplay needs a display with
OpenGL, which was not available when this README was written.

<table>
<tr>
<td width="50%" valign="top">
<img src="./.github/assets/readme/bounce-help.jpg" alt="Help screen listing the controls and the goal of the game" width="100%" />
<p><b>Help.</b> The in-game guide to the controls and the goal.</p>
</td>
<td width="50%" valign="top">
<img src="./.github/assets/readme/bounce-leaderboard.jpg" alt="Leaderboard screen with the top scores" width="100%" />
<p><b>Leaderboard.</b> Names and scores, best first. Only the top five are shown.</p>
</td>
</tr>
<tr>
<td width="50%" valign="top">
<img src="./.github/assets/readme/bounce-name-entry.jpg" alt="Name entry background shown after a game over or a finish" width="100%" />
<p><b>Name entry.</b> The backdrop for typing your name after a game over or a finished run.</p>
</td>
<td width="50%" valign="top">
<img src="./.github/assets/readme/bounce-home.jpg" alt="Main menu" width="100%" />
<p><b>Main menu.</b> New Game, Load Game, Leaderboard, Help and Exit, clicked with the mouse.</p>
</td>
</tr>
</table>

## Levels

Each level is one long horizontal map, 10,000 to 13,000 pixels wide, that scrolls past a
1280-pixel window. The strips below are the level maps from `assets/images/levels/`, scaled
down to fit. Upper and lower blocks, spikes and spiders are placed from coordinate tables in `iMain.cpp`.

**Level 1**

<img src="./.github/assets/readme/bounce-level-1.jpg" alt="Level 1 map: a long strip of blocks above and below the path" width="100%" />

**Level 2**

<img src="./.github/assets/readme/bounce-level-2.jpg" alt="Level 2 map: a long strip with a different block layout" width="100%" />

**Level 3**

<img src="./.github/assets/readme/bounce-level-3.jpg" alt="Level 3 map: the longest and tallest strip" width="100%" />

## Gameplay

- The ball rolls across a scrolling level. Move right to progress; jump to get onto or under blocks.
- Each of the three levels has its own layout of upper and lower blocks, spikes and spiders.
- You start every level with 100 health. Touching a spike or a spider costs 10 health per tick, and the game ends when health reaches 0.
- Moving right adds to your score and moving left takes points away.
- Reaching the end of a level moves you to the next one with health refilled. Your score carries over.
- Finish level 3 to see the "Congratulations" screen with your final score.
- After a game over or a finish, you type a name and your score goes to the leaderboard.

## Flows

### Screens

Every screen is one value of the `pressed` variable, and `iDraw()` draws whichever
one is active.

```mermaid
stateDiagram-v2
    [*] --> Loading
    Loading --> Home: timer fires
    Home --> Playing: New Game
    Home --> Playing: Load Game, reads saved.txt
    Home --> Leaderboard
    Home --> Help
    Leaderboard --> Home: C
    Help --> Home: Home key
    Playing --> Home: Home key
    Playing --> NameEntry: health 0, or level 3 finished
    NameEntry --> Home: Enter, saves the score
    Playing --> [*]: End key, saves and quits
```

### Level progression

```mermaid
flowchart LR
    S([New game]) --> L1[Level 1<br/>health 100]
    L1 -- reach the end --> L2[Level 2<br/>health refilled]
    L2 -- reach the end --> L3[Level 3<br/>health refilled]
    L3 -- reach the end --> W[Congratulations<br/>final score]
    W -- C --> N[Enter your name]
    L1 -- health 0 --> N
    L2 -- health 0 --> N
    L3 -- health 0 --> N
    N -- Enter --> LB[(leaderboard.txt)]
    LB --> H([Main menu])
```

### One frame of play

```mermaid
flowchart TD
    A[iDraw] --> B[Draw level background and blocks]
    B --> C[Draw spikes and spiders]
    C --> D{Touching a spike<br/>or a spider?}
    D -- yes --> E[health -= 10]
    D -- no --> F[Apply gravity and jump]
    E --> G{health == 0?}
    G -- yes --> H[Go to name entry]
    G -- no --> F
    F --> I{Past the level end?}
    I -- yes --> J[Next level, or finish]
    I -- no --> K[Next frame]
```

### Saving and the leaderboard

```mermaid
sequenceDiagram
    participant P as Player
    participant G as iMain.cpp
    participant S as saved.txt
    participant L as leaderboard.txt
    P->>G: End key
    G->>S: write level x y health score
    P->>G: Load Game
    G->>S: read level x y health score
    S-->>G: restore the run
    P->>G: Enter after typing a name
    G->>L: update best score, keep sorted
    P->>G: Leaderboard
    L-->>G: read the top five
```

## Controls

| Input | Action |
| --- | --- |
| Left / Right arrow | Move left / right |
| Up arrow | Jump (only while on the ground) |
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

## Built with

- **C++** for the whole game, in a single `iMain.cpp`
- **iGraphics** (OpenGL, GLUT) for drawing and input
- **SDL2 and SDL2_mixer** for sound
- **FreeType** for the fonts

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

## Status

Finished as a university project. The three levels, saving, the leaderboard and the menus all work from the code as written, and the known quirks are listed under Notes.

## Credits

The graphics, input and sound layer is the iGraphics library (v0.6.0 in `iGraphics.h`) by Mahir Labib Dihan, see [github.com/mahirlabibdihan](https://github.com/mahirlabibdihan). Check the upstream project for the library's terms; this repository has no license file of its own.
