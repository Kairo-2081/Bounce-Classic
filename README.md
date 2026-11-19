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
